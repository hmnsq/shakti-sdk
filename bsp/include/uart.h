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

#अगर_अघोषित UART_H
#घोषणा UART_H
#समावेश <stdint.h>
#समावेश "platform.h"

#घोषणा USE_INTERRUPT 1 //Uncomment or add this line when interrupts are unused
#घोषणा USE_RX_THRESHOLD 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
प्रकार काष्ठा
{
	अचिन्हित लघु baud;	 /*! Baud rate configuration Register -- 16 bits*/
	अचिन्हित लघु reserv0;	 /*! reserved */
	अचिन्हित पूर्णांक  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	अचिन्हित पूर्णांक  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	अचिन्हित अक्षर  status;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	अचिन्हित अक्षर  reserv1;	 /*! reserved */
	अचिन्हित लघु  reserv2; /*! reserved */
	अचिन्हित लघु delay;    /*! Delays the transmit with specified clock - 16bits*/
	अचिन्हित लघु reserv3;  /*! reserved */
	अचिन्हित लघु control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	अचिन्हित लघु reserv5;  /*! reserved */
	अचिन्हित अक्षर ien;	     /*! Enables the required interrupts - 8 bits*/
	अचिन्हित अक्षर reserv6;   /*! reserved */
	अचिन्हित लघु reserv7;  /*! reserved */
	अचिन्हित अक्षर  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	अचिन्हित अक्षर reserv8;   /*! reserved */
	अचिन्हित लघु reserv9;  /*! reserved */
#अगर_घोषित USE_RX_THRESHOLD /*! This is to be used only when support is there. */
	अचिन्हित अक्षर rx_threshold;	/*! RX FIFO size configuration register - 8 bits*/
	अचिन्हित अक्षर reserv10;    /*! reserved */ 
	अचिन्हित लघु reserv11;    /*! reserved */
#पूर्ण_अगर	
} uart_struct;

#घोषणा STS_RX_THRESHOLD    0x1 << 8
#घोषणा BREAK_ERROR	    1 << 7
#घोषणा FRAME_ERROR	    1 << 6
#घोषणा OVERRUN        	    1 << 5
#घोषणा PARITY_ERROR        1 << 4
#घोषणा STS_RX_FULL 	    1 << 3
#घोषणा STS_RX_NOT_EMPTY    1 << 2
#घोषणा STS_TX_FULL 	    1 << 1
#घोषणा STS_TX_EMPTY 	    1 << 0

/*! UART Interrupt Enable bits description */
#घोषणा ENABLE_RX_THRESHOLD	1 << 8
#घोषणा ENABLE_BREAK_ERROR      1 << 7
#घोषणा ENABLE_FRAME_ERROR      1 << 6
#घोषणा ENABLE_OVERRUN          1 << 5
#घोषणा ENABLE_PARITY_ERROR     1 << 4
#घोषणा ENABLE_RX_FULL 		1 << 3
#घोषणा ENABLE_RX_NOT_EMPTY 	1 << 2
#घोषणा ENABLE_TX_FULL 		1 << 1
#घोषणा ENABLE_TX_EMPTY 	1 << 0
#घोषणा UARTX_बफर_आकार       10000

/* UART control register */
#घोषणा STOP_BITS(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#घोषणा PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#घोषणा UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

बाह्य uart_struct *uart_instance[MAX_UART_गिनती];
बाह्य अचिन्हित अक्षर uart0_complete;
बाह्य अचिन्हित अक्षर uart1_complete;
बाह्य अचिन्हित अक्षर uart2_complete;
बाह्य अचिन्हित पूर्णांक uart0_tx_isr_गिनती ;
बाह्य अचिन्हित पूर्णांक uart0_rcv_isr_गिनती ;
बाह्य अचिन्हित पूर्णांक uart1_tx_isr_गिनती ;
बाह्य अचिन्हित पूर्णांक uart1_rcv_isr_गिनती ;
बाह्य अचिन्हित पूर्णांक uart2_tx_isr_गिनती ;
बाह्य अचिन्हित पूर्णांक uart2_rcv_isr_गिनती ;

#अगर_घोषित USE_INTERRUPT
बाह्य अचिन्हित अक्षर u0_rcv_char[UARTX_बफर_आकार];
बाह्य अचिन्हित अक्षर u1_rcv_char[UARTX_बफर_आकार];
बाह्य अचिन्हित अक्षर u2_rcv_char[UARTX_बफर_आकार];
#पूर्ण_अगर

व्योम uart_init(व्योम);
व्योम set_baud_rate(uart_struct * uart_instance, अचिन्हित पूर्णांक baudrate);
व्योम enable_uart_interrupts(uart_struct * uart_instance, अचिन्हित अक्षर interrupt);
व्योम set_uart_rx_threshold(uart_struct * uart_instance, अचिन्हित अक्षर rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, अक्षर * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, अक्षर * ptr_string) ;
व्योम flush_uart(uart_struct * instance);

#अगर_घोषित USE_INTERRUPT
अचिन्हित अक्षर uart0_isr(व्योम);
अचिन्हित अक्षर uart1_isr(व्योम);
अचिन्हित अक्षर uart2_isr(व्योम);
#पूर्ण_अगर

पूर्णांक is_empty(व्योम);

#अघोषित अक्षर_दो
पूर्णांक अक्षर_दो(पूर्णांक ch);

#अघोषित अक्षर_लो
पूर्णांक अक्षर_लो(व्योम);

#पूर्ण_अगर
