/************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: uart.h
 * Brief Description of file    : Header file for uart.
 * Name of Author    	        : Niketan Shahapur,Kotteeswaran & Sathya Narayanan N
 * Email ID                     : niketanshahpur@gmail.com, kottee.1@gmail.com, sathya281@gmail.com

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
************************************************************************/
/**
 * @file uart.h
 * @brief Header file for uart
 * @detail this is the header file for uart.c   
 */

#جيڪڏهن_وصف_نه_ٿيل UART_H
#وصف_ڪريو UART_H
#ضمن <stdint.h>
#ضمن "platform.h"

#وصف_ڪريو USE_مداخلت 1 //Uncomment or add this line when interrupts are unused
#وصف_ڪريو USE_RX_حد 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
تعريفنوع بنية
{
	بنانشان ننڍو baud;	 /*! Baud rate configuration Register -- 16 bits*/
	بنانشان ننڍو reserv0;	 /*! reserved */
	بنانشان صحيح  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	بنانشان صحيح  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	بنانشان حرف  حالت_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	بنانشان حرف  reserv1;	 /*! reserved */
	بنانشان ننڍو  reserv2; /*! reserved */
	بنانشان ننڍو delay;    /*! Delays the transmit with specified clock - 16bits*/
	بنانشان ننڍو reserv3;  /*! reserved */
	بنانشان ننڍو control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	بنانشان ننڍو reserv5;  /*! reserved */
	بنانشان حرف ien;	     /*! Enables the required interrupts - 8 bits*/
	بنانشان حرف reserv6;   /*! reserved */
	بنانشان ننڍو reserv7;  /*! reserved */
	بنانشان حرف  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	بنانشان حرف reserv8;   /*! reserved */
	بنانشان ننڍو reserv9;  /*! reserved */
#جيڪڏهن_وصف_ٿيل USE_RX_حد /*! This is to be used only when support is there. */
	بنانشان حرف rx_حد;	/*! RX FIFO size configuration register - 8 bits*/
	بنانشان حرف reserv10;    /*! reserved */ 
	بنانشان ننڍو reserv11;    /*! reserved */
#جيڪڏهن_پورو	
} uart_struct;

#وصف_ڪريو STS_RX_حد    0x1 << 8
#وصف_ڪريو BREAK_ERROR	    1 << 7
#وصف_ڪريو چوکٺو_ERROR	    1 << 6
#وصف_ڪريو OVERRUN        	    1 << 5
#وصف_ڪريو PARITY_ERROR        1 << 4
#وصف_ڪريو STS_RX_ڀريل 	    1 << 3
#وصف_ڪريو STS_RX_NOT_خالي_جايون    1 << 2
#وصف_ڪريو STS_TX_ڀريل 	    1 << 1
#وصف_ڪريو STS_TX_خالي_جايون 	    1 << 0

/*! UART Interrupt Enable bits description */
#وصف_ڪريو ENABLE_RX_حد	1 << 8
#وصف_ڪريو ENABLE_BREAK_ERROR      1 << 7
#وصف_ڪريو ENABLE_چوکٺو_ERROR      1 << 6
#وصف_ڪريو ENABLE_OVERRUN          1 << 5
#وصف_ڪريو ENABLE_PARITY_ERROR     1 << 4
#وصف_ڪريو ENABLE_RX_ڀريل 		1 << 3
#وصف_ڪريو ENABLE_RX_NOT_خالي_جايون 	1 << 2
#وصف_ڪريو ENABLE_TX_ڀريل 		1 << 1
#وصف_ڪريو ENABLE_TX_خالي_جايون 	1 << 0
#وصف_ڪريو UARTX_بفر_سائيز       10000

/* UART control register */
#وصف_ڪريو STOP_بٽ(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#وصف_ڪريو PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#وصف_ڪريو UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

خارجي uart_struct *uart_instance[MAX_UART_ڳڻپ];
خارجي بنانشان حرف uart0_complete;
خارجي بنانشان حرف uart1_complete;
خارجي بنانشان حرف uart2_complete;
خارجي بنانشان صحيح uart0_tx_isr_ڳڻپ ;
خارجي بنانشان صحيح uart0_rcv_isr_ڳڻپ ;
خارجي بنانشان صحيح uart1_tx_isr_ڳڻپ ;
خارجي بنانشان صحيح uart1_rcv_isr_ڳڻپ ;
خارجي بنانشان صحيح uart2_tx_isr_ڳڻپ ;
خارجي بنانشان صحيح uart2_rcv_isr_ڳڻپ ;

#جيڪڏهن_وصف_ٿيل USE_مداخلت
خارجي بنانشان حرف u0_rcv_char[UARTX_بفر_سائيز];
خارجي بنانشان حرف u1_rcv_char[UARTX_بفر_سائيز];
خارجي بنانشان حرف u2_rcv_char[UARTX_بفر_سائيز];
#جيڪڏهن_پورو

فراغ uart_init(فراغ);
فراغ سيٽ_baud_شرح(uart_struct * uart_instance, بنانشان صحيح baudrate);
فراغ enable_uart_interrupts(uart_struct * uart_instance, بنانشان حرف مداخلت);
فراغ سيٽ_uart_rx_حد(uart_struct * uart_instance, بنانشان حرف rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, حرف * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, حرف * ptr_string) ;
فراغ flush_uart(uart_struct * instance);

#جيڪڏهن_وصف_ٿيل USE_مداخلت
بنانشان حرف uart0_isr(فراغ);
بنانشان حرف uart1_isr(فراغ);
بنانشان حرف uart2_isr(فراغ);
#جيڪڏهن_پورو

صحيح is_خالي_جايون(فراغ);

#وصف_رد اکر_لکو
صحيح اکر_لکو(صحيح ch);

#وصف_رد getchar
صحيح getchar(فراغ);

#جيڪڏهن_پورو
