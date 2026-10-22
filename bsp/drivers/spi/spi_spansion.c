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

#అన్తర్భావ "spi.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "utils.h"

పూర్ణాంకం* spi_cr1    = (పూర్ణాంకం*) SPI_CR1;
పూర్ణాంకం* spi_cr2    = (పూర్ణాంకం*) SPI_CR2;
పూర్ణాంకం* spi_sr     = (పూర్ణాంకం*) SPI_SR ;
పూర్ణాంకం* spi_dr1    = (పూర్ణాంకం*) SPI_DR1;
పూర్ణాంకం* spi_dr2    = (పూర్ణాంకం*) SPI_DR2;
పూర్ణాంకం* spi_dr3    = (పూర్ణాంకం*) SPI_DR3;
పూర్ణాంకం* spi_dr4    = (పూర్ణాంకం*) SPI_DR4;
పూర్ణాంకం* spi_dr5    = (పూర్ణాంకం*) SPI_DR5;
పూర్ణాంకం* spi_crcpr  = (పూర్ణాంకం*) SPI_CRCPR;
పూర్ణాంకం* spi_rxcrcr = (పూర్ణాంకం*) SPI_RXCRCR;
పూర్ణాంకం* spi_txcrcr = (పూర్ణాంకం*) SPI_TXCRCR;

//By default, spi 0 is configured
/**
 * @fn void configure_spi(int offset)
 * @brief assigns memory mapped addres value to SPI registers.
 * @details Takes the SPI Base address and then adds offset to each and every
 *          spi registers..
 * @param int* ---> offset value
 */
శూన్య configure_spi(పూర్ణాంకం స్థానభ్రంశం)
{
	spi_cr1    = (పూర్ణాంకం*) (SPI_CR1 + స్థానభ్రంశం);
	spi_cr2    = (పూర్ణాంకం*) (SPI_CR2 + స్థానభ్రంశం);
	spi_sr     = (పూర్ణాంకం*) (SPI_SR + స్థానభ్రంశం);
	spi_dr1    = (పూర్ణాంకం*) (SPI_DR1 + స్థానభ్రంశం);
	spi_dr2    = (పూర్ణాంకం*) (SPI_DR2 + స్థానభ్రంశం);
	spi_dr3    = (పూర్ణాంకం*) (SPI_DR3 + స్థానభ్రంశం);
	spi_dr4    = (పూర్ణాంకం*) (SPI_DR4 + స్థానభ్రంశం);
	spi_dr5    = (పూర్ణాంకం*) (SPI_DR5 + స్థానభ్రంశం);
	spi_crcpr  = (పూర్ణాంకం*) (SPI_CRCPR + స్థానభ్రంశం);
	spi_rxcrcr = (పూర్ణాంకం*) (SPI_RXCRCR + స్థానభ్రంశం);
	spi_txcrcr = (పూర్ణాంకం*) (SPI_TXCRCR + స్థానభ్రంశం);
}

/**
 * @fn void set_spi(int* addr, int val)
 * @brief to assign value to memory mapped spi register
 * @details writes the given value to given addres (SPI).
 * @param int* addr 
 * @param int val 
 */
శూన్య సమితి_spi(పూర్ణాంకం* addr, పూర్ణాంకం val)
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
పూర్ణాంకం get_spi(పూర్ణాంకం* addr)
{
	తిరిగి *addr;
}

/** @fn void spi_init(void)
 * @brief setting up baud rate and clock pole and phase 
 * @details Initialize the spi controller in Mode 3 (CPOL =1 & CPHA =1) with SCK= clk/16
 */
శూన్య spi_init(శూన్య)
{
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_CPHA|SPI_CPOL));
}

/** @fn  void spi_tx_rx_start(void)
 * @brief to start receiving data as soon as transmit state is complete
 * @details While receiving data from flash (reading Device ID, status register and reading flash)  
 *           in master mode use this function.
 * @warning Should be set before configuring the control register 1.
 */
శూన్య spi_tx_rx_ప్రారంభం(శూన్య)
{
	సమితి_spi(spi_cr2, (SPI_RX_IMM_ప్రారంభం));
}


/** @fn void spi_rx_enable(void)
 * @brief to start receive state 
 * @details This is not in used when spi is in Master mode 
 */
శూన్య spi_rx_enable(శూన్య)
{
	సమితి_spi(spi_cr2, (SPI_RX_ప్రారంభం));
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
పూర్ణాంకం బిట్టు_Extracted(పూర్ణాంకం సంఖ్య, పూర్ణాంకం k, పూర్ణాంకం p)
{
	తిరిగి (((1 << k) - 1) & (సంఖ్య >> (p - 1)));
}

/**
 * @fn  int spi_rxne_enable(void)
 * @brief to check if receive buffer is empty or not
 * @details As soons as data come to receive buffer this bit is set.  
 * @return int (1: if there is data into the RxFIFO else 0)
 */
పూర్ణాంకం spi_rxne_enable(శూన్య)
{
	పూర్ణాంకం విలువ = 0;

	అయితే (!(విలువ & 0x1))
	{
		waitfor(100);
		విలువ = get_spi(spi_sr);
	}
	తిరిగి 1;
}

/**
 * @fn int spi_notbusy(void)
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning One should check this bit before going to next transcation
 * @return int (0: SPI is busy in communication, 1: SPI nt busy)
 */
పూర్ణాంకం spi_notbusy(శూన్య)
{
	పూర్ణాంకం విలువ = 0x80;

	అయితే ((విలువ & 0x80))
	{
		waitfor(10);
		విలువ = get_spi(spi_sr);
	}

	తిరిగి 1;
}

/**
 * @fn int flash_write_enable(void)
 * @brief to set the WEL (Write Enable Latch) bit in status register
 * @details Before modifying content of flash, one should enable the WEL bit first
 * @warning Without enabling this bit one cannot erase/write into the flash
 * @return int
 */
పూర్ణాంకం flash_write_enable(శూన్య)
{
	సమితి_spi(spi_dr1, 0x06000000);
	సమితి_spi(spi_dr5, 0x06);
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(8)|SPI_మొత్తం_బిట్లు_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	తిరిగి 1;
}

/**
 * @fn int flash_clear_sr(void)
 * @brief to reset the status register
 * @details It will reset the bits of status register
 * @return int
 */

పూర్ణాంకం flash_clear_sr(శూన్య)
{
	సమితి_spi(spi_dr1,0x30000000);
	సమితి_spi(spi_dr5,0x30);
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(8)|SPI_మొత్తం_బిట్లు_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	తిరిగి 1;
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
పూర్ణాంకం flash_cmd_addr(పూర్ణాంకం command, పూర్ణాంకం addr)
{
	పూర్ణాంకం address1 = బిట్టు_Extracted(addr, 24, 9);
	పూర్ణాంకం address2 = బిట్టు_Extracted(addr, 8, 1);
	పూర్ణాంకం data1 = command | address1 ;
	address2 = address2 << 24;

	సమితి_spi(spi_dr1, data1);
	సమితి_spi(spi_dr2, address2);
	సమితి_spi(spi_dr5, 0);
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(40)|SPI_మొత్తం_బిట్లు_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();

	తిరిగి 1;
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
శూన్య flash_cmd_addr_దత్తాంశం(పూర్ణాంకం command, పూర్ణాంకం addr, పూర్ణాంకం దత్తాంశం_2)
{
	పూర్ణాంకం cmd_addr = command | ( (addr & 0xFFFFFF00)  >> 8);
	పూర్ణాంకం data1 = ( (addr & 0xFF)  << 24 ) |( (దత్తాంశం_2 & 0xFFFFFF00)  >> 8);
	పూర్ణాంకం data2 = ( (దత్తాంశం_2 & 0xFF)  << 24 ) & 0xFF000000;

	log_debug("\n cmd: %x;d1: %x; d2: %x", cmd_addr, data1, data2);

	సమితి_spi(spi_dr1, cmd_addr);
	సమితి_spi(spi_dr2, data1);
	సమితి_spi(spi_dr3, data2);
	సమితి_spi(spi_dr5, 0);
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(72)|SPI_మొత్తం_బిట్లు_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();
	flash_స్థితి_రిజిస్టరు_read();
}

/**
 * @fn void flash_write(int address, int data)
 * @brief  Write 4bytes of data from given address
 * @details flash_cmd_addr_data with opcode 12h.  
 * @warning before writing into the flash one should enable the WEL bit spi_sr by using write_enable(void)
 * @param int (addres (write address))
 * @param int(data (write data))
 */
శూన్య flash_write(పూర్ణాంకం చిరునామా, పూర్ణాంకం దత్తాంశం_2)
{
	flash_write_enable();
	flash_cmd_addr_దత్తాంశం(0x12000000, చిరునామా,దత్తాంశం_2);
	flash_స్థితి_రిజిస్టరు_read();
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
పూర్ణాంకం flash_cmd_గమ్యం_read(పూర్ణాంకం command, పూర్ణాంకం addr)
{
	పూర్ణాంకం dr5;
	పూర్ణాంకం address2 = బిట్టు_Extracted(addr, 8, 1);

	address2 = address2 << 24;
	సమితి_spi(spi_dr1, ( command  | ( (addr & 0xFFFFFF00) >> 8) ));
	సమితి_spi(spi_dr2, ( (addr & 0xFF) << 24) );
	సమితి_spi(spi_dr5, 0);
	spi_tx_rx_ప్రారంభం();
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(48)|SPI_మొత్తం_బిట్లు_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(2000);

	ఒకవేళ(spi_rxne_enable()) 
	{
		dr5 = *spi_dr5;
	}

	తిరిగి dr5;

}

/** @fn int flash_read(int address)
 * @brief read the 4bytes data from given address 
 * @details flash_cmd_to_read with opcode 0Bh for fast read
 * @param int (address (read address))
 * @return int 
 */
పూర్ణాంకం flash_read(పూర్ణాంకం చిరునామా)
{
	పూర్ణాంకం read_విలువ = flash_cmd_గమ్యం_read(0x0C000000,చిరునామా);
	తిరిగి read_విలువ;
}

/**
 * @fn int flash_cmd_read(int command)
 * @brief usefull for reading status register
 * @details use for sending 8bit command and receive the 32bit of data
 * @param int command (opcode)
 * @return int  value (flash response to opcode)
 */
పూర్ణాంకం flash_cmd_read(పూర్ణాంకం command)
{
	పూర్ణాంకం dr5;
	సమితి_spi(spi_dr1, command);
	సమితి_spi(spi_dr5, command);
	spi_tx_rx_ప్రారంభం();
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(8)|SPI_మొత్తం_బిట్లు_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	ఒకవేళ(spi_rxne_enable()) {
		dr5 = *spi_dr5;
	}
	తిరిగి dr5;
}

/**
 * @fn  void flash_erase(int address)
 * @brief Erase the flash
 * @details Erase the 64kb sector from given address 
 * @warning before erasing the flash one should enable the WEL bit spi_sr by using write_enable()
 * @param int (address (address from which data should erase))
 */
శూన్య flash_erase(పూర్ణాంకం చిరునామా)
{
	flash_cmd_addr(0xdc000000, చిరునామా);
}

/**
 * @fn int flash_status_register_read(void)
 * @briefRead read status register of flash
 * @details  Using flash_cmd_read function with opcode 05h to check status of WIP(Write in progress)
 *           and WEL(Write Enable Latch) bit.
 * @return int
 */
పూర్ణాంకం flash_స్థితి_రిజిస్టరు_read(శూన్య)
{
	పూర్ణాంకం stat = 0x3;

	అయితే (stat & 0x03)
	{
		stat = flash_cmd_read(0x05000000);
		log_debug("flash status register val %x\n", stat);
	}

	తిరిగి 0;
}

/**
 * @fn int flash_device_id(void)
 * @briefto read Device ID and Mfg. ID of flash
 * @details Device ID is 1byte and Mfg. ID of flash is of 2byte. Hence 8bit of command and receiving 
 *          24 bits of data from flash
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @return int
 */
పూర్ణాంకం flash_device_id(శూన్య)
{
	పూర్ణాంకం dr3;
	పూర్ణాంకం val1, val2;

	flash_write_enable();
	సమితి_spi(spi_dr1, 0x9f000000);
	సమితి_spi(spi_dr5, 0x9f000000);
	spi_tx_rx_ప్రారంభం();
	సమితి_spi(spi_cr1, (SPI_BR(7)|SPI_మొత్తం_బిట్లు_TX(8)|SPI_మొత్తం_బిట్లు_RX(24)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	ఒకవేళ(spi_rxne_enable())
	{
		dr3 = *spi_dr5;
	}

	val1 = బిట్టు_Extracted(dr3, 8, 17);
	val2 = బిట్టు_Extracted(dr3, 16, 1);

	log_debug("Device ID %x \n", val1);
	log_debug("extracted device id %x \n",val2);

	తిరిగి 1;
}
