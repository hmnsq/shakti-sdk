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
#شامل "pinmux.h"
#شامل "traps.h"
#شامل "platform.h"
#شامل "plic_driver.h"
#شامل "log.h"
#شامل "uart.h"



غیرعلامتی صحیح uart0_پچھلا_rcv_isr_گنتی_flag = 0;
غیرعلامتی صحیح uart1_پچھلا_rcv_isr_گنتی_flag = 0;
غیرعلامتی صحیح uart2_پچھلا_rcv_isr_گنتی_flag = 0;

غیرعلامتی صحیح uart0_پچھلا_tx_isr_گنتی_flag = 0;
غیرعلامتی صحیح uart1_پچھلا_tx_isr_گنتی_flag = 0;
غیرعلامتی صحیح uart2_پچھلا_tx_isr_گنتی_flag = 0;


خالی init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_گنتی = 0;
	uart0_rcv_isr_گنتی = 0;
	uart1_tx_isr_گنتی = 0;
	uart1_rcv_isr_گنتی = 0;
	uart2_tx_isr_گنتی = 0;
	uart2_rcv_isr_گنتی = 0;
	memset(u0_rcv_char,'\0', UARTX_بفر_سائز);
	memset(u1_rcv_char,'\0', UARTX_بفر_سائز);
	memset(u2_rcv_char,'\0', UARTX_بفر_سائز);
	uart0_پچھلا_rcv_isr_گنتی_flag = 0;
	uart1_پچھلا_rcv_isr_گنتی_flag = 0;
	uart2_پچھلا_rcv_isr_گنتی_flag = 0;

	uart0_پچھلا_tx_isr_گنتی_flag = 0;
	uart1_پچھلا_tx_isr_گنتی_flag = 0;
	uart2_پچھلا_tx_isr_گنتی_flag = 0;
}
خارجی متلون غیرعلامتی صحیح* pinmux_config_reg;



صحیح مین(خالی){


	اندراج uint32_t retval;
	صحیح i;
	init_variables();

	لکھو("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	سیٹ_baud_شرح(uart_instance[0], 19200);
	سیٹ_baud_شرح(uart_instance[1], 19200);
	plic_init();

	configure_مداخلت(PLIC_مداخلت_26);
	isr_جدول[PLIC_مداخلت_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm متلون("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm متلون("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm متلون(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	لکھو("\n retval = %x", retval);
	asm متلون(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	لکھو("\t retval = %x", retval);

	asm متلون(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	لکھو("\t retval = %x", retval);


	uart1_پچھلا_tx_isr_گنتی_flag = uart1_tx_isr_گنتی;
	uart1_پچھلا_rcv_isr_گنتی_flag = uart1_rcv_isr_گنتی;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_خالی_خانے | ENABLE_RX_بھرا);
	لکھو("\n Before Tx: Status Register= %x \n", uart_instance[1]->حالت_3);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	جب(1)
	{
#اگر 0
		اگر(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		ورنہ
			write_uart_string(uart_instance[1], "tEsT");
#اگر_ختم
		delay_loop(2000,2000);
		اگر(uart1_پچھلا_tx_isr_گنتی_flag != uart1_tx_isr_گنتی)
		{
			uart1_پچھلا_tx_isr_گنتی_flag = uart1_tx_isr_گنتی;
		}
		اگر(uart1_پچھلا_rcv_isr_گنتی_flag != uart1_rcv_isr_گنتی)
		{
			uart1_پچھلا_rcv_isr_گنتی_flag = uart1_rcv_isr_گنتی;
		}
		اگر(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_گنتی] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			لکھو("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_گنتی-1);
			i = 0;
			uart1_rcv_isr_گنتی = 0;
			memset(u1_rcv_char,'\0', UARTX_بفر_سائز);
			//break;
		}
	};


	واپس 0;
}
