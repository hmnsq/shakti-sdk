/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: buttons.c
 * Brief Description of file    : Read the value from the switches
 * Name of Author    	        : Madan Kumar S
 * Email ID                     : kumarmadan96@gmail.com

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
@file  buttons.c
@brief Contains the driver routines to read the pressed button.
@detail Detects the pressed key/button and prints pressed button.
*/

#شامل <stdio.h>        
#شامل "platform.h"
#شامل "gpio.h"         
#شامل "button_driver.h"
#شامل "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#تعریف_کرو READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

غیرعلامتی طویل read_ڈیٹا_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
خالی مین()
{

#اگر defined(ARTIX7_35T) || defined(ARTIX7_100T)

	جب (1) {

#اگر_تعریف_شدہ READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#تعریف_کرو BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#اگر_تعریف_شدہ BTN_0
		configure_btn(BTN0);
#اگر_ختم

#اگر_تعریف_شدہ BTN_1
		configure_btn(BTN1);
#اگر_ختم

#اگر_تعریف_شدہ BTN_2
		configure_btn(BTN2);
#اگر_ختم

#اگر_تعریف_شدہ BTN_3
		configure_btn(BTN3);
#اگر_ختم

#اگر_ختم

#اگر_تعریف_شدہ READ_ALL_BTNS

		configure_all_btn();

#اگر_ختم

#اگر_تعریف_شدہ READ_INDIVIDUAL_BTNS

#اگر_تعریف_شدہ BTN_0
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG); /* Copies the GPIO_DATA_REG Register contents */
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x10000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x10000000)
			لکھو("\n BTN0: HIGH"); 		
		ورنہ
			لکھو("\n BTN0: LOW");
#اگر_ختم

#اگر_تعریف_شدہ BTN_1
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x20000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x20000000)
			لکھو("\n BTN1: HIGH"); 		
		ورنہ
			لکھو("\n BTN1: LOW");
#اگر_ختم

#اگر_تعریف_شدہ BTN_2
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x40000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		اگر(read_ڈیٹا_2 == 0x40000000)
			لکھو("\n BTN2: HIGH"); 		
		ورنہ
			لکھو("\n BTN2: LOW");
#اگر_ختم

#اگر_تعریف_شدہ BTN_3
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = (read_ڈیٹا_2 & 0x80000000);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);

		اگر(read_ڈیٹا_2 == 0x80000000)
			لکھو("\n BTN3: HIGH"); 		
		ورنہ
			لکھو("\n BTN3: LOW");
#اگر_ختم

		delay_loop(500, 500);

#اگر_ختم

#اگر_تعریف_شدہ READ_ALL_BTNS	

		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);
		read_ڈیٹا_2 = read_لفظ(GPIO_ڈیٹا_REG);
		لکھو("\n Read Data is :0x%x", read_ڈیٹا_2);

		انتخاب(read_ڈیٹا_2)
		{

		حالت 0x00000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x10000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x20000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x30000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x40000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x50000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x60000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x70000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: LOW");
			توڑو;

		حالت 0x80000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0x90000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xA0000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xB0000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: LOW");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xC0000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xD0000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: LOW");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xE0000000:
			لکھو("\n BTN0: LOW");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: HIGH");
			توڑو;

		حالت 0xF0000000:
			لکھو("\n BTN0: HIGH");
			لکھو("\n BTN1: HIGH");
			لکھو("\n BTN2: HIGH");
			لکھو("\n BTN3: HIGH");
			توڑو;
		}

		delay_loop(500, 500);
#اگر_ختم
	}
	delay_loop(500, 500);
#اگر_ختم
}

