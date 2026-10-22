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

#ضمن "gpio_i2c.h"

#وصف_ڪريو LM75_SLAVE_پتو 0x90
#وصف_ڪريو DELAY_ڳڻپ 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
بنانشان صحيح Lm75ReadTemperature(بنانشان ڊگهو delay)
{
	بنانشان حرف readBuf = 0;
	بنانشان ننڍو read_قدر_2 = 0;
	I2c_Send_Slave_پتو(LM75_SLAVE_پتو, I2C_READ, delay);
	readBuf = I2c_Read_معلومات_Ack(delay);
	read_قدر_2 = (readBuf << 1);
	readBuf = I2c_Read_معلومات_Nack(delay);
	I2cStop(delay);  
	read_قدر_2 = (readBuf >> 7) | read_قدر_2;
	أرجع read_قدر_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
فراغ مکيه() 
{
	بنانشان ننڍو عارضي_Read = 0;
	بنانشان ننڍو عارضي = 0;

	لکو("\n\ttemp sensor initiating!");

	I2cInit();

	عارضي_Read = Lm75ReadTemperature(DELAY_ڳڻپ);
	إذا(عارضي_Read & 0x100) {
		عارضي_Read = ( (~عارضي_Read) + 1 ) >> 1;
		لکو("\n\t Current Temperature:=-%u°C",عارضي_Read);
	}		
	وإلا {
		عارضي_Read = عارضي_Read >> 1;
		لکو("\n\t Current Temperature:=+%u°C",عارضي_Read);
	 }
	delay_loop(10000,20000);
}
