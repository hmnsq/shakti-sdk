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

#ضمن "gpio_i2c.h"

#وصف_ڪريو CDCE913_SLAVE_پتو 0xCA
#وصف_ڪريو DELAY_ڳڻپ 50
#وصف_ڪريو _50MHZ
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
بنانشان صحيح cdce913_write_all_registers(بنانشان صحيح reg_وٿي, بنانشان صحيح reg_ڳڻپ, بنانشان صحيح *write_معلومات_2, بنانشان ڊگهو delay)
{
	I2c_Send_Slave_پتو(CDCE913_SLAVE_پتو, I2C_WRITE, delay);
	إذا(reg_ڳڻپ > 1)
		I2c_Write_معلومات(reg_وٿي, delay);
	وإلا
		I2c_Write_معلومات(reg_وٿي | 0x80, delay);
	I2c_Write_معلومات(reg_ڳڻپ, delay);

	لكل(صحيح i = 0; i < reg_ڳڻپ; i++)
	{
		I2c_Write_معلومات(*write_معلومات_2, delay);
		إذا(reg_ڳڻپ > 1)
			*write_معلومات_2++;
	}
	I2cStop(delay);
	أرجع 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
بنانشان صحيح cdce913_read_all_registers(بنانشان صحيح reg_وٿي, بنانشان صحيح reg_ڳڻپ, بنانشان ڊگهو delay)
{
	بنانشان حرف readBuf = 0;
	بنانشان ننڍو read_قدر_2 = 0;

	I2c_Send_Slave_پتو(CDCE913_SLAVE_پتو, I2C_WRITE, delay);

	إذا(reg_ڳڻپ > 1)
		I2c_Write_معلومات(reg_وٿي, delay);
	وإلا
		I2c_Write_معلومات(reg_وٿي | 0x80, delay);

	I2c_شروعات(delay);
	I2c_Send_Slave_پتو(CDCE913_SLAVE_پتو, I2C_READ, delay);

	إذا(reg_ڳڻپ > 1)
	{
		لكل(صحيح i = 0; i < reg_ڳڻپ; i++)
		{
			readBuf = I2c_Read_معلومات_Ack(delay);
			لکو("\n Read Value: %x", readBuf);
		}
	}
	وإلا
	{
		readBuf = I2c_Read_معلومات_Ack(delay);
		لکو("\n Value @ [%x]: [%x]", reg_وٿي , readBuf);
	}
	I2cStop(delay);

	أرجع readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
فراغ مکيه()
{
	بنانشان ننڍو عارضي_Read = 0;
	بنانشان ننڍو عارضي = 0;

#جيڪڏهن_وصف_ٿيل _50MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _75MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _100MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _125MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _130MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _150MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _175MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل _200MHZ
	بنانشان صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشان صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جيڪڏهن_پورو

	بنانشان صحيح eeprom_write = 0;
	بنانشان صحيح read_قدر = 0xff;

	لکو("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_ڳڻپ);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_ڳڻپ);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ڳڻپ);

	طالما(1)
	{
		read_قدر = cdce913_read_all_registers(0x02, 1, DELAY_ڳڻپ);
		إذا(0 == (read_قدر & 0x40) )
			اكسر;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ڳڻپ);

	لکو("\n After Write");

	لكل(صحيح i = 0; i < 32; i++)
	{
		إذا  ( (i >= 7) && (i <= 15) )
			استمر;
		cdce913_read_all_registers(i, 1, DELAY_ڳڻپ);
		delay_loop(1000,2000);
	}

	طالما(1);
}
