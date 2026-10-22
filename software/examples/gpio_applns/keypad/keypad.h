/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  keypad.h
 * Brief Description of file            :  Declaration for keypad library.
 * Name of Author    	                : Kotteeswaran
 * Email ID                             : kottee.1@gmail.com

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
 * @file keypad.h
 * @brief Declaration for keypad library.
 * @detail Include File Definitions	
 */
#اگر !defined(KYPD_H)
#تعریف_کرو KYPD_H

#تعریف_کرو ROWNUM 4
#تعریف_کرو COLNUM 4

#تعریف_کرو OUTPINS_انحراف 0
#تعریف_کرو INPINS_انحراف 4
#تعریف_کرو OUTPINS (0xF << OUTPINS_انحراف)
#تعریف_کرو INPINS  (0xF << INPINS_انحراف)

//function prototype
خالی سیٹ_pins(غیرعلامتی صحیح* صف, غیرعلامتی صحیح* ستون);
خالی سیٹ_کلید_map(صحیح جدول[COLNUM][ROWNUM]);
صحیح get_کلید();
صحیح get_ستون_صف(خالی);
غیرعلامتی صحیح صف_pins[ROWNUM];
غیرعلامتی صحیح ستون_pins[COLNUM];
صحیح کلید_map[COLNUM][ROWNUM];

#اگر_ختم
