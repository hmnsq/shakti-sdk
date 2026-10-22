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
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ "platform.h"

#define USE_INTERRUPT 1 //Uncomment or add this line when interrupts are unused
#define USE_RX_THRESHOLD 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
પ્રકારવ્યાખ્યા સંરચના
{
	unsigned short baud;	 /*! Baud rate configuration Register -- 16 bits*/
	unsigned short reserv0;	 /*! reserved */
	unsigned પૂર્ણાંક  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	unsigned પૂર્ણાંક  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	unsigned અક્ષર  status;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	unsigned અક્ષર  reserv1;	 /*! reserved */
	unsigned short  reserv2; /*! reserved */
	unsigned short delay;    /*! Delays the transmit with specified clock - 16bits*/
	unsigned short reserv3;  /*! reserved */
	unsigned short control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	unsigned short reserv5;  /*! reserved */
	unsigned અક્ષર ien;	     /*! Enables the required interrupts - 8 bits*/
	unsigned અક્ષર reserv6;   /*! reserved */
	unsigned short reserv7;  /*! reserved */
	unsigned અક્ષર  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	unsigned અક્ષર reserv8;   /*! reserved */
	unsigned short reserv9;  /*! reserved */
#ifdef USE_RX_THRESHOLD /*! This is to be used only when support is there. */
	unsigned અક્ષર rx_threshold;	/*! RX FIFO size configuration register - 8 bits*/
	unsigned અક્ષર reserv10;    /*! reserved */ 
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

બાહ્ય uart_struct *uart_instance[MAX_UART_ગણતરી];
બાહ્ય unsigned અક્ષર uart0_complete;
બાહ્ય unsigned અક્ષર uart1_complete;
બાહ્ય unsigned અક્ષર uart2_complete;
બાહ્ય unsigned પૂર્ણાંક uart0_tx_isr_ગણતરી ;
બાહ્ય unsigned પૂર્ણાંક uart0_rcv_isr_ગણતરી ;
બાહ્ય unsigned પૂર્ણાંક uart1_tx_isr_ગણતરી ;
બાહ્ય unsigned પૂર્ણાંક uart1_rcv_isr_ગણતરી ;
બાહ્ય unsigned પૂર્ણાંક uart2_tx_isr_ગણતરી ;
બાહ્ય unsigned પૂર્ણાંક uart2_rcv_isr_ગણતરી ;

#ifdef USE_INTERRUPT
બાહ્ય unsigned અક્ષર u0_rcv_char[UARTX_BUFFER_SIZE];
બાહ્ય unsigned અક્ષર u1_rcv_char[UARTX_BUFFER_SIZE];
બાહ્ય unsigned અક્ષર u2_rcv_char[UARTX_BUFFER_SIZE];
#endif

શૂન્ય uart_init(શૂન્ય);
શૂન્ય set_baud_rate(uart_struct * uart_instance, unsigned પૂર્ણાંક baudrate);
શૂન્ય enable_uart_interrupts(uart_struct * uart_instance, unsigned અક્ષર interrupt);
શૂન્ય set_uart_rx_threshold(uart_struct * uart_instance, unsigned અક્ષર rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, અક્ષર * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, અક્ષર * ptr_string) ;
શૂન્ય flush_uart(uart_struct * instance);

#ifdef USE_INTERRUPT
unsigned અક્ષર uart0_isr(શૂન્ય);
unsigned અક્ષર uart1_isr(શૂન્ય);
unsigned અક્ષર uart2_isr(શૂન્ય);
#endif

પૂર્ણાંક is_empty(શૂન્ય);

#undef putchar
પૂર્ણાંક putchar(પૂર્ણાંક ch);

#undef getchar
પૂર્ણાંક getchar(શૂન્ય);

#endif
