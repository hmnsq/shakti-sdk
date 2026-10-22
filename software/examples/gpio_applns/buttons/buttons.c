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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>        
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"         
#ਅਨ੍ਤਰ੍ਭਾਵ "button_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
ਖਾਲੀ ਮੁੱਖ()
{

#ਜੇ defined(ARTIX7_35T) || defined(ARTIX7_100T)

	ਜਦੋਂ (1) {

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_0
		configure_btn(BTN0);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_1
		configure_btn(BTN1);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_2
		configure_btn(BTN2);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_3
		configure_btn(BTN3);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_ALL_BTNS

		configure_all_btn();

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_INDIVIDUAL_BTNS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_0
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG); /* Copies the GPIO_DATA_REG Register contents */
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x10000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x10000000)
			ਲਿਖੋ("\n BTN0: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n BTN0: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_1
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x20000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x20000000)
			ਲਿਖੋ("\n BTN1: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n BTN1: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_2
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x40000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x40000000)
			ਲਿਖੋ("\n BTN2: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n BTN2: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BTN_3
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x80000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);

		ਜੇ(read_ਅੰਕੜੇ_2 == 0x80000000)
			ਲਿਖੋ("\n BTN3: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n BTN3: LOW");
#ਜੇ_ਅੰਤ

		delay_loop(500, 500);

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_ALL_BTNS	

		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);

		ਚੋਣ(read_ਅੰਕੜੇ_2)
		{

		ਹਾਲਤ 0x00000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x10000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x20000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x30000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x40000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x50000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x60000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x70000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x80000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x90000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xA0000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xB0000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: LOW");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xC0000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xD0000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: LOW");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xE0000000:
			ਲਿਖੋ("\n BTN0: LOW");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0xF0000000:
			ਲਿਖੋ("\n BTN0: HIGH");
			ਲਿਖੋ("\n BTN1: HIGH");
			ਲਿਖੋ("\n BTN2: HIGH");
			ਲਿਖੋ("\n BTN3: HIGH");
			ਰੋਕੋ;
		}

		delay_loop(500, 500);
#ਜੇ_ਅੰਤ
	}
	delay_loop(500, 500);
#ਜੇ_ਅੰਤ
}

