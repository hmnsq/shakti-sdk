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

#ضمن <stdio.h>        
#ضمن "platform.h"
#ضمن "gpio.h"         
#ضمن "button_driver.h"
#ضمن "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#تعریف_کړه READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

بینښه اوږد read_معلومات_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
فراغ اصلي()
{

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)

	طالما (1) {

#که_تعریف_شوی READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#تعریف_کړه BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#که_تعریف_شوی BTN_0
		configure_btn(BTN0);
#د_که_پای

#که_تعریف_شوی BTN_1
		configure_btn(BTN1);
#د_که_پای

#که_تعریف_شوی BTN_2
		configure_btn(BTN2);
#د_که_پای

#که_تعریف_شوی BTN_3
		configure_btn(BTN3);
#د_که_پای

#د_که_پای

#که_تعریف_شوی READ_ALL_BTNS

		configure_all_btn();

#د_که_پای

#که_تعریف_شوی READ_INDIVIDUAL_BTNS

#که_تعریف_شوی BTN_0
		read_معلومات_2 = read_کلمه(GPIO_معلومات_REG); /* Copies the GPIO_DATA_REG Register contents */
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x10000000);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x10000000)
			چاپ_کړه("\n BTN0: HIGH"); 		
		وإلا
			چاپ_کړه("\n BTN0: LOW");
#د_که_پای

#که_تعریف_شوی BTN_1
		read_معلومات_2 = read_کلمه(GPIO_معلومات_REG);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x20000000);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x20000000)
			چاپ_کړه("\n BTN1: HIGH"); 		
		وإلا
			چاپ_کړه("\n BTN1: LOW");
#د_که_پای

#که_تعریف_شوی BTN_2
		read_معلومات_2 = read_کلمه(GPIO_معلومات_REG);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x40000000);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x40000000)
			چاپ_کړه("\n BTN2: HIGH"); 		
		وإلا
			چاپ_کړه("\n BTN2: LOW");
#د_که_پای

#که_تعریف_شوی BTN_3
		read_معلومات_2 = read_کلمه(GPIO_معلومات_REG);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x80000000);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);

		إذا(read_معلومات_2 == 0x80000000)
			چاپ_کړه("\n BTN3: HIGH"); 		
		وإلا
			چاپ_کړه("\n BTN3: LOW");
#د_که_پای

		delay_loop(500, 500);

#د_که_پای

#که_تعریف_شوی READ_ALL_BTNS	

		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = read_کلمه(GPIO_معلومات_REG);
		چاپ_کړه("\n Read Data is :0x%x", read_معلومات_2);

		بدل(read_معلومات_2)
		{

		حالة 0x00000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x10000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x20000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x30000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x40000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x50000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x60000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x70000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: LOW");
			اكسر;

		حالة 0x80000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0x90000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xA0000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xB0000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: LOW");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xC0000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xD0000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: LOW");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xE0000000:
			چاپ_کړه("\n BTN0: LOW");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;

		حالة 0xF0000000:
			چاپ_کړه("\n BTN0: HIGH");
			چاپ_کړه("\n BTN1: HIGH");
			چاپ_کړه("\n BTN2: HIGH");
			چاپ_کړه("\n BTN3: HIGH");
			اكسر;
		}

		delay_loop(500, 500);
#د_که_پای
	}
	delay_loop(500, 500);
#د_که_پای
}

