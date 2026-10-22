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

#अन्तर्भाव <stdio.h>        
#अन्तर्भाव "platform.h"
#अन्तर्भाव "gpio.h"         
#अन्तर्भाव "button_driver.h"
#अन्तर्भाव "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#परिभाषय READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

अचिह्नित दीर्घ read_दत्त_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
शून्य मुख्यम्()
{

#यदि defined(ARTIX7_35T) || defined(ARTIX7_100T)

	यावत् (1) {

#यदि_परिभाषितम् READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#परिभाषय BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#यदि_परिभाषितम् BTN_0
		configure_btn(BTN0);
#यदि_अन्तः

#यदि_परिभाषितम् BTN_1
		configure_btn(BTN1);
#यदि_अन्तः

#यदि_परिभाषितम् BTN_2
		configure_btn(BTN2);
#यदि_अन्तः

#यदि_परिभाषितम् BTN_3
		configure_btn(BTN3);
#यदि_अन्तः

#यदि_अन्तः

#यदि_परिभाषितम् READ_ALL_BTNS

		configure_all_btn();

#यदि_अन्तः

#यदि_परिभाषितम् READ_INDIVIDUAL_BTNS

#यदि_परिभाषितम् BTN_0
		read_दत्त_2 = read_word(GPIO_दत्त_REG); /* Copies the GPIO_DATA_REG Register contents */
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x10000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x10000000)
			प्रारूप_लिख("\n BTN0: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n BTN0: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् BTN_1
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x20000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x20000000)
			प्रारूप_लिख("\n BTN1: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n BTN1: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् BTN_2
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x40000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x40000000)
			प्रारूप_लिख("\n BTN2: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n BTN2: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् BTN_3
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x80000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);

		यदि(read_दत्त_2 == 0x80000000)
			प्रारूप_लिख("\n BTN3: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n BTN3: LOW");
#यदि_अन्तः

		delay_loop(500, 500);

#यदि_अन्तः

#यदि_परिभाषितम् READ_ALL_BTNS	

		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);

		विकल्प(read_दत्त_2)
		{

		पक्ष 0x00000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x10000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x20000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x30000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x40000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x50000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x60000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x70000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: LOW");
			भङ्ग;

		पक्ष 0x80000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0x90000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xA0000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xB0000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: LOW");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xC0000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xD0000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: LOW");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xE0000000:
			प्रारूप_लिख("\n BTN0: LOW");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;

		पक्ष 0xF0000000:
			प्रारूप_लिख("\n BTN0: HIGH");
			प्रारूप_लिख("\n BTN1: HIGH");
			प्रारूप_लिख("\n BTN2: HIGH");
			प्रारूप_लिख("\n BTN3: HIGH");
			भङ्ग;
		}

		delay_loop(500, 500);
#यदि_अन्तः
	}
	delay_loop(500, 500);
#यदि_अन्तः
}

