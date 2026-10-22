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

शून्य handle_button_press(__attribute__((unused)) uint32_t अंक);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
शून्य handle_button_press(__attribute__((unused)) uint32_t अंक)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
पूर्णांक main(शून्य){
	नोंदणी अचिन्हित पूर्णांक retval;
	पूर्णांक i;

	plic_init();

	साठी(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_enable(i);
	}
	म_लिखो("\n");
	यंत्र("ebreak");

	साठी(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_disable(i);
	}
	म_लिखो("\n");

	यंत्र("ebreak");

	साठी(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_enable(i + 1);
	}
	म_लिखो("\n");

	यंत्र("ebreak");

	पर्यंत(1){
		i++;

		जर((i%10000000) == 0){

			यंत्र अस्थिर(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			म_लिखो("mip = %u\n", retval);
		}
	}
	परत 0;
}
