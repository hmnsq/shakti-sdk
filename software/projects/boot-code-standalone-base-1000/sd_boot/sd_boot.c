/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: sdsupport.c
* Brief Description of file     : 
* Name of Author    	        : Sambhav Jain
* Email ID                      : sambhav.jv @ gmail.com

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

#include <stdint.h>//Includes the definitions of standard input/output functions//
#include "sspi.h"
#include "log.h"
#include "platform.h"
#include "gpio.h"
// #include "uart.h"
#include "pinmux.h"

#include "integer.h"
#include "diskio.h"
#include "ff.h"

// #define PINMUX_CONF_REG 0x41510

// #define SD_WRITE		1
#define SD_READ		1
// #define SD_IOCTL		1
#define FMOUNT		1

//FatFs Objects
FATFS FatFs;	/* FatFs work area needed for each volume */
//

#define SPI1_SCLK 	GPIO13
#define SPI1_MOSI 	GPIO11
#define SPI1_MISO 	GPIO12
#define SPI1_SS 	GPIO10

BYTE f_mount_status =1;

//RAM 
int* bram_address = (int*) 0x80000000;
int t_width = 16; 
int t_length = 2097152;
int c_per_line = 33;

FRESULT FileMountCntrl(unsigned char mntCntrl)
{
    FRESULT status;
    // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;

    if(1 == mntCntrl)
    {
        status = f_mount(&FatFs, "", 1);
        if(FR_OK != status )
        {
            printf("\n\t\t\r Mounting failed statyus - %d",status);
            // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
            return;
        }
        else
        {
            printf("\n\t\t\r Mounting Success.");
            // LPC_GPIO_PORT->CLR1 = (1 << LED1_PIN) ;
        }

    }
    else if (0 == mntCntrl)
    {
        status = f_mount(0,"",0);
        if(FR_OK != status  )
        {
            printf("\n\t\t\r Unmounting failed.");
            // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
            return;
        }
        else
        {
            printf("\n\t\t\r Unmounting Success.");
            // LPC_GPIO_PORT->CLR1 = (1 << LED1_PIN) ;
        }
    }
    return status;
}

BYTE fileOpenGet()
{
	FIL fil;        /* File object */
    char line[100]; /* Line buffer */
    FRESULT fr;     /* FatFs return code */


    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
	if(f_mount_status)
	FileMountCntrl(1);
    /* Open a text file */
    fr = f_open(&fil, "file2.txt", FA_READ);
    if (fr) return (int)fr;

    /* Read every line and display it */
	
    while (f_gets(line, sizeof line, &fil)) {
		printf("%s",line);
    }

    /* Close the file */
    f_close(&fil);

    return 0;
}

BYTE fileOpenRead(char *path)
{
	FIL fil;        /* File object */
    BYTE buffer[4096]; /* Line buffer */
    FRESULT fr;     /* FatFs return code */
	UINT br, bw;         /* File read/write count */
	int fstatus;

    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);

	if(f_mount_status)
		fstatus=FileMountCntrl(1);
	
	if(fstatus)
		return fstatus; 
    /* Open a text file */
	printf("\nfileOpenRead--------------------------------------------------");
    fr = f_open(&fil, path, FA_READ | FA_OPEN_ALWAYS);
	printf("\nf_open resp %d",fr);
    if (fr) return (int)fr;
	printf("\nfileOpenRead -fread \n");
	int counter =100;
	do{
		printf("\n\t\tF_read resp %d\n",f_read(&fil,buffer,sizeof buffer,&br)); //FIL,path,buffer,
		for(int i=0;i < br;i++)
		{
			printf("%c",buffer[i]);
		}
		printf("\n\t\t Buffer br %d",br);
		counter--;
	}while(br && (counter == 0));//br == 0  - eof


    /* Close the file */
	
    fr=f_close(&fil);
	if(fr)
		printf("\nFile did not close resp %d \n",fr);
	
    return 0;
}

#ifdef SD_WRITE_1 

BYTE fileOpenWrite( char *path)
{
	FIL fil;        /* File object */
    BYTE buffer[4096]; /* Line buffer */
    BYTE read_buffer[4096]; /* Line buffer */

    FRESULT fr;     /* FatFs return code */
	UINT br, bw;         /* File read/write count */


    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
	printf("\n\t\tfileOpenWrite");

	if(f_mount_status)
		FileMountCntrl(1);
    /* Open a text file */
	fr=f_open(&fil, path,  FA_WRITE | FA_OPEN_ALWAYS ) ;
    printf("\n\t\tf_open resp %d",fr);
    if (fr) return (int)fr;

	// printf("\n\t\tf_sync1 %d",f_sync(&fil));
	// printf("\n\t\tf_lseek eof resp %d sizeof fil %d",f_lseek(&fil,sizeof(fil)),sizeof(&fil));
	printf("\n\t\tfileOpenWrite -f_write\n");

	for(int i = 0; i<5;i++){
		buffer[i]=i+49;
	}

	// printf("\n\t\tf_write resp %d bw - %d ", (f_write(&fil,buffer,5,&bw)) ,bw);
	printf("\n\n F_Write resp %d",(f_write(&fil, "To workie\r\n", 11, &bw) ));
	fr = f_sync(&fil);
	printf("\nf_sync resp %d",fr);
	// printf("\n\t\tf_write resp %d",fr);
	// printf("\n\t\tf_sync2 %d",f_sync(&fil));
	// if( fr )
	// 	printf("\n\t\tFile did not write \n",fr);
	// printf("\nReading Data");
	// do{
	// 	f_read(&fil,read_buffer,sizeof read_buffer,&br); //FIL,path,buffer,
	// 	printf("\nData Read br - %d",br);
	// 	for(int i=0;i < br;i++)
	// 	{
	// 		printf("%c",buffer[i]);
	// 	}
	// }while(br);//br == 0  - eof

	waitfor(5000);
    /* Close the file */
    fr = f_close(&fil);
	if( fr )
		printf("\nFile did not close %d\n",fr);
	
	printf("\nExiting the fileOpenWrite");
    return 0;
}

#endif

BYTE convCharToHex(char ch) 
{
	if(ch < 'a')
		return  (ch<='9') ? (ch-'0') : (ch-'A'+10) ; 
	else 
		return (ch - 'a'+10);
}


BYTE fileToRam(char *path)
{
	FIL fil;        /* File object */
    BYTE buffer[4092]; // Presently 33 characters per line /* Line buffer */
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
	printf("\nf_open resp %d",fr);
    if (fr) return (int)fr;
	printf("\nfileOpenRead -fread \n");
	int counter =100;
	int res = f_lseek(&fil, 0);
	do{
		printf("\n\t\tF_read resp %d\n",f_read(&fil,buffer,sizeof buffer,&br)); //FIL,path,buffer,
		// For loop which iterates per line in code.mem
		int dot_count =0;
		for(int i=0;i < br; i= i + c_per_line)
		{
			//Loop iterating for ever 8 char bytes
			// printf("\ni%d--",i);
			// printf("\n");
			for(int j=i; j<(32+i); j= j+8)
			{
				// printf("j%d--",j);
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
				*(bram_address) = read_4_bytes;
				bram_address ++;
				// printf("%x ",read_4_bytes);
				

			}
			dot_count ++;
			if (dot_count % 20971 )
			{
				printf(".");
				dot_count =0;
			}			
			
		}
		
		printf("\n\t\t Buffer br %d",br);
	// }while(0);//br == 0  - eof
	}while(br );//br == 0  - eof



    /* Close the file */
	
    fr=f_close(&fil);
	if(fr)
		printf("\nFile did not close resp %d \n",fr);
	
    return 0;
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


void main()	
{
// set_baud_rate(uart_instance[0], 115200);
	
	printf("\n\n\n\t\t\tSHAKTI PROCESSORS -SD Card Support ");
	// printf("Disk Initialize");
    *(pinmux_config_reg) = 0x154000;
	// f_mount_status = (FileMountCntrl(0)) ; 

	//Routine to Initialize and get disk status 
	// int ds = disk_initialize(0);
	BYTE read_count = FF_MAX_SS *2;

	delay_loop(200,200);
	BYTE readBuff[1024]={}; 
	int i=0;

#ifdef FMOUNT 
	disk_initialize(0);
	f_mount_status = FileMountCntrl(0);
	
	// f_mount_status = (FileMountCntrl(1)); 
	f_mount_status = (FileMountCntrl(1)); 

	const char file_path[]="code.mem";
	// printf("\nMounted the File system");
	// fileOpenRead(file_path);
	printf("\n\t\t\t 1111----------------");
	fileToRam(file_path);
	printf("\nFinished Copying to RAM Running Linux");
	// int* bram_address1 = (int*) 0x80000000;
	// print_ram_data(bram_address1,50);
	// // fileOpenWrite(file_path);
	// printf("\n\t\t\t 2222----------------");

	// fileOpenRead(file_path);
	// printf("\n\t\t\t 3333----------------");
	// // printf("\nTest Fats");
	// // testFatfs();
	// //printf("\nFopen");
	delay_loop(100,100);
	FileMountCntrl(0);
	jumpToRAM();
	asm volatile("ebreak");


#endif

	while(1);

}
