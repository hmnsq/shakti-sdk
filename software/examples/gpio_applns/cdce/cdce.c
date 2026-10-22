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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio_i2c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CDCE913_SLAVE_ਪਤਾ 0xCA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਗਿਣਤੀ 50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _50MHZ
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
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cdce913_write_all_registers(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਗਿਣਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *write_ਅੰਕੜੇ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	I2c_Send_Slave_ਪਤਾ(CDCE913_SLAVE_ਪਤਾ, I2C_WRITE, delay);
	ਜੇ(reg_ਗਿਣਤੀ > 1)
		I2c_Write_ਅੰਕੜੇ(reg_ਵਿੱਥ, delay);
	ਨਹੀਂਤਾਂ
		I2c_Write_ਅੰਕੜੇ(reg_ਵਿੱਥ | 0x80, delay);
	I2c_Write_ਅੰਕੜੇ(reg_ਗਿਣਤੀ, delay);

	ਲਈ(ਪੂਰਨ i = 0; i < reg_ਗਿਣਤੀ; i++)
	{
		I2c_Write_ਅੰਕੜੇ(*write_ਅੰਕੜੇ_2, delay);
		ਜੇ(reg_ਗਿਣਤੀ > 1)
			*write_ਅੰਕੜੇ_2++;
	}
	I2cStop(delay);
	ਵਾਪਸ 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cdce913_read_all_registers(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਗਿਣਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ readBuf = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ read_ਮੁੱਲ_2 = 0;

	I2c_Send_Slave_ਪਤਾ(CDCE913_SLAVE_ਪਤਾ, I2C_WRITE, delay);

	ਜੇ(reg_ਗਿਣਤੀ > 1)
		I2c_Write_ਅੰਕੜੇ(reg_ਵਿੱਥ, delay);
	ਨਹੀਂਤਾਂ
		I2c_Write_ਅੰਕੜੇ(reg_ਵਿੱਥ | 0x80, delay);

	I2c_ਸ਼ੁਰੂ(delay);
	I2c_Send_Slave_ਪਤਾ(CDCE913_SLAVE_ਪਤਾ, I2C_READ, delay);

	ਜੇ(reg_ਗਿਣਤੀ > 1)
	{
		ਲਈ(ਪੂਰਨ i = 0; i < reg_ਗਿਣਤੀ; i++)
		{
			readBuf = I2c_Read_ਅੰਕੜੇ_Ack(delay);
			ਲਿਖੋ("\n Read Value: %x", readBuf);
		}
	}
	ਨਹੀਂਤਾਂ
	{
		readBuf = I2c_Read_ਅੰਕੜੇ_Ack(delay);
		ਲਿਖੋ("\n Value @ [%x]: [%x]", reg_ਵਿੱਥ , readBuf);
	}
	I2cStop(delay);

	ਵਾਪਸ readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
ਖਾਲੀ ਮੁੱਖ()
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਆਰਜ਼ੀ_Read = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਆਰਜ਼ੀ = 0;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _50MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _75MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _100MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _125MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _130MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _150MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _175MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _200MHZ
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#ਜੇ_ਅੰਤ

	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ eeprom_write = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ read_ਮੁੱਲ = 0xff;

	ਲਿਖੋ("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_ਗਿਣਤੀ);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_ਗਿਣਤੀ);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ਗਿਣਤੀ);

	ਜਦੋਂ(1)
	{
		read_ਮੁੱਲ = cdce913_read_all_registers(0x02, 1, DELAY_ਗਿਣਤੀ);
		ਜੇ(0 == (read_ਮੁੱਲ & 0x40) )
			ਰੋਕੋ;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_ਗਿਣਤੀ);

	ਲਿਖੋ("\n After Write");

	ਲਈ(ਪੂਰਨ i = 0; i < 32; i++)
	{
		ਜੇ  ( (i >= 7) && (i <= 15) )
			ਜਾਰੀ;
		cdce913_read_all_registers(i, 1, DELAY_ਗਿਣਤੀ);
		delay_loop(1000,2000);
	}

	ਜਦੋਂ(1);
}
