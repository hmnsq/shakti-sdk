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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio_i2c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_SLAVE_ਪਤਾ 0x90
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਗਿਣਤੀ 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ Lm75ReadTemperature(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ readBuf = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ read_ਮੁੱਲ_2 = 0;
	I2c_Send_Slave_ਪਤਾ(LM75_SLAVE_ਪਤਾ, I2C_READ, delay);
	readBuf = I2c_Read_ਅੰਕੜੇ_Ack(delay);
	read_ਮੁੱਲ_2 = (readBuf << 1);
	readBuf = I2c_Read_ਅੰਕੜੇ_Nack(delay);
	I2cStop(delay);  
	read_ਮੁੱਲ_2 = (readBuf >> 7) | read_ਮੁੱਲ_2;
	ਵਾਪਸ read_ਮੁੱਲ_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
ਖਾਲੀ ਮੁੱਖ() 
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਆਰਜ਼ੀ_Read = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਆਰਜ਼ੀ = 0;

	ਲਿਖੋ("\n\ttemp sensor initiating!");

	I2cInit();

	ਆਰਜ਼ੀ_Read = Lm75ReadTemperature(DELAY_ਗਿਣਤੀ);
	ਜੇ(ਆਰਜ਼ੀ_Read & 0x100) {
		ਆਰਜ਼ੀ_Read = ( (~ਆਰਜ਼ੀ_Read) + 1 ) >> 1;
		ਲਿਖੋ("\n\t Current Temperature:=-%u°C",ਆਰਜ਼ੀ_Read);
	}		
	ਨਹੀਂਤਾਂ {
		ਆਰਜ਼ੀ_Read = ਆਰਜ਼ੀ_Read >> 1;
		ਲਿਖੋ("\n\t Current Temperature:=+%u°C",ਆਰਜ਼ੀ_Read);
	 }
	delay_loop(10000,20000);
}
