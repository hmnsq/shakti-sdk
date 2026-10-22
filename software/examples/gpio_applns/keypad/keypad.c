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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
ਪੂਰਨ ਕੁੰਜੀ = -1;
ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ = -1;

ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ_pins[ROWNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ_pins[COLNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ[4]={0, 1, 2, 3};
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ[4]={4, 5, 6, 7};
ਪੂਰਨ ਕੁੰਜੀ_map[COLNUM][ROWNUM];


ਪੂਰਨ  ਕੁੰਜੀ_ਸਾਰਣੀ[4][4] =
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
ਖਾਲੀ ਸੈੱਟ_pins(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ*  ਪੰਕਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਖਾਨਾ)
{
	ਲਈ(ਪੂਰਨ i = 0 ; i < COLNUM ; i++)
	{
		ਖਾਨਾ_pins[i] = ਖਾਨਾ[i];// set col
	}
	ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++) // set row
	{
		ਪੰਕਤੀ_pins[j] = ਪੰਕਤੀ[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
ਖਾਲੀ ਸੈੱਟ_ਕੁੰਜੀ_map(ਪੂਰਨ ਸਾਰਣੀ[COLNUM][ROWNUM])
{
	ਲਈ(ਪੂਰਨ i = 0 ; i < COLNUM ; i++)
	{
		ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++)
		{
			ਕੁੰਜੀ_map[i][j] = ਸਾਰਣੀ[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
ਪੂਰਨ get_ਕੁੰਜੀ_another_way()
{

	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (0xF << OUTPINS_ਵਿੱਥ) );

	ਲਈ (ਪੂਰਨ i = 0 ; i < COLNUM ; i++)
	{
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, ~(0x1 << (OUTPINS_ਵਿੱਥ + i) )   );

		ਲਈ (ਪੂਰਨ j = 0 ; j < ROWNUM ; j++)
		{
			ਜੇ ( ( read_ਸ਼ਬਦ(ਪੰਕਤੀ_pins[j]) & (INPINS << INPINS_ਵਿੱਥ )  ) == 0)
			{
				ਵਾਪਸ ਕੁੰਜੀ_map[i][j];
			}
		}
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (0xF << OUTPINS_ਵਿੱਥ) );
	}

	ਵਾਪਸ 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
ਪੂਰਨ get_ਕੁੰਜੀ(ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ)
{
    ਵਾਪਸ ਕੁੰਜੀ_map[ਖਾਨਾ_ਪੰਕਤੀ>>16][0xFFFF & ਖਾਨਾ_ਪੰਕਤੀ];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
ਪੂਰਨ get_ਖਾਨਾ_ਪੰਕਤੀ(ਖਾਲੀ)
{
	ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਮੁੱਲ = 0;

	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (0xF << OUTPINS_ਵਿੱਥ) );

	ਲਈ(ਪੂਰਨ i = 0 ; i < COLNUM ; i++)
	{
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++)
		{
			read_ਮੁੱਲ =  read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);

			ਜੇ( ( read_ਮੁੱਲ & (1 << ਪੰਕਤੀ_pins[j] ) ) == 0 )
			{
					ਵਾਪਸ ਕੁੰਜੀ_map[i][j];
			}
		}

		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (0xF << OUTPINS_ਵਿੱਥ) );
	}

	ਵਾਪਸ -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
ਖਾਲੀ gpio_init()
{
	ਸੈੱਟ_pins(ਪੰਕਤੀ, ਖਾਨਾ);

	ਸੈੱਟ_ਕੁੰਜੀ_map(ਕੁੰਜੀ_ਸਾਰਣੀ);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
ਪੂਰਨ ਮੁੱਖ()
{
	ਪੂਰਨ prev_ਖਾਨਾ_ਪੰਕਤੀ = 0;
	gpio_init(); //Intialization of gpio //

	ਲਿਖੋ("\nGPIO Init Done");
	ਜਦੋਂ(1)
	{
		ਖਾਨਾ_ਪੰਕਤੀ = get_ਖਾਨਾ_ਪੰਕਤੀ();

		ਜੇ( ਖਾਨਾ_ਪੰਕਤੀ != -1 )
		{
			log_info("\nThe %x Key Pressed", ਖਾਨਾ_ਪੰਕਤੀ);
				delay_loop(600, 2000);
		}
	}

	ਵਾਪਸ 0;
}
