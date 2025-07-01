/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		: uart01_interrupt_test
 * Created date			        :  26.02.2019
 * Brief Description of file    :  UART 1 Interrupt test case
 * Name of Author    	        :  Hari Kheshav S K
 * Email ID                     :  harikheshav@gmail.com

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

 ***************************************************************************/
//#include "gpiov2.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include "log.h"
#include "pinmux.h"
#ifdef BSOC
#include "uartv3.h"
#else
#include "uart.h"
#endif

# define UART1 1
//# define UART2 0

unsigned int uart0_prev_rcv_isr_count_flag = 0;
unsigned int uart1_prev_rcv_isr_count_flag = 0;
unsigned int uart2_prev_rcv_isr_count_flag = 0;

unsigned int uart0_prev_tx_isr_count_flag = 0;
unsigned int uart1_prev_tx_isr_count_flag = 0;
unsigned int uart2_prev_tx_isr_count_flag = 0;
extern volatile unsigned int* pinmux_config_reg;


/**
 * @brief Initialize global variables used in UART interrupt handling.
 *
 * @details
 * This function resets all UART-related state variables to their default values.
 * It is typically called once during system startup or before a new test begins.
 *
 * Specifically:
 * - Sets UART transmission and reception completion flags to 0.
 * - Clears ISR (Interrupt Service Routine) counters for UART0, UART1, and UART2.
 * - Resets the receive buffers (u0_rcv_char, u1_rcv_char, u2_rcv_char) to null.
 * - Clears previous ISR count flags used for checking ISR progress.
 */

void init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_count = 0;
	uart0_rcv_isr_count = 0;
	uart1_tx_isr_count = 0;
	uart1_rcv_isr_count = 0;
	uart2_tx_isr_count = 0;
	uart2_rcv_isr_count = 0;
	memset(u0_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u2_rcv_char,'\0', UARTX_BUFFER_SIZE);
	uart0_prev_rcv_isr_count_flag = 0;
	uart1_prev_rcv_isr_count_flag = 0;
	uart2_prev_rcv_isr_count_flag = 0;

	uart0_prev_tx_isr_count_flag = 0;
	uart1_prev_tx_isr_count_flag = 0;
	uart2_prev_tx_isr_count_flag = 0;
}


/**
 * @brief Main function to initialize UARTs and test UART1 interrupt-driven reception of big file upto 20kb.
 *
 * @details
 * - Enables UART clocks and configures pinmux.
 * - Sets baud rates and initializes global variables.
 * - Configures PLIC and assigns UART1/UART2 ISRs.
 * - Enables global interrupts.
 * - Sends test strings  or file through cutecom using UART0 and UART1.
 * - Monitors UART1 ISR counts and prints received buffer periodically.
 *
 * Note: This test assumes `UART1` is defined for conditional compilation.want UART2 to test enable UART2 at compile time.
 * 
 * USE CUTECOM to send files enable cr lf options
 */

int main(void)
{
#ifdef BSOC
	uart_instance[0]->clk_enable = UART_CLK_EN;
	uart_instance[1]->clk_enable = UART_CLK_EN;
	uart_instance[2]->clk_enable = UART_CLK_EN;
	set_baud_rate(uart_instance[0], 115200);
	set_baud_rate(uart_instance[1], 115200);
	set_baud_rate(uart_instance[2], 115200);
	set_pinmux_configuration(GROUP0_AF2_UART1_NM | GROUP0_AF3_UART2_NM, GROUPx_DEFAULT_GPIOs, GROUPx_DEFAULT_GPIOs, GROUPx_DEFAULT_GPIOs);
#endif
#ifndef BSOC
	*(pinmux_config_reg) = 0x55;
#endif
	write_uart_string(uart_instance[0], "\nHello World from UART0");
	init_variables();
	plic_init();
	configure_interrupt(PLIC_INTERRUPT_28);
	isr_table[PLIC_INTERRUPT_28] = uart1_isr;
	configure_interrupt(PLIC_INTERRUPT_29);
	isr_table[PLIC_INTERRUPT_29] = uart2_isr;
	enable_machine_global_interrupts();
#ifdef UART1
	printf("\tUart0 big file test using uart 1\n");
	uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
	uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
	enable_uart_interrupts(uart_instance[1], ENABLE_RX_NOT_EMPTY | ENABLE_RX_FULL);
	printf("Before Tx\n");
	printf("\n Status Register: %x", uart_instance[1]->status);
	int i = 0;
	write_uart_string(uart_instance[1], "\nUART 1 uart 0 Interrupt TeSt");
	write_uart_string(uart_instance[0], "\nUART 0 uart 1 Interrupt TeSt");
	while (1)
	{
		delay_loop(2000, 1000);
		if (uart1_prev_tx_isr_count_flag != uart1_tx_isr_count)
		{
			uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
		}
		if (uart1_prev_rcv_isr_count_flag != uart1_rcv_isr_count)
		{
			uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
		}
		if (i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_count] = '\0';
			printf("\n Rcv ISR Count Flag: %d", uart1_rcv_isr_count);
			printf("\n recv. Chars: %s", u1_rcv_char);
			i = 0;
			uart1_rcv_isr_count = 0;
			memset(u1_rcv_char, '\0', UARTX_BUFFER_SIZE);
		}
	};
#endif
#ifdef UART2
	// enable_uart_interrupts(uart_instance[2], 0);
	printf("\nUart0 big file test using uart 2\n");
	uart2_prev_tx_isr_count_flag = uart2_tx_isr_count;
	printf("Before Tx\n");
	uart2_prev_rcv_isr_count_flag = uart2_rcv_isr_count;
	printf("Before Tx\n");
	enable_uart_interrupts(uart_instance[2], ENABLE_RX_NOT_EMPTY | ENABLE_RX_FULL);
	printf("Before Tx\n");
	printf("\n Status Register: %x", uart_instance[2]->status);
	int i = 0;
	write_uart_string(uart_instance[2], "\nUART 2 - uart 0 Interrupt TeSt");
	write_uart_string(uart_instance[0], "\nUART 0 - uart 2Interrupt TeSt");
	while (1)
	{
		delay_loop(2000, 1000);
		if (uart2_prev_tx_isr_count_flag != uart2_tx_isr_count)
		{
			uart2_prev_tx_isr_count_flag = uart2_tx_isr_count;
		}
		if (uart2_prev_rcv_isr_count_flag != uart2_rcv_isr_count)
		{
			uart2_prev_rcv_isr_count_flag = uart2_rcv_isr_count;
		}
		if (i++ >= 10)
		{
			u2_rcv_char[++uart2_rcv_isr_count] = '\0';
			printf("\n Rcv ISR Count Flag: %d", uart2_rcv_isr_count);
			printf("\n recv. Chars: %s", u2_rcv_char);
			i = 0;
			uart2_rcv_isr_count = 0;
			memset(u2_rcv_char, '\0', UARTX_BUFFER_SIZE);
			// break;
		}
	};
#endif
	return 0;
}