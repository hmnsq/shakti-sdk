/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  boot.c
 * Created date			        :  3.10.2019
 * Brief Description of file            :  boot code to copy bare metal appln 
                                           from flash to physical memory.

 Copyright (C) 2019  IIT Madras. All rights reserved.

// check LICENSE.iitm

 ***************************************************************************/

#include "boot.h"
#include "sspi.h"
#include "integer.h"
#include "diskio.h"
#include "ff.h"

// #define CODE_SIZE   131072
// #define SPI_CR1     0x00020000
// #define SPI_CR2     0x00020004
// #define SPI_SR      0x00020008
// #define SPI_DR1     0x0002000C
// #define SPI_DR2     0x00020010
// #define SPI_DR3     0x00020014
// #define SPI_DR4	    0x00020018
// #define SPI_DR5	    0x0002001C
// #define SPI_CRCPR   0x00020020
// #define SPI_RXCRCR  0x00020024
// #define SPI_TXCRCR  0x00020028

// // defining SPI_CR1 register

// #define SPI_CPHA		(1 << 0)
// #define SPI_CPOL		(1 << 1)
// #define SPI_MSTR		(1 << 2)
// #define SPI_BR(x)		(x << 3)
// #define SPI_SPE  		(1 << 6)
// #define SPI_LSBFIRST		(1 << 7)
// #define SPI_SSI 		(1 << 8)
// #define SPI_SSM			(1 << 9)
// #define SPI_RXONLY		(1 << 10)
// #define SPI_CRCL		(1 << 11)
// #define SPI_CCRCNEXT		(1 << 12)
// #define SPI_CRCEN		(1 << 13)
// #define SPI_BIDIOE		(1 << 14)
// #define SPI_BIDIMODE		(1 << 15)
// #define SPI_TOTAL_BITS_TX(x)  	(x << 16)
// #define SPI_TOTAL_BITS_RX(x)  	(x << 24)

// // defining SPI_CR2 register

// #define SPI_RX_IMM_START (1 << 16)
// #define SPI_RX_START	 (1 << 15)
// #define SPI_LDMA_TX      (1 << 14)
// #define SPI_LDMA_RX 	 (1 << 13)
// #define SPI_FRXTH	 (1 << 12)
// #define SPI_DS(x)	 (x << 8)
// #define SPI_TXEIE	 (1 << 7)
// #define SPI_RXNEIE	 (1 << 6)
// #define SPI_ERRIE	 (1 << 5)
// #define SPI_FRF		 (1 << 4)
// #define SPI_NSSP	 (1 << 3)
// #define SPI_SSOE	 (1 << 2)
// #define SPI_TXDMAEN	 (1 << 1)
// #define SPI_RXDMAEN	 (1 << 0)

// //defining SR register

// #define SPI_FTLVL(x)  (x << 11)
// #define SPI_FRLVL(x)  (x << 9)
// #define SPI_FRE	      (1 << 8)
// #define SPI_OVR	      (1 << 6)
// #define SPI_MODF      (1 << 5)
// #define SPI_CRCERR    (1 << 4)
// #define TXE	      (1 << 1)
// #define RXNE	      (1 << 0)

// //pointers to register

// int* spi_cr1 = (int*) SPI_CR1;
// int* spi_cr2 = (int*) SPI_CR2;
// int* spi_sr  = (int*) SPI_SR ;
// int* spi_dr1 = (int*) SPI_DR1 ;
// int* spi_dr2 = (int*) SPI_DR2 ;
// //int* spi_dr3  = (int*) SPI_DR3 ;
// //int* spi_dr4  = (int*) SPI_DR4 ;
// int* spi_dr5 = (int*) SPI_DR5 ;
// //int* spi_crcpr  = (int*) SPI_CRCPR;
// //int* spi_rxcrcr = (int*) SPI_RXCRCR;
// //int* spi_txcrcr = (int*) SPI_TXCRCR; 


#define PINMUX_CONFIGURE_REG 0x41510
volatile unsigned int* pinmux_config_reg = PINMUX_CONFIGURE_REG;


#define SD_BOOT		1
BYTE f_mount_status =1;
FATFS FatFs;	/* FatFs work area needed for each volume */

int* bram_address1 = (int*) 0x80000000;
 int t_width = 4;//16; 
int t_length = 8192;//2097152;
int c_per_line;
int buffer_len = 4095;
c_per_line = 9 ; // 33;

#if SHAKTI_SPI
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

#if 0
int spi_notbusy(){
	int value = 0x80;

	while((value & 0x80)){
		//		waitfor(10);
		//		printf("\n Wait for busy");
		value = get_spi(spi_sr);
	}
	return 1;
}
#endif



#if 0
int flash_write_enable(){
	//	printf("Cypress write enable \n");
	set_spi(spi_dr1, 0x06000000);
	set_spi(spi_dr5, 0x06);
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(8)|SPI_TOTAL_BITS_RX(0)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	//	waitfor(20000);
	spi_notbusy();
	//	waitfor(20000);
	return 1;
}
#endif

int flash_cmd_to_read(int command, int addr)
{
	int dr5;

	set_spi(spi_dr1, command  |  (addr >> 8));
	set_spi(spi_dr2, addr << 24);
	set_spi(spi_dr5, 0);
	spi_tx_rx_start();
	set_spi(spi_cr1, (SPI_BR(7)|SPI_TOTAL_BITS_TX(48)|SPI_TOTAL_BITS_RX(32)|SPI_SPE|SPI_CPHA|SPI_CPOL));
	waitfor(20);

	if(spi_rxne_enable()) {
		dr5 = *spi_dr5;
	}
	return dr5;

}

int flash_read(int address)
{
	int read_value = flash_cmd_to_read(0x0c000000,address);

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
	return dr5;
}

int flash_status_register_read()
{
	int stat = 0x3;

	while (stat & 0x03){
		stat = flash_cmd_read(0x05000000);
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
#endif

void waitfor(unsigned int secs) {

	unsigned int time = 0;

	while(time++ < secs);
}

void jumpToRAM()
{
	printf("\n%s\n","Control transferred to RAM");
	asm volatile("fence.i");
	asm volatile( "li x30, 0x80000000" "\n\t"
			"jr x30" "\n\t"
			:
			:
			:"x30","cc","memory"

		    );
}

// SPI 1 SD Card interface
BYTE convCharToHex(char ch) 
{
	if(ch < 'a')
		return  (ch<='9') ? (ch-'0') : (ch-'A'+10) ; 
	else 
		return (ch - 'a'+10);
}

FRESULT FileMountCntrl(unsigned char mntCntrl)
{
    FRESULT status;

    if(1 == mntCntrl)
    {
        status = f_mount(&FatFs, "", 1);
        if(FR_OK != status )
        {
            printf("\n\t\t\r Mounting failed status - %x",status);
           
            return status;
        }
        else
        {
            printf("\n\t\t\r Mounting Success.");
           
        }

    }
    else if (0 == mntCntrl)
    {
        status = f_mount(0,"",0);
        if(FR_OK != status  )
        {
            printf("\n\t\t\r Unmounting failed.");
            // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
            return status;
        }
        else
        {
            printf("\n\t\t\r Unmounting Success.");
            // LPC_GPIO_PORT->CLR1 = (1 << LED1_PIN) ;
        }
    }
    return status;
} 

 
BYTE fileToRam(char *path)
{
	FIL fil;        /* File object */
    BYTE buffer[buffer_len]; // Presently 33 characters per line /* Line buffer */
    FRESULT fr;     /* FatFs return code */
	UINT br, bw;         /* File read/write count */
	int fstatus;

	//RAM 
	int temp_bit_shift	=0;
	uint32_t read_4_bytes =0;
    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);

	if(f_mount_status)
		fstatus=FileMountCntrl(1);
	
	if(fstatus)
		return fstatus; 
    /* Open a text file */
	printf("\nfileOpenRead--------------------------------------------------");
    fr = f_open(&fil, path, FA_READ | FA_OPEN_ALWAYS);
	printf("\nf_open resp %x",fr);
    if (fr) 
		return (int)fr;
	printf("\nfileOpenRead -fread \n");
	int counter =100;
	int res = f_lseek(&fil, 0);
	// int counter_temp =0;
						// 	int* bram_address1 = (int*) 0x80000000;
						// int t_width = 4;//16; 
						// int t_length = 8192;//2097152;
						// int c_per_line = 9; // 33;
						// int buffer_len = 4096;

	do{

		// printf("\ndummy print 2");
		printf("\n\t\tF_read resp %x\n",f_read(&fil,buffer,sizeof buffer,&br)); //FIL,path,buffer,
		// For loop which iterates per line in code.mem
		int dot_count =0;
		for(int i=0;i < br; i= i + c_per_line)
		{
			//Loop iterating for ever 8 char bytes
			// printf("\ni%x--",i);
			// printf("\nSD");
			// for(int x=i;x<((c_per_line-1)+i);x++)
			// 	printf("%c",buffer[x]);

			for(int j=i; j<((c_per_line-1)+i); j= j+8)
			{
				// printf("j%x--",j);
				read_4_bytes = 0x00;
				//Every nibble read as char and conv. to hex
				// is shifted by MSB nibble position
				temp_bit_shift=28;
				for(int k=0; k < 8 ; k++ )
				{	
					read_4_bytes = (read_4_bytes)  | (convCharToHex(buffer[j+k]) << (temp_bit_shift )); 
					// printf("\n buf %c hex %x 32bits %x ",buffer[j+k],(convCharToHex(buffer[j+k])<<(temp_bit_shift)),read_4_bytes );
					temp_bit_shift = temp_bit_shift -4;
				}	
				// printf(" oD%x oA%x",*bram_address1,bram_address1);
				*(bram_address1) = read_4_bytes;
				// printf("  nD%x nRB%x",*bram_address1,read_4_bytes);
				bram_address1 ++;
				

			}
			// dot_count ++;
			// if (dot_count % 4096 )
			// {
			// 	printf(".");
			// 	dot_count =0;
			// }			
			
		}
			dot_count ++;
			if ((dot_count / 4096)==1 )
			{
				printf(".");
				dot_count =0;
			}
		
	//	printf("\n\t\t Buffer br %x",br);
		// counter_temp = br;
		// printf("dummy print");
		
		// asm volatile("ebreak");
		// counter_temp++;
	// }while(0);//br == 0  - eof
	}while(br);//br == 0  - eof
	printf("\n----------Exitting F_read");


    /* Close the file */
	
    fr=f_close(&fil);
	if(fr)
		printf("\nFile did not close resp %x \n",fr);
	
    return 0;
}

void erase_ram_data(int *bram_addr, int num)
{
	printf("\nErasing ram data");
	int counter=0;
	while(counter < num)
	{
		*bram_addr = 0x0;
		bram_addr++;
		counter++;
	}
	printf("\nRam data Erased");

}

void print_ram_data(int *bram_addr, int read_num)
{
	
	printf("\nprint_ram_data");
	int counter =0;
	while(counter < read_num )
	{
		printf("\n%x",*bram_addr);
		bram_addr++;
		counter++;
	}
}

void main()
{
	unsigned int read_address;  // read/write from/to this address
	int* bram_address = (int*) 0x80000000;
	int read_value, i=0;
	int size;
	int retval = 0;
	int arch = 0;



	asm volatile(
		     "csrr %[arch], marchid\n"
		     :
		     [arch]
		     "=r"
		     (arch)
		    );

	printf("%s\n\nSHAKTI PROCESSORS \n\n",bootlogo);
	printf("%s\n","Booting... vspi1.0 \n");

	printf("Booting on SoS! hart 0 \n");
	printf("SoS is a SoC build on top of Artix7 100T.\n");
	printf("The core belongs to Shakti C class, 64 bit.\n\n\n");
	printf("Supported ISA: RV64IMACSU.\n");
	printf("Processor Arch ID: %x.\n", arch);

	//spi_init();
	#if FLASH_BOOT
	if(1 == flash_device_id() )
	{

		read_address = 0x00b00000;

		size = flash_read(read_address);

		//printf("content of address %x is %x ::\n", read_address, size);

		read_address=read_address+4;

		if(size == 0 || size == 0xFFFFFFFF)
		{
			printf("No content to boot \n");
			asm volatile ("ebreak");
		}

		for(i = 0; i < size;i++ )
		{

			read_value= flash_read(read_address);

			*(bram_address) = read_value;

			//printf("read address %x data:  %x      write address: %x data:  %x \n", read_address,read_value, bram_address, *(bram_address));
			
			read_address = read_address+4;
			bram_address++;
			
			if(i%1024 == 0)
			{
				printf(".");
			       //printf("read address %x data:  %x      write address: %x data:  %x :: %x\n", read_address,read_value, bram_address, *(bram_address),i);
			}
		}
	}
	else
	{
		printf("Wrong device id \n");

		asm volatile ("ebreak");
	}
	#endif 


	#ifdef SD_BOOT 
	int ftr_status =1;
	printf("\nPin Config Init");
    *(pinmux_config_reg) = 0x154000;
	printf("\n Disk Initialize");

	int i_status = disk_initialize(0);
	i_status = disk_initialize(0);

	printf("\nDisk Init resp- %x",i_status);
	if(i_status == 0)
	{
		printf("\nUNMOUNTING FS");
		f_mount_status = FileMountCntrl(0);

		if(f_mount_status){
			printf("\nFs did not unmount");
			goto exit;
		}
		printf("\nf_unmount status %x",f_mount_status);
		printf("\n................\nMOUNTING FS");
		f_mount_status = (FileMountCntrl(1)); 

		printf("\nf_mount status %x",f_mount_status);

		if(f_mount_status){
			printf("\nFs did not mount");
			goto exit;
		}
		const char file_path[]="code.mem";
		// erase_ram_data(0x80000000,100);
		// print_ram_data(0x80000000,100);
		ftr_status = fileToRam(file_path);
		print_ram_data(0x80000000,100);
		if(ftr_status!=0)
			printf("\nSD Card Interfaced Successfully \n");
		delay_loop(100,100);
		FileMountCntrl(0);
	}
	printf("End of Program");
	#endif 
	if(!ftr_status)
	{	
		printf("\nJumping to RAM");
		// asm volatile("ebreak");
		jumpToRAM();

	}
exit:
	printf("SD Card was not initialzed properly");
	asm volatile ("ebreak");
}
