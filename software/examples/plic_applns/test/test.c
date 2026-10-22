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

#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "traps.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "plic_driver.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "defines.h"
#ಅನ್ತರ್ಭಾವ "memory.h"

ಶೂನ್ಯ handle_button_press(__attribute__((unused)) uint32_t ಅಂಕೆ);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
ಶೂನ್ಯ handle_button_press(__attribute__((unused)) uint32_t ಅಂಕೆ)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ){
	ಪಞ್ಜಿಕಾ unsigned ಪೂರ್ಣಾಙ್ಕ retval;
	ಪೂರ್ಣಾಙ್ಕ i;

	plic_init();

	ಪ್ರತಿ(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i);
	}
	printf("\n");
	asm("ebreak");

	ಪ್ರತಿ(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_disable(i);
	}
	printf("\n");

	asm("ebreak");

	ಪ್ರತಿ(i=1;i<33;i++)
	{
		printf("i %d\n",i);
		interrupt_enable(i + 1);
	}
	printf("\n");

	asm("ebreak");

	ಯಾವತ್(1){
		i++;

		ಯದಿ((i%10000000) == 0){

			asm ಚಞ್ಚಲ(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			printf("mip = %u\n", retval);
		}
	}
	ಪ್ರತ್ಯಾಗಮ 0;
}
