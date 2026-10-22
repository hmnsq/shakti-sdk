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

#شامل "gpio.h"
#شامل "platform.h"
#شامل "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
صحیح کلید = -1;
صحیح col_row = -1;

unsigned صحیح row_pins[ROWNUM];
unsigned صحیح col_pins[COLNUM];
unsigned صحیح col[4]={0, 1, 2, 3};
unsigned صحیح row[4]={4, 5, 6, 7};
صحیح کلید_map[COLNUM][ROWNUM];


صحیح  کلید_table[4][4] =
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
تهی set_pins(unsigned صحیح*  row, unsigned صحیح* col)
{
	برای(صحیح i = 0 ; i < COLNUM ; i++)
	{
		col_pins[i] = col[i];// set col
	}
	برای(صحیح j = 0 ; j < ROWNUM ; j++) // set row
	{
		row_pins[j] = row[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
تهی set_کلید_map(صحیح table[COLNUM][ROWNUM])
{
	برای(صحیح i = 0 ; i < COLNUM ; i++)
	{
		برای(صحیح j = 0 ; j < ROWNUM ; j++)
		{
			کلید_map[i][j] = table[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
صحیح get_کلید_another_way()
{

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	برای (صحیح i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		برای (صحیح j = 0 ; j < ROWNUM ; j++)
		{
			اگر ( ( read_word(row_pins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				بازگشت کلید_map[i][j];
			}
		}
		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	بازگشت 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
صحیح get_کلید(صحیح col_row)
{
    بازگشت کلید_map[col_row>>16][0xFFFF & col_row];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
صحیح get_col_row(تهی)
{
	صحیح col_row = 0;
	unsigned long read_مقدار = 0;

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	برای(صحیح i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		برای(صحیح j = 0 ; j < ROWNUM ; j++)
		{
			read_مقدار =  read_word(GPIO_DATA_REG);

			اگر( ( read_مقدار & (1 << row_pins[j] ) ) == 0 )
			{
					بازگشت کلید_map[i][j];
			}
		}

		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	بازگشت -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
تهی gpio_init()
{
	set_pins(row, col);

	set_کلید_map(کلید_table);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
صحیح اصلی()
{
	صحیح prev_col_row = 0;
	gpio_init(); //Intialization of gpio //

	printf("\nGPIO Init Done");
	وقتی(1)
	{
		col_row = get_col_row();

		اگر( col_row != -1 )
		{
			log_info("\nThe %x Key Pressed", col_row);
				delay_loop(600, 2000);
		}
	}

	بازگشت 0;
}
