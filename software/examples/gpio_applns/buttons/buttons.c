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

#समावेश <stdio.h>        
#समावेश "platform.h"
#समावेश "gpio.h"         
#समावेश "button_driver.h"
#समावेश "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#घोषणा READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

अचिन्हित दीर्घ read_तथ्य_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
व्योम मुख्य()
{

#अगर defined(ARTIX7_35T) || defined(ARTIX7_100T)

	जबतक (1) {

#अगर_घोषित READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#घोषणा BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#अगर_घोषित BTN_0
		configure_btn(BTN0);
#पूर्ण_अगर

#अगर_घोषित BTN_1
		configure_btn(BTN1);
#पूर्ण_अगर

#अगर_घोषित BTN_2
		configure_btn(BTN2);
#पूर्ण_अगर

#अगर_घोषित BTN_3
		configure_btn(BTN3);
#पूर्ण_अगर

#पूर्ण_अगर

#अगर_घोषित READ_ALL_BTNS

		configure_all_btn();

#पूर्ण_अगर

#अगर_घोषित READ_INDIVIDUAL_BTNS

#अगर_घोषित BTN_0
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG); /* Copies the GPIO_DATA_REG Register contents */
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x10000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x10000000)
			म_लिखो("\n BTN0: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN0: LOW");
#पूर्ण_अगर

#अगर_घोषित BTN_1
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x20000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x20000000)
			म_लिखो("\n BTN1: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN1: LOW");
#पूर्ण_अगर

#अगर_घोषित BTN_2
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x40000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x40000000)
			म_लिखो("\n BTN2: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN2: LOW");
#पूर्ण_अगर

#अगर_घोषित BTN_3
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x80000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);

		अगर(read_तथ्य_2 == 0x80000000)
			म_लिखो("\n BTN3: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN3: LOW");
#पूर्ण_अगर

		delay_loop(500, 500);

#पूर्ण_अगर

#अगर_घोषित READ_ALL_BTNS	

		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);

		चयन(read_तथ्य_2)
		{

		हाल 0x00000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x10000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x20000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x30000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x40000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x50000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x60000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x70000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			अवरोध;

		हाल 0x80000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0x90000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xA0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xB0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xC0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xD0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xE0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;

		हाल 0xF0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			अवरोध;
		}

		delay_loop(500, 500);
#पूर्ण_अगर
	}
	delay_loop(500, 500);
#पूर्ण_अगर
}

