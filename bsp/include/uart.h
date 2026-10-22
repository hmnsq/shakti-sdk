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

#که_نه_تعریف_شوی UART_H
#تعریف_کړه UART_H
#ضمن <stdint.h>
#ضمن "platform.h"

#تعریف_کړه USE_مداخله 1 //Uncomment or add this line when interrupts are unused
#تعریف_کړه USE_RX_پوله 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
تعريفنوع بنية
{
	بینښه لنډ baud;	 /*! Baud rate configuration Register -- 16 bits*/
	بینښه لنډ reserv0;	 /*! reserved */
	بینښه صحيح  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	بینښه صحيح  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	بینښه حرف  حالت_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	بینښه حرف  reserv1;	 /*! reserved */
	بینښه لنډ  reserv2; /*! reserved */
	بینښه لنډ delay;    /*! Delays the transmit with specified clock - 16bits*/
	بینښه لنډ reserv3;  /*! reserved */
	بینښه لنډ control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	بینښه لنډ reserv5;  /*! reserved */
	بینښه حرف ien;	     /*! Enables the required interrupts - 8 bits*/
	بینښه حرف reserv6;   /*! reserved */
	بینښه لنډ reserv7;  /*! reserved */
	بینښه حرف  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	بینښه حرف reserv8;   /*! reserved */
	بینښه لنډ reserv9;  /*! reserved */
#که_تعریف_شوی USE_RX_پوله /*! This is to be used only when support is there. */
	بینښه حرف rx_پوله;	/*! RX FIFO size configuration register - 8 bits*/
	بینښه حرف reserv10;    /*! reserved */ 
	بینښه لنډ reserv11;    /*! reserved */
#د_که_پای	
} uart_struct;

#تعریف_کړه STS_RX_پوله    0x1 << 8
#تعریف_کړه BREAK_ERROR	    1 << 7
#تعریف_کړه چوکاټ_ERROR	    1 << 6
#تعریف_کړه OVERRUN        	    1 << 5
#تعریف_کړه PARITY_ERROR        1 << 4
#تعریف_کړه STS_RX_ډک 	    1 << 3
#تعریف_کړه STS_RX_NOT_تشه    1 << 2
#تعریف_کړه STS_TX_ډک 	    1 << 1
#تعریف_کړه STS_TX_تشه 	    1 << 0

/*! UART Interrupt Enable bits description */
#تعریف_کړه ENABLE_RX_پوله	1 << 8
#تعریف_کړه ENABLE_BREAK_ERROR      1 << 7
#تعریف_کړه ENABLE_چوکاټ_ERROR      1 << 6
#تعریف_کړه ENABLE_OVERRUN          1 << 5
#تعریف_کړه ENABLE_PARITY_ERROR     1 << 4
#تعریف_کړه ENABLE_RX_ډک 		1 << 3
#تعریف_کړه ENABLE_RX_NOT_تشه 	1 << 2
#تعریف_کړه ENABLE_TX_ډک 		1 << 1
#تعریف_کړه ENABLE_TX_تشه 	1 << 0
#تعریف_کړه UARTX_بفر_اندازه       10000

/* UART control register */
#تعریف_کړه STOP_بټونه(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#تعریف_کړه PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#تعریف_کړه UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

خارجي uart_struct *uart_instance[MAX_UART_شمېر];
خارجي بینښه حرف uart0_complete;
خارجي بینښه حرف uart1_complete;
خارجي بینښه حرف uart2_complete;
خارجي بینښه صحيح uart0_tx_isr_شمېر ;
خارجي بینښه صحيح uart0_rcv_isr_شمېر ;
خارجي بینښه صحيح uart1_tx_isr_شمېر ;
خارجي بینښه صحيح uart1_rcv_isr_شمېر ;
خارجي بینښه صحيح uart2_tx_isr_شمېر ;
خارجي بینښه صحيح uart2_rcv_isr_شمېر ;

#که_تعریف_شوی USE_مداخله
خارجي بینښه حرف u0_rcv_char[UARTX_بفر_اندازه];
خارجي بینښه حرف u1_rcv_char[UARTX_بفر_اندازه];
خارجي بینښه حرف u2_rcv_char[UARTX_بفر_اندازه];
#د_که_پای

فراغ uart_init(فراغ);
فراغ سېټ_baud_شرح(uart_struct * uart_instance, بینښه صحيح baudrate);
فراغ enable_uart_interrupts(uart_struct * uart_instance, بینښه حرف مداخله);
فراغ سېټ_uart_rx_پوله(uart_struct * uart_instance, بینښه حرف rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, حرف * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, حرف * ptr_string) ;
فراغ flush_uart(uart_struct * instance);

#که_تعریف_شوی USE_مداخله
بینښه حرف uart0_isr(فراغ);
بینښه حرف uart1_isr(فراغ);
بینښه حرف uart2_isr(فراغ);
#د_که_پای

صحيح is_تشه(فراغ);

#تعریف_لغوه توری_چاپ_کړه
صحيح توری_چاپ_کړه(صحيح ch);

#تعریف_لغوه getchar
صحيح getchar(فراغ);

#د_که_پای
