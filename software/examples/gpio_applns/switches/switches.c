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
#وصف_ڪريو READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

بنانشان ڊگهو read_معلومات_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
فراغ مکيه()
{

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)


	طالما(1){	
#جيڪڏهن_وصف_ٿيل READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#وصف_ڪريو SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#جيڪڏهن_وصف_ٿيل SW_0
		configure_switch(SW0);	
#جيڪڏهن_پورو	

#جيڪڏهن_وصف_ٿيل SW_1
		configure_switch(SW1);	
#جيڪڏهن_پورو	

#جيڪڏهن_وصف_ٿيل SW_2
		configure_switch(SW2);	
#جيڪڏهن_پورو	

#جيڪڏهن_وصف_ٿيل SW_3
		configure_switch(SW3);	
#جيڪڏهن_پورو				

#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل READ_ALL_SWITCHES	

		configure_all_switch();	

#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل READ_INDIVIDUAL_SWITCHES	

#جيڪڏهن_وصف_ٿيل SW_0
		read_معلومات_2 = read_لفظ(GPIO_معلومات_REG); /* Copies the GPIO_DATA_REG Register contents */
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x01000000);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x01000000)
			لکو("\n SW0: HIGH"); 		
		وإلا
			لکو("\n SW0: LOW");
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SW_1
		read_معلومات_2 = read_لفظ(GPIO_معلومات_REG);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x02000000);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x02000000)
			لکو("\n SW1: HIGH"); 		
		وإلا
			لکو("\n SW1: LOW");
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SW_2
		read_معلومات_2 = read_لفظ(GPIO_معلومات_REG);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = (read_معلومات_2 & 0x04000000);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x04000000)
			لکو("\n SW2: HIGH"); 		
		وإلا
			لکو("\n SW2: LOW");
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SW_3
		read_معلومات_2 = read_لفظ(GPIO_معلومات_REG);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		لکو("\n Read Data is :0x%x", read_معلومات_2);
		إذا(read_معلومات_2 == 0x08000000)
			لکو("\n SW3: HIGH"); 		
		وإلا
			لکو("\n SW3: LOW");
#جيڪڏهن_پورو

		delay_loop(500, 500);

#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل READ_ALL_SWITCHES	

		لکو("\n Read Data is :0x%x", read_معلومات_2);
		read_معلومات_2 = read_لفظ(GPIO_معلومات_REG);
		لکو("\n Read Data is :0x%x", read_معلومات_2);

		بدل(read_معلومات_2)
		{

		حالة 0x00000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: LOW");
			لکو("\n SW2: LOW");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x01000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: LOW");
			لکو("\n SW2: LOW");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x02000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: LOW");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x03000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: LOW");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x04000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: LOW");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x05000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: LOW");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x06000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x07000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: LOW");
			اكسر;

		حالة 0x08000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: LOW");
			لکو("\n SW2: LOW");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x09000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: LOW");
			لکو("\n SW2: LOW");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0A000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: LOW");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0B000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: LOW");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0C000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: LOW");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0D000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: LOW");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0E000000:
			لکو("\n SW0: LOW");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: HIGH");
			اكسر;

		حالة 0x0F000000:
			لکو("\n SW0: HIGH");
			لکو("\n SW1: HIGH");
			لکو("\n SW2: HIGH");
			لکو("\n SW3: HIGH");
			اكسر;

		}

		delay_loop(500, 500);

#جيڪڏهن_پورو
	}	
	delay_loop(500, 500);

#جيڪڏهن_پورو
}
