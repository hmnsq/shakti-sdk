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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <uart.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "spi.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "flashdata.h"

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
ਖਾਲੀ deploy()
{
	ਪੂਰਨ read_ਪਤਾ = 0x00b00000;
	ਦੁੱਗਣਾ ਗਿਣਤੀ_2=0.0;

	configure_spi(SPI0_ਵਿੱਥ);
	spi_init();
	flash_device_id();

	waitfor(200);
	ਲਿਖੋ("\nErasing...\n");

	flash_write_enable();
	flash_erase(read_ਪਤਾ);
	flash_ਸਥਿਤੀ_ਰਜਿਸਟਰ_read();
	ਲਿਖੋ("\nErase complete.\n");

	flash_write(read_ਪਤਾ,write_ਅੰਕੜੇ_2[0]);
	read_ਪਤਾ+=4;

	ਲਿਖੋ("\nWriting...");

	ਲਈ(ਪੂਰਨ i =0; i< write_ਅੰਕੜੇ_2[0]; i++)
	{
		waitfor(200);
		flash_write(read_ਪਤਾ,write_ਅੰਕੜੇ_2[i+1]);
		read_ਪਤਾ+=4;

		ਜੇ(i%512 == 0)
			ਲਿਖੋ(".");;
	}

	ਲਿਖੋ("\n\nWrite complete.\n");
	ਲਿਖੋ("\nPlease reset.\n");
	asm ਅਸਥਿਰ ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
ਖਾਲੀ ਮੁੱਖ(){
	deploy();
}
