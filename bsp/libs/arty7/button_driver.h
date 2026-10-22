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

#अगर_अघोषित BUTTON_DRIVER_H
#घोषणा BUTTON_DRIVER_H

#अगर defined(ARTIX7_35T) || defined(ARTIX7_100T)

#समावेश "platform.h"
#समावेश "gpio.h"

//Buttons
#घोषणा BTN0 GPIO28
#घोषणा BTN1 GPIO29
#घोषणा BTN2 GPIO30
#घोषणा BTN3 GPIO31

#घोषणा ALL_BTNS (BTN0 | BTN1 | BTN2 | BTN3)

// function prototype
व्योम configure_btn(अचिन्हित दीर्घ pinCntrl);
व्योम configure_all_btn();

#पूर्ण_अगर
#पूर्ण_अगर
