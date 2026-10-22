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

#అన్తర్భావ "gpio.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "keypad.h"//Includes the definitions of keypad function//

/* global variable definition*/

// initialize key and colrow to -1 indicate no key is pressed
పూర్ణాంకం కీలకం = -1;
పూర్ణాంకం నిలువు_అడ్డువరుస = -1;

గుర్తులేని పూర్ణాంకం అడ్డువరుస_pins[ROWNUM];
గుర్తులేని పూర్ణాంకం నిలువు_pins[COLNUM];
గుర్తులేని పూర్ణాంకం నిలువు[4]={0, 1, 2, 3};
గుర్తులేని పూర్ణాంకం అడ్డువరుస[4]={4, 5, 6, 7};
పూర్ణాంకం కీలకం_map[COLNUM][ROWNUM];


పూర్ణాంకం  కీలకం_పట్టిక[4][4] =
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
శూన్య సమితి_pins(గుర్తులేని పూర్ణాంకం*  అడ్డువరుస, గుర్తులేని పూర్ణాంకం* నిలువు)
{
	కొరకు(పూర్ణాంకం i = 0 ; i < COLNUM ; i++)
	{
		నిలువు_pins[i] = నిలువు[i];// set col
	}
	కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++) // set row
	{
		అడ్డువరుస_pins[j] = అడ్డువరుస[j];
	}
}

/** @fn void set_key_map(int table[COLNUM][ROWNUM])
 * @brief This function maps table in to keymap
 * @details Fills the passed array values into key_map array.
 * @param int table
 */
శూన్య సమితి_కీలకం_map(పూర్ణాంకం పట్టిక[COLNUM][ROWNUM])
{
	కొరకు(పూర్ణాంకం i = 0 ; i < COLNUM ; i++)
	{
		కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++)
		{
			కీలకం_map[i][j] = పట్టిక[i][j];
		}
	}
}

/** @fn int get_key_another_way()
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @return Key value pressed
 */
పూర్ణాంకం get_కీలకం_another_way()
{

	write_మాట(GPIO_దత్తాంశం_REG, (0xF << OUTPINS_స్థానభ్రంశం) );

	కొరకు (పూర్ణాంకం i = 0 ; i < COLNUM ; i++)
	{
		write_మాట(GPIO_దత్తాంశం_REG, ~(0x1 << (OUTPINS_స్థానభ్రంశం + i) )   );

		కొరకు (పూర్ణాంకం j = 0 ; j < ROWNUM ; j++)
		{
			ఒకవేళ ( ( read_మాట(అడ్డువరుస_pins[j]) & (INPINS << INPINS_స్థానభ్రంశం )  ) == 0)
			{
				తిరిగి కీలకం_map[i][j];
			}
		}
		write_మాట(GPIO_దత్తాంశం_REG, (0xF << OUTPINS_స్థానభ్రంశం) );
	}

	తిరిగి 0;
}

/** @fn int get_key(int col_row)
 * @brief This function returns the corresponding value in the keymap
 * @details Detects the press key based on the row value in a particular colomun
 * and returns the decoded key value.
 * @param int col row
 * @return Key value pressed
 */
పూర్ణాంకం get_కీలకం(పూర్ణాంకం నిలువు_అడ్డువరుస)
{
    తిరిగి కీలకం_map[నిలువు_అడ్డువరుస>>16][0xFFFF & నిలువు_అడ్డువరుస];
}

/** @fn int get_col_row(void)
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return Column and row combination.
 */
పూర్ణాంకం get_నిలువు_అడ్డువరుస(శూన్య)
{
	పూర్ణాంకం నిలువు_అడ్డువరుస = 0;
	గుర్తులేని దీర్ఘ read_విలువ = 0;

	write_మాట(GPIO_దత్తాంశం_REG, (0xF << OUTPINS_స్థానభ్రంశం) );

	కొరకు(పూర్ణాంకం i = 0 ; i < COLNUM ; i++)
	{
		write_మాట(GPIO_దత్తాంశం_REG, ~(0x1 << (/* OUTPINS_OFFSET  +*/ i) )   );

		కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++)
		{
			read_విలువ =  read_మాట(GPIO_దత్తాంశం_REG);

			ఒకవేళ( ( read_విలువ & (1 << అడ్డువరుస_pins[j] ) ) == 0 )
			{
					తిరిగి కీలకం_map[i][j];
			}
		}

		write_మాట(GPIO_దత్తాంశం_REG, (0xF << OUTPINS_స్థానభ్రంశం) );
	}

	తిరిగి -1;
}

/** @fn void gpio_init()
 * @brief This maps the keypad from pins
 * @details  Initialises Rows pins and coloumn pins of the mapped GPIO lines to keypad.  
 */
శూన్య gpio_init()
{
	సమితి_pins(అడ్డువరుస, నిలువు);

	సమితి_కీలకం_map(కీలకం_పట్టిక);

	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_మాట(GPIO_DIRECTION_CNTRL_REG, OUTPINS);
}

/** @fn int main()
 * @brief Detects the pressed key
 * @details  Detects the pressed key and prints its decoded value.  
 * @return Zero 
 */
పూర్ణాంకం ప్రధాన()
{
	పూర్ణాంకం prev_నిలువు_అడ్డువరుస = 0;
	gpio_init(); //Intialization of gpio //

	రాయి("\nGPIO Init Done");
	అయితే(1)
	{
		నిలువు_అడ్డువరుస = get_నిలువు_అడ్డువరుస();

		ఒకవేళ( నిలువు_అడ్డువరుస != -1 )
		{
			log_info("\nThe %x Key Pressed", నిలువు_అడ్డువరుస);
				delay_loop(600, 2000);
		}
	}

	తిరిగి 0;
}
