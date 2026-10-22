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

#که_نه_تعریف_شوی BUTTON_DRIVER_H
#تعریف_کړه BUTTON_DRIVER_H

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ضمن "platform.h"
#ضمن "gpio.h"

//Buttons
#تعریف_کړه BTN0 GPIO28
#تعریف_کړه BTN1 GPIO29
#تعریف_کړه BTN2 GPIO30
#تعریف_کړه BTN3 GPIO31

#تعریف_کړه ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
فراغ configure_btn(بینښه اوږد pinCntrl);
فراغ configure_all_btn();

#د_که_پای
#د_که_پای
