/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  ZigBee_Router.c
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
  * @file ZigBee_Router.c
  * @brief ZigBee router acts as intermediary between end node and Coordinator 
  * @details File to demonstrate porting of ZigBee End device onto Shakti Processor and
  * XBEE PRO S2C sensor is used to port ZigBee protocol to Shakti.
  * Prerequisite:

  * 1. XBEE PRO S2C is configured to baud rate 9600
  * 2. XBEE PRO S2C is configured with ZigBee router firmware 
  * 3. UART[0] is for logging purposes
  * 4. UART[1] is to communicate with XBEE PRO S2C
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
  * @fn int write_xbee_uart01(uart_struct * uart_instance, char *str)
  * @brief Writes the AT Commands to XBEE PRO S2C to update the firmware
  * @param uart_instance The instance of uart pointed to XBEE PRO S2C
  * @param str AT Command is passed as string
  * @param length length of the AT Command
*/
int write_xbee_uart01(uart_struct * uart_instance, char *str)
{
    delay(3);
    char *s1 = str;

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


	write_xbee_uart01(uart_instance, "ATCE0");
	write_xbee_uart01(uart_instance, "ATJV1");
	write_xbee_uart01(uart_instance, "ATDL0");

      //Networking commands
   write_xbee_uart01(uart_instance, "ATID1234");
   write_xbee_uart01(uart_instance, "ATSC7FFF");
   write_xbee_uart01(uart_instance, "ATSD3");
   write_xbee_uart01(uart_instance, "ATZS0");
   write_xbee_uart01(uart_instance, "ATNJFF");
   write_xbee_uart01(uart_instance, "ATNW0");
   write_xbee_uart01(uart_instance, "ATJN1");   
   write_xbee_uart01(uart_instance, "ATDO8");
   write_xbee_uart01(uart_instance, "ATDC0");

   //Addressing commands
   write_xbee_uart01(uart_instance, "ATDH0");
   write_xbee_uart01(uart_instance, "ATNH1E");
   write_xbee_uart01(uart_instance, "ATBH0");
   write_xbee_uart01(uart_instance, "ATARFF");
   write_xbee_uart01(uart_instance, "ATDDA0000");
   write_xbee_uart01(uart_instance, "ATNT3C");
   write_xbee_uart01(uart_instance, "ATNO0");
   write_xbee_uart01(uart_instance, "ATCR3");

   //Zigbee Addressing
   write_xbee_uart01(uart_instance, "ATSEE8");
   write_xbee_uart01(uart_instance, "ATDEE8");
   write_xbee_uart01(uart_instance, "ATCI11");
   write_xbee_uart01(uart_instance, "ATTO0");

   //RF Interfacing
   write_xbee_uart01(uart_instance, "ATPL4");

   //Security
   write_xbee_uart01(uart_instance, "ATEE0");
   write_xbee_uart01(uart_instance, "ATEO0");
   write_xbee_uart01(uart_instance, "ATKY0");
   write_xbee_uart01(uart_instance, "ATNK0");
   
   
   //Serial Interfacing
   write_xbee_uart01(uart_instance, "ATBD3");
   write_xbee_uart01(uart_instance, "ATNB0");
   write_xbee_uart01(uart_instance, "ATSB0");
   write_xbee_uart01(uart_instance, "ATRO3");
   write_xbee_uart01(uart_instance, "ATD60");
   write_xbee_uart01(uart_instance, "ATD71");
   write_xbee_uart01(uart_instance, "ATAP1");
   write_xbee_uart01(uart_instance, "ATAO0");

   //AT Command Options
   write_xbee_uart01(uart_instance, "ATCT64");
   write_xbee_uart01(uart_instance, "ATGT3E8");
   write_xbee_uart01(uart_instance, "ATCC2B");
  
   //Sleep Modes
   write_xbee_uart01(uart_instance, "ATSP20" );
   write_xbee_uart01(uart_instance, "ATSN1");
   write_xbee_uart01(uart_instance, "ATSM0");
   write_xbee_uart01(uart_instance, "ATST1388");
   write_xbee_uart01(uart_instance, "ATSO0");
   write_xbee_uart01(uart_instance, "ATWH0");
   write_xbee_uart01(uart_instance, "ATPO0");

   //I/O Settings
   write_xbee_uart01(uart_instance, "ATD01");
   write_xbee_uart01(uart_instance, "ATD10");
   write_xbee_uart01(uart_instance, "ATD20");
   write_xbee_uart01(uart_instance, "ATD30");
   write_xbee_uart01(uart_instance, "ATD40");
   write_xbee_uart01(uart_instance, "ATD51");
   write_xbee_uart01(uart_instance, "ATD81");
   write_xbee_uart01(uart_instance, "ATD91");
   write_xbee_uart01(uart_instance, "ATP01");
   write_xbee_uart01(uart_instance, "ATP10");
   write_xbee_uart01(uart_instance, "ATP20");
   write_xbee_uart01(uart_instance, "ATP31");
   write_xbee_uart01(uart_instance, "ATP41");
   write_xbee_uart01(uart_instance, "ATPR1FBF");
   write_xbee_uart01(uart_instance, "ATPD1FFF");
   write_xbee_uart01(uart_instance, "ATLT0");
   write_xbee_uart01(uart_instance, "ATRP28");

   //I/O Sampling
   write_xbee_uart01(uart_instance, "ATIR0");
   write_xbee_uart01(uart_instance, "ATIC0");
   write_xbee_uart01(uart_instance, "ATV+0");
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
         log_info("Flashing success. The Xbee is configued as a Router.\n PANID: 1234\n ");
    }
    uart1_rcv_isr_count = 0;
    memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
}


/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with XBEE 
  *      Set desired baudrate
*/
int main(void){
	printf("starting router\n");
	unsigned int int_id = 1;
	register uint32_t retval;
	int i;

	init_variables();

	pinmux_enable_uart1_uart2();
	set_baud_rate(uart_instance[0], 115200);
	set_baud_rate(uart_instance[1], 9600);
	//set_baud_rate(uart_instance[2], 115200);

	plic_init();
  //diable all interrupts, 

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
	

    #ifdef CONFIGURE
		configure_xbee(uart_instance[1]);
        flash_xbee_uart01(uart_instance[1]);
    #endif

  //keep router alive
	while(1);
	return 0;
}



/*****************************
 * End of ZigBee_Router.c
 *****************************

