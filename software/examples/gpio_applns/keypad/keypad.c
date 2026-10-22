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
صحيح کلی = -1;
صحيح ستون_لیکه = -1;

بینښه صحيح لیکه_pins[ROWNUM];
بینښه صحيح ستون_pins[COLNUM];
بینښه صحيح ستون[4]={0, 1, 2, 3};
بینښه صحيح لیکه[4]={4, 5, 6, 7};
صحيح کلی_map[COLNUM][ROWNUM];


صحيح  کلی_جدول[4][4] =
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
فراغ سېټ_pins(بینښه صحيح*  لیکه, بینښه صحيح* ستون)
{
	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		ستون_pins[i] = ستون[i];// set col
	}
	لكل(صحيح j = 0 ; j < ROWNUM ; j++) // set row
	{
		لیکه_pins[j] = لیکه[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
فراغ سېټ_کلی_map(صحيح جدول[COLNUM][ROWNUM])
{
	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		لكل(صحيح j = 0 ; j < ROWNUM ; j++)
		{
			کلی_map[i][j] = جدول[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
صحيح get_کلی_another_way()
{

	write_کلمه(GPIO_معلومات_REG, (0xF << OUTPINS_دننه_واټن) );

	لكل (صحيح i = 0 ; i < COLNUM ; i++)
	{
		write_کلمه(GPIO_معلومات_REG, ~(0x1 << (OUTPINS_دننه_واټن + i) )   );

		لكل (صحيح j = 0 ; j < ROWNUM ; j++)
		{
			إذا ( ( read_کلمه(لیکه_pins[j]) & (INPINS << INPINS_دننه_واټن )  ) == 0)
			{
				أرجع کلی_map[i][j];
			}
		}
		write_کلمه(GPIO_معلومات_REG, (0xF << OUTPINS_دننه_واټن) );
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
صحيح get_کلی(صحيح ستون_لیکه)
{
    أرجع کلی_map[ستون_لیکه>>16][0xFFFF & ستون_لیکه];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
صحيح get_ستون_لیکه(فراغ)
{
	صحيح ستون_لیکه = 0;
	بینښه اوږد read_ارزښت = 0;

	write_کلمه(GPIO_معلومات_REG, (0xF << OUTPINS_دننه_واټن) );

	لكل(صحيح i = 0 ; i < COLNUM ; i++)
	{
		write_کلمه(GPIO_معلومات_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		لكل(صحيح j = 0 ; j < ROWNUM ; j++)
		{
			read_ارزښت =  read_کلمه(GPIO_معلومات_REG);

			إذا( ( read_ارزښت & (1 << لیکه_pins[j] ) ) == 0 )
			{
					أرجع کلی_map[i][j];
			}
		}

		write_کلمه(GPIO_معلومات_REG, (0xF << OUTPINS_دننه_واټن) );
	}

	أرجع -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
فراغ gpio_init()
{
	سېټ_pins(لیکه, ستون);

	سېټ_کلی_map(کلی_جدول);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_کلمه(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
صحيح اصلي()
{
	صحيح prev_ستون_لیکه = 0;
	gpio_init(); //Intialization of gpio //

	چاپ_کړه("\nGPIO Init Done");
	طالما(1)
	{
		ستون_لیکه = get_ستون_لیکه();

		إذا( ستون_لیکه != -1 )
		{
			log_info("\nThe %x Key Pressed", ستون_لیکه);
				delay_loop(600, 2000);
		}
	}

	أرجع 0;
}
