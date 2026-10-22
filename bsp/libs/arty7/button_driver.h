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

#اگر_غیر_تعریف_شدہ BUTTON_DRIVER_H
#تعریف_کرو BUTTON_DRIVER_H

#اگر defined(ARTIX7_35T) || defined(ARTIX7_100T)

#شامل "platform.h"
#شامل "gpio.h"

//Buttons
#تعریف_کرو BTN0 GPIO28
#تعریف_کرو BTN1 GPIO29
#تعریف_کرو BTN2 GPIO30
#تعریف_کرو BTN3 GPIO31

#تعریف_کرو ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
خالی configure_btn(غیرعلامتی طویل pinCntrl);
خالی configure_all_btn();

#اگر_ختم
#اگر_ختم
