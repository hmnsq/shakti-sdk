/***************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	      : human_detection.c
 * Brief Description of file  : Helps to detects the persons around the range of the module with the help of gpio pins
 * Name of Author             : Soutrick Roy Chowdhury
 * Email ID                   : soutrick97@gmail.com

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
*****************************************************************************/
/**
@file human_detection.c
@brief Implements gpio functionality
@detail It helps to detect the presence of human within a certain range.
*/

#అన్తర్భావ <stdio.h>
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "utils.h"

/** @fn void main()
 * @brief Used to read through Human Detection Sensors
 * @details Printing the presence of a person near it
 * @warning We have to set the potentiometer correctly to get the correct result
 */
శూన్య ప్రధాన()
{
    గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
    write_మాట(GPIO_DIRECTION_CNTRL_REG, 0x00000000);
    
    అయితే (1){
        	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);

	        ఒకవేళ (read_దత్తాంశం == 0x00000001){

 		రాయి("\nHuman Detected");
                }

                లేకపోతే{
		రాయి("\nNo one detected");
             	}
          
	      	delay_loop(1000, 1000);
    	      }
}
    
