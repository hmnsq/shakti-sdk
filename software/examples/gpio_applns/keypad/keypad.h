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
#تعریف_کرو KYPD_H

#تعریف_کرو ROWNUM 4
#تعریف_کرو COLNUM 4

#تعریف_کرو OUTPINS_وتھ 0
#تعریف_کرو INPINS_وتھ 4
#تعریف_کرو OUTPINS (0xF << OUTPINS_وتھ)
#تعریف_کرو INPINS  (0xF << INPINS_وتھ)

//function prototype
فراغ سیٹ_pins(بنانشانی صحيح* صف, بنانشانی صحيح* خانہ);
فراغ سیٹ_کلید_map(صحيح جدول[COLNUM][ROWNUM]);
صحيح get_کلید();
صحيح get_خانہ_صف(فراغ);
بنانشانی صحيح صف_pins[ROWNUM];
بنانشانی صحيح خانہ_pins[COLNUM];
صحيح کلید_map[COLNUM][ROWNUM];

#جے_انت
