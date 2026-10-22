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

#অন্তর্ভাব "gpio_i2c.h"

#define CDCE913_SLAVE_ADDRESS 0xCA
#define DELAY_গুনতি 50
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
unsigned পূর্ণসংখ্যা cdce913_write_all_registers(unsigned পূর্ণসংখ্যা reg_offset, unsigned পূর্ণসংখ্যা reg_গুনতি, unsigned পূর্ণসংখ্যা *write_তথ্য_2, unsigned long delay)
{
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);
	যদি(reg_গুনতি > 1)
		I2c_Write_তথ্য(reg_offset, delay);
	অন্যথা
		I2c_Write_তথ্য(reg_offset | 0x80, delay);
	I2c_Write_তথ্য(reg_গুনতি, delay);

	জন্য(পূর্ণসংখ্যা i = 0; i < reg_গুনতি; i++)
	{
		I2c_Write_তথ্য(*write_তথ্য_2, delay);
		যদি(reg_গুনতি > 1)
			*write_তথ্য_2++;
	}
	I2cStop(delay);
	ফেরত 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
unsigned পূর্ণসংখ্যা cdce913_read_all_registers(unsigned পূর্ণসংখ্যা reg_offset, unsigned পূর্ণসংখ্যা reg_গুনতি, unsigned long delay)
{
	unsigned অক্ষর readBuf = 0;
	unsigned short read_মান_2 = 0;

	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);

	যদি(reg_গুনতি > 1)
		I2c_Write_তথ্য(reg_offset, delay);
	অন্যথা
		I2c_Write_তথ্য(reg_offset | 0x80, delay);

	I2cStart(delay);
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_READ, delay);

	যদি(reg_গুনতি > 1)
	{
		জন্য(পূর্ণসংখ্যা i = 0; i < reg_গুনতি; i++)
		{
			readBuf = I2c_Read_তথ্য_Ack(delay);
			printf("\n Read Value: %x", readBuf);
		}
	}
	অন্যথা
	{
		readBuf = I2c_Read_তথ্য_Ack(delay);
		printf("\n Value @ [%x]: [%x]", reg_offset , readBuf);
	}
	I2cStop(delay);

	ফেরত readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
শূন্য প্রধান()
{
	unsigned short অস্থায়ী_Read = 0;
	unsigned short অস্থায়ী = 0;

#ifdef _50MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _75MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#endif
#ifdef _100MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _125MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#endif
#ifdef _130MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#endif
#ifdef _150MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#endif
#ifdef _175MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#endif
#ifdef _200MHZ
	unsigned পূর্ণসংখ্যা write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned পূর্ণসংখ্যা write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif

	unsigned পূর্ণসংখ্যা eeprom_write = 0;
	unsigned পূর্ণসংখ্যা read_মান = 0xff;

	printf("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_গুনতি);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_গুনতি);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_গুনতি);

	যখন(1)
	{
		read_মান = cdce913_read_all_registers(0x02, 1, DELAY_গুনতি);
		যদি(0 == (read_মান & 0x40) )
			বিরতি;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_গুনতি);

	printf("\n After Write");

	জন্য(পূর্ণসংখ্যা i = 0; i < 32; i++)
	{
		যদি  ( (i >= 7) && (i <= 15) )
			চালু;
		cdce913_read_all_registers(i, 1, DELAY_গুনতি);
		delay_loop(1000,2000);
	}

	যখন(1);
}
