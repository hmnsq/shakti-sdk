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
#وصف_ڪريو KYPD_H

#وصف_ڪريو ROWNUM 4
#وصف_ڪريو COLNUM 4

#وصف_ڪريو OUTPINS_وٿي 0
#وصف_ڪريو INPINS_وٿي 4
#وصف_ڪريو OUTPINS (0xF << OUTPINS_وٿي)
#وصف_ڪريو INPINS  (0xF << INPINS_وٿي)

//function prototype
فراغ سيٽ_pins(بنانشان صحيح* صف, بنانشان صحيح* کانو);
فراغ سيٽ_ڪنجي_map(صحيح جدول[COLNUM][ROWNUM]);
صحيح get_ڪنجي();
صحيح get_کانو_صف(فراغ);
بنانشان صحيح صف_pins[ROWNUM];
بنانشان صحيح کانو_pins[COLNUM];
صحيح ڪنجي_map[COLNUM][ROWNUM];

#جيڪڏهن_پورو
