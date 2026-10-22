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

#यदि_अपरिभाषितम् UART_H
#परिभाषय UART_H
#अन्तर्भाव <stdint.h>
#अन्तर्भाव "platform.h"

#परिभाषय USE_व्यवधानम् 1 //Uncomment or add this line when interrupts are unused
#परिभाषय USE_RX_देहली 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
प्रकारनिर्देश संरचना
{
	अचिह्नित ह्रस्व baud;	 /*! Baud rate configuration Register -- 16 bits*/
	अचिह्नित ह्रस्व reserv0;	 /*! reserved */
	अचिह्नित पूर्णाङ्क  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	अचिह्नित पूर्णाङ्क  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	अचिह्नित वर्ण  स्थितिः_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	अचिह्नित वर्ण  reserv1;	 /*! reserved */
	अचिह्नित ह्रस्व  reserv2; /*! reserved */
	अचिह्नित ह्रस्व delay;    /*! Delays the transmit with specified clock - 16bits*/
	अचिह्नित ह्रस्व reserv3;  /*! reserved */
	अचिह्नित ह्रस्व control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	अचिह्नित ह्रस्व reserv5;  /*! reserved */
	अचिह्नित वर्ण ien;	     /*! Enables the required interrupts - 8 bits*/
	अचिह्नित वर्ण reserv6;   /*! reserved */
	अचिह्नित ह्रस्व reserv7;  /*! reserved */
	अचिह्नित वर्ण  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	अचिह्नित वर्ण reserv8;   /*! reserved */
	अचिह्नित ह्रस्व reserv9;  /*! reserved */
#यदि_परिभाषितम् USE_RX_देहली /*! This is to be used only when support is there. */
	अचिह्नित वर्ण rx_देहली;	/*! RX FIFO size configuration register - 8 bits*/
	अचिह्नित वर्ण reserv10;    /*! reserved */ 
	अचिह्नित ह्रस्व reserv11;    /*! reserved */
#यदि_अन्तः	
} uart_struct;

#परिभाषय STS_RX_देहली    0x1 << 8
#परिभाषय BREAK_ERROR	    1 << 7
#परिभाषय FRAME_ERROR	    1 << 6
#परिभाषय OVERRUN        	    1 << 5
#परिभाषय PARITY_ERROR        1 << 4
#परिभाषय STS_RX_पूर्णम् 	    1 << 3
#परिभाषय STS_RX_NOT_रिक्तानि    1 << 2
#परिभाषय STS_TX_पूर्णम् 	    1 << 1
#परिभाषय STS_TX_रिक्तानि 	    1 << 0

/*! UART Interrupt Enable bits description */
#परिभाषय ENABLE_RX_देहली	1 << 8
#परिभाषय ENABLE_BREAK_ERROR      1 << 7
#परिभाषय ENABLE_FRAME_ERROR      1 << 6
#परिभाषय ENABLE_OVERRUN          1 << 5
#परिभाषय ENABLE_PARITY_ERROR     1 << 4
#परिभाषय ENABLE_RX_पूर्णम् 		1 << 3
#परिभाषय ENABLE_RX_NOT_रिक्तानि 	1 << 2
#परिभाषय ENABLE_TX_पूर्णम् 		1 << 1
#परिभाषय ENABLE_TX_रिक्तानि 	1 << 0
#परिभाषय UARTX_बफर_आकार       10000

/* UART control register */
#परिभाषय STOP_द्वयङ्काः(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#परिभाषय PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#परिभाषय UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

बाह्य uart_struct *uart_instance[MAX_UART_गणनम्];
बाह्य अचिह्नित वर्ण uart0_complete;
बाह्य अचिह्नित वर्ण uart1_complete;
बाह्य अचिह्नित वर्ण uart2_complete;
बाह्य अचिह्नित पूर्णाङ्क uart0_tx_isr_गणनम् ;
बाह्य अचिह्नित पूर्णाङ्क uart0_rcv_isr_गणनम् ;
बाह्य अचिह्नित पूर्णाङ्क uart1_tx_isr_गणनम् ;
बाह्य अचिह्नित पूर्णाङ्क uart1_rcv_isr_गणनम् ;
बाह्य अचिह्नित पूर्णाङ्क uart2_tx_isr_गणनम् ;
बाह्य अचिह्नित पूर्णाङ्क uart2_rcv_isr_गणनम् ;

#यदि_परिभाषितम् USE_व्यवधानम्
बाह्य अचिह्नित वर्ण u0_rcv_char[UARTX_बफर_आकार];
बाह्य अचिह्नित वर्ण u1_rcv_char[UARTX_बफर_आकार];
बाह्य अचिह्नित वर्ण u2_rcv_char[UARTX_बफर_आकार];
#यदि_अन्तः

शून्य uart_init(शून्य);
शून्य समुच्चयः_baud_दरः(uart_struct * uart_instance, अचिह्नित पूर्णाङ्क baudrate);
शून्य enable_uart_interrupts(uart_struct * uart_instance, अचिह्नित वर्ण व्यवधानम्);
शून्य समुच्चयः_uart_rx_देहली(uart_struct * uart_instance, अचिह्नित वर्ण rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, वर्ण * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, वर्ण * ptr_string) ;
शून्य flush_uart(uart_struct * instance);

#यदि_परिभाषितम् USE_व्यवधानम्
अचिह्नित वर्ण uart0_isr(शून्य);
अचिह्नित वर्ण uart1_isr(शून्य);
अचिह्नित वर्ण uart2_isr(शून्य);
#यदि_अन्तः

पूर्णाङ्क is_रिक्तानि(शून्य);

#अपरिभाषय अक्षरं_लिख
पूर्णाङ्क अक्षरं_लिख(पूर्णाङ्क ch);

#अपरिभाषय अक्षरं_पठ
पूर्णाङ्क अक्षरं_पठ(शून्य);

#यदि_अन्तः
