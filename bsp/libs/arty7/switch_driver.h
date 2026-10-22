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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SWITCH_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWITCH_DRIVER_H

#ਜੇ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"

//Switches
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW0 GPIO24
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW1 GPIO25
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW2 GPIO26
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW3 GPIO27

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALL_SWITCHES (SW0 | SW1 | SW2 | SW3)

// function prototype
ਖਾਲੀ configure_switch(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pinCntrl);
ਖਾਲੀ configure_all_switchs();
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
