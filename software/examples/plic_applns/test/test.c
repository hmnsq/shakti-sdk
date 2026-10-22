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

#ضمن "gpio.h"
#ضمن "uart.h"
#ضمن "utils.h"
#ضمن "traps.h"
#ضمن "platform.h"
#ضمن "plic_driver.h"
#ضمن "log.h"
#ضمن "defines.h"
#ضمن "memory.h"

فراغ handle_button_press(__attribute__((بن_ورتیا)) uint32_t عدد);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
فراغ handle_button_press(__attribute__((بن_ورتیا)) uint32_t عدد)
{
	log_info("button pressed\n");
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
صحيح مکھ(فراغ){
	سجل بنانشانی صحيح retval;
	صحيح i;

	plic_init();

	لكل(i=1;i<33;i++)
	{
		لکھو("i %d\n",i);
		رکاوٹ_enable(i);
	}
	لکھو("\n");
	asm("ebreak");

	لكل(i=1;i<33;i++)
	{
		لکھو("i %d\n",i);
		رکاوٹ_disable(i);
	}
	لکھو("\n");

	asm("ebreak");

	لكل(i=1;i<33;i++)
	{
		لکھو("i %d\n",i);
		رکاوٹ_enable(i + 1);
	}
	لکھو("\n");

	asm("ebreak");

	طالما(1){
		i++;

		إذا((i%10000000) == 0){

			asm متطاير(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );
			لکھو("mip = %u\n", retval);
		}
	}
	أرجع 0;
}
