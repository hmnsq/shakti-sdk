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

#جے_بنا_تعریف UART_H
#تعریف_کرو UART_H
#ضمن <stdint.h>
#ضمن "platform.h"

#تعریف_کرو USE_رکاوٹ 1 //Uncomment or add this line when interrupts are unused
#تعریف_کرو USE_RX_حد 1 //uncomment or add this line when rx_threshold is required


/* Struct to access UART registers as 32 bit registers */
تعريفنوع بنية
{
	بنانشانی چھوٹا baud;	 /*! Baud rate configuration Register -- 16 bits*/
	بنانشانی چھوٹا reserv0;	 /*! reserved */
	بنانشانی صحيح  tx_reg;	 /*! Transmit register -- the value that needs to be tranmitted needs to be written here-32 bits*/
	بنانشانی صحيح  rcv_reg;	 /*! Receive register -- the value that received from uart can be read from here --32 bits*/
	بنانشانی حرف  حالت_2;	 /*! Status register -- Reads various transmit and receive status - 8 bits*/
	بنانشانی حرف  reserv1;	 /*! reserved */
	بنانشانی چھوٹا  reserv2; /*! reserved */
	بنانشانی چھوٹا delay;    /*! Delays the transmit with specified clock - 16bits*/
	بنانشانی چھوٹا reserv3;  /*! reserved */
	بنانشانی چھوٹا control;   /*! Control Register -- Configures the no. of bits used, stop bits, parity enabled or not - 16bits*/
	بنانشانی چھوٹا reserv5;  /*! reserved */
	بنانشانی حرف ien;	     /*! Enables the required interrupts - 8 bits*/
	بنانشانی حرف reserv6;   /*! reserved */
	بنانشانی چھوٹا reserv7;  /*! reserved */
	بنانشانی حرف  iqcycles; /*! 8-bit register that indicates number of input qualification cycles - 8 bits*/
	بنانشانی حرف reserv8;   /*! reserved */
	بنانشانی چھوٹا reserv9;  /*! reserved */
#جے_تعریف_شدہ USE_RX_حد /*! This is to be used only when support is there. */
	بنانشانی حرف rx_حد;	/*! RX FIFO size configuration register - 8 bits*/
	بنانشانی حرف reserv10;    /*! reserved */ 
	بنانشانی چھوٹا reserv11;    /*! reserved */
#جے_انت	
} uart_struct;

#تعریف_کرو STS_RX_حد    0x1 << 8
#تعریف_کرو BREAK_ERROR	    1 << 7
#تعریف_کرو چوکھٹا_ERROR	    1 << 6
#تعریف_کرو OVERRUN        	    1 << 5
#تعریف_کرو PARITY_ERROR        1 << 4
#تعریف_کرو STS_RX_بھریا 	    1 << 3
#تعریف_کرو STS_RX_NOT_خالی_تھاواں    1 << 2
#تعریف_کرو STS_TX_بھریا 	    1 << 1
#تعریف_کرو STS_TX_خالی_تھاواں 	    1 << 0

/*! UART Interrupt Enable bits description */
#تعریف_کرو ENABLE_RX_حد	1 << 8
#تعریف_کرو ENABLE_BREAK_ERROR      1 << 7
#تعریف_کرو ENABLE_چوکھٹا_ERROR      1 << 6
#تعریف_کرو ENABLE_OVERRUN          1 << 5
#تعریف_کرو ENABLE_PARITY_ERROR     1 << 4
#تعریف_کرو ENABLE_RX_بھریا 		1 << 3
#تعریف_کرو ENABLE_RX_NOT_خالی_تھاواں 	1 << 2
#تعریف_کرو ENABLE_TX_بھریا 		1 << 1
#تعریف_کرو ENABLE_TX_خالی_تھاواں 	1 << 0
#تعریف_کرو UARTX_بفر_ناپ       10000

/* UART control register */
#تعریف_کرو STOP_بٹ(x) ( (x & 3) << 1) /*! 00 - 1 stop bits, 01 - 1.5 stop bits; 10 - 2 stop bits; 11 unused */
#تعریف_کرو PARITY(x) ( (x & 3)  << 3 ) /*! 00 --- No parity; 01 -Odd Parity; 10 - Even Parity;  11 - Unused */
#تعریف_کرو UART_TX_RX_LEN(x)       ( (x & 0x1F) << 5) /*! Maximum length 32 bits */

خارجي uart_struct *uart_instance[MAX_UART_گنتی];
خارجي بنانشانی حرف uart0_complete;
خارجي بنانشانی حرف uart1_complete;
خارجي بنانشانی حرف uart2_complete;
خارجي بنانشانی صحيح uart0_tx_isr_گنتی ;
خارجي بنانشانی صحيح uart0_rcv_isr_گنتی ;
خارجي بنانشانی صحيح uart1_tx_isr_گنتی ;
خارجي بنانشانی صحيح uart1_rcv_isr_گنتی ;
خارجي بنانشانی صحيح uart2_tx_isr_گنتی ;
خارجي بنانشانی صحيح uart2_rcv_isr_گنتی ;

#جے_تعریف_شدہ USE_رکاوٹ
خارجي بنانشانی حرف u0_rcv_char[UARTX_بفر_ناپ];
خارجي بنانشانی حرف u1_rcv_char[UARTX_بفر_ناپ];
خارجي بنانشانی حرف u2_rcv_char[UARTX_بفر_ناپ];
#جے_انت

فراغ uart_init(فراغ);
فراغ سیٹ_baud_شرح(uart_struct * uart_instance, بنانشانی صحيح baudrate);
فراغ enable_uart_interrupts(uart_struct * uart_instance, بنانشانی حرف رکاوٹ);
فراغ سیٹ_uart_rx_حد(uart_struct * uart_instance, بنانشانی حرف rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, حرف * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, حرف * ptr_string) ;
فراغ flush_uart(uart_struct * instance);

#جے_تعریف_شدہ USE_رکاوٹ
بنانشانی حرف uart0_isr(فراغ);
بنانشانی حرف uart1_isr(فراغ);
بنانشانی حرف uart2_isr(فراغ);
#جے_انت

صحيح is_خالی_تھاواں(فراغ);

#تعریف_رد حرف_لکھو
صحيح حرف_لکھو(صحيح ch);

#تعریف_رد getchar
صحيح getchar(فراغ);

#جے_انت
