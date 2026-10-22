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

#अन्तर्भाव "gpio_i2c.h"

#परिभाषय LM75_SLAVE_स्थानाङ्कः 0x90
#परिभाषय DELAY_गणनम् 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
अचिह्नित पूर्णाङ्क Lm75ReadTemperature(अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण readBuf = 0;
	अचिह्नित ह्रस्व read_मानम्_2 = 0;
	I2c_Send_Slave_स्थानाङ्कः(LM75_SLAVE_स्थानाङ्कः, I2C_READ, delay);
	readBuf = I2c_Read_दत्त_Ack(delay);
	read_मानम्_2 = (readBuf << 1);
	readBuf = I2c_Read_दत्त_Nack(delay);
	I2cStop(delay);  
	read_मानम्_2 = (readBuf >> 7) | read_मानम्_2;
	प्रत्यागम read_मानम्_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
शून्य मुख्यम्() 
{
	अचिह्नित ह्रस्व अस्थायी_Read = 0;
	अचिह्नित ह्रस्व अस्थायी = 0;

	प्रारूप_लिख("\n\ttemp sensor initiating!");

	I2cInit();

	अस्थायी_Read = Lm75ReadTemperature(DELAY_गणनम्);
	यदि(अस्थायी_Read & 0x100) {
		अस्थायी_Read = ( (~अस्थायी_Read) + 1 ) >> 1;
		प्रारूप_लिख("\n\t Current Temperature:=-%u°C",अस्थायी_Read);
	}		
	अन्यथा {
		अस्थायी_Read = अस्थायी_Read >> 1;
		प्रारूप_लिख("\n\t Current Temperature:=+%u°C",अस्थायी_Read);
	 }
	delay_loop(10000,20000);
}
