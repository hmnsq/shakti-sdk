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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ BUTTON_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_DRIVER_H

#ਜੇ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"

//Buttons
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN0 GPIO28
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN1 GPIO29
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN2 GPIO30
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN3 GPIO31

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
ਖਾਲੀ configure_btn(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pinCntrl);
ਖਾਲੀ configure_all_btn();

#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
