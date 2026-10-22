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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <uart.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "spi.h"
#অন্তর্ভাব "flashdata.h"

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
শূন্য deploy()
{
	পূর্ণাঙ্ক read_address = 0x00b00000;
	দ্বিগুণ গুনতি=0.0;

	configure_spi(SPI0_OFFSET);
	spi_init();
	flash_device_id();

	waitfor(200);
	printf("\nErasing...\n");

	flash_write_enable();
	flash_erase(read_address);
	flash_status_register_read();
	printf("\nErase complete.\n");

	flash_write(read_address,write_data[0]);
	read_address+=4;

	printf("\nWriting...");

	প্রতি(পূর্ণাঙ্ক i =0; i< write_data[0]; i++)
	{
		waitfor(200);
		flash_write(read_address,write_data[i+1]);
		read_address+=4;

		যদি(i%512 == 0)
			printf(".");;
	}

	printf("\n\nWrite complete.\n");
	printf("\nPlease reset.\n");
	asm চঞ্চল ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
শূন্য main(){
	deploy();
}
