/***************************************************************************
 * Project                               :  shakti devt board
 * Name of the file                      :  spi_driver.c
 * Brief Description of file             :  Driver to control the spi device.
 * Name of Author                        :  Kaustubh Ghormade
 * Email ID                              :  kaustubh4347@gmail.com

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
 * @file spi_spansion.c
 * @brief Does basic flash operatons .
 * @detail Configures SPI, flash device and then do all basic flash oerations.
 */

#அந்தர்பாவ "spi.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "utils.h"

முழு* spi_cr1    = (முழு*) SPI_CR1;
முழு* spi_cr2    = (முழு*) SPI_CR2;
முழு* spi_sr     = (முழு*) SPI_SR ;
முழு* spi_dr1    = (முழு*) SPI_DR1;
முழு* spi_dr2    = (முழு*) SPI_DR2;
முழு* spi_dr3    = (முழு*) SPI_DR3;
முழு* spi_dr4    = (முழு*) SPI_DR4;
முழு* spi_dr5    = (முழு*) SPI_DR5;
முழு* spi_crcpr  = (முழு*) SPI_CRCPR;
முழு* spi_rxcrcr = (முழு*) SPI_RXCRCR;
முழு* spi_txcrcr = (முழு*) SPI_TXCRCR;

//By default, spi 0 is configured
/**
 * @fn void configure_spi(int offset)
 * @brief assigns memory mapped addres value to SPI registers.
 * @details Takes the SPI Base address and then adds offset to each and every
 *          spi registers..
 * @param int* ---> offset value
 */
வெறுமை configure_spi(முழு offset)
{
	spi_cr1    = (முழு*) (SPI_CR1 + offset);
	spi_cr2    = (முழு*) (SPI_CR2 + offset);
	spi_sr     = (முழு*) (SPI_SR + offset);
	spi_dr1    = (முழு*) (SPI_DR1 + offset);
	spi_dr2    = (முழு*) (SPI_DR2 + offset);
	spi_dr3    = (முழு*) (SPI_DR3 + offset);
	spi_dr4    = (முழு*) (SPI_DR4 + offset);
	spi_dr5    = (முழு*) (SPI_DR5 + offset);
	spi_crcpr  = (முழு*) (SPI_CRCPR + offset);
	spi_rxcrcr = (முழு*) (SPI_RXCRCR + offset);
	spi_txcrcr = (முழு*) (SPI_TXCRCR + offset);
}

/**
 * @fn void set_spi(int* addr, int val)
 * @brief to assign value to memory mapped spi register
 * @details writes the given value to given addres (SPI).
 * @param int* addr 
 * @param int val 
 */
வெறுமை set_spi(முழு* addr, முழு val)
{
	*addr = val;
}

/**
 * @fn int get_spi(int* addr)
 * @brief to get value for memory mapped spi register
 * @details Reads the SPI register value from passed address.
 * @param int* ---> address from where read has to happen
 * @return int ---> SPI Register read value.
 */
முழு get_spi(முழு* addr)
{
	திரும்பு *addr;
}

/** @fn void spi_init(void)
 * @brief setting up baud rate and clock pole and phase 
 * @details Initialize the spi controller in Mode 3 (CPOL =1 & CPHA =1) with SCK= clk/16
 */
வெறுமை spi_init(வெறுமை)
{
	set_spi(spi_cr1, (SPI_BR(7)|SPI_CPHA|SPI_CPOL));
}

/** @fn  void spi_tx_rx_start(void)
 * @brief to start receiving data as soon as transmit state is complete
 * @details While receiving data from flash (reading Device ID, status register and reading flash)  
 *           in master mode use this function.
 * @warning Should be set before configuring the control register 1.
 */
வெறுமை spi_tx_rx_start(வெறுமை)
{
	set_spi(spi_cr2, (SPI_RX_IMM_START));
}


/** @fn void spi_rx_enable(void)
 * @brief to start receive state 
 * @details This is not in used when spi is in Master mode 
 */
வெறுமை spi_rx_enable(வெறுமை)
{
	set_spi(spi_cr2, (SPI_RX_START));
}

/**
 * @fn int bitExtracted(int number, int k, int p)
 * @brief Extract the k number of bit from (p-1) position of 'number'
 * @details If one want to extract the k bits from (p-1) position in 32 bit "number".   
 * @param int (number (32 bit))
 * @param int (k (number of bits to be extracted))
 * @param int (p (position from where the bits to be extracted))
 * @return int (32 bit which have k bit from "number" and rest are zero)
 */
முழு bitExtracted(முழு எண், முழு k, முழு p)
{
	திரும்பு (((1 << k) - 1) & (எண் >> (p - 1)));
}

/**
 * @fn  int spi_rxne_enable(void)
 * @brief to check if receive buffer is empty or not
 * @details As soons as data come to receive buffer this bit is set.  
 * @return int (1: if there is data into the RxFIFO else 0)
 */
முழு spi_rxne_enable(வெறுமை)
{
	முழு மதிப்பு = 0;

	போது (!(மதிப்பு & 0x1))
	{
		waitfor(100);
		மதிப்பு = get_spi(spi_sr);
	}
	திரும்பு 1;
}

/**
 * @fn int spi_notbusy(void)
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning One should check this bit before going to next transcation
 * @return int (0: SPI is busy in communication, 1: SPI nt busy)
 */
முழு spi_notbusy(வெறுமை)
{
	முழு மதிப்பு = 0x80;

	போது ((மதிப்பு & 0x80))
	{
		waitfor(10);
		மதிப்பு = get_spi(spi_sr);
	}

	திரும்பு 1;
}

/**
 * @fn int flash_write_enable(void)
 * @brief to set the WEL (Write Enable Latch) bit in status register
 * @details Before modifying content of flash, one should enable the WEL bit first
 * @warning Without enabling this bit one cannot erase/write into the flash
 * @return int
 */
முழு flash_write_enable(வெறுமை)
{
	set_spi(spi_dr1, 0x06000000);
	set_spi(spi_dr5, 0x06);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	திரும்பு 1;
}

/**
 * @fn int flash_clear_sr(void)
 * @brief to reset the status register
 * @details It will reset the bits of status register
 * @return int
 */

முழு flash_clear_sr(வெறுமை)
{
	set_spi(spi_dr1,0x30000000);
	set_spi(spi_dr5,0x30);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	திரும்பு 1;
}

/**
 * @fn int flash_cmd_addr(int command, int addr)
 * @brief Use for sending 8bit of command + 32 bit of address 
 * @details Useful for function like erase
 * @warning to move data drom dr register to fifo there must be some data into spi_dr5 
 * @param int (command (opcode))
 * @param int (addr (address after the opcode))
 * @return int
 */
முழு flash_cmd_addr(முழு command, முழு addr)
{
	முழு address1 = bitExtracted(addr, 24, 9);
	முழு address2 = bitExtracted(addr, 8, 1);
	முழு data1 = command | address1 ;
	address2 = address2 << 24;

	set_spi(spi_dr1, data1);
	set_spi(spi_dr2, address2);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(40)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();

	திரும்பு 1;
}

/**
 * @fn void flash_cmd_addr_data(int command, int addr, int data)
 * @brief useful for function like Write 
 * @details use for sending 8bit command +32bit of write address + 32 bit of write data
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @param int (command (opcode))
 * @param int (addr(address after the opcode))
 * @param int (data (data after the address))
 */
வெறுமை flash_cmd_addr_data(முழு command, முழு addr, முழு data)
{
	முழு cmd_addr = command | ( (addr & 0xFFFFFF00)  >> 8);
	முழு data1 = ( (addr & 0xFF)  << 24 ) |( (data & 0xFFFFFF00)  >> 8);
	முழு data2 = ( (data & 0xFF)  << 24 ) & 0xFF000000;

	log_debug("\n cmd: %x;d1: %x; d2: %x", cmd_addr, data1, data2);

	set_spi(spi_dr1, cmd_addr);
	set_spi(spi_dr2, data1);
	set_spi(spi_dr3, data2);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(72)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();
	flash_status_register_read();
}

/**
 * @fn void flash_write(int address, int data)
 * @brief  Write 4bytes of data from given address
 * @details flash_cmd_addr_data with opcode 12h.  
 * @warning before writing into the flash one should enable the WEL bit spi_sr by using write_enable(void)
 * @param int (addres (write address))
 * @param int(data (write data))
 */
வெறுமை flash_write(முழு address, முழு data)
{
	flash_write_enable();
	flash_cmd_addr_data(0x12000000, address,data);
	flash_status_register_read();
}

/**
 * @fn int flash_cmd_to_read(int command, int addr)
 * @briefUse useful for function like read
 * @details for sending command of 8bit + read address of 32bit + 8bit of dummy cycle and receive 
 *          32bit value from flash 
 * @warning As receive shoild start as soon as transmit state end, use spi_rx_tx_start() Before 
 *          setting control register 1
 * @param int (command (opcode))
 * @param int (addr(read_address))
 * @return int 
 */
முழு flash_cmd_to_read(முழு command, முழு addr)
{
	முழு dr5;
	முழு address2 = bitExtracted(addr, 8, 1);

	address2 = address2 << 24;
	set_spi(spi_dr1, ( command  | ( (addr & 0xFFFFFF00) >> 8) ));
	set_spi(spi_dr2, ( (addr & 0xFF) << 24) );
	set_spi(spi_dr5, 0);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(48)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(2000);

	எனில்(spi_rxne_enable()) 
	{
		dr5 = *spi_dr5;
	}

	திரும்பு dr5;

}

/** @fn int flash_read(int address)
 * @brief read the 4bytes data from given address 
 * @details flash_cmd_to_read with opcode 0Bh for fast read
 * @param int (address (read address))
 * @return int 
 */
முழு flash_read(முழு address)
{
	முழு read_மதிப்பு = flash_cmd_to_read(0x0C000000,address);
	திரும்பு read_மதிப்பு;
}

/**
 * @fn int flash_cmd_read(int command)
 * @brief usefull for reading status register
 * @details use for sending 8bit command and receive the 32bit of data
 * @param int command (opcode)
 * @return int  value (flash response to opcode)
 */
முழு flash_cmd_read(முழு command)
{
	முழு dr5;
	set_spi(spi_dr1, command);
	set_spi(spi_dr5, command);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	எனில்(spi_rxne_enable()) {
		dr5 = *spi_dr5;
	}
	திரும்பு dr5;
}

/**
 * @fn  void flash_erase(int address)
 * @brief Erase the flash
 * @details Erase the 64kb sector from given address 
 * @warning before erasing the flash one should enable the WEL bit spi_sr by using write_enable()
 * @param int (address (address from which data should erase))
 */
வெறுமை flash_erase(முழு address)
{
	flash_cmd_addr(0xdc000000, address);
}

/**
 * @fn int flash_status_register_read(void)
 * @briefRead read status register of flash
 * @details  Using flash_cmd_read function with opcode 05h to check status of WIP(Write in progress)
 *           and WEL(Write Enable Latch) bit.
 * @return int
 */
முழு flash_status_register_read(வெறுமை)
{
	முழு stat = 0x3;

	போது (stat & 0x03)
	{
		stat = flash_cmd_read(0x05000000);
		log_debug("flash status register val %x\n", stat);
	}

	திரும்பு 0;
}

/**
 * @fn int flash_device_id(void)
 * @briefto read Device ID and Mfg. ID of flash
 * @details Device ID is 1byte and Mfg. ID of flash is of 2byte. Hence 8bit of command and receiving 
 *          24 bits of data from flash
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @return int
 */
முழு flash_device_id(வெறுமை)
{
	முழு dr3;
	முழு val1, val2;

	flash_write_enable();
	set_spi(spi_dr1, 0x9f000000);
	set_spi(spi_dr5, 0x9f000000);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(24)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	எனில்(spi_rxne_enable())
	{
		dr3 = *spi_dr5;
	}

	val1 = bitExtracted(dr3, 8, 17);
	val2 = bitExtracted(dr3, 16, 1);

	log_debug("Device ID %x \n", val1);
	log_debug("extracted device id %x \n",val2);

	திரும்பு 1;
}
