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

#అన్తర్భావ <stdio.h>        
#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"         
#అన్తర్భావ "button_driver.h"
#అన్తర్భావ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#నిర్వచించు READ_INDIVIDUAL_BTNS /*! Read each button value */
//#define READ_ALL_BTNS /*! Read All button values */

గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;

/** @fn void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details Configures the buttons to be read as inputs and 
 *          displays the pressed button value.
 */
శూన్య ప్రధాన()
{

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)

	అయితే (1) {

#నిర్వచితమైతే READ_INDIVIDUAL_BTNS

		/*! Define any one button from below at a time */
#నిర్వచించు BTN_0  /*! Read BTN0 value */
		//#define BTN_1 /*! Read BTN1 value */
		//#define BTN_2 /*! Read BTN2 value */
		//#define BTN_3 /*! Read BTN3 value */

#నిర్వచితమైతే BTN_0
		configure_btn(BTN0);
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_1
		configure_btn(BTN1);
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_2
		configure_btn(BTN2);
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_3
		configure_btn(BTN3);
#అయితే_ముగింపు

#అయితే_ముగింపు

#నిర్వచితమైతే READ_ALL_BTNS

		configure_all_btn();

#అయితే_ముగింపు

#నిర్వచితమైతే READ_INDIVIDUAL_BTNS

#నిర్వచితమైతే BTN_0
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG); /* Copies the GPIO_DATA_REG Register contents */
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x10000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x10000000)
			రాయి("\n BTN0: HIGH"); 		
		లేకపోతే
			రాయి("\n BTN0: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_1
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x20000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x20000000)
			రాయి("\n BTN1: HIGH"); 		
		లేకపోతే
			రాయి("\n BTN1: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_2
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x40000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x40000000)
			రాయి("\n BTN2: HIGH"); 		
		లేకపోతే
			రాయి("\n BTN2: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే BTN_3
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x80000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);

		ఒకవేళ(read_దత్తాంశం_2 == 0x80000000)
			రాయి("\n BTN3: HIGH"); 		
		లేకపోతే
			రాయి("\n BTN3: LOW");
#అయితే_ముగింపు

		delay_loop(500, 500);

#అయితే_ముగింపు

#నిర్వచితమైతే READ_ALL_BTNS	

		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);

		ఎంపిక(read_దత్తాంశం_2)
		{

		స్థితి 0x00000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x10000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x20000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x30000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x40000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x50000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x60000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x70000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: LOW");
			ఆపు;

		స్థితి 0x80000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0x90000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xA0000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xB0000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: LOW");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xC0000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xD0000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: LOW");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xE0000000:
			రాయి("\n BTN0: LOW");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: HIGH");
			ఆపు;

		స్థితి 0xF0000000:
			రాయి("\n BTN0: HIGH");
			రాయి("\n BTN1: HIGH");
			రాయి("\n BTN2: HIGH");
			రాయి("\n BTN3: HIGH");
			ఆపు;
		}

		delay_loop(500, 500);
#అయితే_ముగింపు
	}
	delay_loop(500, 500);
#అయితే_ముగింపు
}

