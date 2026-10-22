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

#ଅନ୍ତର୍ଭାଵ "gpio.h"
#ଅନ୍ତର୍ଭାଵ "platform.h"
#ଅନ୍ତର୍ଭାଵ "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି = -1;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା col_row = -1;

unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା row_pins[ROWNUM];
unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା col_pins[COLNUM];
unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା col[4]={0, 1, 2, 3};
unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା row[4]={4, 5, 6, 7};
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_map[COLNUM][ROWNUM];


ପୂର୍ଣ୍ଣସଂଖ୍ୟା  ଚାବି_table[4][4] =
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
ଶୂନ୍ୟ set_pins(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା*  row, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା* col)
{
	ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0 ; i < COLNUM ; i++)
	{
		col_pins[i] = col[i];// set col
	}
	ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0 ; j < ROWNUM ; j++) // set row
	{
		row_pins[j] = row[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
ଶୂନ୍ୟ set_ଚାବି_map(ପୂର୍ଣ୍ଣସଂଖ୍ୟା table[COLNUM][ROWNUM])
{
	ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0 ; i < COLNUM ; i++)
	{
		ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0 ; j < ROWNUM ; j++)
		{
			ଚାବି_map[i][j] = table[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_ଚାବି_another_way()
{

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (OUTPINS_OFFSET + i) )   );

		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0 ; j < ROWNUM ; j++)
		{
			ଯଦି ( ( read_word(row_pins[j]) & (INPINS << INPINS_OFFSET )  ) == 0)
			{
				ଫେରନ୍ତୁ ଚାବି_map[i][j];
			}
		}
		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	ଫେରନ୍ତୁ 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_ଚାବି(ପୂର୍ଣ୍ଣସଂଖ୍ୟା col_row)
{
    ଫେରନ୍ତୁ ଚାବି_map[col_row>>16][0xFFFF & col_row];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_col_row(ଶୂନ୍ୟ)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା col_row = 0;
	unsigned long read_ମୂଲ୍ୟ = 0;

	write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );

	ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0 ; i < COLNUM ; i++)
	{
		write_word(GPIO_DATA_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0 ; j < ROWNUM ; j++)
		{
			read_ମୂଲ୍ୟ =  read_word(GPIO_DATA_REG);

			ଯଦି( ( read_ମୂଲ୍ୟ & (1 << row_pins[j] ) ) == 0 )
			{
					ଫେରନ୍ତୁ ଚାବି_map[i][j];
			}
		}

		write_word(GPIO_DATA_REG, (0xF << OUTPINS_OFFSET) );
	}

	ଫେରନ୍ତୁ -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
ଶୂନ୍ୟ gpio_init()
{
	set_pins(row, col);

	set_ଚାବି_map(ଚାବି_table);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ()
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା prev_col_row = 0;
	gpio_init(); //Intialization of gpio //

	printf("\nGPIO Init Done");
	ଯେତେବେଳେ(1)
	{
		col_row = get_col_row();

		ଯଦି( col_row != -1 )
		{
			log_info("\nThe %x Key Pressed", col_row);
				delay_loop(600, 2000);
		}
	}

	ଫେରନ୍ତୁ 0;
}
