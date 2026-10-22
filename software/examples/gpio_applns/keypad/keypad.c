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

#ضمن "gpio.h"
#ضمن "platform.h"
#ضمن "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
صحيح ڪنجي = -1;
صحيح کانو_صف = -1;

بنانشان صحيح صف_pins[ROWNUM];
بنانشان صحيح کانو_pins[COLNUM];
بنانشان صحيح کانو[4]={0, 1, 2, 3};
بنانشان صحيح صف[4]={4, 5, 6, 7};
صحيح ڪنجي_map[COLNUM][ROWNUM];


صحيح  ڪنجي_جدول[4][4] =
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
فراغ سيٽ_pins(بنانشان صحيح*  صف, بنانشان صحيح* کانو)
{
	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		کانو_pins[i] = کانو[i];// set col
	}
	لكل(صحيح j = 0 ; j < ROWNUM ; j++) // set row
	{
		صف_pins[j] = صف[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
فراغ سيٽ_ڪنجي_map(صحيح جدول[COLNUM][ROWNUM])
{
	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		لكل(صحيح j = 0 ; j < ROWNUM ; j++)
		{
			ڪنجي_map[i][j] = جدول[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
صحيح get_ڪنجي_another_way()
{

	write_لفظ(GPIO_معلومات_REG, (0xF << OUTPINS_وٿي) );

	لكل (صحيح i = 0 ; i < COLNUM ; i++)
	{
		write_لفظ(GPIO_معلومات_REG, ~(0x1 << (OUTPINS_وٿي + i) )   );

		لكل (صحيح j = 0 ; j < ROWNUM ; j++)
		{
			إذا ( ( read_لفظ(صف_pins[j]) & (INPINS << INPINS_وٿي )  ) == 0)
			{
				أرجع ڪنجي_map[i][j];
			}
		}
		write_لفظ(GPIO_معلومات_REG, (0xF << OUTPINS_وٿي) );
	}

	أرجع 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
صحيح get_ڪنجي(صحيح کانو_صف)
{
    أرجع ڪنجي_map[کانو_صف>>16][0xFFFF & کانو_صف];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
صحيح get_کانو_صف(فراغ)
{
	صحيح کانو_صف = 0;
	بنانشان ڊگهو read_قدر = 0;

	write_لفظ(GPIO_معلومات_REG, (0xF << OUTPINS_وٿي) );

	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		write_لفظ(GPIO_معلومات_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		لكل(صحيح j = 0 ; j < ROWNUM ; j++)
		{
			read_قدر =  read_لفظ(GPIO_معلومات_REG);

			إذا( ( read_قدر & (1 << صف_pins[j] ) ) == 0 )
			{
					أرجع ڪنجي_map[i][j];
			}
		}

		write_لفظ(GPIO_معلومات_REG, (0xF << OUTPINS_وٿي) );
	}

	أرجع -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
فراغ gpio_init()
{
	سيٽ_pins(صف, کانو);

	سيٽ_ڪنجي_map(ڪنجي_جدول);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
صحيح مکيه()
{
	صحيح prev_کانو_صف = 0;
	gpio_init(); //Intialization of gpio //

	لکو("\nGPIO Init Done");
	طالما(1)
	{
		کانو_صف = get_کانو_صف();

		إذا( کانو_صف != -1 )
		{
			log_info("\nThe %x Key Pressed", کانو_صف);
				delay_loop(600, 2000);
		}
	}

	أرجع 0;
}
