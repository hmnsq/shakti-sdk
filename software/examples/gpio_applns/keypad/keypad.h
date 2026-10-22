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
#यदि !defined(KYPD_H)
#परिभाषय KYPD_H

#परिभाषय ROWNUM 4
#परिभाषय COLNUM 4

#परिभाषय OUTPINS_विस्थापनम् 0
#परिभाषय INPINS_विस्थापनम् 4
#परिभाषय OUTPINS (0xF << OUTPINS_विस्थापनम्)
#परिभाषय INPINS  (0xF << INPINS_विस्थापनम्)

//function prototype
शून्य समुच्चयः_pins(अचिह्नित पूर्णाङ्क* row, अचिह्नित पूर्णाङ्क* col);
शून्य समुच्चयः_कुञ्चिका_map(पूर्णाङ्क सारणी[COLNUM][ROWNUM]);
पूर्णाङ्क get_कुञ्चिका();
पूर्णाङ्क get_col_row(शून्य);
अचिह्नित पूर्णाङ्क row_pins[ROWNUM];
अचिह्नित पूर्णाङ्क col_pins[COLNUM];
पूर्णाङ्क कुञ्चिका_map[COLNUM][ROWNUM];

#यदि_अन्तः
