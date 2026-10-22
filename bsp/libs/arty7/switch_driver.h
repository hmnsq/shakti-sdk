/***************************************************************************
 * Project           		   : shakti devt board
 * Name of the file	           : switch_driver.h
 * Brief Description of file       : Header file for switches
 * Name of Author    	           : Madan Kumar S
 * Email ID                        : kumarmadan96@gmail.com

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
 * @file switch_driver.h
 * @brief Header file for switches
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SWITCH_DRIVER_H
#ವ್ಯಾಖ್ಯಾನಿಸು SWITCH_DRIVER_H

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"

//Switches
#ವ್ಯಾಖ್ಯಾನಿಸು SW0 GPIO24
#ವ್ಯಾಖ್ಯಾನಿಸು SW1 GPIO25
#ವ್ಯಾಖ್ಯಾನಿಸು SW2 GPIO26
#ವ್ಯಾಖ್ಯಾನಿಸು SW3 GPIO27

#ವ್ಯಾಖ್ಯಾನಿಸು ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
ಶೂನ್ಯ configure_switch(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pinCntrl);
ಶೂನ್ಯ configure_all_switchs();
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
