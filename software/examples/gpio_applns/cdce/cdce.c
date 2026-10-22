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

#अन्तर्भाव "gpio_i2c.h"

#define CDCE913_SLAVE_ADDRESS 0xCA
#define DELAY_गन्ती 50
#define _50MHZ
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
अचिन्हित पूर्णाङ्क cdce913_write_all_registers(अचिन्हित पूर्णाङ्क reg_offset, अचिन्हित पूर्णाङ्क reg_गन्ती, अचिन्हित पूर्णाङ्क *write_data, अचिन्हित दीर्घ delay)
{
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);
	यदि(reg_गन्ती > 1)
		I2cWriteData(reg_offset, delay);
	अन्यथा
		I2cWriteData(reg_offset | 0x80, delay);
	I2cWriteData(reg_गन्ती, delay);

	लागि(पूर्णाङ्क i = 0; i < reg_गन्ती; i++)
	{
		I2cWriteData(*write_data, delay);
		यदि(reg_गन्ती > 1)
			*write_data++;
	}
	I2cStop(delay);
	फर्काऊ 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
अचिन्हित पूर्णाङ्क cdce913_read_all_registers(अचिन्हित पूर्णाङ्क reg_offset, अचिन्हित पूर्णाङ्क reg_गन्ती, अचिन्हित दीर्घ delay)
{
	अचिन्हित वर्ण readBuf = 0;
	अचिन्हित लघु read_मान_2 = 0;

	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);

	यदि(reg_गन्ती > 1)
		I2cWriteData(reg_offset, delay);
	अन्यथा
		I2cWriteData(reg_offset | 0x80, delay);

	I2cStart(delay);
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_READ, delay);

	यदि(reg_गन्ती > 1)
	{
		लागि(पूर्णाङ्क i = 0; i < reg_गन्ती; i++)
		{
			readBuf = I2cReadDataAck(delay);
			म_लिखो("\n Read Value: %x", readBuf);
		}
	}
	अन्यथा
	{
		readBuf = I2cReadDataAck(delay);
		म_लिखो("\n Value @ [%x]: [%x]", reg_offset , readBuf);
	}
	I2cStop(delay);

	फर्काऊ readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
शून्य main()
{
	अचिन्हित लघु tempRead = 0;
	अचिन्हित लघु temp = 0;

#ifdef _50MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _75MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#endif
#ifdef _100MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _125MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#endif
#ifdef _130MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#endif
#ifdef _150MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#endif
#ifdef _175MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#endif
#ifdef _200MHZ
	अचिन्हित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif

	अचिन्हित पूर्णाङ्क eeprom_write = 0;
	अचिन्हित पूर्णाङ्क read_मान = 0xff;

	म_लिखो("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_गन्ती);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_गन्ती);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गन्ती);

	जबसम्म(1)
	{
		read_मान = cdce913_read_all_registers(0x02, 1, DELAY_गन्ती);
		यदि(0 == (read_मान & 0x40) )
			रोक;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गन्ती);

	म_लिखो("\n After Write");

	लागि(पूर्णाङ्क i = 0; i < 32; i++)
	{
		यदि  ( (i >= 7) && (i <= 15) )
			जारी;
		cdce913_read_all_registers(i, 1, DELAY_गन्ती);
		delay_loop(1000,2000);
	}

	जबसम्म(1);
}
