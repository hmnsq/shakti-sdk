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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "utils.h"

/** @fn void main()
 * @brief Used to read through Human Detection Sensors
 * @details Printing the presence of a person near it
 * @warning We have to set the potentiometer correctly to get the correct result
 */
শূন্য প্রধান()
{
    unsigned long read_তথ্য = 0;
    write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000);
    
    যখন (1){
        	read_তথ্য = read_word(GPIO_তথ্য_REG);

	        যদি (read_তথ্য == 0x00000001){

 		printf("\nHuman Detected");
                }

                অন্যথা{
		printf("\nNo one detected");
             	}
          
	      	delay_loop(1000, 1000);
    	      }
}
    
