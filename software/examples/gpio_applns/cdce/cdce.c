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

#परिभाषय CDCE913_SLAVE_स्थानाङ्कः 0xCA
#परिभाषय DELAY_गणनम् 50
#परिभाषय _50MHZ
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
अचिह्नित पूर्णाङ्क cdce913_write_all_registers(अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क reg_गणनम्, अचिह्नित पूर्णाङ्क *write_दत्त_2, अचिह्नित दीर्घ delay)
{
	I2c_Send_Slave_स्थानाङ्कः(CDCE913_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
	यदि(reg_गणनम् > 1)
		I2c_Write_दत्त(reg_विस्थापनम्, delay);
	अन्यथा
		I2c_Write_दत्त(reg_विस्थापनम् | 0x80, delay);
	I2c_Write_दत्त(reg_गणनम्, delay);

	प्रति(पूर्णाङ्क i = 0; i < reg_गणनम्; i++)
	{
		I2c_Write_दत्त(*write_दत्त_2, delay);
		यदि(reg_गणनम् > 1)
			*write_दत्त_2++;
	}
	I2cStop(delay);
	प्रत्यागम 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
अचिह्नित पूर्णाङ्क cdce913_read_all_registers(अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क reg_गणनम्, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण readBuf = 0;
	अचिह्नित ह्रस्व read_मानम्_2 = 0;

	I2c_Send_Slave_स्थानाङ्कः(CDCE913_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);

	यदि(reg_गणनम् > 1)
		I2c_Write_दत्त(reg_विस्थापनम्, delay);
	अन्यथा
		I2c_Write_दत्त(reg_विस्थापनम् | 0x80, delay);

	I2cStart(delay);
	I2c_Send_Slave_स्थानाङ्कः(CDCE913_SLAVE_स्थानाङ्कः, I2C_READ, delay);

	यदि(reg_गणनम् > 1)
	{
		प्रति(पूर्णाङ्क i = 0; i < reg_गणनम्; i++)
		{
			readBuf = I2c_Read_दत्त_Ack(delay);
			प्रारूप_लिख("\n Read Value: %x", readBuf);
		}
	}
	अन्यथा
	{
		readBuf = I2c_Read_दत्त_Ack(delay);
		प्रारूप_लिख("\n Value @ [%x]: [%x]", reg_विस्थापनम् , readBuf);
	}
	I2cStop(delay);

	प्रत्यागम readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
शून्य मुख्यम्()
{
	अचिह्नित ह्रस्व अस्थायी_Read = 0;
	अचिह्नित ह्रस्व अस्थायी = 0;

#यदि_परिभाषितम् _50MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#यदि_अन्तः
#यदि_परिभाषितम् _75MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#यदि_अन्तः
#यदि_परिभाषितम् _100MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#यदि_अन्तः
#यदि_परिभाषितम् _125MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#यदि_अन्तः
#यदि_परिभाषितम् _130MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#यदि_अन्तः
#यदि_परिभाषितम् _150MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#यदि_अन्तः
#यदि_परिभाषितम् _175MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#यदि_अन्तः
#यदि_परिभाषितम् _200MHZ
	अचिह्नित पूर्णाङ्क write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिह्नित पूर्णाङ्क write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#यदि_अन्तः

	अचिह्नित पूर्णाङ्क eeprom_write = 0;
	अचिह्नित पूर्णाङ्क read_मानम् = 0xff;

	प्रारूप_लिख("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_गणनम्);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_गणनम्);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गणनम्);

	यावत्(1)
	{
		read_मानम् = cdce913_read_all_registers(0x02, 1, DELAY_गणनम्);
		यदि(0 == (read_मानम् & 0x40) )
			भङ्ग;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गणनम्);

	प्रारूप_लिख("\n After Write");

	प्रति(पूर्णाङ्क i = 0; i < 32; i++)
	{
		यदि  ( (i >= 7) && (i <= 15) )
			अनुवर्त;
		cdce913_read_all_registers(i, 1, DELAY_गणनम्);
		delay_loop(1000,2000);
	}

	यावत्(1);
}
