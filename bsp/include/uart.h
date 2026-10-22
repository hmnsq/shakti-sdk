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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ UART_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UART_H
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USE_ਰੁਕਾਵਟ 1 //Uncomment or add this line when interrupts are unused
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USE_RX_ਹੱਦ 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ baud;	 /*! Baud rate configuration Register -- 16 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv0;	 /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ  ਸਥਿਤੀ_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ  reserv1;	 /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ  reserv2; /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ delay;    /*! Delays the transmit with specified clock - 16bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv3;  /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv5;  /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ien;	     /*! Enables the required interrupts - 8 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ reserv6;   /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv7;  /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ reserv8;   /*! reserved */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv9;  /*! reserved */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_RX_ਹੱਦ /*! This is to be used only when support is there. */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ rx_ਹੱਦ;	/*! RX FIFO size configuration register - 8 bits*/
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ reserv10;    /*! reserved */ 
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ reserv11;    /*! reserved */
#ਜੇ_ਅੰਤ	
} uart_struct;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STS_RX_ਹੱਦ    0x1 << 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BREAK_ERROR	    1 << 7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਚੌਖਟਾ_ERROR	    1 << 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OVERRUN        	    1 << 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PARITY_ERROR        1 << 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STS_RX_ਭਰਿਆ 	    1 << 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ    1 << 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STS_TX_ਭਰਿਆ 	    1 << 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STS_TX_ਖਾਲੀ_ਥਾਵਾਂ 	    1 << 0

/*! UART Interrupt Enable bits description */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_RX_ਹੱਦ	1 << 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_BREAK_ERROR      1 << 7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_ਚੌਖਟਾ_ERROR      1 << 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_OVERRUN          1 << 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_PARITY_ERROR     1 << 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_RX_ਭਰਿਆ 		1 << 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ 	1 << 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_TX_ਭਰਿਆ 		1 << 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_TX_ਖਾਲੀ_ਥਾਵਾਂ 	1 << 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UARTX_ਬਫਰ_ਮਾਪ       10000

/* UART control register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STOP_ਬਿੱਟ(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

ਬਾਹਰੀ uart_struct *uart_instance[MAX_UART_ਗਿਣਤੀ];
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart0_complete;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart1_complete;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart2_complete;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_tx_isr_ਗਿਣਤੀ ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_rcv_isr_ਗਿਣਤੀ ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_tx_isr_ਗਿਣਤੀ ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_rcv_isr_ਗਿਣਤੀ ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_tx_isr_ਗਿਣਤੀ ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_rcv_isr_ਗਿਣਤੀ ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਰੁਕਾਵਟ
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u0_rcv_char[UARTX_ਬਫਰ_ਮਾਪ];
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u1_rcv_char[UARTX_ਬਫਰ_ਮਾਪ];
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u2_rcv_char[UARTX_ਬਫਰ_ਮਾਪ];
#ਜੇ_ਅੰਤ

ਖਾਲੀ uart_init(ਖਾਲੀ);
ਖਾਲੀ ਸੈੱਟ_baud_ਦਰ(uart_struct * uart_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baudrate);
ਖਾਲੀ enable_uart_interrupts(uart_struct * uart_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਰੁਕਾਵਟ);
ਖਾਲੀ ਸੈੱਟ_uart_rx_ਹੱਦ(uart_struct * uart_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, ਅੱਖਰ * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, ਅੱਖਰ * ptr_string) ;
ਖਾਲੀ flush_uart(uart_struct * instance);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਰੁਕਾਵਟ
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart0_isr(ਖਾਲੀ);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart1_isr(ਖਾਲੀ);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart2_isr(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

ਪੂਰਨ is_ਖਾਲੀ_ਥਾਵਾਂ(ਖਾਲੀ);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਅੱਖਰ_ਲਿਖੋ
ਪੂਰਨ ਅੱਖਰ_ਲਿਖੋ(ਪੂਰਨ ch);

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ getchar
ਪੂਰਨ getchar(ਖਾਲੀ);

#ਜੇ_ਅੰਤ
