/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: interrupt_demo.c
 * Brief Description of file    : A application to demonstrate working of plic
 * Name of Author    	        : Sathya Narayanan N 
 * Email ID                     : sathya281@gmail.com

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
/**
@file interrupt_demo.c
@brief A application to demonstrate working of plic
@detail Thsi file contains an application to demonstrate the working of plic.
The interrupts are enabled for a gpio pin. Once the button connected to the gpio
 pin is pressed. An interrupt is generated and it is handled by the isr.
*/

#અન્તર્ભાવ "gpio.h"
#અન્તર્ભાવ "uart.h"
#અન્તર્ભાવ "utils.h"
#અન્તર્ભાવ "traps.h"
#અન્તર્ભાવ "platform.h"
#અન્તર્ભાવ "plic_driver.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "defines.h"
#અન્તર્ભાવ "memory.h"

શૂન્ય handle_button_press(__attribute__((unused)) uint32_t અંક);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
શૂન્ય handle_button_press(__attribute__((unused)) uint32_t અંક)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
પૂર્ણાંક મુખ્ય(શૂન્ય){
	નોંધણી unsigned પૂર્ણાંક retval;
	પૂર્ણાંક i;

	plic_init();

	માટે(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i);
	}
	printf("\n");
	asm("ebreak");

	માટે(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_disable(i);
	}
	printf("\n");

	asm("ebreak");

	માટે(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i + 1);
	}
	printf("\n");

	asm("ebreak");

	જ્યારે(1){
		i++;

		જો((i%10000000) == 0){

			asm અસ્થિર(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			printf("mip = %u\n", retval);
		}
	}
	પાછા 0;
}
