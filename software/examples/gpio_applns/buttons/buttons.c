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
#تعریف_کن READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

بیعلامت دراز read_داده_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
فراغ اصلی()
{

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)

	طالما (1) {

#اگر_تعریف_شده READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#تعریف_کن BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#اگر_تعریف_شده BTN_0
		configure_btn(BTN0);
#پایان_اگر

#اگر_تعریف_شده BTN_1
		configure_btn(BTN1);
#پایان_اگر

#اگر_تعریف_شده BTN_2
		configure_btn(BTN2);
#پایان_اگر

#اگر_تعریف_شده BTN_3
		configure_btn(BTN3);
#پایان_اگر

#پایان_اگر

#اگر_تعریف_شده READ_ALL_BTNS

		configure_all_btn();

#پایان_اگر

#اگر_تعریف_شده READ_INDIVIDUAL_BTNS

#اگر_تعریف_شده BTN_0
		read_داده_2 = read_کلمه(GPIO_داده_REG); /* Copies the GPIO_DATA_REG Register contents */
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x10000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x10000000)
			چاپ_کن("\n BTN0: HIGH"); 		
		وإلا
			چاپ_کن("\n BTN0: LOW");
#پایان_اگر

#اگر_تعریف_شده BTN_1
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x20000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x20000000)
			چاپ_کن("\n BTN1: HIGH"); 		
		وإلا
			چاپ_کن("\n BTN1: LOW");
#پایان_اگر

#اگر_تعریف_شده BTN_2
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x40000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x40000000)
			چاپ_کن("\n BTN2: HIGH"); 		
		وإلا
			چاپ_کن("\n BTN2: LOW");
#پایان_اگر

#اگر_تعریف_شده BTN_3
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x80000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);

		إذا(read_داده_2 == 0x80000000)
			چاپ_کن("\n BTN3: HIGH"); 		
		وإلا
			چاپ_کن("\n BTN3: LOW");
#پایان_اگر

		delay_loop(500, 500);

#پایان_اگر

#اگر_تعریف_شده READ_ALL_BTNS	

		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);

		بدل(read_داده_2)
		{

		حالة 0x00000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x10000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x20000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x30000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x40000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x50000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x60000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x70000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: LOW");
			اكسر;

		حالة 0x80000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0x90000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xA0000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xB0000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: LOW");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xC0000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xD0000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: LOW");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xE0000000:
			چاپ_کن("\n BTN0: LOW");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;

		حالة 0xF0000000:
			چاپ_کن("\n BTN0: HIGH");
			چاپ_کن("\n BTN1: HIGH");
			چاپ_کن("\n BTN2: HIGH");
			چاپ_کن("\n BTN3: HIGH");
			اكسر;
		}

		delay_loop(500, 500);
#پایان_اگر
	}
	delay_loop(500, 500);
#پایان_اگر
}

