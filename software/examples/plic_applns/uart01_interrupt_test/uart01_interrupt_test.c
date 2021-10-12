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


int main(void){

	register uint32_t retval;
	int i;

	plic_init();

	configure_interrupt(PLIC_INTERRUPT_2);
	isr_table[PLIC_INTERRUPT_2] = isr_default;

	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm volatile(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\n retval = %x", retval);
	asm volatile(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\t retval = %x", retval);

	asm volatile(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	printf("\t retval = %x", retval);


	write_uart_string(uart_instance[0], "\n---------------UART 0: TX intrr start --------------\n");
	printf("\n Before Tx: Status Register= %x \n", uart_instance[0]->status);
   while(!(uart_instance[0]-> status & STS_TX_EMPTY));
	enable_uart_interrupts(uart_instance[0], ENABLE_TX_FULL);
   printf("0123456789abcdefgh");//ij-%d-klmnopqrstuvwxyz", uart_instance[0]->status);
   //uart_instance[0]->ien = 0;
   //printf("0123456789abcdefghijklmnopqrstuvwxyz: %x", uart_instance[0]->status);

   while(1);
}
