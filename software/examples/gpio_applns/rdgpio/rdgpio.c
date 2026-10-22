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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "platform.h"

/** @fn void read_data()
 * @brief set the direction reg to input and start reading from the gpio data reg
 * @details Configure the gpio direction reg to 0 for the corresponding gpio
 * pins. start reading the gpio pin value from data reg. delay for some time and
 * read data again 
 */
ಶೂನ್ಯ read_ದತ್ತಾಂಶ_2()
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದತ್ತಾಂಶ_2 = 0;
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, 0x00000000);

	ಆಗ (1) {
		ದತ್ತಾಂಶ_2 =read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);//copi GPIO_DATA_REG content
		log_info("\n Read Data is :%x", ದತ್ತಾಂಶ_2);
		delay_loop(3000, 5000);
	}
}

/** @fn void main()
 * @brief initiate the reading from gpio
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
    read_ದತ್ತಾಂಶ_2();
}


