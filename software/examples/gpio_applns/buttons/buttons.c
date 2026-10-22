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
#define READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

अचिन्हित दीर्घ read_data = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
शून्य main()
{

#जर defined(ARTIX7_35T) || defined(ARTIX7_100T)

	पर्यंत (1) {

#ifdef READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#define BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#ifdef BTN_0
		configure_btn(BTN0);
#endif

#ifdef BTN_1
		configure_btn(BTN1);
#endif

#ifdef BTN_2
		configure_btn(BTN2);
#endif

#ifdef BTN_3
		configure_btn(BTN3);
#endif

#endif

#ifdef READ_ALL_BTNS

		configure_all_btn();

#endif

#ifdef READ_INDIVIDUAL_BTNS

#ifdef BTN_0
		read_data = read_word(GPIO_DATA_REG); /* Copies the GPIO_DATA_REG Register contents */
		म_लिखो("\n Read Data is :0x%x", read_data);
		read_data = (read_data & 0x10000000);
		म_लिखो("\n Read Data is :0x%x", read_data);
		जर(read_data == 0x10000000)
			म_लिखो("\n BTN0: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN0: LOW");
#endif

#ifdef BTN_1
		read_data = read_word(GPIO_DATA_REG);
		म_लिखो("\n Read Data is :0x%x", read_data);
		read_data = (read_data & 0x20000000);
		म_लिखो("\n Read Data is :0x%x", read_data);
		जर(read_data == 0x20000000)
			म_लिखो("\n BTN1: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN1: LOW");
#endif

#ifdef BTN_2
		read_data = read_word(GPIO_DATA_REG);
		म_लिखो("\n Read Data is :0x%x", read_data);
		read_data = (read_data & 0x40000000);
		म_लिखो("\n Read Data is :0x%x", read_data);
		जर(read_data == 0x40000000)
			म_लिखो("\n BTN2: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN2: LOW");
#endif

#ifdef BTN_3
		read_data = read_word(GPIO_DATA_REG);
		म_लिखो("\n Read Data is :0x%x", read_data);
		read_data = (read_data & 0x80000000);
		म_लिखो("\n Read Data is :0x%x", read_data);

		जर(read_data == 0x80000000)
			म_लिखो("\n BTN3: HIGH"); 		
		अन्यथा
			म_लिखो("\n BTN3: LOW");
#endif

		delay_loop(500, 500);

#endif

#ifdef READ_ALL_BTNS	

		म_लिखो("\n Read Data is :0x%x", read_data);
		read_data = read_word(GPIO_DATA_REG);
		म_लिखो("\n Read Data is :0x%x", read_data);

		निवड(read_data)
		{

		स्थिती 0x00000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x10000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x20000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x30000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x40000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x50000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x60000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x70000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: LOW");
			थांबा;

		स्थिती 0x80000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0x90000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xA0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xB0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: LOW");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xC0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xD0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: LOW");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xE0000000:
			म_लिखो("\n BTN0: LOW");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			थांबा;

		स्थिती 0xF0000000:
			म_लिखो("\n BTN0: HIGH");
			म_लिखो("\n BTN1: HIGH");
			म_लिखो("\n BTN2: HIGH");
			म_लिखो("\n BTN3: HIGH");
			थांबा;
		}

		delay_loop(500, 500);
#endif
	}
	delay_loop(500, 500);
#endif
}

