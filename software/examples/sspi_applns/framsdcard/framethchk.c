#include<stdlib.h>
#include<stdint.h>
#include "sspi.h"
#include "uart.h"
//#define PIN_MUX_DRIVER 1
//#include "pinmux.h"
#include "log.h"
#include "platform.h"
#include "gpio.h"

#include "integer.h"
#include "diskio.h"
#include "ff.h"
#include "eth_driver.h"
#include "poll_eg.h"

#define DELAY 100
#define TEST_CODE 1
//#define FULL_TEST 1

#define MANUFACTURER_ID 0x7F7F7F7F7F7FC2
#define DEVICE_ID 0x25C8


#define TOTAL_SIZE_BYTES (2*1024*1024 / 8)
#define TOTAL_SIZE_WORDS (TOTAL_SIZE_BYTES / (4 * 512))

#define WRITE_SIZE 128
//#define WRITE_SIZE 192

#define SSPI_INSTANCE 1

#define FRAM_WRITE_ENABLE 0x06
#define FRAM_WRITE_DISABLE 0x04
#define FRAM_READ_STATUS_REG 0x05
#define FRAM_WRITE_STATUS_REG 0x01
#define FRAM_READ_DATA 0x03
#define FRAM_FAST_READ_DATA 0x0B
#define FRAM_WRITE_DATA 0x02
#define FRAM_SLEEP 0xB9
#define FRAM_READ_DEVICE_ID 0x9F

#define FMOUNT		1
#define EMAC_DEVICE_ID			240


/** @fn void flash_init(void)
 * @brief setting up baud rate and clock pole and phase 
 * @details Initialize the spi controller in Mode 3 (CPOL =1 & CPHA =1) with SCK= clk/16
 */
void flash_init()
{
 	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], DISABLE);
	sspi_configure_clock_in_hz(sspi_instance[SSPI_INSTANCE], 1000000); /* Currently configuring for 100kHz, as the maximum clock is 20MHz */
	sspi_configure_clock_pol(sspi_instance[SSPI_INSTANCE], 0);
	sspi_configure_clock_phase(sspi_instance[SSPI_INSTANCE], 0);	
	sspi_configure_pins(sspi_instance[SSPI_INSTANCE], 1, 0 ,  1 , 1);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE], SPI_MASTER);
	sspi_configure_lsb_first(sspi_instance[SSPI_INSTANCE], MSB_FIRST);
//	sspi_configure_tx_setup_time(sspi_instance[SSPI_INSTANCE], 1);
//	sspi_configure_tx_hold_time(sspi_instance[SSPI_INSTANCE], 0);
	
}


/**
 * @fn int spi_notbusy(void)
 * @brief to check if spi is ready for next transaction or busy with previous one
 * @details it read the status of bsy bit in spi_sr 
 * @warning One should check this bit before going to next transcation
 * @return int (0: SPI is busy in communication, 1: SPI nt busy)
 */
int sspi_notbusy(void)
{
	unsigned char  read_data = 0x01;
	while(read_data & 0x01){
		waitfor(10);
		read_data = sspi_instance[SSPI_INSTANCE]->comm_status;
//		read_data = SSPI0->comm_status;
		log_debug("\n Status Register: %x", read_data);
	}
	log_debug("\n SPI comm done \n");
	return 1;
}




int flash_write_enable(void)
{
#if 0
	set_shakti8(tx,  0x06);
	set_shakti32(commctrl,(COMMCTRL_MOSI_OUTEN|COMMCTRL_SCLK_OUTEN|COMMCTRL_CS_OUTEN|COMMCTRL_TX_BITS(8)|COMMCTRL_RX_BITS(0)|COMMCTRL_COMM_MODE(SIMPLEX_TX)|COMMCTRL_SPI_EN|COMMCTRL_MASTER_MODE));
	sspi_notbusy();
#else
 	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],8,0);//Tx - 8, Rx - 0;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE], SIMPLEX_TX);
	sspi_instance[SSPI_INSTANCE]->data_tx = FRAM_WRITE_ENABLE;	//MSB byte of address.
 	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
 	sspi_notbusy();
	 log_debug("\n Flash write enabled");

#endif
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
void flash_cmd_addr_data(int command, int address, int data)
{

#if 0
	int cmd_addr = (command << 24) |  (addr & 0xFFFFFF)  ;
	log_debug("\n cmd_addr: %x; data: %x", cmd_addr, data);
	*tx = cmd_addr;
	*tx = data;
//	set_shakti32(tx,  cmd_addr);
//	set_shakti32(tx,  data);
	set_shakti32(commctrl,(COMMCTRL_MOSI_OUTEN|COMMCTRL_SCLK_OUTEN|COMMCTRL_CS_OUTEN|COMMCTRL_TX_BITS(64)|COMMCTRL_RX_BITS(0)|COMMCTRL_COMM_MODE(SIMPLEX_TX)|COMMCTRL_SPI_EN|COMMCTRL_MASTER_MODE));
	sspi_notbusy();
#else
	flash_write_enable();
	sspi_instance[SSPI_INSTANCE]->data_tx = command;	//Do not shift  command when passing as argument.
	sspi_instance[SSPI_INSTANCE]->data_tx = (address >> 16);	//2nd byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx = (address >> 8);	//3rd byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx = (address >> 0);	//4th byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 24);	//4th byte of data.
	sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 16);	//4th byte of data.
	sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 8);	//4th byte of data.
	sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 0);	//4th byte of data.
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE], 64, 0);//Tx - 64, Rx - 0;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE], SIMPLEX_TX);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);

#endif
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
	flash_cmd_addr_data(FRAM_WRITE_DATA, address, data); // Used to send opcode 
}

/**
 * @fn int flash_device_id(void)
 * @briefto read Device ID and Mfg. ID of flash
 * @details Device ID is 1byte and Mfg. ID of flash is of 2byte. Hence 8bit of command and receiving 
 *          24 bits of data from flash
 * @warning to move data from data register to fifo there must be some data into spi_dr5
 * @return int
 */
int flash_device_id(long int *manu_id, unsigned short *device_id)
{
	long int manu_id_lsb = 0, manu_id_msb = 0 ;
	int read_data[4] = {'\0'};
	long int val1, val2;
	printf("\n Reading Device ID");
	flash_write_enable();
#if 0
	set_shakti8(tx,  FRAM_READ_DEVICE_ID);
	set_shakti32(commctrl,(COMMCTRL_MOSI_OUTEN|COMMCTRL_SCLK_OUTEN|COMMCTRL_CS_OUTEN|COMMCTRL_TX_BITS(8)|COMMCTRL_RX_BITS(72)|COMMCTRL_COMM_MODE(HALF_DUPLEX)|COMMCTRL_SPI_EN|COMMCTRL_MASTER_MODE));
	sspi_notbusy();
#else
	sspi_instance[SSPI_INSTANCE]->data_tx = FRAM_READ_DEVICE_ID;		
	sspi_configure_tx_setup_time(sspi_instance[SSPI_INSTANCE],  0);
	sspi_configure_tx_hold_time(sspi_instance[SSPI_INSTANCE], 0);
#if 1
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE], 8, 72);//Tx - 8, Rx - 24;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE], HALF_DUPLEX);
#ifdef SHOW_REG
	sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
#endif	
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
	sspi_notbusy();
#endif
#endif

/*
	read_data[0] = get_shakti32(rx);
	read_data[1] = get_shakti32(rx);
	read_data[2] = get_shakti16(rx);
	read_data[3] = get_shakti8(rx);
	read_data[0] = (get_shakti8(rx) << 24) | (get_shakti8(rx) << 16) |(get_shakti8(rx) << 8) |(get_shakti8(rx) << 0);
	read_data[1] = (get_shakti8(rx) << 24) | (get_shakti8(rx) << 16) |(get_shakti8(rx) << 8) |(get_shakti8(rx) << 0);
	read_data[2] = (get_shakti8(rx) << 24);

	printf("\n readdata: [1]: %x; [2]: %x; [3]: %x; [4]: %x", read_data[0], read_data[1], read_data[2], read_data[3] );
*/

//	printf("\n B9: %x", get_shakti8(rx) );
#if 1
	read_data[0]  = (sspi_instance[SSPI_INSTANCE]->data_rx << 24) | (sspi_instance[SSPI_INSTANCE]->data_rx << 16) | \
	(sspi_instance[SSPI_INSTANCE]->data_rx << 8 ) | (sspi_instance[SSPI_INSTANCE]->data_rx );
	read_data[1]  = (sspi_instance[SSPI_INSTANCE]->data_rx << 24) | (sspi_instance[SSPI_INSTANCE]->data_rx << 16) | \
	(sspi_instance[SSPI_INSTANCE]->data_rx << 8 ) | (sspi_instance[SSPI_INSTANCE]->data_rx );

	read_data[2]  = (sspi_instance[SSPI_INSTANCE]->data_rx );


	printf("\n readdata: [1]: %x; [2]: %x; [3]: %x; ", read_data[0], read_data[1], read_data[2] );
//	manu_id_msb = (long int) read_data[0];
//	manu_id_msb <<= 32;
//	manu_id_msb = (long int) (read_data[0] << 32);
//	printf("\n manu id msb: %lx", manu_id_msb);
//	manu_id_lsb |= (long int) read_data[1] ;
//	printf("\n manu id lsb: %lx", manu_id_lsb);
//	manu_id_lsb |= read_data[2];
//	printf("\n manu id lsb: %lx", manu_id_lsb);
//	*manu_id = ((manu_id_msb >> 8 ) & 0xffffffffffffff) ;
//	*device_id =  ( (manu_id_lsb & 0xFF) << 8 ) | read_data[2];
	*manu_id = (long int ) ( (read_data[0] << 24) | ( (read_data[1] >> 8) & 0xFFFFFF) );
	*device_id = ( (read_data[1] << 8) & 0xFF00) | read_data[2];
	log_debug("Device ID %x \n", *device_id);
	log_debug("Manufacture id %lx \n",*manu_id);
	printf("Device ID %x \n", *device_id);
	printf("Manufacture id %lx \n",*manu_id);
#if 0
	if( ( MANUFACTURER_ID == *manu_id) && (DEVICE_ID == *device_id) )
	{
		log_info("\n SPI_RAM Device found. ");
		return 1;
		}
	else
	{
		log_error("Error in device id. Read deviceid: %x; Manu. ID: %lx", *device_id, *manu_id);
		return 0;
	}
#endif	
#endif
		return 1;
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
int flash_cmd_to_read(int command, int address)
{
	int read_data = 0;
#if 0	
	int cmd_addr = (command << 24) |  (addr & 0xFFFFFF)  ;
	log_debug("\n cmd_addr: %x", cmd_addr);
	set_shakti32(tx,  cmd_addr);
	if(FRAM_FAST_READ_DATA == command)
	{
		set_shakti8(tx,  0x0);
	set_shakti32(commctrl,(COMMCTRL_MOSI_OUTEN|COMMCTRL_SCLK_OUTEN|COMMCTRL_CS_OUTEN|COMMCTRL_TX_BITS(40)|COMMCTRL_RX_BITS(32)|COMMCTRL_COMM_MODE(HALF_DUPLEX)|COMMCTRL_SPI_EN|COMMCTRL_MASTER_MODE));
	}
	else if (FRAM_READ_DATA == command)
	set_shakti32(commctrl,(COMMCTRL_MOSI_OUTEN|COMMCTRL_SCLK_OUTEN|COMMCTRL_CS_OUTEN|COMMCTRL_TX_BITS(32)|COMMCTRL_RX_BITS(32)|COMMCTRL_COMM_MODE(HALF_DUPLEX)|COMMCTRL_SPI_EN|COMMCTRL_MASTER_MODE));
	
	sspi_notbusy();
	read_data = get_shakti32(rx);

#else
	sspi_instance[SSPI_INSTANCE]->data_tx =command;	//Do not shift  command when passing as argument.
	sspi_instance[SSPI_INSTANCE]->data_tx =(address >> 16);	//3nd byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx =(address >> 8);	//2rd byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx =(address >> 0);	//1th byte of address.
	sspi_instance[SSPI_INSTANCE]->data_tx = 0xFF;	//Dummy byte.
	if(FRAM_FAST_READ_DATA == command)
	{
		sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE], 40, 32);//Tx - 48, Rx - 32;
	}
	else
	{
		sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE], 32, 32);//Tx - 48, Rx - 32;
	}
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE], HALF_DUPLEX);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);

	sspi_notbusy();
	read_data = (sspi_instance[SSPI_INSTANCE]->data_rx << 24 ) | (sspi_instance[SSPI_INSTANCE]->data_rx << 16 ) | \
				(sspi_instance[SSPI_INSTANCE]->data_rx << 8 ) | (sspi_instance[SSPI_INSTANCE]->data_rx << 0 );
#endif
#ifdef SD_WRITE_DEBUG
printf("\n READ DATA=%x  ",read_data);
#endif

	return read_data;
}
/** @fn int flash_read(int address)
 * @brief read the 4bytes data from given address 
 * @details flash_cmd_to_read with opcode 0Bh for fast read
 * @param int (address (read address))
 * @return int 
 */
int flash_read(int address)
{
	int read_value = flash_cmd_to_read(FRAM_FAST_READ_DATA, address);
	return read_value;
}


void read_fram_locations(uint8_t *buf_data, uint32_t read_address, uint32_t size)
{
	#ifdef SD_WRITE_DEBUG
	printf("read fram_locations");
	#endif
	
	uint32_t temp_data = 0;
	int i, j;
			for(i = 0; i < size; i++)
			{
				temp_data = flash_read(read_address);	
				*buf_data++ = (temp_data >> 24 ) & 0xFF;
				*buf_data++ = (temp_data >> 16 ) & 0xFF;
				*buf_data++ = (temp_data >> 8 ) & 0xFF;
				*buf_data++ = (temp_data >> 0 ) & 0xFF;

				read_address += 0x00000004; //Not sure
			}

}


