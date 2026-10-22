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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "spi.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pinmux.h"

/** 
 * @fn void w25q32()
 * @brief Reads the spi value from w25q32
 * @details Reads SPI over w25q32 interface
 */
ਖਾਲੀ w25q32()
{
	ਪੂਰਨ ਕੁੱਲ_ਅੰਕੜੇ = 100; //total data you want to read/write
	ਪੂਰਨ read_ਪਤਾ = 0x00000100;  //read from this address
	ਪੂਰਨ* bram_ਪਤਾ = (ਪੂਰਨ*) 0x80000100; //write to this address

	*pinmux_config_reg = 0x154000;	

	configure_spi(SPI1_ਵਿੱਥ);
	spi_init();

	ਲਿਖੋ("SPI init done\n");

	flash_device_id();
	waitfor(200);
		
	ਲਈ(ਪੂਰਨ i = 0; i < ਕੁੱਲ_ਅੰਕੜੇ; ++i)
	{
		ਪੂਰਨ read_ਮੁੱਲ= flash_read(read_ਪਤਾ);
		ਲਿਖੋ("Reading from adddress %x and data \ %x\n",read_ਪਤਾ,read_ਮੁੱਲ);
		*(bram_ਪਤਾ+i) = read_ਮੁੱਲ;
		read_ਪਤਾ=read_ਪਤਾ+4;
	}
	ਲਿਖੋ("SPI Read Successr\n");
}

/** 
 * @fn void main()
 * @brief Configures and reads the SPI values.
 * @details Configures the SPI read FLASH values, reads the same 
 * prints the read values.
 */
ਖਾਲੀ ਮੁੱਖ()
{
	w25q32();

	ਜਦੋਂ(1);
}
