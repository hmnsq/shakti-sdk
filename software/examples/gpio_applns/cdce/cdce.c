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

#تعریف_کرو CDCE913_SLAVE_پتہ 0xCA
#تعریف_کرو DELAY_گنتی 50
#تعریف_کرو _50MHZ
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
بنانشانی صحيح cdce913_write_all_registers(بنانشانی صحيح reg_وتھ, بنانشانی صحيح reg_گنتی, بنانشانی صحيح *write_انکڑے_2, بنانشانی لما delay)
{
	I2c_Send_Slave_پتہ(CDCE913_SLAVE_پتہ, I2C_WRITE, delay);
	إذا(reg_گنتی > 1)
		I2c_Write_انکڑے(reg_وتھ, delay);
	وإلا
		I2c_Write_انکڑے(reg_وتھ | 0x80, delay);
	I2c_Write_انکڑے(reg_گنتی, delay);

	لكل(صحيح i = 0; i < reg_گنتی; i++)
	{
		I2c_Write_انکڑے(*write_انکڑے_2, delay);
		إذا(reg_گنتی > 1)
			*write_انکڑے_2++;
	}
	I2cStop(delay);
	أرجع 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
بنانشانی صحيح cdce913_read_all_registers(بنانشانی صحيح reg_وتھ, بنانشانی صحيح reg_گنتی, بنانشانی لما delay)
{
	بنانشانی حرف readBuf = 0;
	بنانشانی چھوٹا read_قدر_2 = 0;

	I2c_Send_Slave_پتہ(CDCE913_SLAVE_پتہ, I2C_WRITE, delay);

	إذا(reg_گنتی > 1)
		I2c_Write_انکڑے(reg_وتھ, delay);
	وإلا
		I2c_Write_انکڑے(reg_وتھ | 0x80, delay);

	I2c_شروع(delay);
	I2c_Send_Slave_پتہ(CDCE913_SLAVE_پتہ, I2C_READ, delay);

	إذا(reg_گنتی > 1)
	{
		لكل(صحيح i = 0; i < reg_گنتی; i++)
		{
			readBuf = I2c_Read_انکڑے_Ack(delay);
			لکھو("\n Read Value: %x", readBuf);
		}
	}
	وإلا
	{
		readBuf = I2c_Read_انکڑے_Ack(delay);
		لکھو("\n Value @ [%x]: [%x]", reg_وتھ , readBuf);
	}
	I2cStop(delay);

	أرجع readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
فراغ مکھ()
{
	بنانشانی چھوٹا عارضی_Read = 0;
	بنانشانی چھوٹا عارضی = 0;

#جے_تعریف_شدہ _50MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جے_انت
#جے_تعریف_شدہ _75MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#جے_انت
#جے_تعریف_شدہ _100MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جے_انت
#جے_تعریف_شدہ _125MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#جے_انت
#جے_تعریف_شدہ _130MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#جے_انت
#جے_تعریف_شدہ _150MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#جے_انت
#جے_تعریف_شدہ _175MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#جے_انت
#جے_تعریف_شدہ _200MHZ
	بنانشانی صحيح write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	بنانشانی صحيح write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#جے_انت

	بنانشانی صحيح eeprom_write = 0;
	بنانشانی صحيح read_قدر = 0xff;

	لکھو("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_گنتی);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_گنتی);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_گنتی);

	طالما(1)
	{
		read_قدر = cdce913_read_all_registers(0x02, 1, DELAY_گنتی);
		إذا(0 == (read_قدر & 0x40) )
			اكسر;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_گنتی);

	لکھو("\n After Write");

	لكل(صحيح i = 0; i < 32; i++)
	{
		إذا  ( (i >= 7) && (i <= 15) )
			استمر;
		cdce913_read_all_registers(i, 1, DELAY_گنتی);
		delay_loop(1000,2000);
	}

	طالما(1);
}
