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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "defines.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "memory.h"

ਖਾਲੀ handle_button_press(__attribute__((ਅਣਵਰਤਿਆ)) uint32_t ਅੰਕ);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
ਖਾਲੀ handle_button_press(__attribute__((ਅਣਵਰਤਿਆ)) uint32_t ਅੰਕ)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ){
	ਰਜਿਸਟਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ retval;
	ਪੂਰਨ i;

	plic_init();

	ਲਈ(i=1;i<33;i++)
	{
		ਲਿਖੋ("i %d\n",i);
		ਰੁਕਾਵਟ_enable(i);
	}
	ਲਿਖੋ("\n");
	asm("ebreak");

	ਲਈ(i=1;i<33;i++)
	{
		ਲਿਖੋ("i %d\n",i);
		ਰੁਕਾਵਟ_disable(i);
	}
	ਲਿਖੋ("\n");

	asm("ebreak");

	ਲਈ(i=1;i<33;i++)
	{
		ਲਿਖੋ("i %d\n",i);
		ਰੁਕਾਵਟ_enable(i + 1);
	}
	ਲਿਖੋ("\n");

	asm("ebreak");

	ਜਦੋਂ(1){
		i++;

		ਜੇ((i%10000000) == 0){

			asm ਅਸਥਿਰ(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			ਲਿਖੋ("mip = %u\n", retval);
		}
	}
	ਵਾਪਸ 0;
}
