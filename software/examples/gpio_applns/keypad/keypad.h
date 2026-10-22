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
#ຖ້າ !defined(KYPD_H)
#define KYPD_H

#define ROWNUM 4
#define COLNUM 4

#define OUTPINS_OFFSET 0
#define INPINS_OFFSET 4
#define OUTPINS (0xF << OUTPINS_OFFSET)
#define INPINS  (0xF << INPINS_OFFSET)

//function prototype
void set_pins(unsigned ຈຳນວນເຕັມ* row, unsigned ຈຳນວນເຕັມ* col);
void set_key_map(ຈຳນວນເຕັມ table[COLNUM][ROWNUM]);
ຈຳນວນເຕັມ get_key();
ຈຳນວນເຕັມ get_col_row(void);
unsigned ຈຳນວນເຕັມ row_pins[ROWNUM];
unsigned ຈຳນວນເຕັມ col_pins[COLNUM];
ຈຳນວນເຕັມ key_map[COLNUM][ROWNUM];

#endif
