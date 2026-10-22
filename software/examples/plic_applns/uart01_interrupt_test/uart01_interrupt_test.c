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
#ਅਨ੍ਤਰ੍ਭਾਵ "pinmux.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"



ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;

ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_prev_tx_isr_ਗਿਣਤੀ_flag = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_prev_tx_isr_ਗਿਣਤੀ_flag = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_prev_tx_isr_ਗਿਣਤੀ_flag = 0;


ਖਾਲੀ init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_ਗਿਣਤੀ = 0;
	uart0_rcv_isr_ਗਿਣਤੀ = 0;
	uart1_tx_isr_ਗਿਣਤੀ = 0;
	uart1_rcv_isr_ਗਿਣਤੀ = 0;
	uart2_tx_isr_ਗਿਣਤੀ = 0;
	uart2_rcv_isr_ਗਿਣਤੀ = 0;
	memset(u0_rcv_char,'\0', UARTX_ਬਫਰ_ਮਾਪ);
	memset(u1_rcv_char,'\0', UARTX_ਬਫਰ_ਮਾਪ);
	memset(u2_rcv_char,'\0', UARTX_ਬਫਰ_ਮਾਪ);
	uart0_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;
	uart1_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;
	uart2_prev_rcv_isr_ਗਿਣਤੀ_flag = 0;

	uart0_prev_tx_isr_ਗਿਣਤੀ_flag = 0;
	uart1_prev_tx_isr_ਗਿਣਤੀ_flag = 0;
	uart2_prev_tx_isr_ਗਿਣਤੀ_flag = 0;
}
ਬਾਹਰੀ ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* pinmux_config_reg;



ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ){


	ਰਜਿਸਟਰ uint32_t retval;
	ਪੂਰਨ i;
	init_variables();

	ਲਿਖੋ("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	ਸੈੱਟ_baud_ਦਰ(uart_instance[0], 19200);
	ਸੈੱਟ_baud_ਦਰ(uart_instance[1], 19200);
	plic_init();

	configure_ਰੁਕਾਵਟ(PLIC_ਰੁਕਾਵਟ_26);
	isr_ਸਾਰਣੀ[PLIC_ਰੁਕਾਵਟ_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm ਅਸਥਿਰ("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm ਅਸਥਿਰ("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm ਅਸਥਿਰ(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	ਲਿਖੋ("\n retval = %x", retval);
	asm ਅਸਥਿਰ(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	ਲਿਖੋ("\t retval = %x", retval);

	asm ਅਸਥਿਰ(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	ਲਿਖੋ("\t retval = %x", retval);


	uart1_prev_tx_isr_ਗਿਣਤੀ_flag = uart1_tx_isr_ਗਿਣਤੀ;
	uart1_prev_rcv_isr_ਗਿਣਤੀ_flag = uart1_rcv_isr_ਗਿਣਤੀ;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ | ENABLE_RX_ਭਰਿਆ);
	ਲਿਖੋ("\n Before Tx: Status Register= %x \n", uart_instance[1]->ਸਥਿਤੀ_2);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	ਜਦੋਂ(1)
	{
#ਜੇ 0
		ਜੇ(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		ਨਹੀਂਤਾਂ
			write_uart_string(uart_instance[1], "tEsT");
#ਜੇ_ਅੰਤ
		delay_loop(2000,2000);
		ਜੇ(uart1_prev_tx_isr_ਗਿਣਤੀ_flag != uart1_tx_isr_ਗਿਣਤੀ)
		{
			uart1_prev_tx_isr_ਗਿਣਤੀ_flag = uart1_tx_isr_ਗਿਣਤੀ;
		}
		ਜੇ(uart1_prev_rcv_isr_ਗਿਣਤੀ_flag != uart1_rcv_isr_ਗਿਣਤੀ)
		{
			uart1_prev_rcv_isr_ਗਿਣਤੀ_flag = uart1_rcv_isr_ਗਿਣਤੀ;
		}
		ਜੇ(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_ਗਿਣਤੀ] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			ਲਿਖੋ("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_ਗਿਣਤੀ-1);
			i = 0;
			uart1_rcv_isr_ਗਿਣਤੀ = 0;
			memset(u1_rcv_char,'\0', UARTX_ਬਫਰ_ਮਾਪ);
			//break;
		}
	};


	ਵਾਪਸ 0;
}
