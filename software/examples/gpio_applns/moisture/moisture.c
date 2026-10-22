/***************************************************************************
* Project           			: shakti devt board
* Name of the file	     		: moisture.c
* Brief Description of file     	: find moisture present in the soil
* Name of Author               		: Soutrick Roy Chowdhury
* Email ID                       	: soutrick97@gmail.com

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
@file moisture.c
@brief Implements gpio functionality.
@detail It helps to find the presence of moisture in the soil.
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

/** @fn void main()
* @brief It used to check the moisture in the soil.
* @details Soil moisture sensors typically refer to sensors that estimate volumetric water content
* @warning  Connection should be done carefully.
*/
ਖਾਲੀ ਮੁੱਖ()
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
    
    ਜਦੋਂ (1) {
        	 write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, 0x00);
		 read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
	
        	 ਲਿਖੋ("\n Read Data:=0x%x", read_ਅੰਕੜੇ);

        	 ਜੇ (read_ਅੰਕੜੇ == 0x00000001) {
            	 write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, 0x00000002);
            	 write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, 0x00000002);

            	 ਲਿਖੋ("\nTurn on Motor");
       		 }
        	 ਨਹੀਂਤਾਂ {
            	 ਲਿਖੋ("\nTurn off Motor");
        	 }
       		 delay_loop(1000,1000);
    	      } 
}
