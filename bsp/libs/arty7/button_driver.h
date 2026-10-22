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

#నిర్వచితం_కాకపోతే BUTTON_DRIVER_H
#నిర్వచించు BUTTON_DRIVER_H

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"

//Buttons
#నిర్వచించు BTN0 GPIO28
#నిర్వచించు BTN1 GPIO29
#నిర్వచించు BTN2 GPIO30
#నిర్వచించు BTN3 GPIO31

#నిర్వచించు ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
శూన్య configure_btn(గుర్తులేని దీర్ఘ pinCntrl);
శూన్య configure_all_btn();

#అయితే_ముగింపు
#అయితే_ముగింపు
