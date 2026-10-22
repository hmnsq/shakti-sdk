/***************************************************************************
 * Project           	           : shakti devt board
 * Name of the file	     	       : w25q32_write.c
 * Brief Description of file       : Performs the windonb flash  spi writing of 0 to 100 nos .
 * Name of Author    	           : G Nambirajan & Koteeswaran
 * Email ID                        : nambirajan2004@gmail.com

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
@file   w25q32_write.c
@brief  Contains the driver routines for flash write over SPI interface.
@detail Configures and writes the flash over SPI interface..
*/
/************************************************
PIN DETAILS CONNECTIONS OF WINBOND W25Q32 FLASH
d1 - spi mosi
d0 - spi miso
clk -spi clk
cs  -spi cs
*************************************************/
#ضمن <stdint.h>
#ضمن "spi.h"
#ضمن "pinmux.h"

/** @fn void w25q32()
 * @brief Writes the spi value to w25q32
 * @details Writes SPI over w25q32 interface
 */
فراغ w25q32()
{
	صحيح tmp = 0x00;//32 bits of data can be written at a time
	صحيح write_پتو = 0x0000100;  // read/write from/to this address

	*pinmux_config_reg = 0x154000;	

	waitfor(200);
	configure_spi(SPI1_وٿي);
	spi_init();
	
	لکو("SPI init done\n");
	
	flash_device_id(); 

	لكل ( صحيح معلومات_2=0;  معلومات_2<=100;  معلومات_2++)
	{
	  flash_erase(write_پتو); //erases an entire sector
	  flash_حالت_رجسٽر_read();
	  //flash write
	  flash_write_enable();
	  flash_write( write_پتو,tmp);
	  
	  لکو("Flash write done on address %x and tmp %x \n", write_پتو, معلومات_2);
	  
	  tmp = tmp+0x1;
	  write_پتو = write_پتو+4;
	}
	لکو("SPI Write Success\n");
}

/**  @fn void main()
 * @brief Configures and Write the SPI values.
 * @details Configures the SPI Write FLASH values, Write the same 
 * prints the write values.
 */
فراغ مکيه()
{
	w25q32();
	طالما (1);
}
