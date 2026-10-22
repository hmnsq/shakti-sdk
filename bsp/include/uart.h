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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ UART_H
#ವ್ಯಾಖ್ಯಾನಿಸು UART_H
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "platform.h"

#ವ್ಯಾಖ್ಯಾನಿಸು USE_ಅಡಚಣೆ 1 //Uncomment or add this line when interrupts are unused
#ವ್ಯಾಖ್ಯಾನಿಸು USE_RX_ಮಿತಿ 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ baud;	 /*! Baud rate configuration Register -- 16 bits*/
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv0;	 /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ  ಸ್ಥಿತಿ_3;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ  reserv1;	 /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ  reserv2; /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ delay;    /*! Delays the transmit with specified clock - 16bits*/
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv3;  /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv5;  /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ien;	     /*! Enables the required interrupts - 8 bits*/
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ reserv6;   /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv7;  /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ reserv8;   /*! reserved */
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv9;  /*! reserved */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_RX_ಮಿತಿ /*! This is to be used only when support is there. */
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rx_ಮಿತಿ;	/*! RX FIFO size configuration register - 8 bits*/
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ reserv10;    /*! reserved */ 
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ reserv11;    /*! reserved */
#ಆದರೆ_ಅಂತ್ಯ	
} uart_struct;

#ವ್ಯಾಖ್ಯಾನಿಸು STS_RX_ಮಿತಿ    0x1 << 8
#ವ್ಯಾಖ್ಯಾನಿಸು BREAK_ERROR	    1 << 7
#ವ್ಯಾಖ್ಯಾನಿಸು ಚೌಕಟ್ಟು_ERROR	    1 << 6
#ವ್ಯಾಖ್ಯಾನಿಸು OVERRUN        	    1 << 5
#ವ್ಯಾಖ್ಯಾನಿಸು PARITY_ERROR        1 << 4
#ವ್ಯಾಖ್ಯಾನಿಸು STS_RX_ತುಂಬಿದ 	    1 << 3
#ವ್ಯಾಖ್ಯಾನಿಸು STS_RX_NOT_ಖಾಲಿಗಳು    1 << 2
#ವ್ಯಾಖ್ಯಾನಿಸು STS_TX_ತುಂಬಿದ 	    1 << 1
#ವ್ಯಾಖ್ಯಾನಿಸು STS_TX_ಖಾಲಿಗಳು 	    1 << 0

/*! UART Interrupt Enable bits description */
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_RX_ಮಿತಿ	1 << 8
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_BREAK_ERROR      1 << 7
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_ಚೌಕಟ್ಟು_ERROR      1 << 6
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_OVERRUN          1 << 5
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_PARITY_ERROR     1 << 4
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_RX_ತುಂಬಿದ 		1 << 3
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_RX_NOT_ಖಾಲಿಗಳು 	1 << 2
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_TX_ತುಂಬಿದ 		1 << 1
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_TX_ಖಾಲಿಗಳು 	1 << 0
#ವ್ಯಾಖ್ಯಾನಿಸು UARTX_ಬಫರ್_ಗಾತ್ರ       10000

/* UART control register */
#ವ್ಯಾಖ್ಯಾನಿಸು STOP_ಬಿಟ್ಟುಗಳು(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#ವ್ಯಾಖ್ಯಾನಿಸು PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#ವ್ಯಾಖ್ಯಾನಿಸು UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

ಬಾಹ್ಯ uart_struct *uart_instance[MAX_UART_ಎಣಿಕೆ];
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart0_complete;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart1_complete;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart2_complete;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart0_tx_isr_ಎಣಿಕೆ ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart0_rcv_isr_ಎಣಿಕೆ ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart1_tx_isr_ಎಣಿಕೆ ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart1_rcv_isr_ಎಣಿಕೆ ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart2_tx_isr_ಎಣಿಕೆ ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart2_rcv_isr_ಎಣಿಕೆ ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ಅಡಚಣೆ
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u0_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ];
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u1_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ];
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u2_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ];
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ uart_init(ಶೂನ್ಯ);
ಶೂನ್ಯ ಗಣ_baud_ದರ(uart_struct * uart_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ baudrate);
ಶೂನ್ಯ enable_uart_interrupts(uart_struct * uart_instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಅಡಚಣೆ);
ಶೂನ್ಯ ಗಣ_uart_rx_ಮಿತಿ(uart_struct * uart_instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, ಅಕ್ಷರ * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, ಅಕ್ಷರ * ptr_string) ;
ಶೂನ್ಯ flush_uart(uart_struct * instance);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ಅಡಚಣೆ
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart0_isr(ಶೂನ್ಯ);
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart1_isr(ಶೂನ್ಯ);
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart2_isr(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ is_ಖಾಲಿಗಳು(ಶೂನ್ಯ);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಅಕ್ಷರ_ಬರೆ
ಪೂರ್ಣಾಂಕ ಅಕ್ಷರ_ಬರೆ(ಪೂರ್ಣಾಂಕ ch);

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು getchar
ಪೂರ್ಣಾಂಕ getchar(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ
