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
#include "flashdata.h"
#define SECTOR_SIZE 0x4000

#define CODE_SIZE   131072
#define SPI_CR1     0x00020000
#define SPI_CR2     0x00020004
#define SPI_SR      0x00020008
#define SPI_DR1     0x0002000C
#define SPI_DR2     0x00020010
#define SPI_DR3     0x00020014
#define SPI_DR4	    0x00020018
#define SPI_DR5	    0x0002001C
#define SPI_CRCPR   0x00020020
#define SPI_RXCRCR  0x00020024
#define SPI_TXCRCR  0x00020028

// defining SPI_CR1 register

#define SPI_CPHA		(1 << 0)
#define SPI_CPOL		(1 << 1)
#define SPI_MSTR		(1 << 2)
#define SPI_BR(x)		(x << 3)
#define SPI_SPE  		(1 << 6)
#define SPI_LSBFIRST		(1 << 7)
#define SPI_SSI 		(1 << 8)
#define SPI_SSM			(1 << 9)
#define SPI_RXONLY		(1 << 10)
#define SPI_CRCL		(1 << 11)
#define SPI_CCRCNEXT		(1 << 12)
#define SPI_CRCEN		(1 << 13)
#define SPI_BIDIOE		(1 << 14)
#define SPI_BIDIMODE		(1 << 15)
#define SPI_TOTAL_BITS_TX(x)  	(x << 16)
#define SPI_TOTAL_BITS_RX(x)  	(x << 24)

// defining SPI_CR2 register

#define SPI_RX_IMM_START (1 << 16)
#define SPI_RX_START	 (1 << 15)
#define SPI_LDMA_TX      (1 << 14)
#define SPI_LDMA_RX 	 (1 << 13)
#define SPI_FRXTH	 (1 << 12)
#define SPI_DS(x)	 (x << 8)
#define SPI_TXEIE	 (1 << 7)
#define SPI_RXNEIE	 (1 << 6)
#define SPI_ERRIE	 (1 << 5)
#define SPI_FRF		 (1 << 4)
#define SPI_NSSP	 (1 << 3)
#define SPI_SSOE	 (1 << 2)
#define SPI_TXDMAEN	 (1 << 1)
#define SPI_RXDMAEN	 (1 << 0)

//defining SR register

#define SPI_FTLVL(x)  (x << 11)
#define SPI_FRLVL(x)  (x << 9)
#define SPI_FRE	      (1 << 8)
#define SPI_OVR	      (1 << 6)
#define SPI_MODF      (1 << 5)
#define SPI_CRCERR    (1 << 4)
#define TXE	      (1 << 1)
#define RXNE	      (1 << 0)


//Flash operations
#define READ_STATUS_COMMAND 0X05
#define READ_FLAG_STATUS_COMMAND 0x70
#define READ_LOCK_STATUS_COMMAND 0xe8
#define READ_NONVOLATILE_STATUS_COMMAND 0xB5


#define ERASE_SUCCESS_BIT (1 << 5) //Needs to be cleared when erase is success. 1 indicates failure.
#define PROGRAM_SUCCESS_BIT (1 << 4)
#define PROGRAM_WRITE_SUCCESS_BIT (1 << 7)


//pointers to register

int* spi_cr1 = (int*) SPI_CR1;
int* spi_cr2 = (int*) SPI_CR2;
int* spi_sr  = (int*) SPI_SR ;
int* spi_dr1 = (int*) SPI_DR1 ;
int* spi_dr2 = (int*) SPI_DR2 ;
int* spi_dr3  = (int*) SPI_DR3 ;
int* spi_dr4  = (int*) SPI_DR4 ;
int* spi_dr5 = (int*) SPI_DR5 ;
//int* spi_crcpr  = (int*) SPI_CRCPR;
//int* spi_rxcrcr = (int*) SPI_RXCRCR;
//int* spi_txcrcr = (int*) SPI_TXCRCR; 

/**
 * @fn int bitExtracted(int number, int k, int p)
 * @brief Extract the k number of bit from (p-1) position of 'number'
 * @details If one want to extract the k bits from (p-1) position in 32 bit "number".   
 * @param int (number (32 bit))
 * @param int (k (number of bits to be extracted))
 * @param int (p (position from where the bits to be extracted))
 * @return int (32 bit which have k bit from "number" and rest are zero)
 */
int bitExtracted(int number, int k, int p)
{
	return (((1 << k) - 1) & (number >> (p - 1)));
}


void set_spi(int* addr, int val)
{
	*addr = val;
}

int get_spi(int* addr)
{
	return *addr;
}

void spi_init(){
	set_spi(spi_cr1, (SPI_BR(7)|SPI_CPHA|SPI_CPOL));
}

void spi_tx_rx_start(){
	set_spi(spi_cr2, (SPI_RX_IMM_START));
}

void spi_enable(){
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(4)|SPI_TOTAL_BITS_RX(16)|SPI_SPE));
}

void spi_rx_enable(){
	set_spi(spi_cr2, (SPI_RX_START));
}

int spi_rxne_enable(){
	int value = 0;
	int count = 0;

	while (!(value & 0x1))
{
		waitfor(100);
		value = get_spi(spi_sr);
		if(count++ > 100)
			return -1;
	}

	return 1;
}

/**
 * @fn int spi_notbusy(void)
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning One should check this bit before going to next transcation
 * @return int (0: SPI is busy in communication, 1: SPI nt busy)
 */
int spi_notbusy(void)
{
	int value = 0x80;

	while ((value & 0x80))
	{
		waitfor(10);
		value = get_spi(spi_sr);
	}

	return 1;
}

/**
 * @fn int flash_write_enable(void)
 * @brief to set the WEL (Write Enable Latch) bit in status register
 * @details Before modifying content of flash, one should enable the WEL bit first
 * @warning Without enabling this bit one cannot erase/write into the flash
 * @return int
 */
int flash_write_enable(void)
{
	set_spi(spi_dr1, 0x06000000);
	set_spi(spi_dr5, 0x06);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	spi_notbusy();

	return 1;
}


void waitfor(unsigned int secs) {

	unsigned int time = 0;

	while(time++ < secs);
}

int flash_cmd_to_read(int command, int addr)
{
	int dr5;

//	set_spi(spi_dr1, command  |  (addr >> 8));
//	set_spi(spi_dr2, addr << 24);
	set_spi(spi_dr1, command  |  (addr & 0xFFFFFF));
	set_spi(spi_dr5, 0);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(32)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);

	if(spi_rxne_enable()) {
		dr5 = *spi_dr5;
	}
	return dr5;

}

int flash_read(int address)
{
	int read_value = flash_cmd_to_read(0x03000000, address);

	return read_value;
}

int flash_cmd_read(int command)
{
	int dr1, dr2, dr5;
	set_spi(spi_dr1, command);
	set_spi(spi_dr5, command);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	if(spi_rxne_enable()) {
		dr5 = *spi_dr5;
		dr2 = *spi_dr2;
	}
	return dr5 & 0xFFFF;
}

int flash_status_register_read()
{
	int stat = 0x3;
#if 0
		stat = flash_cmd_read(READ_NONVOLATILE_STATUS_COMMAND << 24);
		printf("\n READ_NONVOLATILE_STATUS_COMMAND Status: %x", stat);
		stat = flash_cmd_read(READ_LOCK_STATUS_COMMAND << 24);
		printf("\n READ_LOCK_STATUS_COMMAND Status: %x", stat);
		stat = flash_cmd_read(READ_STATUS_COMMAND << 24);
		printf("\n Flash Status: %x", stat);
#endif
		stat = flash_cmd_read(READ_FLAG_STATUS_COMMAND << 24);
//		printf("\n READ_FLAG_STATUS_COMMAND Status: %x", stat);


//	while (stat & 0x03){
	while (!(stat & 0x80) ){
//		stat = flash_cmd_read(READ_STATUS_COMMAND << 24);
		stat = flash_cmd_read(READ_FLAG_STATUS_COMMAND << 24);
//		printf("\n Flash Status: %x", stat);
	}

	return 0;
}


int flash_device_id()
{
	int dr1, dr2, dr3;
	int val1, val2;

	set_spi(spi_dr1, 0x9f000000);
	set_spi(spi_dr5, 0x9f000000);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(24)|SPI_SPE|SPI_CPHA|SPI_CPOL));

	if(1 == spi_rxne_enable()) {
		dr3 = *spi_dr5;
		dr2 = *spi_dr2;
	}
	else
	{
		return -1;
	}

	val1 = ( dr3 >> 16 ) & 0xff; //bitExtracted(dr3, 8, 17);
	val2 = dr3 & 0xffff; //bitExtracted(dr3, 16, 1);

 	printf("Device ID %x \n", val1);
 	printf("extracted device id %x \n",val2); 

	return 1;	
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
int flash_cmd_addr(int command, int addr)
{
#if 0
	int address1 = bitExtracted(addr, 24, 9);
	int address2 = bitExtracted(addr, 8, 1);
	int data1 = command | address1 ;
	address2 = address2 << 24;

	set_spi(spi_dr1, data1);
	set_spi(spi_dr2, address2);
#else
	set_spi(spi_dr1, command | (addr & 0xFFFFFF));
//	set_spi(spi_dr2, address2);
#endif
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(32)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);
	spi_notbusy();

	return 1;
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
void flash_cmd_addr_data(int command, int addr, int data)
{
#if 0
	int cmd_addr = command | ( (addr & 0xFFFFFF00)  >> 8);
	int data1 = ( (addr & 0xFF)  << 24 ) |( (data & 0xFFFFFF00)  >> 8);
	int data2 = ( (data & 0xFF)  << 24 ) & 0xFF000000;

//	printf("\n cmd: %x;d1: %x; d2: %x", cmd_addr, data1, data2);

	set_spi(spi_dr1, cmd_addr);
	set_spi(spi_dr2, data1);
	set_spi(spi_dr3, data2);
#endif
	set_spi(spi_dr1, command | (addr & 0xFFFFFF));
	set_spi(spi_dr2, data);
//	set_spi(spi_dr3, data2);
	set_spi(spi_dr5, 0);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(64)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
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
void flash_write(int address, int data)
{
	flash_write_enable();
	flash_cmd_addr_data(0x02000000, address,data);
	flash_status_register_read();
}

/**
 * @fn  void flash_erase(int address)
 * @brief Erase the flash
 * @details Erase the 64kb sector from given address 
 * @warning before erasing the flash one should enable the WEL bit spi_sr by using write_enable()
 * @param int (address (address from which data should erase))
 */
void flash_erase(int address)
{
	flash_cmd_addr(0xd8000000, address);
}




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

	spi_init();
	flash_device_id();

	waitfor(200);
	printf("\nErasing...\n");

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
	printf("\nErase complete.\n");
	read_address = 0x00b00000;
	printf("\nVerifying...");
	for( i = 0; i < write_data[0]; i++)
	{
		waitfor(200);
		read_value = flash_read(read_address);
//			printf("\n Read value: %x; Write value: %x; offset: %x", read_value, 0xFFFFFFFF, i);
#if 1
		if(read_value != 0xFFFFFFFF)
		{
//			printf("\n Error in verifying");
			printf("\n Read value: %x; Write value: %x; offset: %x", read_value, 0xFFFFFFFF, i);
//			break;
		}
#endif		
		read_address+=4;

		if(i % 2048 == 0)
			printf("+");;
	}
	printf("\n Erase Complete");
	read_address = 0x00b00000;
	flash_write(read_address,write_data[0]);
	read_address+=4;
		printf("\nWriting...");

	for( i = 0; i < write_data[0]; i++)
	{
//		printf("\n read address: %x", read_address);
		waitfor(200);
		flash_write(read_address,write_data[i+1]);
		read_address+=4;

		if(i % 2048 == 0)
			printf(".");;
		
	}

	printf("\n\nWrite complete.\n");
#if 1
	read_address = 0x00b00000;
	printf("\nVerifying...");
	for( i = 0; i < write_data[0]; i++)
	{
		waitfor(200);
		read_value = flash_read(read_address);
//			printf("\n Read value: %x; Write value: %x; offset: %x", read_value, write_data[i], i);
#if 1
		if(read_value != write_data[i])
		{
			printf("\n Error in verifying");
			printf("\n Read value: %x; Write value: %x; offset: %x", read_value, write_data[i], i);
			break;
		}
#endif		
		read_address+=4;

		if(i % 2048 == 0)
			printf("*");;
	}
#endif
	printf("\nPlease reset.\n");
//////	asm volatile ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function
 */
void main(){
	deploy();
	while(1);
}

