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
صحیح ستون_صف = -1;

غیرعلامتی صحیح صف_pins[ROWNUM];
غیرعلامتی صحیح ستون_pins[COLNUM];
غیرعلامتی صحیح ستون[4]={0, 1, 2, 3};
غیرعلامتی صحیح صف[4]={4, 5, 6, 7};
صحیح کلید_map[COLNUM][ROWNUM];


صحیح  کلید_جدول[4][4] =
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
خالی سیٹ_pins(غیرعلامتی صحیح*  صف, غیرعلامتی صحیح* ستون)
{
	برائے(صحیح i = 0 ; i < COLNUM ; i++)
	{
		ستون_pins[i] = ستون[i];// set col
	}
	برائے(صحیح j = 0 ; j < ROWNUM ; j++) // set row
	{
		صف_pins[j] = صف[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
خالی سیٹ_کلید_map(صحیح جدول[COLNUM][ROWNUM])
{
	برائے(صحیح i = 0 ; i < COLNUM ; i++)
	{
		برائے(صحیح j = 0 ; j < ROWNUM ; j++)
		{
			کلید_map[i][j] = جدول[i][j];
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

	write_لفظ(GPIO_ڈیٹا_REG, (0xF << OUTPINS_انحراف) );

	برائے (صحیح i = 0 ; i < COLNUM ; i++)
	{
		write_لفظ(GPIO_ڈیٹا_REG, ~(0x1 << (OUTPINS_انحراف + i) )   );

		برائے (صحیح j = 0 ; j < ROWNUM ; j++)
		{
			اگر ( ( read_لفظ(صف_pins[j]) & (INPINS << INPINS_انحراف )  ) == 0)
			{
				واپس کلید_map[i][j];
			}
		}
		write_لفظ(GPIO_ڈیٹا_REG, (0xF << OUTPINS_انحراف) );
	}

	واپس 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
صحیح get_کلید(صحیح ستون_صف)
{
    واپس کلید_map[ستون_صف>>16][0xFFFF & ستون_صف];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
صحیح get_ستون_صف(خالی)
{
	صحیح ستون_صف = 0;
	غیرعلامتی طویل read_قدر = 0;

	write_لفظ(GPIO_ڈیٹا_REG, (0xF << OUTPINS_انحراف) );

	برائے(صحیح i = 0 ; i < COLNUM ; i++)
	{
		write_لفظ(GPIO_ڈیٹا_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		برائے(صحیح j = 0 ; j < ROWNUM ; j++)
		{
			read_قدر =  read_لفظ(GPIO_ڈیٹا_REG);

			اگر( ( read_قدر & (1 << صف_pins[j] ) ) == 0 )
			{
					واپس کلید_map[i][j];
			}
		}

		write_لفظ(GPIO_ڈیٹا_REG, (0xF << OUTPINS_انحراف) );
	}

	واپس -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
خالی gpio_init()
{
	سیٹ_pins(صف, ستون);

	سیٹ_کلید_map(کلید_جدول);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
صحیح مین()
{
	صحیح پچھلا_ستون_صف = 0;
	gpio_init(); //Intialization of gpio //

	لکھو("\nGPIO Init Done");
	جب(1)
	{
		ستون_صف = get_ستون_صف();

		اگر( ستون_صف != -1 )
		{
			log_info("\nThe %x Key Pressed", ستون_صف);
				delay_loop(600, 2000);
		}
	}

	واپس 0;
}
