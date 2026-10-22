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

#ضمن <stdio.h> //includes the definitions of standard input/output functions
#ضمن "platform.h"
#ضمن "gpio.h" // includes definitions of gpio pins and read, write functions//
#ضمن "switch_driver.h"
#ضمن "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#تعریف_کن READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

بیعلامت دراز read_داده_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
فراغ اصلی()
{

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)


	طالما(1){	
#اگر_تعریف_شده READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#تعریف_کن SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#اگر_تعریف_شده SW_0
		configure_switch(SW0);	
#پایان_اگر	

#اگر_تعریف_شده SW_1
		configure_switch(SW1);	
#پایان_اگر	

#اگر_تعریف_شده SW_2
		configure_switch(SW2);	
#پایان_اگر	

#اگر_تعریف_شده SW_3
		configure_switch(SW3);	
#پایان_اگر				

#پایان_اگر

#اگر_تعریف_شده READ_ALL_SWITCHES	

		configure_all_switch();	

#پایان_اگر

#اگر_تعریف_شده READ_INDIVIDUAL_SWITCHES	

#اگر_تعریف_شده SW_0
		read_داده_2 = read_کلمه(GPIO_داده_REG); /* Copies the GPIO_DATA_REG Register contents */
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x01000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x01000000)
			چاپ_کن("\n SW0: HIGH"); 		
		وإلا
			چاپ_کن("\n SW0: LOW");
#پایان_اگر

#اگر_تعریف_شده SW_1
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x02000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x02000000)
			چاپ_کن("\n SW1: HIGH"); 		
		وإلا
			چاپ_کن("\n SW1: LOW");
#پایان_اگر

#اگر_تعریف_شده SW_2
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = (read_داده_2 & 0x04000000);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x04000000)
			چاپ_کن("\n SW2: HIGH"); 		
		وإلا
			چاپ_کن("\n SW2: LOW");
#پایان_اگر

#اگر_تعریف_شده SW_3
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		إذا(read_داده_2 == 0x08000000)
			چاپ_کن("\n SW3: HIGH"); 		
		وإلا
			چاپ_کن("\n SW3: LOW");
#پایان_اگر

		delay_loop(500, 500);

#پایان_اگر

#اگر_تعریف_شده READ_ALL_SWITCHES	

		چاپ_کن("\n Read Data is :0x%x", read_داده_2);
		read_داده_2 = read_کلمه(GPIO_داده_REG);
		چاپ_کن("\n Read Data is :0x%x", read_داده_2);

		بدل(read_داده_2)
		{

		حالة 0x00000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x01000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x02000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x03000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x04000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x05000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x06000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x07000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: LOW");
			اكسر;

		حالة 0x08000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x09000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0A000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0B000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: LOW");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0C000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0D000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: LOW");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0E000000:
			چاپ_کن("\n SW0: LOW");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		حالة 0x0F000000:
			چاپ_کن("\n SW0: HIGH");
			چاپ_کن("\n SW1: HIGH");
			چاپ_کن("\n SW2: HIGH");
			چاپ_کن("\n SW3: HIGH");
			اكسر;

		}

		delay_loop(500, 500);

#پایان_اگر
	}	
	delay_loop(500, 500);

#پایان_اگر
}
