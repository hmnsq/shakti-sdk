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

#تعریف_کرو LM75_SLAVE_پتہ 0x90
#تعریف_کرو DELAY_گنتی 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
بنانشانی صحيح Lm75ReadTemperature(بنانشانی لما delay)
{
	بنانشانی حرف readBuf = 0;
	بنانشانی چھوٹا read_قدر_2 = 0;
	I2c_Send_Slave_پتہ(LM75_SLAVE_پتہ, I2C_READ, delay);
	readBuf = I2c_Read_انکڑے_Ack(delay);
	read_قدر_2 = (readBuf << 1);
	readBuf = I2c_Read_انکڑے_Nack(delay);
	I2cStop(delay);  
	read_قدر_2 = (readBuf >> 7) | read_قدر_2;
	أرجع read_قدر_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
فراغ مکھ() 
{
	بنانشانی چھوٹا عارضی_Read = 0;
	بنانشانی چھوٹا عارضی = 0;

	لکھو("\n\ttemp sensor initiating!");

	I2cInit();

	عارضی_Read = Lm75ReadTemperature(DELAY_گنتی);
	إذا(عارضی_Read & 0x100) {
		عارضی_Read = ( (~عارضی_Read) + 1 ) >> 1;
		لکھو("\n\t Current Temperature:=-%u°C",عارضی_Read);
	}		
	وإلا {
		عارضی_Read = عارضی_Read >> 1;
		لکھو("\n\t Current Temperature:=+%u°C",عارضی_Read);
	 }
	delay_loop(10000,20000);
}
