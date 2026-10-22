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
#समावेश "pinmux.h"
#समावेश "traps.h"
#समावेश "platform.h"
#समावेश "plic_driver.h"
#समावेश "log.h"
#समावेश "uart.h"



अचिन्हित पूर्णांक uart0_पूर्व_rcv_isr_गिनती_flag = 0;
अचिन्हित पूर्णांक uart1_पूर्व_rcv_isr_गिनती_flag = 0;
अचिन्हित पूर्णांक uart2_पूर्व_rcv_isr_गिनती_flag = 0;

अचिन्हित पूर्णांक uart0_पूर्व_tx_isr_गिनती_flag = 0;
अचिन्हित पूर्णांक uart1_पूर्व_tx_isr_गिनती_flag = 0;
अचिन्हित पूर्णांक uart2_पूर्व_tx_isr_गिनती_flag = 0;


व्योम init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_गिनती = 0;
	uart0_rcv_isr_गिनती = 0;
	uart1_tx_isr_गिनती = 0;
	uart1_rcv_isr_गिनती = 0;
	uart2_tx_isr_गिनती = 0;
	uart2_rcv_isr_गिनती = 0;
	स_रखो(u0_rcv_char,'\0', UARTX_बफर_आकार);
	स_रखो(u1_rcv_char,'\0', UARTX_बफर_आकार);
	स_रखो(u2_rcv_char,'\0', UARTX_बफर_आकार);
	uart0_पूर्व_rcv_isr_गिनती_flag = 0;
	uart1_पूर्व_rcv_isr_गिनती_flag = 0;
	uart2_पूर्व_rcv_isr_गिनती_flag = 0;

	uart0_पूर्व_tx_isr_गिनती_flag = 0;
	uart1_पूर्व_tx_isr_गिनती_flag = 0;
	uart2_पूर्व_tx_isr_गिनती_flag = 0;
}
बाह्य अस्थिर अचिन्हित पूर्णांक* pinmux_config_reg;



पूर्णांक मुख्य(व्योम){


	रेजिस्टर uint32_t retval;
	पूर्णांक i;
	init_variables();

	म_लिखो("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	set_baud_rate(uart_instance[0], 19200);
	set_baud_rate(uart_instance[1], 19200);
	plic_init();

	configure_interrupt(PLIC_INTERRUPT_26);
	isr_table[PLIC_INTERRUPT_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	यंत्र अस्थिर("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	यंत्र अस्थिर("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	यंत्र अस्थिर(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	म_लिखो("\n retval = %x", retval);
	यंत्र अस्थिर(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	म_लिखो("\t retval = %x", retval);

	यंत्र अस्थिर(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	म_लिखो("\t retval = %x", retval);


	uart1_पूर्व_tx_isr_गिनती_flag = uart1_tx_isr_गिनती;
	uart1_पूर्व_rcv_isr_गिनती_flag = uart1_rcv_isr_गिनती;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_EMPTY | ENABLE_RX_FULL);
	म_लिखो("\n Before Tx: Status Register= %x \n", uart_instance[1]->status);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	जबतक(1)
	{
#अगर 0
		अगर(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		अन्यथा
			write_uart_string(uart_instance[1], "tEsT");
#पूर्ण_अगर
		delay_loop(2000,2000);
		अगर(uart1_पूर्व_tx_isr_गिनती_flag != uart1_tx_isr_गिनती)
		{
			uart1_पूर्व_tx_isr_गिनती_flag = uart1_tx_isr_गिनती;
		}
		अगर(uart1_पूर्व_rcv_isr_गिनती_flag != uart1_rcv_isr_गिनती)
		{
			uart1_पूर्व_rcv_isr_गिनती_flag = uart1_rcv_isr_गिनती;
		}
		अगर(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_गिनती] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			म_लिखो("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_गिनती-1);
			i = 0;
			uart1_rcv_isr_गिनती = 0;
			स_रखो(u1_rcv_char,'\0', UARTX_बफर_आकार);
			//break;
		}
	};


	वापस 0;
}
