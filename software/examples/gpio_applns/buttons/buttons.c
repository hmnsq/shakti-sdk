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

#ಅನ್ತರ್ಭಾವ <stdio.h>        
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"         
#ಅನ್ತರ್ಭಾವ "button_driver.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#ವ್ಯಾಖ್ಯಾನಿಸು READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

	ಆಗ (1) {

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_0
		configure_btn(BTN0);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_1
		configure_btn(BTN1);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_2
		configure_btn(BTN2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_3
		configure_btn(BTN3);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_ALL_BTNS

		configure_all_btn();

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_INDIVIDUAL_BTNS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_0
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG); /* Copies the GPIO_DATA_REG Register contents */
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x10000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x10000000)
			ಬರೆ("\n BTN0: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n BTN0: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_1
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x20000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x20000000)
			ಬರೆ("\n BTN1: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n BTN1: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_2
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x40000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x40000000)
			ಬರೆ("\n BTN2: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n BTN2: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BTN_3
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x80000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);

		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x80000000)
			ಬರೆ("\n BTN3: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n BTN3: LOW");
#ಆದರೆ_ಅಂತ್ಯ

		delay_loop(500, 500);

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_ALL_BTNS	

		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);

		ಆಯ್ಕೆ(read_ದತ್ತಾಂಶ_2)
		{

		ಸ್ಥಿತಿ 0x00000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x10000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x20000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x30000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x40000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x50000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x60000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x70000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x80000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x90000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xA0000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xB0000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: LOW");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xC0000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xD0000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: LOW");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xE0000000:
			ಬರೆ("\n BTN0: LOW");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0xF0000000:
			ಬರೆ("\n BTN0: HIGH");
			ಬರೆ("\n BTN1: HIGH");
			ಬರೆ("\n BTN2: HIGH");
			ಬರೆ("\n BTN3: HIGH");
			ನಿಲ್ಲಿಸು;
		}

		delay_loop(500, 500);
#ಆದರೆ_ಅಂತ್ಯ
	}
	delay_loop(500, 500);
#ಆದರೆ_ಅಂತ್ಯ
}

