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

#అన్తర్భావ <stdio.h> //includes the definitions of standard input/output functions
#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h" // includes definitions of gpio pins and read, write functions//
#అన్తర్భావ "switch_driver.h"
#అన్తర్భావ "utils.h"

/*! Define one of the the following macros to read buttons in different ways. */
#నిర్వచించు READ_INDIVIDUAL_SWITCHES /*! Read each switch value */
//#define READ_ALL_SWITCHES /*! Read All switch values */

గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;

/** @fn  void main() 
 * @brief Performs the toggling operation  with the help of button.
 * @details 
 * @warning 
 */
శూన్య ప్రధాన()
{

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)


	అయితే(1){	
#నిర్వచితమైతే READ_INDIVIDUAL_SWITCHES		
		/*! Define any one button from below at a time */
#నిర్వచించు SW_0 /*! Read SW0 value */
		//#define SW_1 /*! Read SW1 value */
		//#define SW_2 /*! Read SW2 value */
		//#define SW_3 /*! Read SW3 value */

#నిర్వచితమైతే SW_0
		configure_switch(SW0);	
#అయితే_ముగింపు	

#నిర్వచితమైతే SW_1
		configure_switch(SW1);	
#అయితే_ముగింపు	

#నిర్వచితమైతే SW_2
		configure_switch(SW2);	
#అయితే_ముగింపు	

#నిర్వచితమైతే SW_3
		configure_switch(SW3);	
#అయితే_ముగింపు				

#అయితే_ముగింపు

#నిర్వచితమైతే READ_ALL_SWITCHES	

		configure_all_switch();	

#అయితే_ముగింపు

#నిర్వచితమైతే READ_INDIVIDUAL_SWITCHES	

#నిర్వచితమైతే SW_0
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG); /* Copies the GPIO_DATA_REG Register contents */
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x01000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x01000000)
			రాయి("\n SW0: HIGH"); 		
		లేకపోతే
			రాయి("\n SW0: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే SW_1
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x02000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x02000000)
			రాయి("\n SW1: HIGH"); 		
		లేకపోతే
			రాయి("\n SW1: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే SW_2
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = (read_దత్తాంశం_2 & 0x04000000);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x04000000)
			రాయి("\n SW2: HIGH"); 		
		లేకపోతే
			రాయి("\n SW2: LOW");
#అయితే_ముగింపు

#నిర్వచితమైతే SW_3
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		ఒకవేళ(read_దత్తాంశం_2 == 0x08000000)
			రాయి("\n SW3: HIGH"); 		
		లేకపోతే
			రాయి("\n SW3: LOW");
#అయితే_ముగింపు

		delay_loop(500, 500);

#అయితే_ముగింపు

#నిర్వచితమైతే READ_ALL_SWITCHES	

		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
		రాయి("\n Read Data is :0x%x", read_దత్తాంశం_2);

		ఎంపిక(read_దత్తాంశం_2)
		{

		స్థితి 0x00000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x01000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x02000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x03000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x04000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x05000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x06000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x07000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: LOW");
			ఆపు;

		స్థితి 0x08000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x09000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0A000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0B000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: LOW");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0C000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0D000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: LOW");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0E000000:
			రాయి("\n SW0: LOW");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: HIGH");
			ఆపు;

		స్థితి 0x0F000000:
			రాయి("\n SW0: HIGH");
			రాయి("\n SW1: HIGH");
			రాయి("\n SW2: HIGH");
			రాయి("\n SW3: HIGH");
			ఆపు;

		}

		delay_loop(500, 500);

#అయితే_ముగింపు
	}	
	delay_loop(500, 500);

#అయితే_ముగింపు
}
