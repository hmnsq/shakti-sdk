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

#شامل <stdint.h>
#شامل <uart.h>
#شامل <stdio.h>
#شامل "spi.h"
#شامل "flashdata.h"

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
خالی deploy()
{
	صحیح read_پتہ = 0x00b00000;
	دوہرا گنتی=0.0;

	configure_spi(SPI0_انحراف);
	spi_init();
	flash_device_id();

	waitfor(200);
	لکھو("\nErasing...\n");

	flash_write_enable();
	flash_erase(read_پتہ);
	flash_حالت_رجسٹر_read();
	لکھو("\nErase complete.\n");

	flash_write(read_پتہ,write_ڈیٹا_2[0]);
	read_پتہ+=4;

	لکھو("\nWriting...");

	برائے(صحیح i =0; i< write_ڈیٹا_2[0]; i++)
	{
		waitfor(200);
		flash_write(read_پتہ,write_ڈیٹا_2[i+1]);
		read_پتہ+=4;

		اگر(i%512 == 0)
			لکھو(".");;
	}

	لکھو("\n\nWrite complete.\n");
	لکھو("\nPlease reset.\n");
	asm متلون ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
خالی مین(){
	deploy();
}
