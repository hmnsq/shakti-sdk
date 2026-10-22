/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	        : w25q32_read.c
 * Brief Description of file    : Performs the windonb flash  spi reading of 0 to 100                                                  numbers.
 * Name of Author    	        : G Nambirajan & Koteeswaran
 * Email ID                     : nambirajan2004@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

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
***************************************************************************/
/**
@file   w25q32_read.c
@brief  Contains the driver routines for flash read over SPI interface.
@detail Configures and reads the flash over SPI interface..
*/

/*********************************************
PIN DETAILS CONNECTION OF WINBOND W25Q32 FLASH
d1 - spi mosi
d0 - spi miso
clk -spi clk
cs  -spi cs
**********************************************/
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ "spi.h"
#അന്തര്ഭാവ "pinmux.h"

/** 
 * @fn void w25q32()
 * @brief Reads the spi value from w25q32
 * @details Reads SPI over w25q32 interface
 */
ശൂന്യം w25q32()
{
	പൂർണ്ണസംഖ്യ total_data = 100; //total data you want to read/write
	പൂർണ്ണസംഖ്യ read_address = 0x00000100;  //read from this address
	പൂർണ്ണസംഖ്യ* bram_address = (പൂർണ്ണസംഖ്യ*) 0x80000100; //write to this address

	*pinmux_config_reg = 0x154000;	

	configure_spi(SPI1_OFFSET);
	spi_init();

	printf("SPI init done\n");

	flash_device_id();
	waitfor(200);
		
	വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < total_data; ++i)
	{
		പൂർണ്ണസംഖ്യ read_മൂല്യം= flash_read(read_address);
		printf("Reading from adddress %x and data \ %x\n",read_address,read_മൂല്യം);
		*(bram_address+i) = read_മൂല്യം;
		read_address=read_address+4;
	}
	printf("SPI Read Successr\n");
}

/** 
 * @fn void main()
 * @brief Configures and reads the SPI values.
 * @details Configures the SPI read FLASH values, reads the same 
 * prints the read values.
 */
ശൂന്യം പ്രധാന()
{
	w25q32();

	ആകുമ്പോൾ(1);
}
