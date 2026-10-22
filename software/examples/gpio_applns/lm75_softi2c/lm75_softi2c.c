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

#অন্তর্ভাব "gpio_i2c.h"

#define LM75_SLAVE_ADDRESS 0x90
#define DELAY_গুনতি 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
unsigned পূর্ণসংখ্যা Lm75ReadTemperature(unsigned long delay)
{
	unsigned অক্ষর readBuf = 0;
	unsigned short read_মান_2 = 0;
	I2cSendSlaveAddress(LM75_SLAVE_ADDRESS, I2C_READ, delay);
	readBuf = I2c_Read_তথ্য_Ack(delay);
	read_মান_2 = (readBuf << 1);
	readBuf = I2c_Read_তথ্য_Nack(delay);
	I2cStop(delay);  
	read_মান_2 = (readBuf >> 7) | read_মান_2;
	ফেরত read_মান_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
শূন্য প্রধান() 
{
	unsigned short অস্থায়ী_Read = 0;
	unsigned short অস্থায়ী = 0;

	printf("\n\ttemp sensor initiating!");

	I2cInit();

	অস্থায়ী_Read = Lm75ReadTemperature(DELAY_গুনতি);
	যদি(অস্থায়ী_Read & 0x100) {
		অস্থায়ী_Read = ( (~অস্থায়ী_Read) + 1 ) >> 1;
		printf("\n\t Current Temperature:=-%u°C",অস্থায়ী_Read);
	}		
	অন্যথা {
		অস্থায়ী_Read = অস্থায়ী_Read >> 1;
		printf("\n\t Current Temperature:=+%u°C",অস্থায়ী_Read);
	 }
	delay_loop(10000,20000);
}
