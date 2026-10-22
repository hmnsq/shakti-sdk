/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: switch_driver.c
 * Brief Description of file    : Reads onboard switch values from gpio pins.
 * Name of Author    	        : Madan Kumar S
 * Email ID                     : kumarmadan96@gmail.com

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
@file switch_driver.c
@brief Reads onboard switch values from gpio pins.
@detail Configures Switches and maps to the gpio pins 
*/ 

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "switch_driver.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/** @fn void configure_switch(unsigned long pinCntrl)
 * @brief Function for configure Individual Switch pins as input.
 * @details 4 GPIO pins are mapped to 4 Switches. This function configures
 * each SW as input pin.
 * @param unsigned long (Pin that needs to be configured as SW.)
 */
ಶೂನ್ಯ configure_switch(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pinCntrl)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | ~(pinCntrl) ) );
}

/** @fn  void configure_all_switchs()
 * @brief Function for configure All SWs as input.
 * @details 4 GPIO pins are mapped to 4 Switches. This function configures
 *          all SWs as input pin.
 */
ಶೂನ್ಯ configure_all_switchs()
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | ~(ALL_SWITCHES) ) );
}

#ಆದರೆ_ಅಂತ್ಯ
