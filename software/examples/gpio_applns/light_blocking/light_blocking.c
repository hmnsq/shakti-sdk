/***************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	      : light_blocking.c
 * Brief Description of file  : Photo Interrupter key module will trigger a signal when light between the sensor's gap is blocked.
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
@file light_blocking.c
@brief Implements gpio functionality.
@detail Photo Interrupter key module will trigger a signal when light between the sensor's gap is blocked.
*/

#ضمن "gpio.h"
#ضمن "platform.h"
#ضمن <stdio.h>
#ضمن "utils.h"

/** @fn void main()
 * @brief Gives output as HIGH when partition is introduced and LOW when partition is removed with the help of gpio pins  
 */
فراغ اصلی()
{   
    بیعلامت دراز read_داده = 0;
    write_کلمه(GPIO_DIRECTION_CNTRL_REG, 0x0000);

    طالما (1) {
        	read_داده = read_کلمه(GPIO_داده_REG);

        	إذا(read_داده == 0x00000001) {

		 چاپ_کن("\n Blocked");
        	 }
        	وإلا {
            
		چاپ_کن("\n Not Blocked");
        	 }
       		delay_loop(1000,1000);
    	      }
}
    
