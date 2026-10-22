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
#ಅನ್ತರ್ಭಾವ "spi.h"
#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/** @fn void main()
 * @brief Configures the SPI flash and reads the flash.
 * @details Configures the SPI flash, Confirms the flash device id,
            then read 10 addresses in flash and prints the value.
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ){

	configure_spi(SPI0_ಸ್ಥಾನಾಂತರ);

	spi_init();
	ಬರೆ("SPI init done\n");
	flash_device_id();
	waitfor(200);
	ಪೂರ್ಣಾಂಕ ಒಟ್ಟು_ದತ್ತಾಂಶ = 10; //total data you want to read/write
	ಪೂರ್ಣಾಂಕ read_ವಿಳಾಸ = 0x00b00000;  //read from this address

	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < ಒಟ್ಟು_ದತ್ತಾಂಶ; ++i)
	{
		ಪೂರ್ಣಾಂಕ read_ಮೌಲ್ಯ= flash_read(read_ವಿಳಾಸ);
		ಬರೆ("Reading from adddress %x and ದತ್ತಾಂಶ_2 \
		       %x\n",read_ವಿಳಾಸ,read_ಮೌಲ್ಯ);
		read_ವಿಳಾಸ=read_ವಿಳಾಸ+4;
	}
	asm ಅಸ್ಥಿರ ("ebreak");
	ಹಿಂತಿರುಗಿ 0;
}
