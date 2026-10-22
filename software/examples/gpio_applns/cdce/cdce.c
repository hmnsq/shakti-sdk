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

#అన్తర్భావ "gpio_i2c.h"

#నిర్వచించు CDCE913_SLAVE_చిరునామా 0xCA
#నిర్వచించు DELAY_లెక్క 50
#నిర్వచించు _50MHZ
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
గుర్తులేని పూర్ణాంకం cdce913_write_all_registers(గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం reg_లెక్క, గుర్తులేని పూర్ణాంకం *write_దత్తాంశం_2, గుర్తులేని దీర్ఘ delay)
{
	I2c_Send_Slave_చిరునామా(CDCE913_SLAVE_చిరునామా, I2C_WRITE, delay);
	ఒకవేళ(reg_లెక్క > 1)
		I2c_Write_దత్తాంశం(reg_స్థానభ్రంశం, delay);
	లేకపోతే
		I2c_Write_దత్తాంశం(reg_స్థానభ్రంశం | 0x80, delay);
	I2c_Write_దత్తాంశం(reg_లెక్క, delay);

	కొరకు(పూర్ణాంకం i = 0; i < reg_లెక్క; i++)
	{
		I2c_Write_దత్తాంశం(*write_దత్తాంశం_2, delay);
		ఒకవేళ(reg_లెక్క > 1)
			*write_దత్తాంశం_2++;
	}
	I2cStop(delay);
	తిరిగి 0;
}

/** @fn unsigned int cdceReadunsigned long delay)
 * @brief Complete function to read value from cdce ic
 * @param unsigned long delay
 * @return unsigned int
 */
గుర్తులేని పూర్ణాంకం cdce913_read_all_registers(గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం reg_లెక్క, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం readBuf = 0;
	గుర్తులేని పొట్టి read_విలువ_2 = 0;

	I2c_Send_Slave_చిరునామా(CDCE913_SLAVE_చిరునామా, I2C_WRITE, delay);

	ఒకవేళ(reg_లెక్క > 1)
		I2c_Write_దత్తాంశం(reg_స్థానభ్రంశం, delay);
	లేకపోతే
		I2c_Write_దత్తాంశం(reg_స్థానభ్రంశం | 0x80, delay);

	I2c_ప్రారంభం(delay);
	I2c_Send_Slave_చిరునామా(CDCE913_SLAVE_చిరునామా, I2C_READ, delay);

	ఒకవేళ(reg_లెక్క > 1)
	{
		కొరకు(పూర్ణాంకం i = 0; i < reg_లెక్క; i++)
		{
			readBuf = I2c_Read_దత్తాంశం_Ack(delay);
			రాయి("\n Read Value: %x", readBuf);
		}
	}
	లేకపోతే
	{
		readBuf = I2c_Read_దత్తాంశం_Ack(delay);
		రాయి("\n Value @ [%x]: [%x]", reg_స్థానభ్రంశం , readBuf);
	}
	I2cStop(delay);

	తిరిగి readBuf;
}

/** @fn void main()
 * @brief Calling cdceRead to check the register value
 * @details to check the given value
 */
శూన్య ప్రధాన()
{
	గుర్తులేని పొట్టి తాత్కాలిక_Read = 0;
	గుర్తులేని పొట్టి తాత్కాలిక = 0;

#నిర్వచితమైతే _50MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x04, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#అయితే_ముగింపు
#నిర్వచితమైతే _75MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x03, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xFE, 0xBA, 0x32, 0x7, 0xFE, 0xBA, 0x32, 0x04};
#అయితే_ముగింపు
#నిర్వచితమైతే _100MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x02, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#అయితే_ముగింపు
#నిర్వచితమైతే _125MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x8C, 0xA7, 0xE2, 0x49, 0x8C, 0xA7, 0xE2, 0x48};
#అయితే_ముగింపు
#నిర్వచితమైతే _130MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0x92, 0x43, 0xF2, 0x69, 0x92, 0x43, 0xF2, 0x68};
#అయితే_ముగింపు
#నిర్వచితమైతే _150MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xAF, 0x03, 0x82, 0xCA, 0xAF, 0x03, 0x82, 0xC8};
#అయితే_ముగింపు
#నిర్వచితమైతే _175MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xC4, 0xEE, 0x23, 0x2B, 0xC4, 0xEE, 0x23, 0x28};
#అయితే_ముగింపు
#నిర్వచితమైతే _200MHZ
	గుర్తులేని పూర్ణాంకం write_buf1[] = {0x00, 0x07, 0x01, 0x01, 0xb4, 0x01, 0x02, 0x90, 0x40};
	గుర్తులేని పూర్ణాంకం write_buf2[] = {0x10, 16, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x02, 0x00, 0x00, 0xE1, 0x09, 0x93, 0xAB, 0xE1, 0x09, 0x93, 0xA8};
#అయితే_ముగింపు

	గుర్తులేని పూర్ణాంకం eeprom_write = 0;
	గుర్తులేని పూర్ణాంకం read_విలువ = 0xff;

	రాయి("\n\ttemp sensor initiating!");

	I2cInit();

	cdce913_write_all_registers(write_buf1[0], write_buf1[1], &write_buf1[2], DELAY_లెక్క);
	cdce913_write_all_registers(write_buf2[0], write_buf2[1], &write_buf2[2], DELAY_లెక్క);

	eeprom_write = 0x21;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_లెక్క);

	అయితే(1)
	{
		read_విలువ = cdce913_read_all_registers(0x02, 1, DELAY_లెక్క);
		ఒకవేళ(0 == (read_విలువ & 0x40) )
			ఆపు;
	}
	eeprom_write = 0x20;
	cdce913_write_all_registers(0x06, 1, &eeprom_write, DELAY_లెక్క);

	రాయి("\n After Write");

	కొరకు(పూర్ణాంకం i = 0; i < 32; i++)
	{
		ఒకవేళ  ( (i >= 7) && (i <= 15) )
			కొనసాగు;
		cdce913_read_all_registers(i, 1, DELAY_లెక్క);
		delay_loop(1000,2000);
	}

	అయితే(1);
}
