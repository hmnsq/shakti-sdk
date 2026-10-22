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

#समावेश "gpio.h"
#समावेश "uart.h"
#समावेश "utils.h"
#समावेश "traps.h"
#समावेश "platform.h"
#समावेश "plic_driver.h"
#समावेश "log.h"
#समावेश "defines.h"
#समावेश "memory.h"

व्योम handle_button_press(__attribute__((unused)) uint32_t अंक);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
व्योम handle_button_press(__attribute__((unused)) uint32_t अंक)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
पूर्णांक मुख्य(व्योम){
	रेजिस्टर अचिन्हित पूर्णांक retval;
	पूर्णांक i;

	plic_init();

	क्रम(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_enable(i);
	}
	म_लिखो("\n");
	यंत्र("ebreak");

	क्रम(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_disable(i);
	}
	म_लिखो("\n");

	यंत्र("ebreak");

	क्रम(i=1;i<33;i++)
	{
		म_लिखो("i %d\n",i);
		interrupt_enable(i + 1);
	}
	म_लिखो("\n");

	यंत्र("ebreak");

	जबतक(1){
		i++;

		अगर((i%10000000) == 0){

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
	वापस 0;
}
