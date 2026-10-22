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

#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
ಪೂರ್ಣಾಂಕ ಕೀಲಿ = -1;
ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = -1;

ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_pins[ROWNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_pins[COLNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು[4]={0, 1, 2, 3};
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು[4]={4, 5, 6, 7};
ಪೂರ್ಣಾಂಕ ಕೀಲಿ_map[COLNUM][ROWNUM];


ಪೂರ್ಣಾಂಕ  ಕೀಲಿ_ಕೋಷ್ಟಕ[4][4] =
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
ಶೂನ್ಯ ಗಣ_pins(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ*  ಅಡ್ಡಸಾಲು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಲಂಬಸಾಲು)
{
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++)
	{
		ಲಂಬಸಾಲು_pins[i] = ಲಂಬಸಾಲು[i];// set col
	}
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++) // set row
	{
		ಅಡ್ಡಸಾಲು_pins[j] = ಅಡ್ಡಸಾಲು[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
ಶೂನ್ಯ ಗಣ_ಕೀಲಿ_map(ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ[COLNUM][ROWNUM])
{
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++)
	{
		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++)
		{
			ಕೀಲಿ_map[i][j] = ಕೋಷ್ಟಕ[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ_another_way()
{

	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) );

	ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++)
	{
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, ~(0x1 << (OUTPINS_ಸ್ಥಾನಾಂತರ + i) )   );

		ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++)
		{
			ಆದರೆ ( ( read_ಶಬ್ದ(ಅಡ್ಡಸಾಲು_pins[j]) & (INPINS << INPINS_ಸ್ಥಾನಾಂತರ )  ) == 0)
			{
				ಹಿಂತಿರುಗಿ ಕೀಲಿ_map[i][j];
			}
		}
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) );
	}

	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ(ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು)
{
    ಹಿಂತಿರುಗಿ ಕೀಲಿ_map[ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು>>16][0xFFFF & ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ಮೌಲ್ಯ = 0;

	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) );

	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++)
	{
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++)
		{
			read_ಮೌಲ್ಯ =  read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);

			ಆದರೆ( ( read_ಮೌಲ್ಯ & (1 << ಅಡ್ಡಸಾಲು_pins[j] ) ) == 0 )
			{
					ಹಿಂತಿರುಗಿ ಕೀಲಿ_map[i][j];
			}
		}

		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) );
	}

	ಹಿಂತಿರುಗಿ -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
ಶೂನ್ಯ gpio_init()
{
	ಗಣ_pins(ಅಡ್ಡಸಾಲು, ಲಂಬಸಾಲು);

	ಗಣ_ಕೀಲಿ_map(ಕೀಲಿ_ಕೋಷ್ಟಕ);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ prev_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = 0;
	gpio_init(); //Intialization of gpio //

	ಬರೆ("\nGPIO Init Done");
	ಆಗ(1)
	{
		ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು();

		ಆದರೆ( ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು != -1 )
		{
			log_info("\nThe %x Key Pressed", ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು);
				delay_loop(600, 2000);
		}
	}

	ಹಿಂತಿರುಗಿ 0;
}
