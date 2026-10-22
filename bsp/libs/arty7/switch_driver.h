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

#यदि_अपरिभाषितम् SWITCH_DRIVER_H
#परिभाषय SWITCH_DRIVER_H

#यदि defined(ARTIX7_35T) || defined(ARTIX7_100T)

#अन्तर्भाव "platform.h"
#अन्तर्भाव "gpio.h"

//Switches
#परिभाषय SW0 GPIO24
#परिभाषय SW1 GPIO25
#परिभाषय SW2 GPIO26
#परिभाषय SW3 GPIO27

#परिभाषय ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
शून्य configure_switch(अचिह्नित दीर्घ pinCntrl);
शून्य configure_all_switchs();
#यदि_अन्तः
#यदि_अन्तः
