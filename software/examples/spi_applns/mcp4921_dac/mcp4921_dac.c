/***************************************************************************
 * Project           	     	:  shakti devt board
 * Name of the file	     	    :  mcp4921_dac.c
 * Brief Description of file    :  Performs the Digital to analog operation with spi writing.
 * Name of Author    	        :  G Nambirajan, Koteeswaran
 * Email ID                     :  nambirajan2004@gmail.com

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
@file   mcp4921_dac.c
@brief  Configures and write a value to DAC.
@detail SPI interface is used to configure the DAC and then write passed 
        value to DAC for converstion.
*/
#അന്തര്ഭാവ "spi.h"
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ "platform.h"
#അന്തര്ഭാവ "pinmux.h"

ബാഹ്യ അസ്ഥിര unsigned പൂർണ്ണസംഖ്യ* pinmux_config_reg;
ബാഹ്യ പൂർണ്ണസംഖ്യ* spi_cr1 ;
ബാഹ്യ പൂർണ്ണസംഖ്യ* spi_dr1 ;
ബാഹ്യ പൂർണ്ണസംഖ്യ* spi_dr5;

/** @fn void spi_dac()
 * @brief Configures DAC and write digital value to DAC.
 * @details configures the DAC and writes the digital value to DAC to convert 
 *          with digital to analog. Configuration is done using SPI.
 */
ശൂന്യം spi_dac()
{
	*(pinmux_config_reg) =  0x154000;
    configure_spi(SPI1_OFFSET);	
	spi_init();

	log_debug("SPI init done\n");

	waitfor(200);
	write_dac_മൂല്യം(0xfff);

	log_debug("\nDac Value Written\n");

	ആകുമ്പോൾ(1)
	{
		write_dac_മൂല്യം(0xFFF);
		log_debug("Dac Value Written - 4096\n");

		delay_loop(0x1750, 0x1750);
		write_dac_മൂല്യം(0x0);
		log_debug("Dac Value Written - 0\n");

		delay_loop(0x1750, 0x1750);
	}
} 

/** @fn int write_dac_value(unsigned dac_value)
 * @brief Writes the passed Value to DAC
 * @details Writes Digital value that needs to be convert into analog over SPI interface
 * @param dac_value
 * @return One.
 */
പൂർണ്ണസംഖ്യ write_dac_മൂല്യം(unsigned dac_മൂല്യം)
{
	പൂർണ്ണസംഖ്യ data1 = ((0x3 << 28) | (dac_മൂല്യം << 16));

	log_info("\n Data value written: %x", data1);

	set_spi(spi_dr1, data1);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(16)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	waitfor(20);
	spi_notbusy();

	തിരികെ 1;
}

/** @fn void main()
 * @brief Configures and Write the SPI values.
 * @details Configures DAC registers and then write the digital 
 *          that needs to be converted to analog.  
 */
ശൂന്യം പ്രധാന()
{
	spi_dac();
}
