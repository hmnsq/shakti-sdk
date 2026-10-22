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

#تعریف_کن CDCE913_SLAVE_آدرس 0xCA
#تعریف_کن DELAY_شمار 50
#تعریف_کن _50MHZ
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
بیعلامت صحيح cdce913_write_all_registers(بیعلامت صحيح reg_جابه_جایی, بیعلامت صحيح reg_شمار, بیعلامت صحيح *write_داده_2, بیعلامت دراز delay)
{
	I2c_Send_Slave_آدرس(CDCE913_SLAVE_آدرس, I2C_WRITE, delay);
	إذا(reg_شمار > 1)
		I2c_Write_داده(reg_جابه_جایی, delay);
	وإلا
		I2c_Write_داده(reg_جابه_جایی | 0x80, delay);
	I2c_Write_داده(reg_شمار, delay);

	لكل(صحيح i = 0; i < reg_شمار; i++)
	{
		I2c_Write_داده(*write_داده_2, delay);
		إذا(reg_شمار > 1)
			*write_داده_2++;
	}
	I2cStop(delay);
	أرجع 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
بیعلامت صحيح cdce913_read_all_registers(بیعلامت صحيح reg_جابه_جایی, بیعلامت صحيح reg_شمار, بیعلامت دراز delay)
{
	بیعلامت حرف readBuf = 0;
	بیعلامت کوتاه read_مقدار_2 = 0;

	I2c_Send_Slave_آدرس(CDCE913_SLAVE_آدرس, I2C_WRITE, delay);

	إذا(reg_شمار > 1)
		I2c_Write_داده(reg_جابه_جایی, delay);
	وإلا
		I2c_Write_داده(reg_جابه_جایی | 0x80, delay);

	I2c_شروع(delay);
	I2c_Send_Slave_آدرس(CDCE913_SLAVE_آدرس, I2C_READ, delay);

	إذا(reg_شمار > 1)
	{
		لكل(صحيح i = 0; i < reg_شمار; i++)
		{
			readBuf = I2c_Read_داده_Ack(delay);
			چاپ_کن("\n Read Value: %x", readBuf);
		}
	}
	وإلا
	{
		readBuf = I2c_Read_داده_Ack(delay);
		چاپ_کن("\n Value @ [%x]: [%x]", reg_جابه_جایی , readBuf);
	}
	I2cStop(delay);

	أرجع readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
فراغ اصلی()
{
	بیعلامت کوتاه موقت_Read = 0;
	بیعلامت کوتاه موقت = 0;

#اگر_تعریف_شده _50MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#پایان_اگر
#اگر_تعریف_شده _75MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#پایان_اگر
#اگر_تعریف_شده _100MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#پایان_اگر
#اگر_تعریف_شده _125MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#پایان_اگر
#اگر_تعریف_شده _130MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#پایان_اگر
#اگر_تعریف_شده _150MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#پایان_اگر
#اگر_تعریف_شده _175MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#پایان_اگر
#اگر_تعریف_شده _200MHZ
	بیعلامت صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بیعلامت صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#پایان_اگر

	بیعلامت صحيح eeprom_write = 0;
	بیعلامت صحيح read_مقدار = 0xff;

	چاپ_کن("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_شمار);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_شمار);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_شمار);

	طالما(1)
	{
		read_مقدار = cdce913_read_all_registers(0x02, 1, DELAY_شمار);
		إذا(0 == (read_مقدار & 0x40) )
			اكسر;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_شمار);

	چاپ_کن("\n After Write");

	لكل(صحيح i = 0; i < 32; i++)
	{
		إذا  ( (i >= 7) && (i <= 15) )
			استمر;
		cdce913_read_all_registers(i, 1, DELAY_شمار);
		delay_loop(1000,2000);
	}

	طالما(1);
}
