/***************************************************************************
* Project                               : shakti devt board
* Name of the file                      : mq2.c
* Brief Description of file             : Demonstrates the usage of MQ2 gas sensor.
* Name of Student                       : Kolan Nikshith Reddy
* Email ID                              : cs20m030@smail.iitm.ac.in
* Name of mentor                        : Kottesswaran Ekambaram
* Email ID of Mentor                    : kottee.1@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file mq2.c
@brief  write data to flash by xadc
@detail Contains driver codes to read and write flash using SPI interface.
*/

#include <stdint.h>
#include "xadc_driver.h"
#include "uart.h"
#include <math.h>

//0x41250 is the address for A0 pin
//0x41254 is the address for A1 pin
//0x41258 is the address for A2 pin
//0x4125c is the address for A3 pin


int MQ7sensorValue = 0;   // value read from the sensor

/** 
 * @fn int main()
 * @brief Calls the xadc apis to read Carbon Monoxide.
 * @return none
 */
void main()
{       
    
    uint32_t value ;
    printf("MQ-7 Gas Sensor started...");
    while(1){

    //Reading the analog value
    MQ7sensorValue = xadc_read_data(0x41250)>>4;


    if (MQ7sensorValue <= 200) 
    {
        printf("CO: %d PPM \t Air-Quality: CO perfect\n", MQ7sensorValue);
    }
    else if ((MQ7sensorValue > 200) && (MQ7sensorValue <= 800))
    {
        printf("CO: %d PPM \t Air-Quality: CO Normal\n", MQ7sensorValue);
    }
    else if ((MQ7sensorValue > 800) && (MQ7sensorValue <= 1800))
    {
        printf("CO: %d PPM \t Air-Quality: CO High\n", MQ7sensorValue);
    }
    else if (MQ7sensorValue > 1800) 
    {
        printf("CO: %d PPM \t Air-Quality: Very High\n", MQ7sensorValue);
    }
    else
    {
        printf("MQ-7 - cant read any value - check the sensor!");
    }

  delay(5);

    }

}




