/***************************************************************************
 * Project           	        : shakti devt board
 * Name of the file	        : btnled.c
 * Brief Description of file    : Controls the led operation with help of button,gpio based.
 * Name of Author    	        : Sathya Narayanan N & Raghav
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
@file btnled.c
@brief Controls the led operation with help of button,gpio based.
@detail A led glows when a button is pressed. The button controlled led is
implemented using gpio pins.
*/

#شامل "gpio.h"
#شامل "platform.h"

/** @fn int main(void)
 * @brief on press of a button led grows. The technique used here is polling
 *    based.
 * @return int
 */
صحیح مین(خالی)
{
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, ~(1 << 0) );

	جب (1) {

		غیرعلامتی طویل read_ڈیٹا = 0;

		read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG) & 0x1;    

		log_debug("\n Read Data is :0x%08lx", read_ڈیٹا);

		اگر (read_ڈیٹا) {           //if readdata //
			log_debug("; LED ON");
			write_لفظ(GPIO_ڈیٹا_REG, 0X2); 
		}
		ورنہ {                    //if not //
			log_debug("; LED OFF");
			write_لفظ(GPIO_ڈیٹا_REG, 0X0); 
		}
		delay_loop(1000,1000);
	}

	واپس 0;
}
