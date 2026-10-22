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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h> //includes the definitions of standard input/output functions
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h" // includes definitions of gpio pins and read, write functions//
#ਅਨ੍ਤਰ੍ਭਾਵ "switch_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
ਖਾਲੀ ਮੁੱਖ()
{

#ਜੇ defined(ARTIX7_35T) || defined(ARTIX7_100T)


	ਜਦੋਂ(1){	
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_0
		configure_switch(SW0);	
#ਜੇ_ਅੰਤ	

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_1
		configure_switch(SW1);	
#ਜੇ_ਅੰਤ	

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_2
		configure_switch(SW2);	
#ਜੇ_ਅੰਤ	

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_3
		configure_switch(SW3);	
#ਜੇ_ਅੰਤ				

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_ALL_SWITCHES	

		configure_all_switch();	

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_INDIVIDUAL_SWITCHES	

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_0
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG); /* Copies the GPIO_DATA_REG Register contents */
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x01000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x01000000)
			ਲਿਖੋ("\n SW0: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n SW0: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_1
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x02000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x02000000)
			ਲਿਖੋ("\n SW1: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n SW1: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_2
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = (read_ਅੰਕੜੇ_2 & 0x04000000);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x04000000)
			ਲਿਖੋ("\n SW2: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n SW2: LOW");
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SW_3
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		ਜੇ(read_ਅੰਕੜੇ_2 == 0x08000000)
			ਲਿਖੋ("\n SW3: HIGH"); 		
		ਨਹੀਂਤਾਂ
			ਲਿਖੋ("\n SW3: LOW");
#ਜੇ_ਅੰਤ

		delay_loop(500, 500);

#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ READ_ALL_SWITCHES	

		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		ਲਿਖੋ("\n Read Data is :0x%x", read_ਅੰਕੜੇ_2);

		ਚੋਣ(read_ਅੰਕੜੇ_2)
		{

		ਹਾਲਤ 0x00000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x01000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x02000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x03000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x04000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x05000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x06000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x07000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: LOW");
			ਰੋਕੋ;

		ਹਾਲਤ 0x08000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x09000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0A000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0B000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: LOW");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0C000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0D000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: LOW");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0E000000:
			ਲਿਖੋ("\n SW0: LOW");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		ਹਾਲਤ 0x0F000000:
			ਲਿਖੋ("\n SW0: HIGH");
			ਲਿਖੋ("\n SW1: HIGH");
			ਲਿਖੋ("\n SW2: HIGH");
			ਲਿਖੋ("\n SW3: HIGH");
			ਰੋਕੋ;

		}

		delay_loop(500, 500);

#ਜੇ_ਅੰਤ
	}	
	delay_loop(500, 500);

#ਜੇ_ਅੰਤ
}
