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
#ضمن "pinmux.h"
#ضمن "traps.h"
#ضمن "platform.h"
#ضمن "plic_driver.h"
#ضمن "log.h"
#ضمن "uart.h"



بینښه صحيح uart0_prev_rcv_isr_شمېر_flag = 0;
بینښه صحيح uart1_prev_rcv_isr_شمېر_flag = 0;
بینښه صحيح uart2_prev_rcv_isr_شمېر_flag = 0;

بینښه صحيح uart0_prev_tx_isr_شمېر_flag = 0;
بینښه صحيح uart1_prev_tx_isr_شمېر_flag = 0;
بینښه صحيح uart2_prev_tx_isr_شمېر_flag = 0;


فراغ init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_شمېر = 0;
	uart0_rcv_isr_شمېر = 0;
	uart1_tx_isr_شمېر = 0;
	uart1_rcv_isr_شمېر = 0;
	uart2_tx_isr_شمېر = 0;
	uart2_rcv_isr_شمېر = 0;
	memset(u0_rcv_char,'\0', UARTX_بفر_اندازه);
	memset(u1_rcv_char,'\0', UARTX_بفر_اندازه);
	memset(u2_rcv_char,'\0', UARTX_بفر_اندازه);
	uart0_prev_rcv_isr_شمېر_flag = 0;
	uart1_prev_rcv_isr_شمېر_flag = 0;
	uart2_prev_rcv_isr_شمېر_flag = 0;

	uart0_prev_tx_isr_شمېر_flag = 0;
	uart1_prev_tx_isr_شمېر_flag = 0;
	uart2_prev_tx_isr_شمېر_flag = 0;
}
خارجي متطاير بینښه صحيح* pinmux_config_reg;



صحيح اصلي(فراغ){


	سجل uint32_t retval;
	صحيح i;
	init_variables();

	چاپ_کړه("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	سېټ_baud_شرح(uart_instance[0], 19200);
	سېټ_baud_شرح(uart_instance[1], 19200);
	plic_init();

	configure_مداخله(PLIC_مداخله_26);
	isr_جدول[PLIC_مداخله_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm متطاير("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm متطاير("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm متطاير(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	چاپ_کړه("\n retval = %x", retval);
	asm متطاير(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	چاپ_کړه("\t retval = %x", retval);

	asm متطاير(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	چاپ_کړه("\t retval = %x", retval);


	uart1_prev_tx_isr_شمېر_flag = uart1_tx_isr_شمېر;
	uart1_prev_rcv_isr_شمېر_flag = uart1_rcv_isr_شمېر;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_تشه | ENABLE_RX_ډک);
	چاپ_کړه("\n Before Tx: Status Register= %x \n", uart_instance[1]->حالت_2);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	طالما(1)
	{
#إذا 0
		إذا(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		وإلا
			write_uart_string(uart_instance[1], "tEsT");
#د_که_پای
		delay_loop(2000,2000);
		إذا(uart1_prev_tx_isr_شمېر_flag != uart1_tx_isr_شمېر)
		{
			uart1_prev_tx_isr_شمېر_flag = uart1_tx_isr_شمېر;
		}
		إذا(uart1_prev_rcv_isr_شمېر_flag != uart1_rcv_isr_شمېر)
		{
			uart1_prev_rcv_isr_شمېر_flag = uart1_rcv_isr_شمېر;
		}
		إذا(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_شمېر] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			چاپ_کړه("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_شمېر-1);
			i = 0;
			uart1_rcv_isr_شمېر = 0;
			memset(u1_rcv_char,'\0', UARTX_بفر_اندازه);
			//break;
		}
	};


	أرجع 0;
}
