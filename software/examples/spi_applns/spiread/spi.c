/***************************************************************************
 * Project                               : shakti devt board
 * Name of the file                      : spi.c
 * Brief Description of file             : read data from the flash by spi 
 * Name of Author                        : Kaustubh Ghormade
 * Email ID                              : kaustubh4347@gmail.com

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
  @file spi.c
  @brief read data from the flash by spi
  @detail Contains driver codes to read and write flash using SPI interface.
 */
#شامل "spi.h"
#شامل "uart.h"
#شامل "utils.h"

/** @fn void main()
 * @brief Configures the SPI flash and reads the flash.
 * @details Configures the SPI flash, Confirms the flash device id,
            then read 10 addresses in flash and prints the value.
 */
صحیح مین(خالی){

	configure_spi(SPI0_انحراف);

	spi_init();
	لکھو("SPI init done\n");
	flash_device_id();
	waitfor(200);
	صحیح کل_ڈیٹا = 10; //total data you want to read/write
	صحیح read_پتہ = 0x00b00000;  //read from this address

	برائے(صحیح i = 0; i < کل_ڈیٹا; ++i)
	{
		صحیح read_قدر= flash_read(read_پتہ);
		لکھو("Reading from adddress %x and ڈیٹا_2 \
		       %x\n",read_پتہ,read_قدر);
		read_پتہ=read_پتہ+4;
	}
	asm متلون ("ebreak");
	واپس 0;
}
