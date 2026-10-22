/***************************************************************************
 * Project           		 : shakti devt board
 * Name of the file	         : cdce913.c
 * Brief Description of file     : Helps to write the register value in the IC,
 *				   to change the clock frequecy with the help of
 *				   i2c gpio pins.
 * Name of Author                : kotteeswaran
 * Email ID                      :  kottee.1@gmail.com

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

 *****************************************************************************/
/**
  @file cdce.c
  @brief Implements gpio functionality.
  @detail Helps to write the values in flash of cdceic to set clock frequecy.
 */

#ಅನ್ತರ್ಭಾವ "gpio_i2c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು CDCE913_SLAVE_ವಿಳಾಸ 0xCA
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಎಣಿಕೆ 50
#ವ್ಯಾಖ್ಯಾನಿಸು _50MHZ
//#define _75MHZ
//#define _100MHZ
//#define _125MHZ
//#define _130MHZ
//#define _150MHZ
//#define _175MHZ
//#define _200MHZ

/** @fn unsigned int cdceRead(unsigned long delay)
 * @brief Complete function to read value from cdce
 * @param unsigned long delay
 * @return unsigned int
 */
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cdce913_write_all_registers(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಎಣಿಕೆ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *write_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	I2c_Send_Slave_ವಿಳಾಸ(CDCE913_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
	ಆದರೆ(reg_ಎಣಿಕೆ > 1)
		I2c_Write_ದತ್ತಾಂಶ(reg_ಸ್ಥಾನಾಂತರ, delay);
	ಇಲ್ಲದಿದ್ದರೆ
		I2c_Write_ದತ್ತಾಂಶ(reg_ಸ್ಥಾನಾಂತರ | 0x80, delay);
	I2c_Write_ದತ್ತಾಂಶ(reg_ಎಣಿಕೆ, delay);

	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < reg_ಎಣಿಕೆ; i++)
	{
		I2c_Write_ದತ್ತಾಂಶ(*write_ದತ್ತಾಂಶ_2, delay);
		ಆದರೆ(reg_ಎಣಿಕೆ > 1)
			*write_ದತ್ತಾಂಶ_2++;
	}
	I2cStop(delay);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cdce913_read_all_registers(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಎಣಿಕೆ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ readBuf = 0;
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ read_ಮೌಲ್ಯ_2 = 0;

	I2c_Send_Slave_ವಿಳಾಸ(CDCE913_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);

	ಆದರೆ(reg_ಎಣಿಕೆ > 1)
		I2c_Write_ದತ್ತಾಂಶ(reg_ಸ್ಥಾನಾಂತರ, delay);
	ಇಲ್ಲದಿದ್ದರೆ
		I2c_Write_ದತ್ತಾಂಶ(reg_ಸ್ಥಾನಾಂತರ | 0x80, delay);

	I2c_ಆರಂಭ(delay);
	I2c_Send_Slave_ವಿಳಾಸ(CDCE913_SLAVE_ವಿಳಾಸ, I2C_READ, delay);

	ಆದರೆ(reg_ಎಣಿಕೆ > 1)
	{
		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < reg_ಎಣಿಕೆ; i++)
		{
			readBuf = I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
			ಬರೆ("\n Read Value: %x", readBuf);
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		readBuf = I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
		ಬರೆ("\n Value @ [%x]: [%x]", reg_ಸ್ಥಾನಾಂತರ , readBuf);
	}
	I2cStop(delay);

	ಹಿಂತಿರುಗಿ readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ತಾತ್ಕಾಲಿಕ_Read = 0;
	ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ತಾತ್ಕಾಲಿಕ = 0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _50MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _75MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _100MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _125MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _130MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _150MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _175MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _200MHZ
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ಆದರೆ_ಅಂತ್ಯ

	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ eeprom_write = 0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ read_ಮೌಲ್ಯ = 0xff;

	ಬರೆ("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_ಎಣಿಕೆ);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_ಎಣಿಕೆ);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ಎಣಿಕೆ);

	ಆಗ(1)
	{
		read_ಮೌಲ್ಯ = cdce913_read_all_registers(0x02, 1, DELAY_ಎಣಿಕೆ);
		ಆದರೆ(0 == (read_ಮೌಲ್ಯ & 0x40) )
			ನಿಲ್ಲಿಸು;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ಎಣಿಕೆ);

	ಬರೆ("\n After Write");

	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < 32; i++)
	{
		ಆದರೆ  ( (i >= 7) && (i <= 15) )
			ಮುಂದುವರಿ;
		cdce913_read_all_registers(i, 1, DELAY_ಎಣಿಕೆ);
		delay_loop(1000,2000);
	}

	ಆಗ(1);
}
