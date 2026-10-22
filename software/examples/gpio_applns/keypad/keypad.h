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
#എങ്കിൽ !defined(KYPD_H)
#define KYPD_H

#define ROWNUM 4
#define COLNUM 4

#define OUTPINS_OFFSET 0
#define INPINS_OFFSET 4
#define OUTPINS (0xF << OUTPINS_OFFSET)
#define INPINS  (0xF << INPINS_OFFSET)

//function prototype
ശൂന്യം set_pins(unsigned പൂർണ്ണസംഖ്യ* row, unsigned പൂർണ്ണസംഖ്യ* col);
ശൂന്യം set_താക്കോൽ_map(പൂർണ്ണസംഖ്യ table[COLNUM][ROWNUM]);
പൂർണ്ണസംഖ്യ get_താക്കോൽ();
പൂർണ്ണസംഖ്യ get_col_row(ശൂന്യം);
unsigned പൂർണ്ണസംഖ്യ row_pins[ROWNUM];
unsigned പൂർണ്ണസംഖ്യ col_pins[COLNUM];
പൂർണ്ണസംഖ്യ താക്കോൽ_map[COLNUM][ROWNUM];

#endif
