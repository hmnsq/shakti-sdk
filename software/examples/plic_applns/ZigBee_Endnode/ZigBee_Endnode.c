/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  ZigBeeEndnode.c
 * Created date			        :  31.03.2022
 * Brief Description of file    :  ZigBee Router acts as an intermediary between ZigBee Coordinator and ZigBee Endnode
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
  * @file ZigBee_Endnode.c
  * @brief ZigBee endnode acts as ZigBee end device and collects data using sensors 
  * @details File to demonstrate porting of ZigBee End device onto Shakti Processor and
  * XBEE PRO S2C sensor is used to port ZigBee protocol to Shakti , Other sensor drives are interfaced
  * Prerequisite:

  * 1. XBEE PRO S2C is configured to baud rate 9600
  * 2. XBEE PRO S2C is configured with ZigBee End device firmware 
  * 3. Change the address of the data collecting sensor code in ZigBee_Endnode.c
  * 4. UART[0] is for logging purposes
  * 5. UART[1] is to communicate with XBEE PRO S2C
*/


#include <stdint.h>
#include <stddef.h>
#include "log.h"
#include "uart.h"
#include "pinmux.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include <stdio.h>
#include <string.h>


#include <stdint.h>
#include "xadc_driver.h"
#include <math.h>

#define FIXEDOFFSET 14
#define MQ2 0
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

//Denote to use the interrupts
#define USE_INTERRUPT
#define MAX_OUTPUT_SIZE 1024

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
  * @fn int enterATMode(uart_struct * uart_instance)
  * @brief XBEE PRO S2C enters AT Mode before updating the firmware to coordinator
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
*/
int enterATMode(uart_struct * uart_instance)
{
   delay(20);
    write_uart_character(uart_instance,'+');
    write_uart_character(uart_instance,'+');
    write_uart_character(uart_instance,'+');
   delay(20);

    u1_rcv_char[++uart1_rcv_isr_count] = '\0';

    if(strstr(u1_rcv_char,"OK")==NULL)
    {
        log_info("Entered AT Command Mode");
        return 1;
    }
    else {
        log_info("Failed to enter AT Mode");
        return 0;
    }
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

    // for(int i=0;i<length;i++){
    //     write_uart_character(uart_instance, *str);
    //     str++;
    // }
    while(*str!='\0')
    {
       write_uart_character(uart_instance,*str);
       str++;
    }
    write_uart_character(uart_instance,'\r');

    delay(2);
    u1_rcv_char[++uart1_rcv_isr_count] = '\0';

    if(strstr(u1_rcv_char,"ERROR")==NULL)
    {
        log_info("%s command failed", s1);
    }
    else {
        log_info("%s command success", s1);
    }
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
}

/**
  * @fn void configure_xbee(uart_struct * uart_instance)
  * @brief Configures XBEE PRO S2C as ZigBee Coordintaor
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
*/
void configure_xbee(uart_struct * uart_instance){
    
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


   write_xbee_uart01(uart_instance, "ATCE0", 5);
   write_xbee_uart01(uart_instance, "ATJV1", 5);
   write_xbee_uart01(uart_instance, "ATDL0", 8);

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
   write_xbee_uart01(uart_instance, "ATSP64",6 );       //ATSP64 = 64(HEX) = 100(decimal)*10ms = 1 second.
   write_xbee_uart01(uart_instance, "ATSN1", 5);
   write_xbee_uart01(uart_instance, "ATSM4", 5);        //ATSM4 = Cyclic Sleep mode
   write_xbee_uart01(uart_instance, "ATST1388", 8);    //ATST1f4 = 1f4 HEX = 500(decimal) * 10ms = 5 Seconds.

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
    delay(3);
    write_uart_character(uart_instance,'A');
    write_uart_character(uart_instance,'T');
    write_uart_character(uart_instance,'W');
    write_uart_character(uart_instance,'R');
    write_uart_character(uart_instance,'\r');
    delay(2);


    u1_rcv_char[++uart1_rcv_isr_count] = '\0';
    if(strstr(u1_rcv_char,"ERROR")==NULL)
    {
        log_info("Flashing failed. The above configuration stays until next reboot!\n");
    }
    else {
         log_info("Flashing success. The Xbee is configued as a End Node.\n PANID: 1234\n ");
    }
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
}

/**
  * @fn int SendDataRF(uart_struct * uart_instance, int enddevice , char *rfdata)
  * @brief used by XBEE Coordintaor to send data to ZigBee end device
  * @param uart_instance uart_instance of Shakti-UART
  * @param enddevice Selects the enddevice. 0 for mq2, 1 for mq7, 2 for lm75
  * @param rfdata Holds the data that needs to be sent to zigbee end node
*/
int SendDataRF(uart_struct * uart_instance, char *rfdata){

   //Creating the RF Frame to send data to end device
    unsigned char data[500];
    //start delimiter  
	memset(data, NULL, sizeof(data));  
    data[start] = '\x7E';
    //rf data
    for(int i=0;i<strlen(rfdata);i++){
        data[rfdatabase+i] = rfdata[i]; 
    }

    //length 2 bytes
    unsigned short int len = FIXEDOFFSET + strlen(rfdata);
    char *p = (char*)&len;
    data[lenbyte0] = *(p++); // length (2B)
    data[lenbyte1] = *p;

    //frametype and frame id
    data[frametype] = '\x10';
    data[frameid] = '\x01';

    //destination address 64-bit
    char addr[8] ={ '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};
   
    for(int i=0;i<8;i++){
        data[addrbase+i] = addr[i]; 
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

    printf("sending rf data\n");

    //sending RF data
	for (int i = 0; i < len+4; i++)
	{
        	write_uart_character(uart_instance,data[i]);
	}	
}



/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with XBEE
  *      Set desired baudrate, get data from data collecting sensor module and and transmit to coordinator.
*/
int main(void){
    printf("starting enddevice\n");
	unsigned int int_id = 1;
	register uint32_t retval;
	int i;

	init_variables();

	pinmux_enable_uart1_uart2();
	set_baud_rate(uart_instance[0], 115200);
	set_baud_rate(uart_instance[1], 9600);

	plic_init();

	configure_interrupt(PLIC_INTERRUPT_26);
	isr_table[PLIC_INTERRUPT_26] = uart1_isr;

	uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
	uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
	free_uart_buffers();
	printf("Before Tx00\n");
	printf("\n UART 1 Status Register: %x", uart_instance[1]->status);
	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_EMPTY );//| ENABLE_RX_FULL);

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
	
   printf("starting Co-ordinator\n");
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
				for(int i=0;i<uart1_rcv_isr_count-1;i++){
					if(u1_rcv_char[i]  ==0x7E && i+3 < uart1_rcv_isr_count-1 &&  u1_rcv_char[i+3]==0x8B){
						log_info("Received acknowledgement from the receiver\n");
						i=i+10;
					}

					if(u1_rcv_char[i]==0x7E && i+3 < uart1_rcv_isr_count-1 &&  u1_rcv_char[i+3]==0x90){
						
						unsigned short int datalen;// = FIXEDOFFSET + strlen(rfdata);
						char *p = (char*)&datalen;
						p[0] = u1_rcv_char[i+2];
						p[1] = u1_rcv_char[i+1];

						char recvdata[500]={0};
						for(int tempi = 0;tempi<datalen-12;tempi++){
							recvdata[tempi] = u1_rcv_char[i+tempi+15]; 
						}
						log_info("datareceived::%s\n", recvdata);

						unsigned int datasum=0;
						int startchecksum = i+frametype, endchecksum = i+datalen+frametype;
						for(int tempi=startchecksum;tempi<=endchecksum;tempi++){
							datasum+=u1_rcv_char[tempi];
						}
						if(datasum&0xFF == 0xFF){
							log_info("checksum verified for received  data\n\n");
						}

						i=i+endchecksum;
					}
				}
				uart1_rcv_isr_count = 0;
				memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);				
			}
			k++;
			k=k%3;

			if(k%3==0){
					char mq2values[200];
                    /***********************************************
                    //perform sensor read operation here.					
					//mq2values contains the string that need to be sent to coordinator. Add 0 for MQ2, 1 for MQ7, 2 for LM75.
					//for example : sprintf(mq2values,"0LPG:%d,CO:%d,SMOKE:%d,ID:Hall");
                    ***********************************************/                
                    SendDataRF(uart_instance[1],mq2values);
			}
		delay_loop(2000,1000);	
	};

  //Exiting End Device;
	return 0;
}


/*****************************
 * End of ZigBee_Endnode.c
 *****************************