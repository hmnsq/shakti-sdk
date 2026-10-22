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

#నిర్వచితం_కాకపోతే UART_H
#నిర్వచించు UART_H
#అన్తర్భావ <stdint.h>
#అన్తర్భావ "platform.h"

#నిర్వచించు USE_అంతరాయం 1 //Uncomment or add this line when interrupts are unused
#నిర్వచించు USE_RX_పరిమితి 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
రకనిర్వచనం నిర్మాణం
{
	గుర్తులేని పొట్టి baud;	 /*! Baud rate configuration Register -- 16 bits*/
	గుర్తులేని పొట్టి reserv0;	 /*! reserved */
	గుర్తులేని పూర్ణాంకం  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	గుర్తులేని పూర్ణాంకం  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	గుర్తులేని అక్షరం  స్థితి_3;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	గుర్తులేని అక్షరం  reserv1;	 /*! reserved */
	గుర్తులేని పొట్టి  reserv2; /*! reserved */
	గుర్తులేని పొట్టి delay;    /*! Delays the transmit with specified clock - 16bits*/
	గుర్తులేని పొట్టి reserv3;  /*! reserved */
	గుర్తులేని పొట్టి control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	గుర్తులేని పొట్టి reserv5;  /*! reserved */
	గుర్తులేని అక్షరం ien;	     /*! Enables the required interrupts - 8 bits*/
	గుర్తులేని అక్షరం reserv6;   /*! reserved */
	గుర్తులేని పొట్టి reserv7;  /*! reserved */
	గుర్తులేని అక్షరం  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	గుర్తులేని అక్షరం reserv8;   /*! reserved */
	గుర్తులేని పొట్టి reserv9;  /*! reserved */
#నిర్వచితమైతే USE_RX_పరిమితి /*! This is to be used only when support is there. */
	గుర్తులేని అక్షరం rx_పరిమితి;	/*! RX FIFO size configuration register - 8 bits*/
	గుర్తులేని అక్షరం reserv10;    /*! reserved */ 
	గుర్తులేని పొట్టి reserv11;    /*! reserved */
#అయితే_ముగింపు	
} uart_struct;

#నిర్వచించు STS_RX_పరిమితి    0x1 << 8
#నిర్వచించు BREAK_ERROR	    1 << 7
#నిర్వచించు చట్రం_ERROR	    1 << 6
#నిర్వచించు OVERRUN        	    1 << 5
#నిర్వచించు PARITY_ERROR        1 << 4
#నిర్వచించు STS_RX_నిండిన 	    1 << 3
#నిర్వచించు STS_RX_NOT_ఖాళీలు    1 << 2
#నిర్వచించు STS_TX_నిండిన 	    1 << 1
#నిర్వచించు STS_TX_ఖాళీలు 	    1 << 0

/*! UART Interrupt Enable bits description */
#నిర్వచించు ENABLE_RX_పరిమితి	1 << 8
#నిర్వచించు ENABLE_BREAK_ERROR      1 << 7
#నిర్వచించు ENABLE_చట్రం_ERROR      1 << 6
#నిర్వచించు ENABLE_OVERRUN          1 << 5
#నిర్వచించు ENABLE_PARITY_ERROR     1 << 4
#నిర్వచించు ENABLE_RX_నిండిన 		1 << 3
#నిర్వచించు ENABLE_RX_NOT_ఖాళీలు 	1 << 2
#నిర్వచించు ENABLE_TX_నిండిన 		1 << 1
#నిర్వచించు ENABLE_TX_ఖాళీలు 	1 << 0
#నిర్వచించు UARTX_బఫరు_కొలత       10000

/* UART control register */
#నిర్వచించు STOP_బిట్లు(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#నిర్వచించు PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#నిర్వచించు UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

బాహ్య uart_struct *uart_instance[MAX_UART_లెక్క];
బాహ్య గుర్తులేని అక్షరం uart0_complete;
బాహ్య గుర్తులేని అక్షరం uart1_complete;
బాహ్య గుర్తులేని అక్షరం uart2_complete;
బాహ్య గుర్తులేని పూర్ణాంకం uart0_tx_isr_లెక్క ;
బాహ్య గుర్తులేని పూర్ణాంకం uart0_rcv_isr_లెక్క ;
బాహ్య గుర్తులేని పూర్ణాంకం uart1_tx_isr_లెక్క ;
బాహ్య గుర్తులేని పూర్ణాంకం uart1_rcv_isr_లెక్క ;
బాహ్య గుర్తులేని పూర్ణాంకం uart2_tx_isr_లెక్క ;
బాహ్య గుర్తులేని పూర్ణాంకం uart2_rcv_isr_లెక్క ;

#నిర్వచితమైతే USE_అంతరాయం
బాహ్య గుర్తులేని అక్షరం u0_rcv_char[UARTX_బఫరు_కొలత];
బాహ్య గుర్తులేని అక్షరం u1_rcv_char[UARTX_బఫరు_కొలత];
బాహ్య గుర్తులేని అక్షరం u2_rcv_char[UARTX_బఫరు_కొలత];
#అయితే_ముగింపు

శూన్య uart_init(శూన్య);
శూన్య సమితి_baud_రేటు(uart_struct * uart_instance, గుర్తులేని పూర్ణాంకం baudrate);
శూన్య enable_uart_interrupts(uart_struct * uart_instance, గుర్తులేని అక్షరం అంతరాయం);
శూన్య సమితి_uart_rx_పరిమితి(uart_struct * uart_instance, గుర్తులేని అక్షరం rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, అక్షరం * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, అక్షరం * ptr_string) ;
శూన్య flush_uart(uart_struct * instance);

#నిర్వచితమైతే USE_అంతరాయం
గుర్తులేని అక్షరం uart0_isr(శూన్య);
గుర్తులేని అక్షరం uart1_isr(శూన్య);
గుర్తులేని అక్షరం uart2_isr(శూన్య);
#అయితే_ముగింపు

పూర్ణాంకం is_ఖాళీలు(శూన్య);

#నిర్వచనం_రద్దు అక్షరం_రాయి
పూర్ణాంకం అక్షరం_రాయి(పూర్ణాంకం ch);

#నిర్వచనం_రద్దు getchar
పూర్ణాంకం getchar(శూన్య);

#అయితే_ముగింపు
