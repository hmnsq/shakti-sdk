/************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: Keypad.c 
 * Brief Description of file    : reads and prints pressed key in 4x4 keypad
 * Name of Author    	        : Kotteeswaran
 * Email ID                     : kottee.1@gmail.com
  
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

************************************************************************/
/**
@file   keypad.c
@brief  Contains the driver routines to read the pressed keypad.
@detail Detects the pressed key/button and prints decoded keypad value (0 - 15).
*/

#समावेश "gpio.h"
#समावेश "platform.h"
#समावेश "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
पूर्णांक कुंजी = -1;
पूर्णांक col_row = -1;

अचिन्हित पूर्णांक row_pins[ROWNUM];
अचिन्हित पूर्णांक col_pins[COLNUM];
अचिन्हित पूर्णांक col[4]={0, 1, 2, 3};
अचिन्हित पूर्णांक row[4]={4, 5, 6, 7};
पूर्णांक कुंजी_map[COLNUM][ROWNUM];


पूर्णांक  कुंजी_table[4][4] =
{
	{  1,  4,  7,  0},
	{  2,  5,  8, 15},
	{  3,  6,  9, 14},
	{ 10, 11, 12, 13}
};

/** @fn void set_pins(unsigned int*  row, unsigned int* col)
 * @brief This function sets the pins for the row and column
 * @details Fills the row and coloumn values into row and coloumn arrays.
 * @param unsigned int* row
 * @param unsigned int* col
 */
व्योम set_pins(अचिन्हित पूर्णांक*  row, अचिन्हित पूर्णांक* col)
{
	क्रम(पूर्णांक i = 0 ; i < COLNUM ; i++)
	{
		col_pins[i] = col[i];// set col
	}
	क्रम(पूर्णांक j = 0 ; j < ROWNUM ; j++) // set row
	{
		row_pins[j] = row[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
व्योम set_कुंजी_map(पूर्णांक table[COLNUM][ROWNUM])
{
	क्रम(पूर्णांक i = 0 ; i < COLNUM ; i++)
	{
		क्रम(पूर्णांक j = 0 ; j < ROWNUM ; j++)
		{
			कुंजी_map[i][j] = table[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
पूर्णांक get_कुंजी_another_way()
{

	write_word(GPIO_तथ्य_REG, (0xF << OUTPINS_OFFSET) );

	क्रम (पूर्णांक i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_तथ्य_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		क्रम (पूर्णांक j = 0 ; j < ROWNUM ; j++)
		{
			अगर ( ( read_word(row_pins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				वापस कुंजी_map[i][j];
			}
		}
		write_word(GPIO_तथ्य_REG, (0xF << OUTPINS_OFFSET) );
	}

	वापस 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
पूर्णांक get_कुंजी(पूर्णांक col_row)
{
    वापस कुंजी_map[col_row>>16][0xFFFF & col_row];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
पूर्णांक get_col_row(व्योम)
{
	पूर्णांक col_row = 0;
	अचिन्हित दीर्घ read_मूल्य = 0;

	write_word(GPIO_तथ्य_REG, (0xF << OUTPINS_OFFSET) );

	क्रम(पूर्णांक i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_तथ्य_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		क्रम(पूर्णांक j = 0 ; j < ROWNUM ; j++)
		{
			read_मूल्य =  read_word(GPIO_तथ्य_REG);

			अगर( ( read_मूल्य & (1 << row_pins[j] ) ) == 0 )
			{
					वापस कुंजी_map[i][j];
			}
		}

		write_word(GPIO_तथ्य_REG, (0xF << OUTPINS_OFFSET) );
	}

	वापस -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
व्योम gpio_init()
{
	set_pins(row, col);

	set_कुंजी_map(कुंजी_table);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
पूर्णांक मुख्य()
{
	पूर्णांक पूर्व_col_row = 0;
	gpio_init(); //Intialization of gpio //

	म_लिखो("\nGPIO Init Done");
	जबतक(1)
	{
		col_row = get_col_row();

		अगर( col_row != -1 )
		{
			log_info("\nThe %x Key Pressed", col_row);
				delay_loop(600, 2000);
		}
	}

	वापस 0;
}
