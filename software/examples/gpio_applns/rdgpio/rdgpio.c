/***************************************************************************
* Project                      : shakti devt board
* Name of the file	       : rdgpio.c
* Brief Description of file    : Performs the reading operation with the help of gpio pins.
* Name of Author    	       : Sathya Narayanan N
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
@file rdgpio.c
@brief Performs the reading operation with the help of gpio pins.
*/

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "utils.h"
#অন্তর্ভাব "platform.h"

/** @fn void read_data()
 * @brief set the direction reg to input and start reading from the gpio data reg
 * @details Configure the gpio direction reg to 0 for the corresponding gpio
 * pins. start reading the gpio pin value from data reg. delay for some time and
 * read data again 
 */
শূন্য read_তথ্য_2()
{
	unsigned long তথ্য_2 = 0;
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);

	যখন (1) {
		তথ্য_2 =read_word(GPIO_তথ্য_REG);//copi GPIO_DATA_REG content
		log_info("\n Read Data is :%x", তথ্য_2);
		delay_loop(3000, 5000);
	}
}

/** @fn void main()
 * @brief initiate the reading from gpio
 */
শূন্য প্রধান()
{
    read_তথ্য_2();
}


