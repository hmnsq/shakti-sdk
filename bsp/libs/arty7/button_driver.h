/***************************************************************************
 * Project           		   : shakti devt board
 * Name of the file	           : buttons_driver.h
 * Brief Description of file       : Header file for buttons
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
 * @file button_driver.h
 * @brief Header file for buttons 
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ BUTTON_DRIVER_H
#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_DRIVER_H

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"

//Buttons
#ವ್ಯಾಖ್ಯಾನಿಸು BTN0 GPIO28
#ವ್ಯಾಖ್ಯಾನಿಸು BTN1 GPIO29
#ವ್ಯಾಖ್ಯಾನಿಸು BTN2 GPIO30
#ವ್ಯಾಖ್ಯಾನಿಸು BTN3 GPIO31

#ವ್ಯಾಖ್ಯಾನಿಸು ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
ಶೂನ್ಯ configure_btn(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pinCntrl);
ಶೂನ್ಯ configure_all_btn();

#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
