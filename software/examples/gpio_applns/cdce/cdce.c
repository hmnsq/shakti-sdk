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

#تعریف_کړه CDCE913_SLAVE_پته 0xCA
#تعریف_کړه DELAY_شمېر 50
#تعریف_کړه _50MHZ
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
بینښه صحيح cdce913_write_all_registers(بینښه صحيح reg_دننه_واټن, بینښه صحيح reg_شمېر, بینښه صحيح *write_معلومات_2, بینښه اوږد delay)
{
	I2c_Send_Slave_پته(CDCE913_SLAVE_پته, I2C_WRITE, delay);
	إذا(reg_شمېر > 1)
		I2c_Write_معلومات(reg_دننه_واټن, delay);
	وإلا
		I2c_Write_معلومات(reg_دننه_واټن | 0x80, delay);
	I2c_Write_معلومات(reg_شمېر, delay);

	لكل(صحيح i = 0; i < reg_شمېر; i++)
	{
		I2c_Write_معلومات(*write_معلومات_2, delay);
		إذا(reg_شمېر > 1)
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
بینښه صحيح cdce913_read_all_registers(بینښه صحيح reg_دننه_واټن, بینښه صحيح reg_شمېر, بینښه اوږد delay)
{
	بینښه حرف readBuf = 0;
	بینښه لنډ read_ارزښت_2 = 0;

	I2c_Send_Slave_پته(CDCE913_SLAVE_پته, I2C_WRITE, delay);

	إذا(reg_شمېر > 1)
		I2c_Write_معلومات(reg_دننه_واټن, delay);
	وإلا
		I2c_Write_معلومات(reg_دننه_واټن | 0x80, delay);

	I2c_پیل(delay);
	I2c_Send_Slave_پته(CDCE913_SLAVE_پته, I2C_READ, delay);

	إذا(reg_شمېر > 1)
	{
		لكل(صحيح i = 0; i < reg_شمېر; i++)
		{
			readBuf = I2c_Read_معلومات_Ack(delay);
			چاپ_کړه("\n Read Value: %x", readBuf);
		}
	}
	وإلا
	{
		readBuf = I2c_Read_معلومات_Ack(delay);
		چاپ_کړه("\n Value @ [%x]: [%x]", reg_دننه_واټن , readBuf);
	}
	I2cStop(delay);

	أرجع readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
فراغ اصلي()
{
	بینښه لنډ لنډمهاله_Read = 0;
	بینښه لنډ لنډمهاله = 0;

#که_تعریف_شوی _50MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#د_که_پای
#که_تعریف_شوی _75MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#د_که_پای
#که_تعریف_شوی _100MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#د_که_پای
#که_تعریف_شوی _125MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#د_که_پای
#که_تعریف_شوی _130MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#د_که_پای
#که_تعریف_شوی _150MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#د_که_پای
#که_تعریف_شوی _175MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#د_که_پای
#که_تعریف_شوی _200MHZ
	بینښه صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بینښه صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#د_که_پای

	بینښه صحيح eeprom_write = 0;
	بینښه صحيح read_ارزښت = 0xff;

	چاپ_کړه("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_شمېر);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_شمېر);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_شمېر);

	طالما(1)
	{
		read_ارزښت = cdce913_read_all_registers(0x02, 1, DELAY_شمېر);
		إذا(0 == (read_ارزښت & 0x40) )
			اكسر;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_شمېر);

	چاپ_کړه("\n After Write");

	لكل(صحيح i = 0; i < 32; i++)
	{
		إذا  ( (i >= 7) && (i <= 15) )
			استمر;
		cdce913_read_all_registers(i, 1, DELAY_شمېر);
		delay_loop(1000,2000);
	}

	طالما(1);
}
