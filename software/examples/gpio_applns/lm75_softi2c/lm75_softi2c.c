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

#تعریف_کن LM75_SLAVE_آدرس 0x90
#تعریف_کن DELAY_شمار 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
بیعلامت صحيح Lm75ReadTemperature(بیعلامت دراز delay)
{
	بیعلامت حرف readBuf = 0;
	بیعلامت کوتاه read_مقدار_2 = 0;
	I2c_Send_Slave_آدرس(LM75_SLAVE_آدرس, I2C_READ, delay);
	readBuf = I2c_Read_داده_Ack(delay);
	read_مقدار_2 = (readBuf << 1);
	readBuf = I2c_Read_داده_Nack(delay);
	I2cStop(delay);  
	read_مقدار_2 = (readBuf >> 7) | read_مقدار_2;
	أرجع read_مقدار_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
فراغ اصلی() 
{
	بیعلامت کوتاه موقت_Read = 0;
	بیعلامت کوتاه موقت = 0;

	چاپ_کن("\n\ttemp sensor initiating!");

	I2cInit();

	موقت_Read = Lm75ReadTemperature(DELAY_شمار);
	إذا(موقت_Read & 0x100) {
		موقت_Read = ( (~موقت_Read) + 1 ) >> 1;
		چاپ_کن("\n\t Current Temperature:=-%u°C",موقت_Read);
	}		
	وإلا {
		موقت_Read = موقت_Read >> 1;
		چاپ_کن("\n\t Current Temperature:=+%u°C",موقت_Read);
	 }
	delay_loop(10000,20000);
}
