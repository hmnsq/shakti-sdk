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

#ಅನ್ತರ್ಭಾವ "gpio_i2c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು LM75_SLAVE_ವಿಳಾಸ 0x90
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಎಣಿಕೆ 200

/** @fn unsigned int Lm75ReadTemperature(unsigned long delay)
 * @brief Complete function to read value from LM75 sensors 
 * @param unsigned long delay
 * @return unsigned int
 */
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ Lm75ReadTemperature(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ readBuf = 0;
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ read_ಮೌಲ್ಯ_2 = 0;
	I2c_Send_Slave_ವಿಳಾಸ(LM75_SLAVE_ವಿಳಾಸ, I2C_READ, delay);
	readBuf = I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
	read_ಮೌಲ್ಯ_2 = (readBuf << 1);
	readBuf = I2c_Read_ದತ್ತಾಂಶ_Nack(delay);
	I2cStop(delay);  
	read_ಮೌಲ್ಯ_2 = (readBuf >> 7) | read_ಮೌಲ್ಯ_2;
	ಹಿಂತಿರುಗಿ read_ಮೌಲ್ಯ_2;
}

/** @fn void main()
 * @brief Calling Lm75ReadTemperature to find the temperature
 * @details Printing the Current temperature
 */
ಶೂನ್ಯ ಮುಖ್ಯ() 
{
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ತಾತ್ಕಾಲಿಕ_Read = 0;
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ತಾತ್ಕಾಲಿಕ = 0;

	ಬರೆ("\n\ttemp sensor initiating!");

	I2cInit();

	ತಾತ್ಕಾಲಿಕ_Read = Lm75ReadTemperature(DELAY_ಎಣಿಕೆ);
	ಆದರೆ(ತಾತ್ಕಾಲಿಕ_Read & 0x100) {
		ತಾತ್ಕಾಲಿಕ_Read = ( (~ತಾತ್ಕಾಲಿಕ_Read) + 1 ) >> 1;
		ಬರೆ("\n\t Current Temperature:=-%u°C",ತಾತ್ಕಾಲಿಕ_Read);
	}		
	ಇಲ್ಲದಿದ್ದರೆ {
		ತಾತ್ಕಾಲಿಕ_Read = ತಾತ್ಕಾಲಿಕ_Read >> 1;
		ಬರೆ("\n\t Current Temperature:=+%u°C",ತಾತ್ಕಾಲಿಕ_Read);
	 }
	delay_loop(10000,20000);
}
