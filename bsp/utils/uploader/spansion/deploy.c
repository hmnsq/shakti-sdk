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

#ضمن <stdint.h>
#ضمن <uart.h>
#ضمن <stdio.h>
#ضمن "spi.h"
#ضمن "flashdata.h"

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
فراغ deploy()
{
	صحيح read_پته = 0x00b00000;
	مزدوج شمېر=0.0;

	configure_spi(SPI0_دننه_واټن);
	spi_init();
	flash_device_id();

	waitfor(200);
	چاپ_کړه("\nErasing...\n");

	flash_write_enable();
	flash_erase(read_پته);
	flash_حالت_ثبتوونکی_read();
	چاپ_کړه("\nErase complete.\n");

	flash_write(read_پته,write_معلومات_2[0]);
	read_پته+=4;

	چاپ_کړه("\nWriting...");

	لكل(صحيح i =0; i< write_معلومات_2[0]; i++)
	{
		waitfor(200);
		flash_write(read_پته,write_معلومات_2[i+1]);
		read_پته+=4;

		إذا(i%512 == 0)
			چاپ_کړه(".");;
	}

	چاپ_کړه("\n\nWrite complete.\n");
	چاپ_کړه("\nPlease reset.\n");
	asm متطاير ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
فراغ اصلي(){
	deploy();
}
