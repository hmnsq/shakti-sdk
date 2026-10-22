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

#अन्तर्भाव "gpio.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
पूर्णाङ्क कुञ्चिका = -1;
पूर्णाङ्क col_row = -1;

अचिह्नित पूर्णाङ्क row_pins[ROWNUM];
अचिह्नित पूर्णाङ्क col_pins[COLNUM];
अचिह्नित पूर्णाङ्क col[4]={0, 1, 2, 3};
अचिह्नित पूर्णाङ्क row[4]={4, 5, 6, 7};
पूर्णाङ्क कुञ्चिका_map[COLNUM][ROWNUM];


पूर्णाङ्क  कुञ्चिका_सारणी[4][4] =
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
शून्य समुच्चयः_pins(अचिह्नित पूर्णाङ्क*  row, अचिह्नित पूर्णाङ्क* col)
{
	प्रति(पूर्णाङ्क i = 0 ; i < COLNUM ; i++)
	{
		col_pins[i] = col[i];// set col
	}
	प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++) // set row
	{
		row_pins[j] = row[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
शून्य समुच्चयः_कुञ्चिका_map(पूर्णाङ्क सारणी[COLNUM][ROWNUM])
{
	प्रति(पूर्णाङ्क i = 0 ; i < COLNUM ; i++)
	{
		प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++)
		{
			कुञ्चिका_map[i][j] = सारणी[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
पूर्णाङ्क get_कुञ्चिका_another_way()
{

	write_word(GPIO_दत्त_REG, (0xF << OUTPINS_विस्थापनम्) );

	प्रति (पूर्णाङ्क i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_दत्त_REG, ~(0x1 << (OUTPINS_विस्थापनम् + i) )   );

		प्रति (पूर्णाङ्क j = 0 ; j < ROWNUM ; j++)
		{
			यदि ( ( read_word(row_pins[j]) & (INPINS << INPINS_विस्थापनम् )  ) == 0)
			{
				प्रत्यागम कुञ्चिका_map[i][j];
			}
		}
		write_word(GPIO_दत्त_REG, (0xF << OUTPINS_विस्थापनम्) );
	}

	प्रत्यागम 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
पूर्णाङ्क get_कुञ्चिका(पूर्णाङ्क col_row)
{
    प्रत्यागम कुञ्चिका_map[col_row>>16][0xFFFF & col_row];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
पूर्णाङ्क get_col_row(शून्य)
{
	पूर्णाङ्क col_row = 0;
	अचिह्नित दीर्घ read_मानम् = 0;

	write_word(GPIO_दत्त_REG, (0xF << OUTPINS_विस्थापनम्) );

	प्रति(पूर्णाङ्क i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_दत्त_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++)
		{
			read_मानम् =  read_word(GPIO_दत्त_REG);

			यदि( ( read_मानम् & (1 << row_pins[j] ) ) == 0 )
			{
					प्रत्यागम कुञ्चिका_map[i][j];
			}
		}

		write_word(GPIO_दत्त_REG, (0xF << OUTPINS_विस्थापनम्) );
	}

	प्रत्यागम -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
शून्य gpio_init()
{
	समुच्चयः_pins(row, col);

	समुच्चयः_कुञ्चिका_map(कुञ्चिका_सारणी);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
पूर्णाङ्क मुख्यम्()
{
	पूर्णाङ्क पूर्व_col_row = 0;
	gpio_init(); //Intialization of gpio //

	प्रारूप_लिख("\nGPIO Init Done");
	यावत्(1)
	{
		col_row = get_col_row();

		यदि( col_row != -1 )
		{
			log_info("\nThe %x Key Pressed", col_row);
				delay_loop(600, 2000);
		}
	}

	प्रत्यागम 0;
}
