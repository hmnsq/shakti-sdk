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

#അന്തര്ഭാവ "gpio_i2c.h"

#define CDCE913_SLAVE_ADDRESS 0xCA
#define DELAY_എണ്ണം 50
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
unsigned പൂർണ്ണസംഖ്യ cdce913_write_all_registers(unsigned പൂർണ്ണസംഖ്യ reg_offset, unsigned പൂർണ്ണസംഖ്യ reg_എണ്ണം, unsigned പൂർണ്ണസംഖ്യ *write_data, unsigned long delay)
{
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);
	എങ്കിൽ(reg_എണ്ണം > 1)
		I2cWriteData(reg_offset, delay);
	അല്ലെങ്കിൽ
		I2cWriteData(reg_offset | 0x80, delay);
	I2cWriteData(reg_എണ്ണം, delay);

	വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < reg_എണ്ണം; i++)
	{
		I2cWriteData(*write_data, delay);
		എങ്കിൽ(reg_എണ്ണം > 1)
			*write_data++;
	}
	I2cStop(delay);
	തിരികെ 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
unsigned പൂർണ്ണസംഖ്യ cdce913_read_all_registers(unsigned പൂർണ്ണസംഖ്യ reg_offset, unsigned പൂർണ്ണസംഖ്യ reg_എണ്ണം, unsigned long delay)
{
	unsigned അക്ഷരം readBuf = 0;
	unsigned short read_മൂല്യം_2 = 0;

	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_WRITE, delay);

	എങ്കിൽ(reg_എണ്ണം > 1)
		I2cWriteData(reg_offset, delay);
	അല്ലെങ്കിൽ
		I2cWriteData(reg_offset | 0x80, delay);

	I2cStart(delay);
	I2cSendSlaveAddress(CDCE913_SLAVE_ADDRESS, I2C_READ, delay);

	എങ്കിൽ(reg_എണ്ണം > 1)
	{
		വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < reg_എണ്ണം; i++)
		{
			readBuf = I2cReadDataAck(delay);
			printf("\n Read Value: %x", readBuf);
		}
	}
	അല്ലെങ്കിൽ
	{
		readBuf = I2cReadDataAck(delay);
		printf("\n Value @ [%x]: [%x]", reg_offset , readBuf);
	}
	I2cStop(delay);

	തിരികെ readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
ശൂന്യം പ്രധാന()
{
	unsigned short tempRead = 0;
	unsigned short temp = 0;

#ifdef _50MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _75MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#endif
#ifdef _100MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif
#ifdef _125MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#endif
#ifdef _130MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#endif
#ifdef _150MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#endif
#ifdef _175MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#endif
#ifdef _200MHZ
	unsigned പൂർണ്ണസംഖ്യ write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	unsigned പൂർണ്ണസംഖ്യ write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#endif

	unsigned പൂർണ്ണസംഖ്യ eeprom_write = 0;
	unsigned പൂർണ്ണസംഖ്യ read_മൂല്യം = 0xff;

	printf("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_എണ്ണം);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_എണ്ണം);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_എണ്ണം);

	ആകുമ്പോൾ(1)
	{
		read_മൂല്യം = cdce913_read_all_registers(0x02, 1, DELAY_എണ്ണം);
		എങ്കിൽ(0 == (read_മൂല്യം & 0x40) )
			നിർത്തുക;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_എണ്ണം);

	printf("\n After Write");

	വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < 32; i++)
	{
		എങ്കിൽ  ( (i >= 7) && (i <= 15) )
			തുടരുക;
		cdce913_read_all_registers(i, 1, DELAY_എണ്ണം);
		delay_loop(1000,2000);
	}

	ആകുമ്പോൾ(1);
}
