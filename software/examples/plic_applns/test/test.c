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

#అన్తర్భావ "gpio.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "utils.h"
#అన్తర్భావ "traps.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "plic_driver.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "defines.h"
#అన్తర్భావ "memory.h"

శూన్య handle_button_press(__attribute__((వాడని)) uint32_t అంకె);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
శూన్య handle_button_press(__attribute__((వాడని)) uint32_t అంకె)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
పూర్ణాంకం ప్రధాన(శూన్య){
	నమోదు గుర్తులేని పూర్ణాంకం retval;
	పూర్ణాంకం i;

	plic_init();

	కొరకు(i=1;i<33;i++)
	{
		రాయి("i %d\n",i);
		అంతరాయం_enable(i);
	}
	రాయి("\n");
	asm("ebreak");

	కొరకు(i=1;i<33;i++)
	{
		రాయి("i %d\n",i);
		అంతరాయం_disable(i);
	}
	రాయి("\n");

	asm("ebreak");

	కొరకు(i=1;i<33;i++)
	{
		రాయి("i %d\n",i);
		అంతరాయం_enable(i + 1);
	}
	రాయి("\n");

	asm("ebreak");

	అయితే(1){
		i++;

		ఒకవేళ((i%10000000) == 0){

			asm అస్థిర(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			రాయి("mip = %u\n", retval);
		}
	}
	తిరిగి 0;
}
