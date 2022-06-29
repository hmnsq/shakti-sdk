/***************************************************************************
 * Project           			  :  shakti devt board
 * Name of the file	     		  :  ZigBee_Gateway.c
 * Created date			        :  31.03.2022
 * Brief Description of file    :  Zigbee Gateway acts as Zigbee Coordinator and handles communication with remote aws server
 * Name of Author               :  Kolan Nikshith Reddy
 * Email ID of Author           :  nkreddy100@gmail.com
 * Name of Mentor               :  E. Kotteeswaran
 * Email ID of Mentor           :  kottee.1@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/

/**
  * @file ZigBee_Gateway.c
  * @brief ZigBee Gateway acts as ZigBee Coordinator and uses A7600C1 4G LTE 
  * @details File to demonstrate porting of ZigBee protocol onto Shakti Processor and
  * transmission of data to a website.
  * XBEE PRO S2C sensor is used to port ZigBee protocol to Shakti , A7600C1 4G LTE module is  used to
  * send data to flask based AWS Remote server.
  * Prerequisite:

  * 1. XBEE PRO S2C is configured to baud rate 9600
  * 2. A7600C1 LTE is configured to baud rate 115200
  * 3. XBEE PRO S2C is configured with ZigBee Coordintaor firmware 
  * 4. A7600C1 is set initialised and signal strength is checked
  * 5. A7600C1 is configured to connect to send data remote flask web server hosted on AWS.
  * 6. A flask based web application to receive data is hosted AWS.
  * 7. Change the address of the remote web application in ZigBee_Gateway.c
  * 8. UART[0] is for logging purposes
  * 8. UART[1] is to communicate with XBEE PRO S2C
  * 9. UART[2] is to communicate with A7600C1 LTE Module
*/


#include <stdint.h>
#include <stddef.h>
#include "log.h"
#include "uart.h"  //Includes the definitions of uart communication protocol//
#include "pinmux.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h" //Includes the definitions of interrupt handling in Shakti//
#include <stdio.h>
#include <string.h>


#define FIXEDOFFSET 14 // Used in base address calculation of XBEE PRO S2C API Mode packets
#define MQ2 0          //Each sensor is given a number and used to refer the sensor
#define MQ7 1
#define LM75 2

//enum location, is used to frame the raw packet in API mode of XBEE PRO S2C Communication.
enum location{start,lenbyte1,lenbyte0,frametype, frameid,addrbase, addr16bit0=13, addr16bit1, broadcast, options, rfdatabase};


//Initialise all the receive and transmit counters of UART
unsigned int uart0_prev_rcv_isr_count_flag = 0;
unsigned int uart1_prev_rcv_isr_count_flag = 0;
unsigned int uart2_prev_rcv_isr_count_flag = 0;

unsigned int uart0_prev_tx_isr_count_flag = 0;
unsigned int uart1_prev_tx_isr_count_flag = 0;
unsigned int uart2_prev_tx_isr_count_flag = 0;


#define UART_INST uart_instance[2]

//Denote to use the interrupts
#define USE_INTERRUPT
#define MAX_OUTPUT_SIZE 1024

//Remote address of the Flask web server.
// /admin/data/1 receives the data of mq2
// /admin/data/2 receives the data of mq7
// /admin/data/3 receives the data of lm75

#define APIPOST "http://43.204.75.91/admin/data/1" 
#define TIME "1000"

/**
  * @fn void init_variables()
  * @brief initialise all the transmit-receive buffers and counters
*/
void init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_count = 0;
	uart0_rcv_isr_count = 0;
	uart1_tx_isr_count = 0;
	uart1_rcv_isr_count = 0;
	uart2_tx_isr_count = 0;
	uart2_rcv_isr_count = 0;
	memset(u0_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u2_rcv_char,'\0', UARTX_BUFFER_SIZE);
	uart0_prev_rcv_isr_count_flag = 0;
	uart1_prev_rcv_isr_count_flag = 0;
	uart2_prev_rcv_isr_count_flag = 0;

	uart0_prev_tx_isr_count_flag = 0;
	uart1_prev_tx_isr_count_flag = 0;
	uart2_prev_tx_isr_count_flag = 0;
}
extern volatile unsigned int* pinmux_config_reg;


/**
  * @fn void init_variables()
  * @brief flush the Uart Buffers before using them
*/
void free_uart_buffers()
{
	flush_uart( uart_instance[0] );
	flush_uart( uart_instance[1] );
	flush_uart( uart_instance[2] );

}

/**
  * @fn int str_length(char *str)
  * @brief calculates the length of the string
  * @param str string of which length is calculated
*/
int str_length(char *str)
{
    int len=0;
    while(*str!='\0')
    {
        len++;
        str++;
    }
    return len;
}

/**
  * @fn int int_to_str(int data, char * str)
  * @brief Converts the interger to string. Used by A7600C1 while sending data to remote server
  * @param data interger that will be converted to string
  * @param str converted integer is stored in str variable
*/
int int_to_str(int data, char * str)
{
   int i=0;
   while( data > 0 )
   {
      str[i]='0'+ (data%10);
      data/=10;
      i++;
   }
   str[i]='\0';
   int n=str_length(str)-1;
   int len=n+1;
   i=0;
   while(i<n)
   {
      char ch=str[i];
      str[i]=str[n];
      str[n]=ch;
      i++;
      n--;
   }
   return len;
}


/**
  * @fn int enterATMode(uart_struct * uart_instance)
  * @brief XBEE PRO S2C enters AT Mode before updating the firmware to coordinator
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
*/
int enterATMode(uart_struct * uart_instance)
{
   //+++ is sent with a delay before and after, to enter into AT Command mode.
   delay(20);
    write_uart_character(uart_instance,'+');
    write_uart_character(uart_instance,'+');
    write_uart_character(uart_instance,'+');
   delay(20);
   
   //the response of XBEE PRO S2C is stored in uart receive buffer
    u1_rcv_char[++uart1_rcv_isr_count] = '\0';

   //the response of XBEE PRO S2C is checked
    if(strstr(u1_rcv_char,"OK")==NULL)
    {
        log_info("Entered AT Command Mode");
        return 1;
    }
    else {
        log_info("Failed to enter AT Mode");
        return 0;
    }

    //clear the uart receive buffer
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);

}



/**
  * @fn int write_xbee_uart01(uart_struct * uart_instance, char *str, int length)
  * @brief Writes the AT Commands to XBEE PRO S2C to update the firmware
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
  * @param str AT Command is passed as string
  * @param length length of the AT Command
*/
int write_xbee_uart01(uart_struct * uart_instance, char *str, int length)
{
    delay(3);
    char *s1 = str;

   //  for(int i=0;i<length;i++){
   //      write_uart_character(uart_instance, *str);
   //      str++;
   //  }

   //length variable is not used to check the end of string
   while(*str!='\0')
    {
       write_uart_character(uart_instance,*str);
       str++;
    }
    //AT Command is send by carrige return
    write_uart_character(uart_instance,'\r');

    delay(2);
   
   //the response of XBEE PRO S2C is stored in uart receive buffer
    u1_rcv_char[++uart1_rcv_isr_count] = '\0';

   // The response of XBEE PRO S2C is checked
    if(strstr(u1_rcv_char,"ERROR")==NULL)
    {
        log_info("%s command failed", s1);
    }
    else {
        log_info("%s command success", s1);
    }
    //clear the uart receive buffers
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
}


/**
  * @fn void configure_xbee(uart_struct * uart_instance)
  * @brief Configures XBEE PRO S2C as ZigBee Coordintaor
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
*/
void configure_xbee(uart_struct * uart_instance){

   //Trying to enter AT Command Mode    
   int attempts_flag=0;
   printf("Enterting AT Command Mode");
   for(int i=0;i<5;i++){
       if(enterATMode(uart_instance)==1){
           attempts_flag=1;
           break;
       };
   } 
   if(attempts_flag==0){
       printf("Could not enter AT Mode. Exiting Now.");
        exit(-1);
   }

   // The main three commands of ZigBee Coordintaor configuration
   // 1.  Coordinator Enable
   // 2. Join Verification
   // 3. Destinator Low Address
   write_xbee_uart01(uart_instance, "ATCE1", 5);
   write_xbee_uart01(uart_instance, "ATJV0", 5);
   write_xbee_uart01(uart_instance, "ATDLFFFF", 8);

   //Networking commands
   write_xbee_uart01(uart_instance, "ATID1234", 5);
   write_xbee_uart01(uart_instance, "ATSC7FFF", 8);
   write_xbee_uart01(uart_instance, "ATSD3", 5);
   write_xbee_uart01(uart_instance, "ATZS0", 5);
   write_xbee_uart01(uart_instance, "ATNJFF",6);
   write_xbee_uart01(uart_instance, "ATNW0", 5);
   write_xbee_uart01(uart_instance, "ATJN1", 5);   
   write_xbee_uart01(uart_instance, "ATDO8", 5);
   write_xbee_uart01(uart_instance, "ATDC0", 5);

   //Addressing commands
   write_xbee_uart01(uart_instance, "ATDH0", 5);
   write_xbee_uart01(uart_instance, "ATNH1E", 6);
   write_xbee_uart01(uart_instance, "ATBH0", 5);
   write_xbee_uart01(uart_instance, "ATARFF", 6);
   write_xbee_uart01(uart_instance, "ATDDA0000", 9);
   write_xbee_uart01(uart_instance, "ATNT3C", 6);
   write_xbee_uart01(uart_instance, "ATNO0", 5);
   write_xbee_uart01(uart_instance, "ATCR3", 5);

   //Zigbee Addressing
   write_xbee_uart01(uart_instance, "ATSEE8", 6);
   write_xbee_uart01(uart_instance, "ATDEE8", 6);
   write_xbee_uart01(uart_instance, "ATCI11", 6);
   write_xbee_uart01(uart_instance, "ATTO0", 5);

   //RF Interfacing
   write_xbee_uart01(uart_instance, "ATPL4", 5);

   //Security
   write_xbee_uart01(uart_instance, "ATEE0", 5);
   write_xbee_uart01(uart_instance, "ATEO0", 5);
   write_xbee_uart01(uart_instance, "ATKY0", 5);
   write_xbee_uart01(uart_instance, "ATNK0", 5);
   
   
   //Serial Interfacing
   write_xbee_uart01(uart_instance, "ATBD3", 5);
   write_xbee_uart01(uart_instance, "ATNB0", 5);
   write_xbee_uart01(uart_instance, "ATSB0", 5);
   write_xbee_uart01(uart_instance, "ATRO3", 5);
   write_xbee_uart01(uart_instance, "ATD60", 5);
   write_xbee_uart01(uart_instance, "ATD71", 5);
   write_xbee_uart01(uart_instance, "ATAP1", 5);
   write_xbee_uart01(uart_instance, "ATAO0", 5);

   //AT Command Options
   write_xbee_uart01(uart_instance, "ATCT64", 6);
   write_xbee_uart01(uart_instance, "ATGT3E8",7);
   write_xbee_uart01(uart_instance, "ATCC2B", 6);
  
   //Sleep Modes
   write_xbee_uart01(uart_instance, "ATSP20",6 );
   write_xbee_uart01(uart_instance, "ATSN1", 5);
   write_xbee_uart01(uart_instance, "ATSM0", 5);
   write_xbee_uart01(uart_instance, "ATST1388", 8);
   write_xbee_uart01(uart_instance, "ATSO0", 5);
   write_xbee_uart01(uart_instance, "ATWH0", 5);
   write_xbee_uart01(uart_instance, "ATPO0", 5);

   //I/O Settings
   write_xbee_uart01(uart_instance, "ATD01", 5);
   write_xbee_uart01(uart_instance, "ATD10", 5);
   write_xbee_uart01(uart_instance, "ATD20", 5);
   write_xbee_uart01(uart_instance, "ATD30", 5);
   write_xbee_uart01(uart_instance, "ATD40", 5);
   write_xbee_uart01(uart_instance, "ATD51", 5);
   write_xbee_uart01(uart_instance, "ATD81", 5);
   write_xbee_uart01(uart_instance, "ATD91", 5);
   write_xbee_uart01(uart_instance, "ATP01", 5);
   write_xbee_uart01(uart_instance, "ATP10", 5);
   write_xbee_uart01(uart_instance, "ATP20", 5);
   write_xbee_uart01(uart_instance, "ATP31", 5);
   write_xbee_uart01(uart_instance, "ATP41", 5);
   write_xbee_uart01(uart_instance, "ATPR1FBF", 8);
   write_xbee_uart01(uart_instance, "ATPD1FFF", 8);
   write_xbee_uart01(uart_instance, "ATLT0",5 );
   write_xbee_uart01(uart_instance, "ATRP28",6 );

   //I/O Sampling
   write_xbee_uart01(uart_instance, "ATIR0", 5);
   write_xbee_uart01(uart_instance, "ATIC0", 5);
   write_xbee_uart01(uart_instance, "ATV+0", 5);
}

/**
  * @fn void flash_xbee_uart01(uart_struct * uart_instance)
  * @brief Finalises the flashing of XBEE PRO S2C as ZigBee Coordintaor
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
*/
void flash_xbee_uart01(uart_struct * uart_instance){
    //ATWR is used to finalise the configuration
    delay(3);
    write_uart_character(uart_instance,'A');
    write_uart_character(uart_instance,'T');
    write_uart_character(uart_instance,'W');
    write_uart_character(uart_instance,'R');
    write_uart_character(uart_instance,'\r');
    delay(2);


   //the response of XBEE PRO S2C is stored in uart receive buffer
    u1_rcv_char[++uart1_rcv_isr_count] = '\0';
    // the response is checked
    if(strstr(u1_rcv_char,"ERROR")==NULL)
    {
        log_info("Flashing failed. The above configuration stays until next reboot!\n");
    }
    else {
         log_info("Flashing success. The Xbee is configued as a Coordinator.\n PANID: 1234\n ");
    }
    //clear uart receive buffers
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
}

/**
  * @fn int write_cmd(uart_struct * uart_instance, char *str)
  * @brief Writes the AT Commands. Used by A7600C1 LTE sensor
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
  * @param str AT Command that need to be sent
*/
int write_cmd(uart_struct * uart_instance, char *str)
{
    while(*str!='\0')
    {
       write_uart_character(uart_instance,*str);
       str++;
    }
    write_uart_character(uart_instance,'\r');
}

/**
  * @fn int cmp_str(char *str1,char *str2)
  * @brief Used in string comparision
  * @param str1 holds string 1
  * @param str2 holds string 2
*/
int cmp_str(char *str1,char *str2)
{
   while(*str1!='\0' && *str2!='\0')
   {
      if(*str1==*str2)
      {
         str1++;
         str2++;
      }
      else
         //return failure if strings are not same
         return 0;
   }
   //return success if both are equal
   return 1;
}

/**
  * @fn int read_output(uart_struct * uart_instance, char *st)
  * @brief used to check the receive buffer of UART 2. Used by A7600C1 4G LTE Sensor.
  * @param st holds string to compare with response of sensor
*/
int read_output(uart_struct * uart_instance, char *st)
{
   delay(1);
   u2_rcv_char[++uart2_rcv_isr_count] = '\0';
   //compare response with string passed
   if(strstr(u2_rcv_char,st)==NULL)
   {
      //clear uart buffers and return failure
      uart2_rcv_isr_count = 0;
	   memset(u2_rcv_char,'\0', UARTX_BUFFER_SIZE);
      return 0;
   }
   //clear uart buffers and return success.
   uart2_rcv_isr_count = 0;
	memset(u2_rcv_char,'\0', UARTX_BUFFER_SIZE);
   return 1;
}

/**
  * @fn int int setup(uart_struct * uart_instance)
  * @brief used to setup A7600C1 LTE Module
*/
int setup(uart_struct * uart_instance)
{
   write_cmd(uart_instance,"AT+CGEREP=0");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nDisabled unsolicited result code");
   }
   else
   {
      log_info("\nAT+CGEREP command failed");
      return 0;
   }

   write_cmd(uart_instance,"AT");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nCommunication Verified");
   }
   else
   {
      log_info("\nAT command failed");
      return 0;
   }

   write_cmd(uart_instance,"AT+CPIN?");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nCPIN Success");
   }
   else
   {
      log_info("\nAT+CPIN? command failed");
      return 0;
   }

   write_cmd(uart_instance,"AT+CSQ");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nSignal strength:OK");
   }
   else
   {
      log_info("\nAT+CSQ command failed");
      return 0;
   }
   
   write_cmd(uart_instance,"AT+CREG?");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nReg to Circuit Switching Domain");
   }
   else
   {
      log_info("\nAT+CREG? command failed");
      return 0;
   }

   write_cmd(uart_instance,"AT+CGREG?");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nReg to Packet  Switching Domain");
   }
   else
   {
      log_info("\nAT+CGREG? command failed");
      return 0;
   }
   
   write_cmd(uart_instance,"AT+CPSI?");
   if(read_output(uart_instance,"OK"))
   {
      log_info("\nUE System Info : OK");
   }
   else
   {
      log_info("\nAT+CPSI? command failed");
      return 0;
   }
   return 1;
}

/**
  * @fn int recall_HTTP_service(uart_struct * uart_instance)
  * @brief used to restart HTTP service of A7600C1 if it failed.
*/
int recall_HTTP_service(uart_struct * uart_instance)
{
   int i=5;
   while(i--)
   {
      delay(20);
      //Terminating the sensor
      write_cmd(uart_instance,"AT+HTTPTERM");
      if(read_output(uart_instance,"OK"))
      {
         log_info("\nHTTP Service Terminated");
      }
      else
      {
         log_info("\nAT+HTTPTERM Failed");
         continue;
      }
      //initialising the sensor
      write_cmd(uart_instance,"AT+HTTPINIT");
      if(read_output(uart_instance,"OK"))
      {
         log_info("\nHTTP Service Started");
         return 1;
      }
      else
      {
         log_info("\nAT+HTTPINIT command failed again");
      }
   }
   return 0;
}


/**
  * @fn int SendDataPOST(uart_struct * uart_instance, char *api, char *data , char *time)
  * @brief used by A7600C1 4G LTE Sensor to send post data to remote server
  * @param uart_instance uart_instance of Shakti-UART
  * @param api Holds the address of the remote server
  * @param data Holds the data that needs to be sent to remote server
  * @param time 
*/

int SendDataPOST(uart_struct * uart_instance, char *api, char *data , char *time)
{
   delay(3);
   //initialising the sensor
    write_cmd(uart_instance,"AT+HTTPINIT");
    if(read_output(uart_instance,"OK"))
    {
        log_info("\nHTTP Service Started");
    }
    else
    {
        if(!recall_HTTP_service(uart_instance))
            return 0;
    }
    char cmd[200]={0};

   //Framing the parameter command
    char cmd[200]="AT+HTTPPARA=\"URL\",\"";
    int len1=str_length(cmd);
    int len2=str_length(api);
    int len3;

    int i,j,n,flag;
    i=len1;
    j=0;
    n=len1+len2;

    while(i<n)
    {
        cmd[i++]=api[j++];
    }
    cmd[i++]='"';
    cmd[i]='\0';
    
    write_cmd(uart_instance,cmd);
    if(read_output(uart_instance,"OK"))
    {
        log_info("\nURL set:%s",cmd);
    }
    else
    {
        log_info("\nAT+HTTPPARA command failed");
        return 0;
    }

   //sending the data to sensor module    
    char cmd2[50]="AT+HTTPDATA=";
    len1=str_length(cmd2);
    int temp=str_length(data)+1;
    char str[32];
    len2=int_to_str(temp,str);
    len3=str_length(time);

    i=len1;
    j=0;
    n=len1+len2;
    
    while(i<n)
    {
        cmd2[i++]=str[j++];
    }
    cmd2[i++]=',';
    j=0;
    n+=len3;

    while(i<n)
    {
       cmd2[i++]=time[j++];
    }
    cmd2[i]='\0';

    write_cmd(uart_instance,cmd2);
    if(read_output(uart_instance,"DOWNLOAD"))
    {
        write_cmd(uart_instance,data);
        if(read_output(uart_instance,"OK"))
        {
           log_info("\nData Uploaded to LTE Module");
        }
        else
        {
           log_info("\nData Uploading failed");
           return 0;
        }
    }
    else
    {
        log_info("\nAT+HTTPDATA command failed");
    }
    
   
   //sending the data to remote server
    flag=0;
    write_cmd(uart_instance,"AT+HTTPACTION=1");
    if(read_output(uart_instance,"OK"))
    {
        while(flag!=1)
        {
            if(read_output(uart_instance,"+HTTPACTION"))
            {
                log_info("\nData Sent to remote aws server");
                flag=1;
            }
            else
                delay(10);
        }
        
    }
    else
    {
        log_info("\nAT+HTTPACTION command failed");
        return 0;
    }    
    return 1;
   //return success

}


/**
  * @fn int SendDataRF(uart_struct * uart_instance, int enddevice , char *rfdata)
  * @brief used by XBEE Coordintaor to send data to ZigBee end device
  * @param uart_instance uart_instance of Shakti-UART
  * @param enddevice Selects the enddevice. 0 for mq2, 1 for mq7, 2 for lm75
  * @param rfdata Holds the data that needs to be sent to zigbee end node
*/
int SendDataRF(uart_struct * uart_instance, int enddevice, char *rfdata){

   //Creating the RF Frame to send data to end device
    unsigned char data[500];
    
    //start delimiter of API frame packet
	memset(data, NULL, sizeof(data));  
    data[start] = '\x7E';

    //rf data to send to zigbee end node
    for(int i=0;i<strlen(rfdata);i++){
        data[rfdatabase+i] = rfdata[i]; 
    }

    //length of frame packet : 2 bytes
    unsigned short int len = FIXEDOFFSET + strlen(rfdata);
    char *p = (char*)&len;
    data[lenbyte0] = *(p++); // length (2B)
    data[lenbyte1] = *p;

    //frametype and frame id
    data[frametype] = '\x10';
    data[frameid] = '\x01';

    //destination address 64-bit
    char addr[4][8] ={ {'\x00','\x13','\xA2','\x00','\x41','\xDE','\x54','\x0F'},
                       {'\x00','\x13','\xA2','\x00','\x41','\xF1','\xD3','\xD7'},
                       {'\x00','\x13','\xA2','\x00','\x41','\xF1','\xD3','\xD7'},
                       {'\x00','\x13','\xA2','\x00','\x41','\xF1','\xD3','\xD7'} 
                     };
   
    for(int i=0;i<8;i++){
        data[addrbase+i] = addr[enddevice][i]; 
    }
    //destination address 16-bit
    data[addr16bit0] = '\xFF';
    data[addr16bit1] = '\xFE';
    data[broadcast] = '\x00';
    data[options] = '\x00';

    //checksum calculation
    unsigned int sum=0;
    for(int i=frametype;i<rfdatabase+strlen(rfdata);i++){
         sum+=data[i];
    }
    int checksum = 0xFF - (sum&0xFF);
    int checksumoffest = rfdatabase+strlen(rfdata);
    data[checksumoffest] = checksum;

   //end node selection
   if(enddevice == MQ2){
          printf("\nsending remote server response to MQ2 node\n");
   }
   else if(enddevice ==  MQ7){
          printf("\nsending remote server response to MQ7 node\n");
   }
   else if(enddevice ==  LM75){
          printf("\nsending remote server response to LM75 node\n");
   }

    //sending RF data to end node
	for (int i = 0; i < len+4; i++)
	{	
      write_uart_character(uart_instance,data[i]);
	}	
}


/**
  * @fn void checkReceivedData(char *recv)
  * @brief checks which end device sent the data to coordinator
  * @param recv Holds the data  to identify end node
*/
void checkReceivedData(char *recv){
   int ch = recv[0]-'0';
   // based on 0th character of data, end node is identified
   switch (ch)
      {
      case MQ2: 
         printf("\nreceived data from MQ2 node:\n\t\"");
         break;
      
      case MQ7:
         printf("\nreceived data from MQ7 node:\n\t\"");
         break;

      case LM75:
         printf("\nreceived data from LM75 node:\n\t\"");
         break;

      default:
         break;
      }
   printf("%s\"\n", recv+1);
   //print the data received from end node
}

/**
  * @fn void sendDatatoNode(char recv)
  * @brief sends remote server response to the end node
  * @param recv used to identify end node
*/
void sendDatatoNode(char recv){
      int choice = recv-'0';
      switch (choice)
      {
      case MQ2: 
         SendDataRF(uart_instance[1], MQ2 , "success. data sent to remote server");
         break;
      
      case MQ7:
         SendDataRF(uart_instance[1], MQ7 , "success. data sent to remote server");
         break;

      case LM75:
         SendDataRF(uart_instance[1], LM75 , "success. data sent to remote server");
         break;

      default:
         break;
      }
}



/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with XBEE and UART 2 for A7600C1 LTE Module
  *      Set desired baudrate, get data from end nodes, and transmit to flask server 
  *      hosted on AWS
*/
int main(void){ 
    printf("starting Co-ordinator\n");
	unsigned int int_id = 1;
	register uint32_t retval;
	int i;
   //initialises the variables
	init_variables();

	pinmux_enable_uart1_uart2();
	
   //setting the baud rates of UART 
   set_baud_rate(uart_instance[0], 115200);
	set_baud_rate(uart_instance[1], 9600);
	set_baud_rate(uart_instance[2], 115200);

	plic_init();
   //configuring interrupt service routines   
	configure_interrupt(PLIC_INTERRUPT_26);
	isr_table[PLIC_INTERRUPT_26] = uart1_isr;
	configure_interrupt(PLIC_INTERRUPT_27);
	isr_table[PLIC_INTERRUPT_27] = uart2_isr;

	uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
	uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
	uart2_prev_tx_isr_count_flag = uart2_tx_isr_count;
	uart2_prev_rcv_isr_count_flag = uart2_rcv_isr_count;
   //flush uart buffers
	free_uart_buffers();
	printf("\n UART 1 Status Register: %x", uart_instance[1]->status);
	printf("\n UART 2 Status Register: %x", uart_instance[2]->status);
   //enable the interrupts
	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_EMPTY );//| ENABLE_RX_FULL);
	enable_uart_interrupts(uart_instance[2],  ENABLE_RX_NOT_EMPTY );//| ENABLE_RX_FULL);

	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm volatile(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf(" retval = %x\n", retval);
	asm volatile(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf(" retval = %x\n", retval);

	asm volatile(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	printf(" retval = %x\n", retval);

   //Enable this to update XBEE PRO S2C firmware to work as coordinator
    #ifdef CONFIGURE      
        configure_xbee(uart_instance[1]);
        flash_xbee_uart01(uart_instance[1]);
    #endif

   //initialise the lte module
    if(setup(uart_instance[2])){
	   printf("\nLTE module initialised!");
   }
   else{
	   printf("\nLTE module not working!");
   }

   int j=0;
   int k=0;
	while(1)
	{

		for(int tt=0;tt<10;tt++){
			delay_loop(2000,1000);	
		}

		if(uart1_rcv_isr_count != 0)
			{
				u1_rcv_char[++uart1_rcv_isr_count] = '\0';

            //checking the frame packet type
				for(int i=0;i<uart1_rcv_isr_count-1;i++){
					if(u1_rcv_char[i]  ==0x7E && i+3 < uart1_rcv_isr_count-1 &&  u1_rcv_char[i+3]==0x8B){
						log_info("Received acknowledgement packet\n");
						i=i+10;
					}

               //received data packet
					if(u1_rcv_char[i]==0x7E && i+3 < uart1_rcv_isr_count-1 &&  u1_rcv_char[i+3]==0x90){
						
						unsigned short int datalen;// = FIXEDOFFSET + strlen(rfdata);
						char *p = (char*)&datalen;
						p[0] = u1_rcv_char[i+2];
						p[1] = u1_rcv_char[i+1];

                  //extracting data from frame
						char recvdata[500]={0};
						for(int tempi = 0;tempi<datalen-12;tempi++){
							recvdata[tempi] = u1_rcv_char[i+tempi+15]; 
						}
                  checkReceivedData(recvdata);

                  //checksum verification
						unsigned int datasum=0;
						int startchecksum = i+frametype, endchecksum = i+datalen+frametype;
						for(int tempi=startchecksum;tempi<=endchecksum;tempi++){
							datasum+=u1_rcv_char[tempi];
						}
						if(datasum&0xFF == 0xFF){
							log_info("checksum verified for received  data\n\n");
						}
                  SendDataPOST(uart_instance[2],APIPOST,recvdata,TIME);

                  sendDatatoNode(recvdata[0]);

						i=i+endchecksum;
					}

				}
            //clear the uart buffers
				uart1_rcv_isr_count = 0;
				memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
				
			}
	
	};


	return 0;
}

/*****************************
 * End of ZigBee_Gateway.c
 *****************************/