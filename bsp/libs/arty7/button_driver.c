/***************************************************************************
* Project           	         : shakti devt board
* Name of the file	         : button_driver.c
* Brief Description of file      : Reads onboard button values from gpio pins.
* Name of Author    	         : Madan Kumar S
* Email ID                       : kumarmadan96@gmail.com

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
@file button_driver.c
@brief Reads onboard button values from gpio pins.
@detail configures buttons to serve as Input 
*/ 

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "button_driver.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/**
 * @fn void configure_btn(unsigned long pinCntrl)
 * @brief Function for configure Individual Buttons as input.
 * @details 4 GPIO pins are mapped to 4 Buttons. This function configures
 *          each BTN as input pin.
 * @param unsigned long (Pin that needs to be configured as BTN.)
 */
ಶೂನ್ಯ configure_btn(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pinCntrl)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | ~(pinCntrl) ) );
}

/** @fn void configure_all_btn()
 * @brief Function for configure All BTNs as input.
 * @details 4 GPIO pins are mapped to 4 Buttons. This function configures
 *          all BTNs as input pin.
 */
ಶೂನ್ಯ configure_all_btn()
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | ~(ALL_BTNS) ) );
}
#ಆದರೆ_ಅಂತ್ಯ

