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

#నిర్వచితం_కాకపోతే SWITCH_DRIVER_H
#నిర్వచించు SWITCH_DRIVER_H

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"

//Switches
#నిర్వచించు SW0 GPIO24
#నిర్వచించు SW1 GPIO25
#నిర్వచించు SW2 GPIO26
#నిర్వచించు SW3 GPIO27

#నిర్వచించు ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
శూన్య configure_switch(గుర్తులేని దీర్ఘ pinCntrl);
శూన్య configure_all_switchs();
#అయితే_ముగింపు
#అయితే_ముగింపు
