/***************************************************************************
 * Project           		 : shakti devt board
 * Name of the file	         : lm75_softi2c.c
 * Brief Description of file     : Helps to find out temperature of a surrounding with the help of gpio pins.
 * Name of Author                : Soutrick Roy Chowdhury.
 * Email ID                      : soutrick97@gmail.com

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
@file lm75_softi2c.c
@brief Implements gpio functionality.
@detail Helps to find out temperature of a surrounding with the help of gpio pins.
*/

#అన్తర్భావ "gpio_i2c.h"

#నిర్వచించు LM75_SLAVE_చిరునామా 0x90
#నిర్వచించు DELAY_లెక్క 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
గుర్తులేని పూర్ణాంకం Lm75ReadTemperature(గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం readBuf = 0;
	గుర్తులేని పొట్టి read_విలువ_2 = 0;
	I2c_Send_Slave_చిరునామా(LM75_SLAVE_చిరునామా, I2C_READ, delay);
	readBuf = I2c_Read_దత్తాంశం_Ack(delay);
	read_విలువ_2 = (readBuf << 1);
	readBuf = I2c_Read_దత్తాంశం_Nack(delay);
	I2cStop(delay);  
	read_విలువ_2 = (readBuf >> 7) | read_విలువ_2;
	తిరిగి read_విలువ_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
శూన్య ప్రధాన() 
{
	గుర్తులేని పొట్టి తాత్కాలిక_Read = 0;
	గుర్తులేని పొట్టి తాత్కాలిక = 0;

	రాయి("\n\ttemp sensor initiating!");

	I2cInit();

	తాత్కాలిక_Read = Lm75ReadTemperature(DELAY_లెక్క);
	ఒకవేళ(తాత్కాలిక_Read & 0x100) {
		తాత్కాలిక_Read = ( (~తాత్కాలిక_Read) + 1 ) >> 1;
		రాయి("\n\t Current Temperature:=-%u°C",తాత్కాలిక_Read);
	}		
	లేకపోతే {
		తాత్కాలిక_Read = తాత్కాలిక_Read >> 1;
		రాయి("\n\t Current Temperature:=+%u°C",తాత్కాలిక_Read);
	 }
	delay_loop(10000,20000);
}
