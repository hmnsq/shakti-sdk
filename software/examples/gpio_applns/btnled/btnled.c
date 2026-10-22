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

#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "platform.h"

/** @fn int main(void)
 * @brief on press of a button led grows. The technique used here is polling
 *    based.
 * @return int
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ~(1 << 0) );

	ಆಗ (1) {

		ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;

		read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & 0x1;    

		log_debug("\n Read Data is :0x%08lx", read_ದತ್ತಾಂಶ);

		ಆದರೆ (read_ದತ್ತಾಂಶ) {           //if readdata //
			log_debug("; LED ON");
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, 0X2); 
		}
		ಇಲ್ಲದಿದ್ದರೆ {                    //if not //
			log_debug("; LED OFF");
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, 0X0); 
		}
		delay_loop(1000,1000);
	}

	ಹಿಂತಿರುಗಿ 0;
}
