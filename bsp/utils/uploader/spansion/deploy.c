/***************************************************************************
 * Project                               :  shakti devt board
 * Name of the file                      :  deploy.c
 * Brief Description of file             :  Deploy elf into flash in board.
 * Name of Author                        :  Sathya Narayanan N & Anand Kumar S
 * Email ID                              :  sathya281@gmail.com

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
@file deploy.c
@brief Deploy elf into flash in board.
@detail This file has functions that can write an array of hex numbers into the
flash device. SPI protocol is used for this purporse. The array is usually a
project's hex file 
*/

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <uart.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ "spi.h"
#అన్తర్భావ "flashdata.h"

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
శూన్య deploy()
{
	పూర్ణాంకం read_చిరునామా = 0x00b00000;
	ద్విగుణ లెక్క=0.0;

	configure_spi(SPI0_స్థానభ్రంశం);
	spi_init();
	flash_device_id();

	waitfor(200);
	రాయి("\nErasing...\n");

	flash_write_enable();
	flash_erase(read_చిరునామా);
	flash_స్థితి_రిజిస్టరు_read();
	రాయి("\nErase complete.\n");

	flash_write(read_చిరునామా,write_దత్తాంశం_2[0]);
	read_చిరునామా+=4;

	రాయి("\nWriting...");

	కొరకు(పూర్ణాంకం i =0; i< write_దత్తాంశం_2[0]; i++)
	{
		waitfor(200);
		flash_write(read_చిరునామా,write_దత్తాంశం_2[i+1]);
		read_చిరునామా+=4;

		ఒకవేళ(i%512 == 0)
			రాయి(".");;
	}

	రాయి("\n\nWrite complete.\n");
	రాయి("\nPlease reset.\n");
	asm అస్థిర ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
శూన్య ప్రధాన(){
	deploy();
}
