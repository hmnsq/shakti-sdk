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

#समावेश <stdio.h> //includes the definitions of standard input/output functions
#समावेश "platform.h"
#समावेश "gpio.h" // includes definitions of gpio pins and read, write functions//
#समावेश "switch_driver.h"
#समावेश "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#घोषणा READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

अचिन्हित दीर्घ read_तथ्य_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
व्योम मुख्य()
{

#अगर defined(ARTIX7_35T) || defined(ARTIX7_100T)


	जबतक(1){	
#अगर_घोषित READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#घोषणा SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#अगर_घोषित SW_0
		configure_switch(SW0);	
#पूर्ण_अगर	

#अगर_घोषित SW_1
		configure_switch(SW1);	
#पूर्ण_अगर	

#अगर_घोषित SW_2
		configure_switch(SW2);	
#पूर्ण_अगर	

#अगर_घोषित SW_3
		configure_switch(SW3);	
#पूर्ण_अगर				

#पूर्ण_अगर

#अगर_घोषित READ_ALL_SWITCHES	

		configure_all_switch();	

#पूर्ण_अगर

#अगर_घोषित READ_INDIVIDUAL_SWITCHES	

#अगर_घोषित SW_0
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG); /* Copies the GPIO_DATA_REG Register contents */
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x01000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x01000000)
			म_लिखो("\n SW0: HIGH"); 		
		अन्यथा
			म_लिखो("\n SW0: LOW");
#पूर्ण_अगर

#अगर_घोषित SW_1
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x02000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x02000000)
			म_लिखो("\n SW1: HIGH"); 		
		अन्यथा
			म_लिखो("\n SW1: LOW");
#पूर्ण_अगर

#अगर_घोषित SW_2
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = (read_तथ्य_2 & 0x04000000);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x04000000)
			म_लिखो("\n SW2: HIGH"); 		
		अन्यथा
			म_लिखो("\n SW2: LOW");
#पूर्ण_अगर

#अगर_घोषित SW_3
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		अगर(read_तथ्य_2 == 0x08000000)
			म_लिखो("\n SW3: HIGH"); 		
		अन्यथा
			म_लिखो("\n SW3: LOW");
#पूर्ण_अगर

		delay_loop(500, 500);

#पूर्ण_अगर

#अगर_घोषित READ_ALL_SWITCHES	

		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);
		read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
		म_लिखो("\n Read Data is :0x%x", read_तथ्य_2);

		चयन(read_तथ्य_2)
		{

		हाल 0x00000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x01000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x02000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x03000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x04000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x05000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x06000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x07000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: LOW");
			अवरोध;

		हाल 0x08000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x09000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0A000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0B000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: LOW");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0C000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0D000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: LOW");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0E000000:
			म_लिखो("\n SW0: LOW");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		हाल 0x0F000000:
			म_लिखो("\n SW0: HIGH");
			म_लिखो("\n SW1: HIGH");
			म_लिखो("\n SW2: HIGH");
			म_लिखो("\n SW3: HIGH");
			अवरोध;

		}

		delay_loop(500, 500);

#पूर्ण_अगर
	}	
	delay_loop(500, 500);

#पूर्ण_अगर
}
