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
#अन्तर्भाव "pinmux.h"
#अन्तर्भाव "traps.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "plic_driver.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"



अचिह्नित पूर्णाङ्क uart0_पूर्व_rcv_isr_गणनम्_flag = 0;
अचिह्नित पूर्णाङ्क uart1_पूर्व_rcv_isr_गणनम्_flag = 0;
अचिह्नित पूर्णाङ्क uart2_पूर्व_rcv_isr_गणनम्_flag = 0;

अचिह्नित पूर्णाङ्क uart0_पूर्व_tx_isr_गणनम्_flag = 0;
अचिह्नित पूर्णाङ्क uart1_पूर्व_tx_isr_गणनम्_flag = 0;
अचिह्नित पूर्णाङ्क uart2_पूर्व_tx_isr_गणनम्_flag = 0;


शून्य init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_गणनम् = 0;
	uart0_rcv_isr_गणनम् = 0;
	uart1_tx_isr_गणनम् = 0;
	uart1_rcv_isr_गणनम् = 0;
	uart2_tx_isr_गणनम् = 0;
	uart2_rcv_isr_गणनम् = 0;
	स्मृतिं_पूरय(u0_rcv_char,'\0', UARTX_बफर_आकार);
	स्मृतिं_पूरय(u1_rcv_char,'\0', UARTX_बफर_आकार);
	स्मृतिं_पूरय(u2_rcv_char,'\0', UARTX_बफर_आकार);
	uart0_पूर्व_rcv_isr_गणनम्_flag = 0;
	uart1_पूर्व_rcv_isr_गणनम्_flag = 0;
	uart2_पूर्व_rcv_isr_गणनम्_flag = 0;

	uart0_पूर्व_tx_isr_गणनम्_flag = 0;
	uart1_पूर्व_tx_isr_गणनम्_flag = 0;
	uart2_पूर्व_tx_isr_गणनम्_flag = 0;
}
बाह्य चञ्चल अचिह्नित पूर्णाङ्क* pinmux_config_reg;



पूर्णाङ्क मुख्यम्(शून्य){


	पञ्जिका uint32_t retval;
	पूर्णाङ्क i;
	init_variables();

	प्रारूप_लिख("\n---------------Uart 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	समुच्चयः_baud_दरः(uart_instance[0], 19200);
	समुच्चयः_baud_दरः(uart_instance[1], 19200);
	plic_init();

	configure_व्यवधानम्(PLIC_व्यवधानम्_26);
	isr_सारणी[PLIC_व्यवधानम्_26] = uart1_isr;

	// Enable Global (PLIC) interrupts.
	asm चञ्चल("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm चञ्चल("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm चञ्चल(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	प्रारूप_लिख("\n retval = %x", retval);
	asm चञ्चल(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	प्रारूप_लिख("\t retval = %x", retval);

	asm चञ्चल(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	प्रारूप_लिख("\t retval = %x", retval);


	uart1_पूर्व_tx_isr_गणनम्_flag = uart1_tx_isr_गणनम्;
	uart1_पूर्व_rcv_isr_गणनम्_flag = uart1_rcv_isr_गणनम्;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_रिक्तानि | ENABLE_RX_पूर्णम्);
	प्रारूप_लिख("\n Before Tx: Status Register= %x \n", uart_instance[1]->स्थितिः_2);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 0: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 1: Type the chars you want to transmit-----------\n");
	यावत्(1)
	{
#यदि 0
		यदि(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		अन्यथा
			write_uart_string(uart_instance[1], "tEsT");
#यदि_अन्तः
		delay_loop(2000,2000);
		यदि(uart1_पूर्व_tx_isr_गणनम्_flag != uart1_tx_isr_गणनम्)
		{
			uart1_पूर्व_tx_isr_गणनम्_flag = uart1_tx_isr_गणनम्;
		}
		यदि(uart1_पूर्व_rcv_isr_गणनम्_flag != uart1_rcv_isr_गणनम्)
		{
			uart1_पूर्व_rcv_isr_गणनम्_flag = uart1_rcv_isr_गणनम्;
		}
		यदि(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_गणनम्] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			प्रारूप_लिख("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_गणनम्-1);
			i = 0;
			uart1_rcv_isr_गणनम् = 0;
			स्मृतिं_पूरय(u1_rcv_char,'\0', UARTX_बफर_आकार);
			//break;
		}
	};


	प्रत्यागम 0;
}
