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

#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "uart.h"
#অন্তর্ভাব "utils.h"
#অন্তর্ভাব "traps.h"
#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "plic_driver.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "defines.h"
#অন্তর্ভাব "memory.h"

শূন্য handle_button_press(__attribute__((unused)) uint32_t অঙ্ক);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
শূন্য handle_button_press(__attribute__((unused)) uint32_t অঙ্ক)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
পূর্ণসংখ্যা প্রধান(শূন্য){
	নিবন্ধ unsigned পূর্ণসংখ্যা retval;
	পূর্ণসংখ্যা i;

	plic_init();

	জন্য(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i);
	}
	printf("\n");
	asm("ebreak");

	জন্য(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_disable(i);
	}
	printf("\n");

	asm("ebreak");

	জন্য(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i + 1);
	}
	printf("\n");

	asm("ebreak");

	যখন(1){
		i++;

		যদি((i%10000000) == 0){

			asm অস্থির(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			printf("mip = %u\n", retval);
		}
	}
	ফেরত 0;
}
