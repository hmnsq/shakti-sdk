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
#అన్తర్భావ "pinmux.h"
#అన్తర్భావ "traps.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "plic_driver.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"



గుర్తులేని పూర్ణాంకం uart0_prev_rcv_isr_లెక్క_flag = 0;
గుర్తులేని పూర్ణాంకం uart1_prev_rcv_isr_లెక్క_flag = 0;
గుర్తులేని పూర్ణాంకం uart2_prev_rcv_isr_లెక్క_flag = 0;

గుర్తులేని పూర్ణాంకం uart0_prev_tx_isr_లెక్క_flag = 0;
గుర్తులేని పూర్ణాంకం uart1_prev_tx_isr_లెక్క_flag = 0;
గుర్తులేని పూర్ణాంకం uart2_prev_tx_isr_లెక్క_flag = 0;


శూన్య init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_లెక్క = 0;
	uart0_rcv_isr_లెక్క = 0;
	uart1_tx_isr_లెక్క = 0;
	uart1_rcv_isr_లెక్క = 0;
	uart2_tx_isr_లెక్క = 0;
	uart2_rcv_isr_లెక్క = 0;
	memset(u0_rcv_char,'\0', UARTX_బఫరు_కొలత);
	memset(u1_rcv_char,'\0', UARTX_బఫరు_కొలత);
	memset(u2_rcv_char,'\0', UARTX_బఫరు_కొలత);
	uart0_prev_rcv_isr_లెక్క_flag = 0;
	uart1_prev_rcv_isr_లెక్క_flag = 0;
	uart2_prev_rcv_isr_లెక్క_flag = 0;

	uart0_prev_tx_isr_లెక్క_flag = 0;
	uart1_prev_tx_isr_లెక్క_flag = 0;
	uart2_prev_tx_isr_లెక్క_flag = 0;
}
బాహ్య అస్థిర గుర్తులేని పూర్ణాంకం* pinmux_config_reg;



పూర్ణాంకం ప్రధాన(శూన్య){


	నమోదు uint32_t retval;
	పూర్ణాంకం i;
	init_variables();

	రాయి("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	సమితి_baud_రేటు(uart_instance[0], 19200);
	సమితి_baud_రేటు(uart_instance[1], 19200);
	plic_init();

	configure_అంతరాయం(PLIC_అంతరాయం_26);
	isr_పట్టిక[PLIC_అంతరాయం_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm అస్థిర("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm అస్థిర("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm అస్థిర(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	రాయి("\n retval = %x", retval);
	asm అస్థిర(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	రాయి("\t retval = %x", retval);

	asm అస్థిర(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	రాయి("\t retval = %x", retval);


	uart1_prev_tx_isr_లెక్క_flag = uart1_tx_isr_లెక్క;
	uart1_prev_rcv_isr_లెక్క_flag = uart1_rcv_isr_లెక్క;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_ఖాళీలు | ENABLE_RX_నిండిన);
	రాయి("\n Before Tx: Status Register= %x \n", uart_instance[1]->స్థితి_3);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	అయితే(1)
	{
#ఒకవేళ 0
		ఒకవేళ(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		లేకపోతే
			write_uart_string(uart_instance[1], "tEsT");
#అయితే_ముగింపు
		delay_loop(2000,2000);
		ఒకవేళ(uart1_prev_tx_isr_లెక్క_flag != uart1_tx_isr_లెక్క)
		{
			uart1_prev_tx_isr_లెక్క_flag = uart1_tx_isr_లెక్క;
		}
		ఒకవేళ(uart1_prev_rcv_isr_లెక్క_flag != uart1_rcv_isr_లెక్క)
		{
			uart1_prev_rcv_isr_లెక్క_flag = uart1_rcv_isr_లెక్క;
		}
		ఒకవేళ(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_లెక్క] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			రాయి("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_లెక్క-1);
			i = 0;
			uart1_rcv_isr_లెక్క = 0;
			memset(u1_rcv_char,'\0', UARTX_బఫరు_కొలత);
			//break;
		}
	};


	తిరిగి 0;
}
