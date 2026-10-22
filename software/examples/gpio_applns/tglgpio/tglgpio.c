/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: tglgpio.c
* Brief Description of file     : Control an led with the help of a button, gpio based.
* Name of Author    	        : Sathya Narayanan N
* Email ID                      : sathya281@gmail.com

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
@file tglgpio.c
@brief Control an led with the help of a button, gpio based.
*/

#ضمن "platform.h"
#ضمن "utils.h" 
#ضمن "gpio.h" 

/** @fn tglgpio
 * @brief Performs the toggling operation  with the help of button.
 */
فراغ tglgpio()
{
//Assumption 1 ---> output, 0 ---> input
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, 0x00FFFFFF);

	طالما (1) {
		write_لفظ(GPIO_معلومات_REG, 0x00FFFFFF);
		delay_loop(1000, 5000);
		write_لفظ(GPIO_معلومات_REG, 0x00);
		delay_loop(1000, 5000);
	}
}

/** @fn main
 * @brief Initiates writing to gpio pins by calling tglgpio
 */ 
فراغ مکيه()
{
	tglgpio();
	أرجع 0;
}

