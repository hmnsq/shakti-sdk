/***************************************************************************
* Project                               : shakti devt board
* Name of the file                      : spi.c
* Brief Description of file             : write data to flash by spi 
* Name of Author                        : Kaustubh Ghormade, Kotteswaran
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
@brief  write data to flash by spi
@detail Contains driver codes to read and write flash using SPI interface.
*/

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "spi.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "utils.h"

#నిర్వచించు DELAY1 1000//Determines the duration of delay1//
#నిర్వచించు DELAY2 2000//Determines the duration of delay2//

/** @fn static void flash_read_locations(uint32_t read_address, uint16_t length)
 * @brief Reads the flash memory contents starting from read_address.
          Totally length number of bytes will be read.
 * @param unsigned int (32-bit).
 * @param unsigned int (16-bit).           
 */
స్థిర శూన్య flash_read_locations(uint32_t read_చిరునామా, uint16_t నిడివి_2)
{
	కొరకు(పూర్ణాంకం i = 0; i < నిడివి_2; ++i)
	{
		పూర్ణాంకం read_విలువ= flash_read(read_చిరునామా);
		రాయి("\nReading from adddress %x and దత్తాంశం_2 \
			   %x\n",read_చిరునామా,read_విలువ);
		read_చిరునామా=read_చిరునామా+4;
	}
}

/** @fn void main()
 * @brief Configures the SPI flash and writes into a flash location.
 * @details Configures the SPI flash, Confirms the flash device id,erases a sector
 *           and then write into a flash location and prints the value.
 */
శూన్య ప్రధాన()
{
	పూర్ణాంకం write_చిరునామా = 0x00b00004;  // read/write from/to this address
	పూర్ణాంకం read_చిరునామా  = 0x00b00004;  // read/write from/to this address
	పూర్ణాంకం దత్తాంశం_2 = 0xDEADBEEF; //32 bits of data can be written at a time
	uint16_t నిడివి_2 = 11;

	configure_spi(SPI0_స్థానభ్రంశం);
	spi_init();

	రాయి("SPI init done\n");

	flash_device_id(); 

	waitfor(200);

	రాయి("\n Before Erase");
	flash_read_locations(read_చిరునామా, నిడివి_2);
	flash_write_enable();
	flash_erase(0x00b00000); //erases an entire sector
	flash_స్థితి_రిజిస్టరు_read();
	రాయి("\n After Erase");
	flash_read_locations(read_చిరునామా, నిడివి_2);

	//flash write
	flash_write( write_చిరునామా, 0x12345678);
	flash_write( write_చిరునామా + 0x04, 0xaaaaaaaa);
	flash_write( write_చిరునామా + 0x08, 0x55555555);
	flash_write( write_చిరునామా + 0x0C, 0xAAAA5555);
	flash_write( write_చిరునామా + 0x10, 0x5555AAAA);
	flash_write( write_చిరునామా + 0x14, 0xaaa5aaa5);
	flash_write( write_చిరునామా + 0x18, 0x555A555A);
	flash_write( write_చిరునామా + 0x1c, 0xaa55aa55);
	flash_write( write_చిరునామా + 0x20, 0x55aa55aa);
	flash_write( write_చిరునామా + 0x24, 0x5a5a5a5a);
	flash_write( write_చిరునామా + 0x28, 0xa5a5a5a5);

	రాయి("\nFlash write done on address %x and data %x \n", 
	       write_చిరునామా, దత్తాంశం_2);

	రాయి("\n After Write");
	flash_read_locations(read_చిరునామా, నిడివి_2);
	asm అస్థిర ("ebreak");
}
