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

#اگر_تعریف_نشده UART_H
#تعریف_کن UART_H
#ضمن <stdint.h>
#ضمن "platform.h"

#تعریف_کن USE_وقفه 1 //Uncomment or add this line when interrupts are unused
#تعریف_کن USE_RX_آستانه 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
تعريفنوع بنية
{
	بیعلامت کوتاه baud;	 /*! Baud rate configuration Register -- 16 bits*/
	بیعلامت کوتاه reserv0;	 /*! reserved */
	بیعلامت صحيح  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	بیعلامت صحيح  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	بیعلامت حرف  وضعیت_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	بیعلامت حرف  reserv1;	 /*! reserved */
	بیعلامت کوتاه  reserv2; /*! reserved */
	بیعلامت کوتاه delay;    /*! Delays the transmit with specified clock - 16bits*/
	بیعلامت کوتاه reserv3;  /*! reserved */
	بیعلامت کوتاه control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	بیعلامت کوتاه reserv5;  /*! reserved */
	بیعلامت حرف ien;	     /*! Enables the required interrupts - 8 bits*/
	بیعلامت حرف reserv6;   /*! reserved */
	بیعلامت کوتاه reserv7;  /*! reserved */
	بیعلامت حرف  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	بیعلامت حرف reserv8;   /*! reserved */
	بیعلامت کوتاه reserv9;  /*! reserved */
#اگر_تعریف_شده USE_RX_آستانه /*! This is to be used only when support is there. */
	بیعلامت حرف rx_آستانه;	/*! RX FIFO size configuration register - 8 bits*/
	بیعلامت حرف reserv10;    /*! reserved */ 
	بیعلامت کوتاه reserv11;    /*! reserved */
#پایان_اگر	
} uart_struct;

#تعریف_کن STS_RX_آستانه    0x1 << 8
#تعریف_کن BREAK_ERROR	    1 << 7
#تعریف_کن قاب_ERROR	    1 << 6
#تعریف_کن OVERRUN        	    1 << 5
#تعریف_کن PARITY_ERROR        1 << 4
#تعریف_کن STS_RX_پر 	    1 << 3
#تعریف_کن STS_RX_NOT_خالی    1 << 2
#تعریف_کن STS_TX_پر 	    1 << 1
#تعریف_کن STS_TX_خالی 	    1 << 0

/*! UART Interrupt Enable bits description */
#تعریف_کن ENABLE_RX_آستانه	1 << 8
#تعریف_کن ENABLE_BREAK_ERROR      1 << 7
#تعریف_کن ENABLE_قاب_ERROR      1 << 6
#تعریف_کن ENABLE_OVERRUN          1 << 5
#تعریف_کن ENABLE_PARITY_ERROR     1 << 4
#تعریف_کن ENABLE_RX_پر 		1 << 3
#تعریف_کن ENABLE_RX_NOT_خالی 	1 << 2
#تعریف_کن ENABLE_TX_پر 		1 << 1
#تعریف_کن ENABLE_TX_خالی 	1 << 0
#تعریف_کن UARTX_میانگیر_اندازه       10000

/* UART control register */
#تعریف_کن STOP_بیتها(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#تعریف_کن PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#تعریف_کن UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

خارجي uart_struct *uart_instance[MAX_UART_شمار];
خارجي بیعلامت حرف uart0_complete;
خارجي بیعلامت حرف uart1_complete;
خارجي بیعلامت حرف uart2_complete;
خارجي بیعلامت صحيح uart0_tx_isr_شمار ;
خارجي بیعلامت صحيح uart0_rcv_isr_شمار ;
خارجي بیعلامت صحيح uart1_tx_isr_شمار ;
خارجي بیعلامت صحيح uart1_rcv_isr_شمار ;
خارجي بیعلامت صحيح uart2_tx_isr_شمار ;
خارجي بیعلامت صحيح uart2_rcv_isr_شمار ;

#اگر_تعریف_شده USE_وقفه
خارجي بیعلامت حرف u0_rcv_char[UARTX_میانگیر_اندازه];
خارجي بیعلامت حرف u1_rcv_char[UARTX_میانگیر_اندازه];
خارجي بیعلامت حرف u2_rcv_char[UARTX_میانگیر_اندازه];
#پایان_اگر

فراغ uart_init(فراغ);
فراغ مجموعه_baud_نرخ(uart_struct * uart_instance, بیعلامت صحيح baudrate);
فراغ enable_uart_interrupts(uart_struct * uart_instance, بیعلامت حرف وقفه);
فراغ مجموعه_uart_rx_آستانه(uart_struct * uart_instance, بیعلامت حرف rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, حرف * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, حرف * ptr_string) ;
فراغ flush_uart(uart_struct * instance);

#اگر_تعریف_شده USE_وقفه
بیعلامت حرف uart0_isr(فراغ);
بیعلامت حرف uart1_isr(فراغ);
بیعلامت حرف uart2_isr(فراغ);
#پایان_اگر

صحيح is_خالی(فراغ);

#لغو_تعریف حرف_چاپ_کن
صحيح حرف_چاپ_کن(صحيح ch);

#لغو_تعریف getchar
صحيح getchar(فراغ);

#پایان_اگر
