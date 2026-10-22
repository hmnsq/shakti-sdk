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
#अगर !defined(KYPD_H)
#घोषणा KYPD_H

#घोषणा ROWNUM 4
#घोषणा COLNUM 4

#घोषणा OUTPINS_OFFSET 0
#घोषणा INPINS_OFFSET 4
#घोषणा OUTPINS (0xF << OUTPINS_OFFSET)
#घोषणा INPINS  (0xF << INPINS_OFFSET)

//function prototype
व्योम set_pins(अचिन्हित पूर्णांक* row, अचिन्हित पूर्णांक* col);
व्योम set_कुंजी_map(पूर्णांक table[COLNUM][ROWNUM]);
पूर्णांक get_कुंजी();
पूर्णांक get_col_row(व्योम);
अचिन्हित पूर्णांक row_pins[ROWNUM];
अचिन्हित पूर्णांक col_pins[COLNUM];
पूर्णांक कुंजी_map[COLNUM][ROWNUM];

#पूर्ण_अगर
