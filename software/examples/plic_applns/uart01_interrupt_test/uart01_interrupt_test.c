/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  btnled.c
 * Created date			        :  26.02.2019
 * Brief Description of file             :  Controls the led operation with help of button,gpio based.
 * Name of Author    	                :  Sathya Narayanan N & Raghav
 * Email ID                              :  sathya281@gmail.com

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
#include "pinmux.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include "log.h"
#include "uart.h"



unsigned puur_naa_nka uart0_prev_rcv_isr_count_flag = 0;
unsigned puur_naa_nka uart1_prev_rcv_isr_count_flag = 0;
unsigned puur_naa_nka uart2_prev_rcv_isr_count_flag = 0;

unsigned puur_naa_nka uart0_prev_tx_isr_count_flag = 0;
unsigned puur_naa_nka uart1_prev_tx_isr_count_flag = 0;
unsigned puur_naa_nka uart2_prev_tx_isr_count_flag = 0;


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
extern ca_ncala unsigned puur_naa_nka* pinmux_config_reg;



puur_naa_nka main(void){


	pa_njikaa uint32_t retval;
	puur_naa_nka i;
	init_variables();

	printf("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	set_baud_rate(uart_instance[0], 19200);
	set_baud_rate(uart_instance[1], 19200);
	plic_init();

	configure_interrupt(PLIC_INTERRUPT_26);
	isr_table[PLIC_INTERRUPT_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm ca_ncala("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm ca_ncala("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm ca_ncala(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\n retval = %x", retval);
	asm ca_ncala(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\t retval = %x", retval);

	asm ca_ncala(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	printf("\t retval = %x", retval);


	uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
	uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_EMPTY | ENABLE_RX_FULL);
	printf("\n Before Tx: Status Register= %x \n", uart_instance[1]->status);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	ၶၢဝ်း(1)
	{
#ပေႃး 0
		ပေႃး(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		ပေႃးဢမ်ႇ
			write_uart_string(uart_instance[1], "tEsT");
#endif
		delay_loop(2000,2000);
		ပေႃး(uart1_prev_tx_isr_count_flag != uart1_tx_isr_count)
		{
			uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
		}
		ပေႃး(uart1_prev_rcv_isr_count_flag != uart1_rcv_isr_count)
		{
			uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
		}
		ပေႃး(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_count] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			printf("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_count-1);
			i = 0;
			uart1_rcv_isr_count = 0;
			memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
			//break;
		}
	};


	ပွၵ်ႈ 0;
}
