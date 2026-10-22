/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  spi_driver.c
* Brief Description of file             :  driver file for SPI based flash W25Q32
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
@file spi_flash_w25q32.c
@brief Does basic flash operatons . 
@detail Configures SPI, flash device and then do all basic flash oerations.* 
*/
#ಅನ್ತರ್ಭಾವ "spi.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
ಪೂರ್ಣಾಂಕ* spi_cr1    = (ಪೂರ್ಣಾಂಕ*) SPI_CR1;
ಪೂರ್ಣಾಂಕ* spi_cr2    = (ಪೂರ್ಣಾಂಕ*) SPI_CR2;
ಪೂರ್ಣಾಂಕ* spi_sr     = (ಪೂರ್ಣಾಂಕ*) SPI_SR ;
ಪೂರ್ಣಾಂಕ* spi_dr1    = (ಪೂರ್ಣಾಂಕ*) SPI_DR1 ;
ಪೂರ್ಣಾಂಕ* spi_dr2    = (ಪೂರ್ಣಾಂಕ*) SPI_DR2 ;
ಪೂರ್ಣಾಂಕ* spi_dr3    = (ಪೂರ್ಣಾಂಕ*) SPI_DR3 ;
ಪೂರ್ಣಾಂಕ* spi_dr4    = (ಪೂರ್ಣಾಂಕ*) SPI_DR4 ;
ಪೂರ್ಣಾಂಕ* spi_dr5    = (ಪೂರ್ಣಾಂಕ*) SPI_DR5 ;
ಪೂರ್ಣಾಂಕ* spi_crcpr  = (ಪೂರ್ಣಾಂಕ*) SPI_CRCPR;
ಪೂರ್ಣಾಂಕ* spi_rxcrcr = (ಪೂರ್ಣಾಂಕ*) SPI_RXCRCR;
ಪೂರ್ಣಾಂಕ* spi_txcrcr = (ಪೂರ್ಣಾಂಕ*) SPI_TXCRCR; 


//By default, spi 0 is configured
/**
 * @fn void configure_spi(int offset)
 * @brief assigns memory mapped addres value to SPI registers.
 * @details Takes the SPI Base address and then adds offset to each and every
 *          spi registers..
 * @param int* ---> offset value 
 */
ಶೂನ್ಯ configure_spi(ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ)	
{
	spi_cr1    = (ಪೂರ್ಣಾಂಕ*) (SPI_CR1 + ಸ್ಥಾನಾಂತರ);
	spi_cr2    = (ಪೂರ್ಣಾಂಕ*) (SPI_CR2 + ಸ್ಥಾನಾಂತರ);
	spi_sr     = (ಪೂರ್ಣಾಂಕ*) (SPI_SR + ಸ್ಥಾನಾಂತರ);
	spi_dr1    = (ಪೂರ್ಣಾಂಕ*) (SPI_DR1 + ಸ್ಥಾನಾಂತರ);
	spi_dr2    = (ಪೂರ್ಣಾಂಕ*) (SPI_DR2 + ಸ್ಥಾನಾಂತರ);
	spi_dr3    = (ಪೂರ್ಣಾಂಕ*) (SPI_DR3 + ಸ್ಥಾನಾಂತರ);
	spi_dr4    = (ಪೂರ್ಣಾಂಕ*) (SPI_DR4 + ಸ್ಥಾನಾಂತರ);
	spi_dr5    = (ಪೂರ್ಣಾಂಕ*) (SPI_DR5 + ಸ್ಥಾನಾಂತರ);
	spi_crcpr  = (ಪೂರ್ಣಾಂಕ*) (SPI_CRCPR + ಸ್ಥಾನಾಂತರ);
	spi_rxcrcr = (ಪೂರ್ಣಾಂಕ*) (SPI_RXCRCR + ಸ್ಥಾನಾಂತರ);
	spi_txcrcr = (ಪೂರ್ಣಾಂಕ*) (SPI_TXCRCR + ಸ್ಥಾನಾಂತರ); 
}

/**
 * @fn void set_spi(int* addr, int val)
 * @brief to assign value to memory mapped spi register
 * @details writes the given value to given addres (SPI).
 * @param int* addr
 * @param int val
 */
ಶೂನ್ಯ ಗಣ_spi(ಪೂರ್ಣಾಂಕ* addr, ಪೂರ್ಣಾಂಕ val)
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
ಪೂರ್ಣಾಂಕ get_spi(ಪೂರ್ಣಾಂಕ* addr)
{
	ಹಿಂತಿರುಗಿ *addr;
}

/** @fn void spi_init()
 * @brief setting up baud rate and clock pole and phase 
 * @details Initialize the spi controller in Mode 3 (CPOL =1 & CPHA =1) with SCK= clk/16;
 */
ಶೂನ್ಯ spi_init()
{
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_CPHA|SPI_CPOL));
}

/** @fn void spi_tx_rx_start()
 * @brief to start receiving data as soon as transmit state is complete
 * @details While receiving data from flash (reading Device ID, status register and reading flash)   
 *           in master mode use this function.
 * @warning Should be set before configuring the control register 1.
 */
ಶೂನ್ಯ spi_tx_rx_ಆರಂಭ()
{
	ಗಣ_spi(spi_cr2, (SPI_RX_IMM_ಆರಂಭ));
}


/** @fn void spi_rx_enable()
 * @brief to start receive state 
 * @details This is not in used when spi is in Master mode 
 */
ಶೂನ್ಯ spi_rx_enable()
{
	ಗಣ_spi(spi_cr2, (SPI_RX_ಆರಂಭ));
}

/**
 * @fn int bitExtracted(int number, int k, int p) 
 * @brief Extract the k number of bit from (p-1) position of 'number'
 * @details If one want to extract the k bits from (p-1) position in 32 bit "number".   
 * @param int (number (32 bit)), int (k (number of bits to be extracted)), 
 * @param int (p (position from where the bits to be extracted))
 * @return int (32 bit which have k bit from "number" and rest are zero)
 */
ಪೂರ್ಣಾಂಕ ಬಿಟ್_Extracted(ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ k, ಪೂರ್ಣಾಂಕ p) 
{
	ಹಿಂತಿರುಗಿ (((1 << k) - 1) & (ಸಂಖ್ಯೆ >> (p - 1))); 
}

/**
 * @fn int spi_rxne_enable()
 * @brief to check if receive buffer is empty or not
 * @details As soons as data come to receive buffer this bit is set.  
 * @return int (1: if there is data into the RxFIFO else 0)
 */
ಪೂರ್ಣಾಂಕ spi_rxne_enable()
{
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 0;

	ಆಗ (!(ಮೌಲ್ಯ & 0x1))
	{
		waitfor(100);
		ಮೌಲ್ಯ = get_spi(spi_sr);
	}
	ಹಿಂತಿರುಗಿ 1;
}

/**
 * @fn int spi_notbusy()
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning One should check this bit before going to next transcation
 * @return int (0: SPI is busy in communication, 1: SPI nt busy)
 */
ಪೂರ್ಣಾಂಕ spi_notbusy()
{
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 0x80;

	ಆಗ ((ಮೌಲ್ಯ & 0x80))
	{
		waitfor(10);
		ಮೌಲ್ಯ = get_spi(spi_sr);
	}

	ಹಿಂತಿರುಗಿ 1;
}

/**
 * @fn int flash_write_enable()
 * @brief to set the WEL (Write Enable Latch) bit in status register
 * @details Before modifying content of flash, one should enable the WEL bit first
 * @warning Without enabling this bit one cannot erase/write into the flash
 * @return int
 */
ಪೂರ್ಣಾಂಕ flash_write_enable()
{
	ಗಣ_spi(spi_dr1, 0x06000000);
	ಗಣ_spi(spi_dr5, 0x06);
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(8)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();
	ಹಿಂತಿರುಗಿ 1;
}

/**
 * @fn int flash_clear_sr()
 * @brief to reset the status register
 * @details It will reset the bits of status register
 * @return int
 */
ಪೂರ್ಣಾಂಕ flash_clear_sr()
{
	ಗಣ_spi(spi_dr1,0x30000000);
	ಗಣ_spi(spi_dr5,0x30);
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(8)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();
	ಹಿಂತಿರುಗಿ 1;
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
ಪೂರ್ಣಾಂಕ flash_cmd_addr(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr)
{
	ಬರೆ("Erase dr1 \n");
	ಗಣ_spi(spi_dr1, ((command << 24) | (addr) ) );
	ಗಣ_spi(spi_dr5, 0);
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(32)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();
	ಹಿಂತಿರುಗಿ 1;
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
ಶೂನ್ಯ flash_cmd_addr_ದತ್ತಾಂಶ(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_2)
{
#ಆದರೆ 0
	ಪೂರ್ಣಾಂಕ address1 = ಬಿಟ್_Extracted(addr, 24, 9);
	ಪೂರ್ಣಾಂಕ address2 = ಬಿಟ್_Extracted(addr, 8, 1);
	ಪೂರ್ಣಾಂಕ cmd_addr = command  | address1;
	address2 = address2 << 24;
	ಪೂರ್ಣಾಂಕ data1 = ಬಿಟ್_Extracted(ದತ್ತಾಂಶ_2, 24, 9);
	data1 = address2 | data1;
	ಪೂರ್ಣಾಂಕ data2 = ಬಿಟ್_Extracted(ದತ್ತಾಂಶ_2, 8, 1);
	data2 = data2 << 24;
	ಗಣ_spi(spi_dr1, cmd_addr);
	ಗಣ_spi(spi_dr2, data1);
	ಗಣ_spi(spi_dr3, data2);
	ಗಣ_spi(spi_dr5, 0);
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(40)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();
#ಇಲ್ಲದಿದ್ದರೆ
	ಗಣ_spi(spi_dr1,  ( (command << 24) | (addr) ) );
//	printf("\n Write Command: %x; Data: %x",  ((command << 24) | (addr) ), data );

	ಗಣ_spi(spi_dr2, ದತ್ತಾಂಶ_2);
//	set_spi(spi_dr3, data2);
	ಗಣ_spi(spi_dr5, 0);
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(64)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();

#ಆದರೆ_ಅಂತ್ಯ
}

/**
 * @fn void flash_write(int address, int data)
 * @brief  Write 4bytes of data from given address
 * @details flash_cmd_addr_data with opcode 12h.  
 * @warning before writing into the flash one should enable the WEL bit spi_sr by using write_enable()
 * @param int (addres (write address))
 * @param int(data (write data))
 */
ಶೂನ್ಯ flash_write(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_2)
{
	flash_cmd_addr_ದತ್ತಾಂಶ(0x02, ವಿಳಾಸ,ದತ್ತಾಂಶ_2);
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
ಪೂರ್ಣಾಂಕ flash_cmd_ಗಮ್ಯ_read(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr)
{

	ಪೂರ್ಣಾಂಕ dr5;
//	int address1 = bitExtracted(addr, 24, 9);
//    int address2 = bitExtracted(addr, 8, 1);
//	int cmd_addr = command  | address1;
//	int address2 = address2 << 24;
//	printf("\n Read Command: %x",  ( (command << 24) | (addr) ) );
	ಗಣ_spi(spi_dr1,  ( (command << 24) | (addr) ) );
//	set_spi(spi_dr2, address2);
	ಗಣ_spi(spi_dr5, 0);
	spi_tx_rx_ಆರಂಭ();
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(40)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	 
	ಆದರೆ(spi_rxne_enable()) 
	{
		dr5 = *spi_dr5;
	}
   // printf("Reading from dr5 %x \n", dr5);
	ಹಿಂತಿರುಗಿ dr5;

}

/** @fn int flash_read(int address)
 * @brief read the 4bytes data from given address 
 * @details flash_cmd_to_read with opcode 0Bh for fast read
 * @param int (address (read address))
 * @return int 
 */
ಪೂರ್ಣಾಂಕ flash_read(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ)
{
	ಪೂರ್ಣಾಂಕ read_ಮೌಲ್ಯ = flash_cmd_ಗಮ್ಯ_read(0x0B,ವಿಳಾಸ);
	
	ಹಿಂತಿರುಗಿ read_ಮೌಲ್ಯ;
}

/**
 * @fn int flash_cmd_read(int command)
 * @brief usefull for reading status register
 * @details use for sending 8bit command and receive the 32bit of data
 * @param int command (opcode)
 * @return int  value (flash response to opcode)
 */
ಪೂರ್ಣಾಂಕ flash_cmd_read(ಪೂರ್ಣಾಂಕ command)
{
	ಪೂರ್ಣಾಂಕ dr1, dr2, dr5;
	ಗಣ_spi(spi_dr1, command);
	ಗಣ_spi(spi_dr5, command);
	spi_tx_rx_ಆರಂಭ();
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(8)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	ಆದರೆ(spi_rxne_enable()) {
		dr5 = *spi_dr5;
		}
	
	ಹಿಂತಿರುಗಿ dr5;
}

/**
 * @fn void flash_erase(int address)
 * @brief Erase the flash
 * @details Erase the 64kb sector from given address 
 * @warning before erasing the flash one should enable the WEL bit spi_sr by using write_enable()
 * @param int (address (address from which data should erase))
 */
ಶೂನ್ಯ flash_erase(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ)
{
	ಬರೆ("Cypress erase \n");
	flash_cmd_addr(0xD8, ವಿಳಾಸ);
	ಬರೆ("Cypress erase done\n");
}

/**
 * @fn int flash_status_register_read()
 * @briefRead read status register of flash
 * @details  Using flash_cmd_read function with opcode 05h to check status of WIP(Write in progress) 
 *           and WEL(Write Enable Latch) bit.
 * @return int
 */
ಪೂರ್ಣಾಂಕ flash_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್_read()
{
	ಪೂರ್ಣಾಂಕ stat = 0x3;

	ಆಗ (stat & 0x03)
	{
		stat = flash_cmd_read(0x05000000);
		//printf("flash status register val %x\n", stat);
	}

	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn flash_device_id
 * @briefto read Device ID and Mfg. ID of flash
 * @details Device ID is 1byte and Mfg. ID of flash is of 2byte. Hence 8bit of command and receiving 
 *          24 bits of data from flash
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @return int
 */
ಪೂರ್ಣಾಂಕ flash_device_id()
{
	ಪೂರ್ಣಾಂಕ dr1, dr2, dr3;
	ಪೂರ್ಣಾಂಕ val1, val2;
	flash_write_enable();
	ಗಣ_spi(spi_dr1, 0x9F000000);
	ಗಣ_spi(spi_dr5, 0x9F000000);
	spi_tx_rx_ಆರಂಭ();
	ಗಣ_spi(spi_cr1, (SPI_BR(7)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(8)|SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(24)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	ಆದರೆ(spi_rxne_enable())
	{
		dr3 = *spi_dr5;
		dr2 = *spi_dr2;
	}

	val1 = ಬಿಟ್_Extracted(dr3, 8, 17);
	val2 = ಬಿಟ್_Extracted(dr3, 16, 1);

	ಬರೆ("Device ID %x \n", val1);
	ಬರೆ("extracted device id %x \n",val2);

	ಹಿಂತಿರುಗಿ 1;	
}

