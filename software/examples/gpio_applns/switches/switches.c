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

#अन्तर्भाव <stdio.h> //includes the definitions of standard input/output functions
#अन्तर्भाव "platform.h"
#अन्तर्भाव "gpio.h" // includes definitions of gpio pins and read, write functions//
#अन्तर्भाव "switch_driver.h"
#अन्तर्भाव "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#परिभाषय READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

अचिह्नित दीर्घ read_दत्त_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
शून्य मुख्यम्()
{

#यदि defined(ARTIX7_35T) || defined(ARTIX7_100T)


	यावत्(1){	
#यदि_परिभाषितम् READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#परिभाषय SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#यदि_परिभाषितम् SW_0
		configure_switch(SW0);	
#यदि_अन्तः	

#यदि_परिभाषितम् SW_1
		configure_switch(SW1);	
#यदि_अन्तः	

#यदि_परिभाषितम् SW_2
		configure_switch(SW2);	
#यदि_अन्तः	

#यदि_परिभाषितम् SW_3
		configure_switch(SW3);	
#यदि_अन्तः				

#यदि_अन्तः

#यदि_परिभाषितम् READ_ALL_SWITCHES	

		configure_all_switch();	

#यदि_अन्तः

#यदि_परिभाषितम् READ_INDIVIDUAL_SWITCHES	

#यदि_परिभाषितम् SW_0
		read_दत्त_2 = read_word(GPIO_दत्त_REG); /* Copies the GPIO_DATA_REG Register contents */
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x01000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x01000000)
			प्रारूप_लिख("\n SW0: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n SW0: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् SW_1
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x02000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x02000000)
			प्रारूप_लिख("\n SW1: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n SW1: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् SW_2
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = (read_दत्त_2 & 0x04000000);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x04000000)
			प्रारूप_लिख("\n SW2: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n SW2: LOW");
#यदि_अन्तः

#यदि_परिभाषितम् SW_3
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		यदि(read_दत्त_2 == 0x08000000)
			प्रारूप_लिख("\n SW3: HIGH"); 		
		अन्यथा
			प्रारूप_लिख("\n SW3: LOW");
#यदि_अन्तः

		delay_loop(500, 500);

#यदि_अन्तः

#यदि_परिभाषितम् READ_ALL_SWITCHES	

		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);
		read_दत्त_2 = read_word(GPIO_दत्त_REG);
		प्रारूप_लिख("\n Read Data is :0x%x", read_दत्त_2);

		विकल्प(read_दत्त_2)
		{

		पक्ष 0x00000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x01000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x02000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x03000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x04000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x05000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x06000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x07000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: LOW");
			भङ्ग;

		पक्ष 0x08000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x09000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0A000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0B000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: LOW");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0C000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0D000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: LOW");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0E000000:
			प्रारूप_लिख("\n SW0: LOW");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		पक्ष 0x0F000000:
			प्रारूप_लिख("\n SW0: HIGH");
			प्रारूप_लिख("\n SW1: HIGH");
			प्रारूप_लिख("\n SW2: HIGH");
			प्रारूप_लिख("\n SW3: HIGH");
			भङ्ग;

		}

		delay_loop(500, 500);

#यदि_अन्तः
	}	
	delay_loop(500, 500);

#यदि_अन्तः
}
