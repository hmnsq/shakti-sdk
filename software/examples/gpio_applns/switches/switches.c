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

#شامل <stdio.h> //includes the definitions of standard input/output functions
#شامل "platform.h"
#شامل "gpio.h" // includes definitions of gpio pins and read, write functions//
#شامل "switch_driver.h"
#شامل "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#تعریف_کرو READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

غیرعلامتی طویل read_ڈیٹا_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
خالی مین()
{

#اگر defined(ARTIX7_35T) || defined(ARTIX7_100T)


	جب(1){	
#اگر_تعریف_شدہ READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#تعریف_کرو SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#اگر_تعریف_شدہ SW_0
		configure_switch(SW0);	
#اگر_ختم	

#اگر_تعریف_شدہ SW_1
		configure_switch(SW1);	
#اگر_ختم	

#اگر_تعریف_شدہ SW_2
		configure_switch(SW2);	
#اگر_ختم	

#اگر_تعریف_شدہ SW_3
		configure_switch(SW3);	
#اگر_ختم				

#اگر_ختم

#اگر_تعریف_شدہ READ_ALL_SWITCHES	

		configure_all_switch();	

#اگر_ختم

#اگر_تعریف_شدہ READ_INDIVIDUAL_SWITCHES	

#اگر_تعریف_شدہ SW_0
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG); /* Copies the GPIO_DATA_REG Register contents */
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x01000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x01000000)
			لکھو("\n SW0: HIGH"); 		
		ورنہ
			لکھو("\n SW0: LOW");
#اگر_ختم

#اگر_تعریف_شدہ SW_1
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x02000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x02000000)
			لکھو("\n SW1: HIGH"); 		
		ورنہ
			لکھو("\n SW1: LOW");
#اگر_ختم

#اگر_تعریف_شدہ SW_2
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x04000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x04000000)
			لکھو("\n SW2: HIGH"); 		
		ورنہ
			لکھو("\n SW2: LOW");
#اگر_ختم

#اگر_تعریف_شدہ SW_3
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x08000000)
			لکھو("\n SW3: HIGH"); 		
		ورنہ
			لکھو("\n SW3: LOW");
#اگر_ختم

		delay_loop(500, 500);

#اگر_ختم

#اگر_تعریف_شدہ READ_ALL_SWITCHES	

		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);

		انتخاب(read_ڈیٹا_2)
		{

		حالت 0x00000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x01000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x02000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x03000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x04000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x05000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x06000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x07000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: LOW");
			توڑو;

		حالت 0x08000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x09000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0A000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0B000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: LOW");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0C000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0D000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: LOW");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0E000000:
			لکھو("\n SW0: LOW");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			توڑو;

		حالت 0x0F000000:
			لکھو("\n SW0: HIGH");
			لکھو("\n SW1: HIGH");
			لکھو("\n SW2: HIGH");
			لکھو("\n SW3: HIGH");
			توڑو;

		}

		delay_loop(500, 500);

#اگر_ختم
	}	
	delay_loop(500, 500);

#اگر_ختم
}
