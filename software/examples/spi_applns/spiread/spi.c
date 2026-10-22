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
#అన్తర్భావ "spi.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "utils.h"

/** @fn void main()
 * @brief Configures the SPI flash and reads the flash.
 * @details Configures the SPI flash, Confirms the flash device id,
            then read 10 addresses in flash and prints the value.
 */
పూర్ణాంకం ప్రధాన(శూన్య){

	configure_spi(SPI0_స్థానభ్రంశం);

	spi_init();
	రాయి("SPI init done\n");
	flash_device_id();
	waitfor(200);
	పూర్ణాంకం మొత్తం_దత్తాంశం = 10; //total data you want to read/write
	పూర్ణాంకం read_చిరునామా = 0x00b00000;  //read from this address

	కొరకు(పూర్ణాంకం i = 0; i < మొత్తం_దత్తాంశం; ++i)
	{
		పూర్ణాంకం read_విలువ= flash_read(read_చిరునామా);
		రాయి("Reading from adddress %x and దత్తాంశం_2 \
		       %x\n",read_చిరునామా,read_విలువ);
		read_చిరునామా=read_చిరునామా+4;
	}
	asm అస్థిర ("ebreak");
	తిరిగి 0;
}
