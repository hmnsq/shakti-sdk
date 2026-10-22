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
#إذا !defined(KYPD_H)
#تعریف_کن KYPD_H

#تعریف_کن ROWNUM 4
#تعریف_کن COLNUM 4

#تعریف_کن OUTPINS_جابه_جایی 0
#تعریف_کن INPINS_جابه_جایی 4
#تعریف_کن OUTPINS (0xF << OUTPINS_جابه_جایی)
#تعریف_کن INPINS  (0xF << INPINS_جابه_جایی)

//function prototype
فراغ مجموعه_pins(بیعلامت صحيح* ردیف, بیعلامت صحيح* ستون);
فراغ مجموعه_کلید_map(صحيح جدول[COLNUM][ROWNUM]);
صحيح get_کلید();
صحيح get_ستون_ردیف(فراغ);
بیعلامت صحيح ردیف_pins[ROWNUM];
بیعلامت صحيح ستون_pins[COLNUM];
صحيح کلید_map[COLNUM][ROWNUM];

#پایان_اگر
