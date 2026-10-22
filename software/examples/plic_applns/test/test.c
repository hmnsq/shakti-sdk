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

#अन्तर्भाव "gpio.h"
#अन्तर्भाव "uart.h"
#अन्तर्भाव "utils.h"
#अन्तर्भाव "traps.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "plic_driver.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "defines.h"
#अन्तर्भाव "memory.h"

शून्य handle_button_press(__attribute__((अप्रयुक्तम्)) uint32_t अङ्कः);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
शून्य handle_button_press(__attribute__((अप्रयुक्तम्)) uint32_t अङ्कः)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
पूर्णाङ्क मुख्यम्(शून्य){
	पञ्जिका अचिह्नित पूर्णाङ्क retval;
	पूर्णाङ्क i;

	plic_init();

	प्रति(i=1;i<33;i++)
	{
		प्रारूप_लिख("i %d\n",i);
		व्यवधानम्_enable(i);
	}
	प्रारूप_लिख("\n");
	asm("ebreak");

	प्रति(i=1;i<33;i++)
	{
		प्रारूप_लिख("i %d\n",i);
		व्यवधानम्_disable(i);
	}
	प्रारूप_लिख("\n");

	asm("ebreak");

	प्रति(i=1;i<33;i++)
	{
		प्रारूप_लिख("i %d\n",i);
		व्यवधानम्_enable(i + 1);
	}
	प्रारूप_लिख("\n");

	asm("ebreak");

	यावत्(1){
		i++;

		यदि((i%10000000) == 0){

			asm चञ्चल(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			प्रारूप_लिख("mip = %u\n", retval);
		}
	}
	प्रत्यागम 0;
}
