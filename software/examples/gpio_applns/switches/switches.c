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

#ಅನ್ತರ್ಭಾವ <stdio.h> //includes the definitions of standard input/output functions
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h" // includes definitions of gpio pins and read, write functions//
#ಅನ್ತರ್ಭಾವ "switch_driver.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#ವ್ಯಾಖ್ಯಾನಿಸು READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)


	ಆಗ(1){	
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#ವ್ಯಾಖ್ಯಾನಿಸು SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_0
		configure_switch(SW0);	
#ಆದರೆ_ಅಂತ್ಯ	

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_1
		configure_switch(SW1);	
#ಆದರೆ_ಅಂತ್ಯ	

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_2
		configure_switch(SW2);	
#ಆದರೆ_ಅಂತ್ಯ	

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_3
		configure_switch(SW3);	
#ಆದರೆ_ಅಂತ್ಯ				

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_ALL_SWITCHES	

		configure_all_switch();	

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_INDIVIDUAL_SWITCHES	

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_0
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG); /* Copies the GPIO_DATA_REG Register contents */
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x01000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x01000000)
			ಬರೆ("\n SW0: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n SW0: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_1
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x02000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x02000000)
			ಬರೆ("\n SW1: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n SW1: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_2
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = (read_ದತ್ತಾಂಶ_2 & 0x04000000);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x04000000)
			ಬರೆ("\n SW2: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n SW2: LOW");
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SW_3
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		ಆದರೆ(read_ದತ್ತಾಂಶ_2 == 0x08000000)
			ಬರೆ("\n SW3: HIGH"); 		
		ಇಲ್ಲದಿದ್ದರೆ
			ಬರೆ("\n SW3: LOW");
#ಆದರೆ_ಅಂತ್ಯ

		delay_loop(500, 500);

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ READ_ALL_SWITCHES	

		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		ಬರೆ("\n Read Data is :0x%x", read_ದತ್ತಾಂಶ_2);

		ಆಯ್ಕೆ(read_ದತ್ತಾಂಶ_2)
		{

		ಸ್ಥಿತಿ 0x00000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x01000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x02000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x03000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x04000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x05000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x06000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x07000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: LOW");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x08000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x09000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0A000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0B000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: LOW");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0C000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0D000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: LOW");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0E000000:
			ಬರೆ("\n SW0: LOW");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0x0F000000:
			ಬರೆ("\n SW0: HIGH");
			ಬರೆ("\n SW1: HIGH");
			ಬರೆ("\n SW2: HIGH");
			ಬರೆ("\n SW3: HIGH");
			ನಿಲ್ಲಿಸು;

		}

		delay_loop(500, 500);

#ಆದರೆ_ಅಂತ್ಯ
	}	
	delay_loop(500, 500);

#ಆದರೆ_ಅಂತ್ಯ
}
