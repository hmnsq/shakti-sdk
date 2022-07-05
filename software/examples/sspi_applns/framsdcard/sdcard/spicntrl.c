/*===============================================================================
 Name        : SPI0M_SPI1S.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <stdio.h>
// #include "LPC8xx.h"
// #include "swm.h"
// #include "syscon.h"
// #include "utilities.h"
// #include "board.h"
#include "platform.h"
#include "sspi.h" //SSPI Driver header file
#include "integer.h"
#include "diskio.h"
#include "ff.h"
#include "clint_driver.h"
uint64_t tickvalue = ( CLOCK_FREQUENCY / CLINT_DIVISOR );

//--------SHAKTI PORT
//#include "pinmux.h"
// #include "gpio_spi.h"
#include "gpio.h"

//#define PINMUX_CONF_REG 0x41510
#define IISU 1  //USing the iisu spi drivers. 

//-----selected sspi for transfer----
#define SSPI_INSTANCE 2

// macros for debugging purpose
//#define SD_WRITE 1
//#define SD_WRITE_DEBUG 1
// #define SD_DEBUG 1 

//#define SPIBAUD_LOW 200000
//#define SPIBAUD_HIGH 10000000
// #define SPIBAUD_HIGH 2500000
//#define DEBUG


#define	MMC_CD		(!(FIO2PIN1 & _BV(1)))	/* Card detect (yes:true, no:false, default:true) */
#define	MMC_WP		0						/* Write protected (yes:true, no:false, default:false) */


/* MMC/SD command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define	CMD48	(48)		/* READ_EXTR_SINGLE */
#define	CMD49	(49)		/* WRITE_EXTR_SINGLE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

//SHAKTI SPI Macros 
#define SPI_DEFAULT (SPI_MSTR | SPI_SPE | SPI_BR(7))
#define SPI_CS_GPIO GPIO6

//multi byte transfer  macros
# define TX_MULBYTE_LEN 24
# define RX_MULBYTE_LEN 24
// # define TX_MULBYTE_LEN 16
// # define RX_MULBYTE_LEN 16

//write attempt count
#define SD_MAX_WRITE_ATTEMPTS   3907

static volatile DSTATUS Stat = STA_NOINIT;	/* Physical drive status */
static volatile UINT Timer1, Timer2;	/* 1kHz decrement timer stopped at zero (disk_timerproc()) */
static BYTE CardType;			/* Card type flags */
extern FATFS FatFs;	/* FatFs work area needed for each volume */
extern FIL Fil;		/* File object needed for each open file */
volatile enum {false=0, true=1} master_handshake, slave_handshake;
volatile unsigned char master_rx_buffer[32];
volatile unsigned char slave_rx_buffer[32];
//char thestring[32];
uint8_t spi0DoneFlag = 0;
uint8_t spiRcvData = 0;
uint8_t bytedata[] = {'0', '0', 'S', 'P', 'I', ' ',  'R', 'C', 'V', ' ', 'D', 'A', 'T', 'A', ':', ' ', '0', '0','\0', '\0'};
void DisplayData(uint8_t displayData);
uint64_t t0 = 0,diff = 0,t1 = 0;

/*****************************************************************************
** Function name:DisplayData	
** Description: display a byte data
** parameters: displayData)
** Returned value: None
*****************************************************************************/
void DisplayData(uint8_t displayData)
{
    uint8_t tempChar;
    //PutTerminalCharacter(LPC_USART2, '0');
    //PutTerminalCharacter(LPC_USART2, 'x');
    tempChar = ( (displayData >> 4) & 0x0f) ;
    if(tempChar >= 0 && tempChar <= 9)
        //PutTerminalCharacter(LPC_USART2, (tempChar  + 0x30) );
	printf("");
    else if (tempChar >= 0x0a && tempChar <= 0x0f)
    //PutTerminalCharacter(LPC_USART2, ( (tempChar % 10 ) + 0x41) );
    //PutTerminalCharacter(LPC_USART2, ';');
    //PutTerminalCharacter(LPC_USART2, ' ');
    //PutTerminalCharacter(LPC_USART2, '0');
    //PutTerminalCharacter(LPC_USART2, 'x');
    //PutTerminalCharacter(LPC_USART2, ((displayData >> 0) & 0x0f) );
	tempChar =  ( (displayData >> 0) & 0x0f) ;
    if(tempChar >= 0 && tempChar <= 9)
    //PutTerminalCharacter(LPC_USART2, (tempChar  + 0x30) );
	printf("");//DEBUG
    else if (tempChar >= 0x0a && tempChar <= 0x0f)
	printf("");//DEBUG
    //PutTerminalCharacter(LPC_USART2, ( (tempChar % 10 ) + 0x41) );
    //PutTerminalCharacter(LPC_USART2, '\r');
    //PutTerminalCharacter(LPC_USART2, '\n');

}

/*****************************************************************************
** Function name:	SPI0_IRQHandler
** Description: SPI0 interrupt service routine (handles master RX data)
** parameters: None
** Returned value: None
*****************************************************************************/
void SPI0_IRQHandler()
{
	unsigned char temp;
	//  PutTerminalString(LPC_USART2, 
	printf("\n SPI ISR");
  	printf("SPI ISR");
	 // temp = LPC_SPI0->RXDAT;
	spiRcvData = temp;
	spi0DoneFlag = 1;
  	return;
}

void SPISdCardInit(uint8_t baudSelect)
{
#ifdef SD_WRITE_DEBUG
	printf("\n Inside sd card init");
#endif
  
#ifdef DEBUG
    // ConfigSWM(SPI0_SCK,   P1_1); 
    // ConfigSWM(SPI0_MISO,  P1_2);
    // ConfigSWM(SPI0_MOSI,  P1_3); 
    // ConfigSWM(SPI0_SSEL0, P1_4); 
#else
    // ConfigSWM(SPI0_SCK,   P0_26); 
    // ConfigSWM(SPI0_MISO,  P0_25);
    // ConfigSWM(SPI0_MOSI,  P0_24); 
    // ConfigSWM(SPI0_SSEL0, P0_27); 
#endif
 
#ifdef SD_WRITE_DEBUG
//   PutTerminalString(LPC_USART2, "\nReturning from SD card init");
#endif

	uint32_t clock_hz = 0; 
	if(baudSelect)
	clock_hz = 2000000; //2MHz  Not implemented for now 
	// gpio_init(); --IISU 
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], DISABLE);
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_configure_pins(sspi_instance[SSPI_INSTANCE], ENABLE, DISABLE, ENABLE,ENABLE); //MOSI, MISO, CLK, NS
	sspi_configure_lsb_first(sspi_instance[SSPI_INSTANCE], MSB_FIRST);
	sspi_configure_clock_in_hz(sspi_instance[SSPI_INSTANCE], 10000); /* Currently configuring for 100kHz, as the maximum clock is 20MHz */
	sspi_configure_clock_pol(sspi_instance[SSPI_INSTANCE], 0);
	sspi_configure_clock_phase(sspi_instance[SSPI_INSTANCE], 0);	
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	uint8_t temprx=0;
	//Clearing the FIFO RX before starting the SPI Transaction
	while( sspi_instance[SSPI_INSTANCE]->comm_status & (0x60))  //Checking the SPIRXFIFO 
	{
		temprx=sspi_instance[SSPI_INSTANCE]->data_rx;
	//	sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
//		delay_loop(1000, 2000);
	}	
	while(1)
	{
		if(! ( sspi_instance[SSPI_INSTANCE]->fifo_status & 0x10) )
		temprx=sspi_instance[SSPI_INSTANCE]->data_rx;
		else
		break;
		sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
        //delay_loop(1000, 2000);
	}
	//Clearing the FIFO TX /
	//TODO: 
}

//We dont use this function 
void SpiTxData( uint8_t txData)
{
#ifdef SHAKTI_SDK
	printf("\nSpiTxData txData %x",txData);
    uint8_t i = 0;
	uint32_t myData = (txData <<24);
	set_spi(spi_dr1, myData);
	set_spi(spi_dr5, 0 );
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)| SPI_DEFAULT ));
	spi_notbusy();
	delay_loop(100,100);

#elif IISU
//	uint8_t txData1[]={0xFF};
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],FULL_DUPLEX);
	// sspi_enable_txrx(sspi_instance[SSPI_INSTANCE],ENABLE);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],8,8);//Tx - 8, Rx - 0;
	// printf("\nSpiTxData txData %x",txData);


//-----TRANSMIT DATA------
	uint8_t comm_status  = sspi_instance[SSPI_INSTANCE]-> comm_status;
	sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	//if(comm_status & SPI_TXE) {
	printf("\n TXdata: %x", txData);
	sspi_instance[SSPI_INSTANCE]->data_tx =txData;
	// printf("\nEnabling SPI0 %x",txData);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
	//	printf("\n Send data : %x", sspi_instance[SSPI_INSTANCE]-> data_tx);
	//}
	// sspi_transmit_data(sspi_instance[SSPI_INSTANCE],txData1,1);
	while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
	//SSPI NOT BUSY 
#endif
}

uint8_t SpiRcvData(uint8_t txData)
{
#ifdef SHAKTI_SDK
	uint32_t myData = (txData<<24);
	set_spi(spi_dr1,myData);
	set_spi(spi_dr3, 0);
	set_spi(spi_dr4, 0);
	set_spi(spi_dr5, 0);
	spi_tx_rx_start(); 
	set_spi(spi_cr1, (SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(8)| SPI_DEFAULT ));
	spi_rxne_enable();
	delay_loop(100,100);
	uint32_t spiRcvData_temp = *spi_dr5;
	//printf("\nSpiRcvData Response %d",spiRcvData_temp);
	//uint8_t recvData = ((spiRcvData_temp >>24) & 0xFF);
	uint8_t recvData = (spiRcvData_temp & 0xFF);
#elif IISU //The new SSPI Drivers

#ifdef SD_WRITE_DEBUG
	//	printf("\n\t\tSpiTxRxData txData %x",txData);
#endif

	uint8_t i = 0;
	uint8_t recvData = 0;
	sspi_instance[SSPI_INSTANCE]->data_tx = txData;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],FULL_DUPLEX);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],8,8);//Tx - 8, Rx - 8;
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
	while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
	if((sspi_instance[SSPI_INSTANCE]->fifo_status & SPI_RX_EMPTY) != 1 )
	{
		recvData = sspi_instance[SSPI_INSTANCE] -> data_rx;
	}

#ifdef SD_WRITE_DEBUG
	printf("\n\t\t\tRcvData rx- %x",recvData);
#endif

#endif 
    return recvData;
}
//This function not used anymore -SJ
uint32_t SpiRcvData32(uint32_t txData)
{
	uint32_t myData = (txData<<24);

#ifdef SHAKTI

	set_spi(spi_dr1,myData);
	// set_spi(spi_dr3, 0);
	// set_spi(spi_dr4, 0);
	set_spi(spi_dr5, 0);
	spi_tx_rx_start(); 
	// set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(0)|SPI_TOTAL_BITS_RX(80) | SPI_MSTR |SPI_SPE | SPI_BIDIMODE | SPI_RXONLY));
	set_spi(spi_cr1, (SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(24) |SPI_DEFAULT));
	spi_rxne_enable();
	delay_loop(100,100);
	uint32_t spiRcvData_temp = *spi_dr5;
	//int32_t spiRcvData_temp1 = *spi_dr4;
	printf("\nSpiRcvData32 Response spi_dr5 %x ",spiRcvData_temp);
	uint32_t recvData = ((spiRcvData_temp) & 0xFFFFFFFF);

#elif IISU 

	uint8_t i = 0;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],FULL_DUPLEX);
	// sspi_enable_txrx(sspi_instance[SSPI_INSTANCE],ENABLE);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],32,32);//Tx - 0, Rx - 32;
	sspi_transmit_data(sspi_instance[SSPI_INSTANCE],txData,1);
	uint32_t recvData = 0;
	sspi_receive_data(sspi_instance[SSPI_INSTANCE],recvData);

#endif	
    return recvData;
}


/*-----------------------------------------------------------------------*/
/* Send/Receive data to the MMC  (Platform dependent)                    */
/*-----------------------------------------------------------------------*/

/* Exchange a byte */
 BYTE xchg_spi (
	uint8_t dat	/* Data to send */
)
{
	return SpiRcvData(dat);
}

/*-----------------------------------------------------------------------*/
/*  Receive data in  multi byte  order                   */
/*-----------------------------------------------------------------------*/

static void rcvr_spi_multi (
	BYTE *buff,		/* Pointer to data buffer */
	UINT btr		/* Number of bytes to receive (16, 64 or 512) */
)
{
	UINT n;
	WORD d;
	uint32_t temp_data = 0,temp_data2 = 0;
	uint8_t recvData = 0;

#if 1

uint32_t count = 0;
uint32_t timeout = 0;
 //printf("\n Receive data in  multi byte  order");
	// t0 = *mtime;
	// printf("--------\n start value new = %lx----------------",t0);
do
{	
uint16_t rem_loop = btr - count * RX_MULBYTE_LEN;
if (!rem_loop) break;
// printf("\n loop of byte count-%d",rem_loop);
if(btr - count * RX_MULBYTE_LEN >= RX_MULBYTE_LEN)
{
	uint8_t recvData = 0;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],SIMPLEX_RX);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],0, TX_MULBYTE_LEN*8);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
	// while(!(sspi_instance[SSPI_INSTANCE] -> comm_status & SPI_RXNE) )
	// {
	// 	if(timeout++ > 0x1000) //0x8FFFFFFF)
	// 	{
	// 		printf("\n sspi_instance -> comm_status : %x", sspi_instance[SSPI_INSTANCE]-> comm_status );
	// 		return TIMEOUT;
	// 	}
	// }
	//printf("\n Buf data: ");
	for(int i = 0; i < RX_MULBYTE_LEN; i++)
	{
		*buff = sspi_instance[SSPI_INSTANCE] -> data_rx; 
		temp_data2 = *buff++;
		//printf("%x-", temp_data2);
		//printf("%x-", *buff++);
 	}
    count++;
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
}

else 
{
	
	uint8_t recvData = 0;
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],SIMPLEX_RX);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE], 0, rem_loop*8);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
	// while(!(sspi_instance[SSPI_INSTANCE] -> comm_status & SPI_RXNE) )
	// 	{
	// 		if(timeout++ > 0x1000) //0x8FFFFFFF)
	// 		{
	// 			printf("\n sspi_instance -> comm_status : %x", sspi_instance[SSPI_INSTANCE]-> comm_status );
	// 			return TIMEOUT;
	// 		}
	// 	}
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	//printf("\n Buf data: ");
	for(int i = 0; i < rem_loop; i++)
	{
		*buff = sspi_instance[SSPI_INSTANCE] -> data_rx; 
		temp_data = *buff++;
		//printf("%x-", temp_data);
	}	
	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
	break;
}

}while(1);	
// t1 = *mtime;
// diff = t1 - t0;
// printf("--------\n t0: %lx", t0);
// printf("--------\n t1: %lx", t1);
// printf("--------\n  diff value recr = %lx----------------", diff);
//configure_counter(tickvalue);
//printf("--------\n t0: %lx; t1: %lx; diff1 value new = %lx----------------", t0, t1, diff);
#else
	// uint64_t t0,diff;
	// t0=*mtime;
	do 
	{					/* Receive the data block into buffer */
	buff[0] = SpiRcvData(0xFF);       
	buff[1] = SpiRcvData(0xFF);       /* Store received data */
	//printf("\n\t\t\trc_mul btr%d b0 %x b1 %x",btr,buff[0],buff[1]);
	buff += 2;   // 2- incase of reading 2 bytes per iteration in loop
	}while (btr -= 2 );
// 	diff = *mtime - t0;
// //configure_counter(tickvalue);
// printf("--------\n diff2 value existing = %lx----------------",diff);

#endif

}

#if _DISKIO_WRITE

/*-----------------------------------------------------------------------*/
/*  Send data in  multi byte  order                   */
/*-----------------------------------------------------------------------*/
static void xmit_spi_multi (
	const BYTE *buff,	/* Pointer to the data */
	UINT btx			/* Number of bytes to send (multiple of 16) */
)
{
	UINT n;
	WORD d;
	uint8_t temp_data = 0,temp_data2 = 0;
	uint8_t recvData = 0;

	#if 1
	uint32_t count = 0;
	//printf("\n transmit data in  multi byte  order");
//	uint64_t t0=0,diff=0,t1=0;
	// t0 = *mtime;
	// printf("--------\n start 512 xmit = %lx----------------",t0);
	do
	{
		uint16_t rem_loop = btx - count * TX_MULBYTE_LEN;
		if (!rem_loop) break;
		//printf("\n loop of byte count-%d",rem_loop);
		if((btx - count * TX_MULBYTE_LEN ) >= TX_MULBYTE_LEN)
		{
			uint8_t recvData = 0;
		//	printf("\n Buf data: ");
			for(int i = 0; i < TX_MULBYTE_LEN; i++)
			{
				temp_data = *buff++;
    			sspi_instance[SSPI_INSTANCE]->data_tx = temp_data;
				//printf("%x-", temp_data);
 			}
			count++;
			sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],SIMPLEX_TX);
			sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],TX_MULBYTE_LEN*8, 0);//Tx - 8, Rx - 8;
			sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
			sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
			//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
			while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
		/*	while((sspi_instance[SSPI_INSTANCE]->comm_status & SPI_RX_FIFO) != 0 )
			{
				recvData = sspi_instance[SSPI_INSTANCE] -> data_rx;
			}
		*/	//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
		}
		else 
		{
			uint8_t recvData = 0;
			//printf("\n Buf data: ");
			for(int i = 0; i < rem_loop; i++)
			{
				temp_data2 = *buff++;
				sspi_instance[SSPI_INSTANCE]->data_tx = temp_data2;
				//printf("%x-", temp_data2);
			} 
			sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE], SIMPLEX_TX);
			sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],rem_loop*8, 0);//Tx - 8, Rx - 8;
			sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
			sspi_enable_txrx(sspi_instance[SSPI_INSTANCE], ENABLE);
			//sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
			while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
/*
			while((sspi_instance[SSPI_INSTANCE]->comm_status & SPI_RX_FIFO) != 0 )
			{
				recvData = sspi_instance[SSPI_INSTANCE] -> data_rx;
				printf(" recvv%x",recvData);
			}
			sspi_read_registers(sspi_instance[SSPI_INSTANCE]);
*/
			break;
		}

	}while(1);	
// t1 = *mtime;
// printf("--------\n end 512 xmit t1 : %lx", t1);
// diff = t1 - t0;
// printf("--------\n t0: %lx", t0);
// printf("--------\n t1: %lx", t1);
// printf("--------\n  diff value txt 512  = %lx----------------", diff);
//configure_counter(tickvalue);
	//printf("--------\nt0: %lx; t1: %lx diff2 value new = %lx----------------", t0, t1, diff);
	#else
    // uint64_t t0,diff;
	// t0=*mtime; 
		while (1)
		{			/* Transmit data block */
			xchg_spi((uint8_t) ( (*buff++ )& 0xff) );  //Replaced SpiTxData with xchg_spi
			btx--;
			if(btx == 0)
				{
				//	printf("\n bytes to send reaches zero");
				//xchg_spi((uint8_t) ( (*buff++ )& 0xff) );
				break;
				}
		}
// 		diff = *mtime - t0;
// //configure_counter(tickvalue);
// printf("--------\n diff2 value existing = %lx----------------",diff);

	#endif
}
#endif


/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/


static
int wait_ready (	/* 1:Ready, 0:Timeout */
	UINT wt			/* Timeout [ms] */
)
{
	BYTE d;
	BYTE timeout=20;

#if 1
	Timer2 = wt;
	do 
	{
	d = xchg_spi(0xFF);
	/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
	} while (d != 0xFF && Timer2);	/* Wait for card goes ready or timeout */
	return (d == 0xFF) ? 1 : 0;
#else
	do 
	{
		d = xchg_spi(0xFF);
		timeout--;
		/* This loop takes a time. Insert rot_rdq() here for multitask envilonment. */
 		//PutTerminalString(LPC_USART2,  "\n Inside Wait_loop");
	} while (d != 0xFF & timeout );	/* Wait for card goes ready or timeout */
	//	return (d == 0xFF) ? 1 : 0;
	return 1; //Time out needed to be checked later TODO 
    #endif
}

/*-----------------------------------------------------------------------*/
/* Deselect card and release SPI                                         */
/*-----------------------------------------------------------------------*/

static void deselect_cs (void)
{
#ifdef SD_DEBUG
	printf("\ndeselect_cs");
#endif
	xchg_spi(0xFF);	/* Dummy clock (force DO hi-z for multiple slave SPI) */
}

/*-----------------------------------------------------------------------*/
/* Select card and wait for ready                                        */
/*-----------------------------------------------------------------------*/

static int select_cs (void)	/* 1:OK, 0:Timeout */
{

#ifdef SD_DEBUG
	printf("\nselect_cs");
#endif
	xchg_spi(0xFF);	/* Dummy clock (force DO enabled) */
	if (wait_ready(500)) return 1;	/* Leading busy check: Wait for card ready */
	deselect_cs();		/* Timeout */
	return 0;
}

/*-----------------------------------------------------------------------*/
/* Control SPI module (Platform dependent)                               */
/*-----------------------------------------------------------------------*/


void power_on (uint8_t speedCtrl)	/* Enable SSP module and attach it to I/O pads */
{
	SPISdCardInit(speedCtrl);
}

static void power_off (void)		/* Disable SPI function */
{
	select_cs();				/* Wait for card ready */
	deselect_cs();
}

/*-----------------------------------------------------------------------*/
/* Receive a data packet from the MMC                                    */
/*-----------------------------------------------------------------------*/

static int rcvr_datablock (	/* 1:OK, 0:Error */
	BYTE *buff,			/* Data buffer */
	UINT btr			/* Data block length (byte) */
)
{
	BYTE token;
	Timer1 = 200;
	do 
	{							/* Wait for DataStart token in timeout of 200ms */
		token = xchg_spi(0xFF);

		#ifdef SPI_WRITE_DEBUG
			printf("\ntoken - %x",token);
		#endif 

		/* This loop will take a time. Insert rot_rdq() here for multitask envilonment. */
		Timer1 --;
	} while ((token == 0xFF) && Timer1);
	if(token != 0xFE)
	{
		printf("\nNo token of FE detected");
		return 0;		/* Function fails if invalid DataStart token or timeout */
	}
	#ifdef SD_WRITE_DEBUG
		printf("\nrcvr_datablock -Data Token 0xFE detected");
	#endif	
	rcvr_spi_multi(buff, btr);		/* Store trailing data to the buffer */
	xchg_spi(0xFF);  //Discarding 16 bits of CRC 
	xchg_spi(0xFF);	/* Discard CRC */
	return 1;						/* Function succeeded */
}

/*-----------------------------------------------------------------------*/
/* Send a data packet to the MMC                                         */
/*-----------------------------------------------------------------------*/

#if _DISKIO_WRITE
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* Ponter to 512 byte data to be sent */
	BYTE token			/* Token */
)
{
		int i = 0, readattempts = 0;
       int temp = 0;

	BYTE resp;
	#ifdef SPI_WRITE_DEBUG
		printf("\nxmit_datablock waiting for ready");
	#endif
	if (!wait_ready(500))
	{ 	
	return 0;		/* Leading busy check: Wait for card ready to accept data block */
	}
	xchg_spi(token);					/* Send token */
	if (token == 0xFD)
	{
	return 1;/* Do not send data if token is StopTran */
	}	
	xmit_spi_multi(buff, 512);			/* Data */
	xchg_spi(0xFF); xchg_spi(0xFF);		/* Dummy CRC */
	while(++readattempts != SD_MAX_WRITE_ATTEMPTS )
	{ 
		if((resp = xchg_spi(0xFF)) != 0xFF)
			{ 
				token = 0xFF; 
				break; 
			}	
		}
		if((resp & 0x1F) == 0x05)
        {
            // set token to data accepted
            token = 0x05;
            // wait for write to finish (timeout = 250ms)
            readattempts= 0;
			while(1)
			{
				temp = xchg_spi(0xFF);
				if(temp != 0x00)
				{	
					break;
				}
				else
				{
					if(++readattempts == SD_MAX_WRITE_ATTEMPTS)
					{ 
						token = 0x00; 
						break;
					}
			   	}
			}
		}
	//printf("\n final response=%x",resp);
	return (resp & 0x1F) == 0x05 ? 1 : 0;	/* Data was accepted or not */
	/* Busy check is done at next transmission */
}
#endif

/*-----------------------------------------------------------------------*/
/* Send a command packet to the MMC                                      */
/*-----------------------------------------------------------------------*/

uint8_t send_cmd (		/* Return value: R1 resp (bit7==1:Failed to send) */
	uint8_t cmd,		/* Command index */
	uint32_t arg		/* Argument */
)
{
	BYTE n, res;
	//printf("\nCMD%d Arg- %x",cmd,arg);
	if (cmd & 0x80) {	/* Send a CMD55 prior to ACMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}
	/* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect_cs();
		if (!select_cs()) return 0xFF;
	}
	//CRC 
	n = 0x01;  /* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8)
	{	
		n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
		// rx_count = 16;
	}
	if (cmd == CMD55) n = 0x65;
	if (cmd == (ACMD41 & 0x7f) ) n = 0x77; /*CRC for ACMD41 */
	if (cmd == CMD58) n = 0xfd;
	if (cmd == CMD17) n = 0x3b; /*CRC for CMD17*/
	if (cmd == CMD18) n = 0x57; /*CRC for CMD18*/
	if (cmd == CMD24) n = 0x6f; /*CRC for CMD24*/
	if (cmd == CMD25) n = 0x03; /*CRC for CMD25*/
	if (cmd == CMD1) n = 0xf9; /*CRC for CMD1*/
	if (cmd == CMD16) n = 0x81; /*CRC for CMD16*/

	uint32_t data2 = (0x1 << 30 ) | (cmd << 24) |(arg >> 8);
//	uint32_t data3 = (((arg & 0xFFFF)<<8) | (n)) << 16 ;  //SP2020 
	uint32_t data3 = (((arg & 0xFFFF)<<8) | (n)); //For SSPI driver alone 

#ifdef SPI_WRITE_DEBUG
	printf("\nCMD%d arg%x is %x %x",cmd,arg,data2,data3);
#endif
	//printf("\n----CMD%d arg%x is %x-%x",cmd,arg,data2,data3);

	/* Send command packet */
	uint8_t send_data = (0x40 | cmd); 
	SpiRcvData(send_data);				/* Start + command index */
	SpiRcvData((uint8_t)(arg >> 24));		/* Argument[31..24] */
	SpiRcvData((uint8_t)(arg >> 16));		/* Argument[23..16] */
	SpiRcvData((uint8_t)(arg >> 8));			/* Argument[15..8] */
	SpiRcvData((uint8_t)arg);				/* Argument[7..0] */
	// n = 0x01;							/* Dummy CRC + Stop */
	// if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	// if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
	SpiRcvData(n);

	/* Receive command resp */
	if (cmd == CMD12) SpiRcvData(0xFF);	/* Diacard following one byte when CMD12 */
	n = 10;								/* Wait for response (10 bytes max) */
	//printf("\nChecking for response");
	do{
		res = SpiRcvData(0xFF);
	//	printf(".");
	// }while ((--n));
	}while ((res & 0x80) && (--n));
//printf("\n sendcomd res=%x",res);
	return res;							/* Return received response */
}

uint32_t send_cmd_48 (		/* Return value: R1 resp (bit7==1:Failed to send) */
	uint8_t cmd,		/* Command index */
	uint32_t arg		/* Argument */
)
{	

	printf("\nCMD_48%x Arg- %x",cmd,arg);
	BYTE n=0, res;
	int rx_count =16; 
	if (cmd & 0x80) {	/* Send a CMD55 prior to ACMD<n> */
		cmd &= 0x7F;
		res = send_cmd_48(CMD55, 0);
		printf("\nCMD55 Response is %x",res);
		if (res > 1) return res;
	}
	/* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect_cs();
		if (!select_cs()) return 0xFF;
	}

	/* Send command packet */
	//Sending all the command of 48 bit frame in 2 frames of 32 bit (MSB) and 16 bit (LSB)
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8)
	{	
		n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
		rx_count = 16;
	}
	if (cmd == CMD55) n = 0x65;
	if (cmd == (ACMD41 & 0x7f) ) n = 0x77; /*CRC for ACMD41 */
	if (cmd == CMD58) n = 0xfd;
	if (cmd == CMD17) n = 0x3b; /*CRC for CMD17*/
	if (cmd == CMD24) n = 0x6f; /*CRC for CMD17*/
	if (cmd == CMD1) n = 0xf9; /*CRC for CMD17*/
	if (cmd == CMD16) n = 0x81; /*CRC for CMD17*/

//	uint64_t data1 = (0x400000000001) | (cmd_num << 40) | (argu << 8 ) | (crc << 1);
	uint32_t data2 = (0x1 << 30 ) | (cmd << 24) |(arg >> 8);
//	uint32_t data3 = (((arg & 0xFFFF)<<8) | (n)) << 16 ;  //SP2020 
	uint32_t data3 = (((arg & 0xFFFF)<<8) | (n)); //For SSPI driver alone 
	uint32_t resp1,resp2=0;
	printf("\nCMD%d arg%x is %x %x",cmd,arg,data2,data3);

#ifdef SHAKTI
	set_spi(spi_dr1,data2);
	set_spi(spi_dr2,data3);
	set_spi(spi_dr5,0);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_TOTAL_BITS_TX(48)|SPI_TOTAL_BITS_RX(rx_count)|SPI_DEFAULT ));
	delay_loop(100,100);
	// spi_notbusy();
	resp1 = *spi_dr5; 
	//resp2 = *spi_dr4; 

#elif IISU 
#endif

	// if (resp1 == 0xff01)
	// 		printf("\nCorrect Response received; CMD0 is accepted \n");
	// resp2 = *spi_dr4;
	uint8_t txData[6];
	uint8_t rxData[2];
	txData[0]=(data2 & 0xFF000000) >> 24;
	txData[1]=(data2 & 0x00FF0000) >> 16;
	txData[2]=(data2 & 0x0000FF00) >>  8;
	txData[3]=(data2 & 0x000000FF);
	txData[4]=(data3 & 0x0000FF00) >> 8;
	txData[5]=(data3 & 0x00000FF);

	//TRANSMIT DATA 
	uint8_t tx_buf_length = 6,i;
	for( i=0; i < tx_buf_length; i++){
		//  if(comm_status & SPI_TXE) {
				printf("\n Setting %x to data tx",txData[i]);
				sspi_instance[SSPI_INSTANCE] -> data_tx = txData[i];
				printf("\nEnabling SPI0 %x",txData[i]);
		//    }
	}

	 
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE],HALF_DUPLEX);
	sspi_configure_mas_slv(sspi_instance[SSPI_INSTANCE],MASTER);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE],64,16);//Tx - 8, Rx - 8;
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE],ENABLE);
	// sspi_transmit_data(sspi_instance[SSPI_INSTANCE], &txData,6); // (32+16)
	while( (sspi_instance[SSPI_INSTANCE]->comm_status & SPI_BUSY) != 0 );
	// Is SPI not busy check needed ? ?? 
	//sspi_receive_n_data(sspi_instance[SSPI_INSTANCE],&rxData,2);
	uint8_t rx_buf_length = 2;
	if( sspi_instance[SSPI_INSTANCE]->comm_status & SPI_RXNE){
		for(i=0; i < rx_buf_length ; i++ )
		{
			rxData[i]= sspi_instance[SSPI_INSTANCE]->data_rx;
			printf("\nsend_cmd_48 Rx data %x",rxData[i]);
		}
	}

	// printf("\nResponse for CMD%d is %x",cmd, rxData );
	/* Receive command resp */
	if (cmd == CMD12) SpiRcvData(0xFF);	/* Diacard following one byte when CMD12 */
	// n = 10;								/* Wait for response (10 bytes max) */
	// printf("\nChecking for response");
	// do{
	// 	res = SpiRcvData(0xFF);
	// 	printf(".");
	// }while ((--n));
	// }while ((res & 0x80) && (--n));
	return ( rxData[1] & 0xFF );							/* Return received response */
}

/*--------------------------------------------------------------------------
   Public Functions
---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Initialize disk drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive number (0) */
)
{
	BYTE n, cmd, ty, ocr[4];
#ifdef SD_WRITE_DEBUG
	printf("\nFN-Disk_initialize");
#endif

	if (drv) return STA_NOINIT;			/* Supports only drive 0 */
	power_on(0);							/* Initialize SPI */
	if (Stat & STA_NODISK) return Stat;	/* Is a card existing in the soket? */

//	FCLK_SLOW();
#ifdef SD_WRITE_DEBUG
	printf("\n80 Dummy cycles ");
#endif

	// for (n = 10; n; n--) xchg_spi(0xFF);	/* Send 80 dummy clocks */
	for (n = 10; n; n--) xchg_spi(0xFF);	/* Send 80 dummy clocks */
	ty = 0;

#ifdef SD_WRITE_DEBUG
	printf("\nSending idle command CMD0 ");	
#endif
  
	if (send_cmd(CMD0, 0) == 1) 
	{			/* Put the card SPI state */
		Timer1 = 1000;						/* Initialization timeout = 1 sec */
		#ifdef SD_WRITE_DEBUG
		printf("\nSending Command 8 ");
		#endif        
		delay_loop(100,100);
		if (send_cmd(CMD8, 0x1AA) == 1) 
		{	/* Is the catd SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);	/* Get 32 bit return value of R7 resp */
			// for (n = 0; n < 4; n++) printf("\nOCR Register %d is %x",n,ocr[n]);
			if (ocr[2] == 0x01 && ocr[3] == 0xAA)
			{				/* Does the card support 2.7-3.6V? */
	#ifdef SD_WRITE_DEBUG           
	printf("\nSending Command 41");
	#endif
				while (Timer1 && send_cmd(ACMD41, 1UL << 30))
				{
					Timer1--;
				}	/* Wait for end of initialization with ACMD41(HCS) */
				Timer1=1000;

	#ifdef SD_WRITE_DEBUG
	printf("\nSending Command 58");
	#endif

                if (Timer1 && send_cmd(CMD58, 0) == 0)
				{		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Check if the card is SDv2 */
				//    uint32_t ocr_temp = SpiRcvData32(0xFFFF);
				//	ty = ((ocr_temp>>24) & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* Check if the card is SDv2 */
				}
			}
		} 
		else
		{	/* Not an SDv2 card */
			if (send_cmd(ACMD41, 0) <= 1) 
				{	/* SDv1 or MMCv3? */
					ty = CT_SD1; cmd = ACMD41;	/* SDv1 (ACMD41(0)) */
				} 
				else	
				{
					ty = CT_MMC; cmd = CMD1;	/* MMCv3 (CMD1(0)) */
				}
			while (Timer1 && send_cmd(cmd, 0)) ;		/* Wait for the card leaves idle state */
			if (!Timer1 || send_cmd(CMD16, 512) != 0)	/* Set block length: 512 */
			ty = 0;
		}
	}
	CardType = ty;	/* Card type */

	#ifdef SD_WRITE_DEBUG       
	printf("\nCard Type is : %d",CardType);     
	#endif

	deselect_cs();
	if (ty) 
	{		/* OK */      
		//printf("\nChanging to high speed");
		power_on(1);
//		FCLK_FAST();			/* Set fast clock */
		Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT flag */
	} 
	else
	{		/* Failed */
		power_off();
		Stat = STA_NOINIT;
	}

	#ifdef SD_WRITE_DEBUG  
	printf("\nReturning from disk_initialise");
	#endif

return Stat;
}

/*-----------------------------------------------------------------------*/
/* Get disk status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive number (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only drive 0 */
	return Stat;	/* Return disk status */
}

/*-----------------------------------------------------------------------*/
/* Read sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive number (0) */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	DWORD sector,	/* Start sector number (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	BYTE cmd;
   
	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */
	if (!(CardType & CT_BLOCK)) sector *= 512;	/* LBA ot BA conversion (byte addressing cards) */

	//Temporary for debugging 
	cmd = count > 1 ? CMD18 : CMD17;
	#ifdef SD_WRITE_DEBUG
	printf("--cmd =%d", cmd);	
	printf("--count =%d", count);			/*  READ_MULTIPLE_BLOCK : READ_SINGLE_BLOCK */	
    #endif
	
	if (send_cmd(cmd, sector) == 0)//read single block
	{
	
		#ifdef SD_WRITE_DEBUG
		printf("\ndisk read CMD17 Response - 0");
		#endif
		do 
		{
			if (!rcvr_datablock(buff, 512)) break;
			buff += 512;
		} while (--count);
		if (cmd == CMD18) send_cmd(CMD12, 0);	/* STOP_TRANSMISSION */
	}
	deselect_cs();	
	return count ? RES_ERROR : RES_OK;	/* Return result */
}

/*-----------------------------------------------------------------------*/
/* Write sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _DISKIO_WRITE
DRESULT disk_write (
	BYTE drv,			/* Physical drive number (0) */
	const BYTE *buff,	/* Ponter to the data to write */
	DWORD sector,		/* Start sector number (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{

	#ifdef SD_WRITE  
	printf("\nInside disk_write");    
	#endif

	if (drv || !count) return RES_PARERR;		/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check drive status */
	if (Stat & STA_PROTECT) return RES_WRPRT;	/* Check write protect */
	if (!(CardType & CT_BLOCK)) sector *= 512;	/* LBA ==> BA conversion (byte addressing cards) */
   
    #ifdef SD_WRITE_DEBUG
	printf("\n dwcount value at entry=%d",count);	
    #endif
	
	if (count == 1)
	{	/* Single sector write */
		#ifdef SD_WRITE
		printf("\ndisk_write Count is 1");    
		#endif
		/* WRITE_BLOCK */
	
		if ((send_cmd(CMD24, sector) == 0)	&& xmit_datablock(buff, 0xFE))
		{	
		#ifdef SD_WRITE_DEBUG
			printf("\n cmd24 & xmit data block called");
		#endif		
		count = 0;
		}
	
	}
	else
	{				/* Multiple sector write */
	#ifdef SD_WRITE_DEBUG  
	printf("\ndisk_write Count not equal to 1");    
	#endif

	if (CardType & CT_SDC) send_cmd(ACMD23, count);	/* Predefine number of sectors */
		if (send_cmd(CMD25, sector) == 0) /* WRITE_MULTIPLE_BLOCK */
		{	
			do 
			{
				
				if (!xmit_datablock(buff, 0xFC)) { printf("\nExiting the xmit_datablock-----------------");break; }
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD)) count = 1;	/* STOP_TRAN token */
		}
	}
	deselect_cs();

#ifdef SD_WRITE
printf("\nreturn from disk_write %d\n",count);    
#endif

	return count ? RES_ERROR : RES_OK;	/* Return result */
}
#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous drive controls other than data read/write               */
/*-----------------------------------------------------------------------*/

#if _DISKIO_IOCTL

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE cmd,		/* Control command code */
	void *buff		/* Pointer to the conrtol data */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD *dp, st, ed, csize;
#if _DISKIO_ISDIO
	SDIO_CMD *sdio = buff;
	BYTE rc, *buff;
	UINT dc;
#endif

	if (drv) return RES_PARERR;					/* Check parameter */
	if (Stat & STA_NOINIT) return RES_NOTRDY;	/* Check if drive is ready */

	res = RES_ERROR;

	switch (cmd) {
	case CTRL_SYNC:			/* Wait for end of internal write process of the drive */
		if (select_cs()) res = RES_OK;
		break;

	case GET_SECTOR_COUNT:	/* Get drive capacity in unit of sector (DWORD) */
		if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
			if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
				csize = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(DWORD*)buff = csize << 10;
			} else {					/* SDC ver 1.XX or MMC ver 3 */
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(DWORD*)buff = csize << (n - 9);
			}
			res = RES_OK;
		}
		break;

	case GET_BLOCK_SIZE:	/* Get erase block size in unit of sector (DWORD) */
		if (CardType & CT_SD2) {	/* SDC ver 2.00 */
			if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
				xchg_spi(0xFF);
				if (rcvr_datablock(csd, 16)) {				/* Read partial block */
					for (n = 64 - 16; n; n--) xchg_spi(0xFF);	/* Purge trailing data */
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
		} else {					/* SDC ver 1.XX or MMC */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
				if (CardType & CT_SD1) {	/* SDC ver 1.XX */
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
				} else {					/* MMC */
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		break;

	case CTRL_TRIM:		/* Erase a block of sectors (used when _USE_TRIM in ffconf.h is 1) */
		if (!(CardType & CT_SDC)) break;				/* Check if the card is SDC */
		if (disk_ioctl(drv, MMC_GET_CSD, csd)) break;	/* Get CSD */
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;	/* Check if sector erase can be applied to the card */
		dp = buff; st = dp[0]; ed = dp[1];				/* Load sector block */
		if (!(CardType & CT_BLOCK)) {
			st *= 512; ed *= 512;
		}
		if (send_cmd(CMD32, st) == 0 && send_cmd(CMD33, ed) == 0 && send_cmd(CMD38, 0) == 0 && wait_ready(30000)) {	/* Erase sector block */
			res = RES_OK;	/* FatFs does not check result of this command */
		}
		break;

	/* Following commands are never used by FatFs module */

	case MMC_GET_TYPE:		/* Get MMC/SDC type (BYTE) */
		*ptr = CardType;
		res = RES_OK;
		break;

	case MMC_GET_CSD:		/* Read CSD (16 bytes) */
		if (send_cmd(CMD9, 0) == 0 && rcvr_datablock(ptr, 16)) {	/* READ_CSD */
			res = RES_OK;
		}
		break;

	case MMC_GET_CID:		/* Read CID (16 bytes) */
		if (send_cmd(CMD10, 0) == 0 && rcvr_datablock(ptr, 16)) {	/* READ_CID */
			res = RES_OK;
		}
		break;

	case MMC_GET_OCR:		/* Read OCR (4 bytes) */
		if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
			for (n = 4; n; n--) *ptr++ = xchg_spi(0xFF);
			res = RES_OK;
		}
		break;

	case MMC_GET_SDSTAT:	/* Read SD status (64 bytes) */
		if (send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
			xchg_spi(0xFF);
			if (rcvr_datablock(ptr, 64)) res = RES_OK;
		}
		break;
#if _DISKIO_ISDIO
	case ISDIO_READ:
		sdio = buff;
		if (send_cmd(CMD48, 0x80000000 | sdio->func << 28 | sdio->addr << 9 | ((sdio->ndata - 1) & 0x1FF)) == 0) {
			for (Timer1 = 1000; (rc = xchg_spi(0xFF)) == 0xFF && Timer1; ) ;
			if (rc == 0xFE) {
				for (buf = sdio->data, dc = sdio->ndata; dc; dc--) *buf++ = xchg_spi(0xFF);
				for (dc = 514 - sdio->ndata; dc; dc--) xchg_spi(0xFF);
				res = RES_OK;
			}
		}
		break;
	case ISDIO_WRITE:
		sdio = buff;
		if (send_cmd(CMD49, 0x80000000 | sdio->func << 28 | sdio->addr << 9 | ((sdio->ndata - 1) & 0x1FF)) == 0) {
			xchg_spi(0xFF); xchg_spi(0xFE);
			for (buf = sdio->data, dc = sdio->ndata; dc; dc--) xchg_spi(*buf++);
			for (dc = 514 - sdio->ndata; dc; dc--) xchg_spi(0xFF);
			if ((xchg_spi(0xFF) & 0x1F) == 0x05) res = RES_OK;
		}
		break;
	case ISDIO_MRITE:
		sdio = buff;
		if (send_cmd(CMD49, 0x84000000 | sdio->func << 28 | sdio->addr << 9 | sdio->ndata >> 8) == 0) {
			xchg_spi(0xFF); xchg_spi(0xFE);
			xchg_spi(sdio->ndata);
			for (dc = 513; dc; dc--) xchg_spi(0xFF);
			if ((xchg_spi(0xFF) & 0x1F) == 0x05) res = RES_OK;
		}
		break;
#endif
	default:
		res = RES_PARERR;
	}

	deselect_cs();
	return res;
}
#endif


/*-----------------------------------------------------------------------*/
/* Device timer function                                                 */
/*-----------------------------------------------------------------------*/
/* This function must be called from timer interrupt routine in period
/  of 1 ms to generate card control timing.
*/

void disk_timerproc (void)
{
	WORD n;
	BYTE s;


	n = Timer1;						/* 1kHz decrement timer stopped at 0 */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;

	s = Stat;
	if (MMC_WP) {	/* Write protected */
		s |= STA_PROTECT;
	} else {		/* Write enabled */
		s &= ~STA_PROTECT;
	}
#if 0
	if (MMC_CD) {	/* Card is in socket */
		s &= ~STA_NODISK;
	} else {		/* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);
	}
	#else
		s &= ~STA_NODISK;
	#endif
	
	Stat = s;
}

