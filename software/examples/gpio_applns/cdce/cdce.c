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

#समावेश "gpio_i2c.h"

#घोषणा CDCE913_SLAVE_ADDRESS 0xCA
#घोषणा DELAY_गिनती 50
#घोषणा _50MHZ
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
अचिन्हित पूर्णांक cdce913_write_all_registers(अचिन्हित पूर्णांक reg_offset, अचिन्हित पूर्णांक reg_गिनती, अचिन्हित पूर्णांक *write_तथ्य_2, अचिन्हित दीर्घ delay)
{
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);
	अगर(reg_गिनती > 1)
		I2c_Write_तथ्य(reg_offset, delay);
	अन्यथा
		I2c_Write_तथ्य(reg_offset | 0x80, delay);
	I2c_Write_तथ्य(reg_गिनती, delay);

	क्रम(पूर्णांक i = 0; i < reg_गिनती; i++)
	{
		I2c_Write_तथ्य(*write_तथ्य_2, delay);
		अगर(reg_गिनती > 1)
			*write_तथ्य_2++;
	}
	I2cStop(delay);
	वापस 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
अचिन्हित पूर्णांक cdce913_read_all_registers(अचिन्हित पूर्णांक reg_offset, अचिन्हित पूर्णांक reg_गिनती, अचिन्हित दीर्घ delay)
{
	अचिन्हित अक्षर readBuf = 0;
	अचिन्हित लघु read_मूल्य_2 = 0;

	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);

	अगर(reg_गिनती > 1)
		I2c_Write_तथ्य(reg_offset, delay);
	अन्यथा
		I2c_Write_तथ्य(reg_offset | 0x80, delay);

	I2cStart(delay);
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_READ, delay);

	अगर(reg_गिनती > 1)
	{
		क्रम(पूर्णांक i = 0; i < reg_गिनती; i++)
		{
			readBuf = I2c_Read_तथ्य_Ack(delay);
			म_लिखो("\n Read Value: %x", readBuf);
		}
	}
	अन्यथा
	{
		readBuf = I2c_Read_तथ्य_Ack(delay);
		म_लिखो("\n Value @ [%x]: [%x]", reg_offset , readBuf);
	}
	I2cStop(delay);

	वापस readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
व्योम मुख्य()
{
	अचिन्हित लघु अस्थायी_Read = 0;
	अचिन्हित लघु अस्थायी = 0;

#अगर_घोषित _50MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#पूर्ण_अगर
#अगर_घोषित _75MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#पूर्ण_अगर
#अगर_घोषित _100MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#पूर्ण_अगर
#अगर_घोषित _125MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#पूर्ण_अगर
#अगर_घोषित _130MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#पूर्ण_अगर
#अगर_घोषित _150MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#पूर्ण_अगर
#अगर_घोषित _175MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#पूर्ण_अगर
#अगर_घोषित _200MHZ
	अचिन्हित पूर्णांक write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	अचिन्हित पूर्णांक write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#पूर्ण_अगर

	अचिन्हित पूर्णांक eeprom_write = 0;
	अचिन्हित पूर्णांक read_मूल्य = 0xff;

	म_लिखो("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_गिनती);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_गिनती);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गिनती);

	जबतक(1)
	{
		read_मूल्य = cdce913_read_all_registers(0x02, 1, DELAY_गिनती);
		अगर(0 == (read_मूल्य & 0x40) )
			अवरोध;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_गिनती);

	म_लिखो("\n After Write");

	क्रम(पूर्णांक i = 0; i < 32; i++)
	{
		अगर  ( (i >= 7) && (i <= 15) )
			जारी;
		cdce913_read_all_registers(i, 1, DELAY_गिनती);
		delay_loop(1000,2000);
	}

	जबतक(1);
}
