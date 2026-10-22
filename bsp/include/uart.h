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

#ifndef UART_H
#define UART_H
#अन्तर्भाव <stdint.h>
#अन्तर्भाव "platform.h"

#define USE_INTERRUPT 1 //Uncomment or add this line when interrupts are unused
#define USE_RX_THRESHOLD 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
प्रकारनिर्देश संरचना
{
	unsigned short baud;	 /*! Baud rate configuration Register -- 16 bits*/
	unsigned short reserv0;	 /*! reserved */
	unsigned पूर्णाङ्क  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	unsigned पूर्णाङ्क  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	unsigned वर्ण  status;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	unsigned वर्ण  reserv1;	 /*! reserved */
	unsigned short  reserv2; /*! reserved */
	unsigned short delay;    /*! Delays the transmit with specified clock - 16bits*/
	unsigned short reserv3;  /*! reserved */
	unsigned short control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	unsigned short reserv5;  /*! reserved */
	unsigned वर्ण ien;	     /*! Enables the required interrupts - 8 bits*/
	unsigned वर्ण reserv6;   /*! reserved */
	unsigned short reserv7;  /*! reserved */
	unsigned वर्ण  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	unsigned वर्ण reserv8;   /*! reserved */
	unsigned short reserv9;  /*! reserved */
#ifdef USE_RX_THRESHOLD /*! This is to be used only when support is there. */
	unsigned वर्ण rx_threshold;	/*! RX FIFO size configuration register - 8 bits*/
	unsigned वर्ण reserv10;    /*! reserved */ 
	unsigned short reserv11;    /*! reserved */
#endif	
} uart_struct;

#define STS_RX_THRESHOLD    0x1 << 8
#define BREAK_ERROR	    1 << 7
#define FRAME_ERROR	    1 << 6
#define OVERRUN        	    1 << 5
#define PARITY_ERROR        1 << 4
#define STS_RX_FULL 	    1 << 3
#define STS_RX_NOT_EMPTY    1 << 2
#define STS_TX_FULL 	    1 << 1
#define STS_TX_EMPTY 	    1 << 0

/*! UART Interrupt Enable bits description */
#define ENABLE_RX_THRESHOLD	1 << 8
#define ENABLE_BREAK_ERROR      1 << 7
#define ENABLE_FRAME_ERROR      1 << 6
#define ENABLE_OVERRUN          1 << 5
#define ENABLE_PARITY_ERROR     1 << 4
#define ENABLE_RX_FULL 		1 << 3
#define ENABLE_RX_NOT_EMPTY 	1 << 2
#define ENABLE_TX_FULL 		1 << 1
#define ENABLE_TX_EMPTY 	1 << 0
#define UARTX_BUFFER_SIZE       10000

/* UART control register */
#define STOP_BITS(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#define PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#define UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

बाह्य uart_struct *uart_instance[MAX_UART_मोजणी];
बाह्य unsigned वर्ण uart0_complete;
बाह्य unsigned वर्ण uart1_complete;
बाह्य unsigned वर्ण uart2_complete;
बाह्य unsigned पूर्णाङ्क uart0_tx_isr_मोजणी ;
बाह्य unsigned पूर्णाङ्क uart0_rcv_isr_मोजणी ;
बाह्य unsigned पूर्णाङ्क uart1_tx_isr_मोजणी ;
बाह्य unsigned पूर्णाङ्क uart1_rcv_isr_मोजणी ;
बाह्य unsigned पूर्णाङ्क uart2_tx_isr_मोजणी ;
बाह्य unsigned पूर्णाङ्क uart2_rcv_isr_मोजणी ;

#ifdef USE_INTERRUPT
बाह्य unsigned वर्ण u0_rcv_char[UARTX_BUFFER_SIZE];
बाह्य unsigned वर्ण u1_rcv_char[UARTX_BUFFER_SIZE];
बाह्य unsigned वर्ण u2_rcv_char[UARTX_BUFFER_SIZE];
#endif

शून्य uart_init(शून्य);
शून्य set_baud_rate(uart_struct * uart_instance, unsigned पूर्णाङ्क baudrate);
शून्य enable_uart_interrupts(uart_struct * uart_instance, unsigned वर्ण interrupt);
शून्य set_uart_rx_threshold(uart_struct * uart_instance, unsigned वर्ण rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, वर्ण * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, वर्ण * ptr_string) ;
शून्य flush_uart(uart_struct * instance);

#ifdef USE_INTERRUPT
unsigned वर्ण uart0_isr(शून्य);
unsigned वर्ण uart1_isr(शून्य);
unsigned वर्ण uart2_isr(शून्य);
#endif

पूर्णाङ्क is_empty(शून्य);

#undef putchar
पूर्णाङ्क putchar(पूर्णाङ्क ch);

#undef getchar
पूर्णाङ्क getchar(शून्य);

#endif
