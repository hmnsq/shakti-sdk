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

#include <stdint.h>
#include <uart.h>
#include <stdio.h>
#include "spi.h"
#include "flashdata.h"
#define SECTOR_SIZE 0x4000

/** @fn void deploy()
 * @brief Erases flash and writes the hex array entry by entry into the flash
 *       memory. Here SPI protocol is used.
 */
void deploy()
{
	int read_address = 0x00b00000;
	double count=0.0;
	int read_value = 0;
	int i = 0;
	configure_spi(SPI0_OFFSET);
	spi_init();
	flash_device_id();

	waitfor(200);
	printf("\nErasing...\n");

	i = 0;
	while(1)
	{
		flash_write_enable();
		flash_erase(read_address);
		flash_status_register_read();
//		printf("\nErase complete for sector address %x.\n", read_address);
		read_address += (i * SECTOR_SIZE);
		if(read_address > 0x00F00000)
			break;
			i++;
	}

	read_address = 0x00b00000;
	flash_write(read_address,write_data[0]);
	read_address+=4;
		printf("\nWriting...");

	for( i = 0; i < write_data[0]; i++)
	{
		waitfor(200);
		flash_write(read_address,write_data[i+1]);
		read_address+=4;

		if(i % 2048 == 0)
			printf(".");;
	}

	printf("\n\nWrite complete.\n");
	read_address = 0x00b00000;
#if 0
	printf("\nVerifying...");
	for( i = 0; i < write_data[0]; i++)
	{
		waitfor(200);
		read_value = flash_read(read_address);
		if(read_value != write_data[i])
		{
			printf("\n Error in verifying");
			printf("\n Read value: %x; Write value: %x; offset: %x", read_value, write_data[i], i);
			break;
		}
		read_address+=4;

		if(i % 2048 == 0)
			printf("*");;
	}
#endif

	printf("\nPlease reset.\n");
	asm volatile ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
void main(){
	deploy();
}
