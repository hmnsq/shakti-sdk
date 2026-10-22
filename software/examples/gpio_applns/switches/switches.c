/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: switches.c
* Brief Description of file     : Read the value from the switches
* Name of Author    	        : Madan Kumar S
* Email ID                      : kumarmadan96@gmail.com

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

***************************************************************************/
/**
@file switches.c
@brief Read the value from the switches
@detail 
*/

#ضمن <stdio.h> //includes the definitions of standard input/output functions
#ضمن "platform.h"
#ضمن "gpio.h" // includes definitions of gpio pins and read, write functions//
#ضمن "switch_driver.h"
#ضمن "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#تعریف_کرو READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

بنانشانی لما read_انکڑے_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
فراغ مکھ()
{

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)


	طالما(1){	
#جے_تعریف_شدہ READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#تعریف_کرو SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#جے_تعریف_شدہ SW_0
		configure_switch(SW0);	
#جے_انت	

#جے_تعریف_شدہ SW_1
		configure_switch(SW1);	
#جے_انت	

#جے_تعریف_شدہ SW_2
		configure_switch(SW2);	
#جے_انت	

#جے_تعریف_شدہ SW_3
		configure_switch(SW3);	
#جے_انت				

#جے_انت

#جے_تعریف_شدہ READ_ALL_SWITCHES	

		configure_all_switch();	

#جے_انت

#جے_تعریف_شدہ READ_INDIVIDUAL_SWITCHES	

#جے_تعریف_شدہ SW_0
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG); /* Copies the GPIO_DATA_REG Register contents */
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		read_انکڑے_2 = (read_انکڑے_2 & 0x01000000);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		إذا(read_انکڑے_2 == 0x01000000)
			لکھو("\n SW0: HIGH"); 		
		وإلا
			لکھو("\n SW0: LOW");
#جے_انت

#جے_تعریف_شدہ SW_1
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		read_انکڑے_2 = (read_انکڑے_2 & 0x02000000);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		إذا(read_انکڑے_2 == 0x02000000)
			لکھو("\n SW1: HIGH"); 		
		وإلا
			لکھو("\n SW1: LOW");
#جے_انت

#جے_تعریف_شدہ SW_2
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		read_انکڑے_2 = (read_انکڑے_2 & 0x04000000);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		إذا(read_انکڑے_2 == 0x04000000)
			لکھو("\n SW2: HIGH"); 		
		وإلا
			لکھو("\n SW2: LOW");
#جے_انت

#جے_تعریف_شدہ SW_3
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		إذا(read_انکڑے_2 == 0x08000000)
			لکھو("\n SW3: HIGH"); 		
		وإلا
			لکھو("\n SW3: LOW");
#جے_انت

		delay_loop(500, 500);

#جے_انت

#جے_تعریف_شدہ READ_ALL_SWITCHES	

		لکھو("\n Read Data is :0x%x", read_انکڑے_2);
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);
		لکھو("\n Read Data is :0x%x", read_انکڑے_2);

		بدل(read_انکڑے_2)
		{

		حالة 0x00000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x01000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x02000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x03000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x04000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x05000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x06000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x07000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			اكسر;

		حالة 0x08000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x09000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0A000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0B000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0C000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0D000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0E000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			اكسر;

		حالة 0x0F000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			اكسر;

		}

		delay_loop(500, 500);

#جے_انت
	}	
	delay_loop(500, 500);

#جے_انت
}
