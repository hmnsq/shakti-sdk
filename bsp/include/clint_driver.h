/***************************************************************************
* Project           		:  shakti devt board
* Name of the file	     	:  clint_driver.h
* Brief Description of file     :  Header file for clint.
* Name of Author    	        :  Sathya Narayanan N
* Email ID                      :  sathya281@gmail.com

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
 * @file clint_driver.h
 * @brief  Header file for clint
 * @detail This is the header file for clint_driver.c
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ CLIC_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIC_DRIVER_H
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"

ਬਾਹਰੀ ਅਸਥਿਰ uint64_t* mtime;
ਬਾਹਰੀ ਅਸਥਿਰ uint64_t* mtimecmp;

/* function prototype */
uint64_t get_timer_ਮੁੱਲ(ਖਾਲੀ);
ਖਾਲੀ configure_counter(uint64_t ਮੁੱਲ);
ਖਾਲੀ mach_clint_handler(uintptr_t int_id, uintptr_t epc);

#ਜੇ_ਅੰਤ
