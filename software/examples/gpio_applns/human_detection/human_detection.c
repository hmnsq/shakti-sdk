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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव "gpio.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "utils.h"

/** @fn void main()
 * @brief Used to read through Human Detection Sensors
 * @details Printing the presence of a person near it
 * @warning We have to set the potentiometer correctly to get the correct result
 */
शून्य मुख्यम्()
{
    अचिह्नित दीर्घ read_दत्त = 0;
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);
    
    यावत् (1){
        	read_दत्त = read_word(GPIO_दत्त_REG);

	        यदि (read_दत्त == 0x00000001){

 		प्रारूप_लिख("\nHuman Detected");
                }

                अन्यथा{
		प्रारूप_लिख("\nNo one detected");
             	}
          
	      	delay_loop(1000, 1000);
    	      }
}
    
