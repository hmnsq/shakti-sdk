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

#که_نه_تعریف_شوی SWITCH_DRIVER_H
#تعریف_کړه SWITCH_DRIVER_H

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ضمن "platform.h"
#ضمن "gpio.h"

//Switches
#تعریف_کړه SW0 GPIO24
#تعریف_کړه SW1 GPIO25
#تعریف_کړه SW2 GPIO26
#تعریف_کړه SW3 GPIO27

#تعریف_کړه ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
فراغ configure_switch(بینښه اوږد pinCntrl);
فراغ configure_all_switchs();
#د_که_پای
#د_که_پای
