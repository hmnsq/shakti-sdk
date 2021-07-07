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

	do{
		printf("\n\t\tF_read resp %d\n",f_read(&fil,buffer,sizeof buffer,&br)); //FIL,path,buffer,
		for(int i=0;i < br;i++)
		{
			printf("%c",buffer[i]);
		}
		printf("\n\t\t Buffer br %d",br);
	}while(br);//br == 0  - eof


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

void main()	
{
// set_baud_rate(uart_instance[0], 115200);
	BYTE read_count = FF_MAX_SS *2;
	delay_loop(200,200);
	BYTE readBuff[1024]={}; 
	int i=0;

	printf("\n\n\n\t\t\tSHAKTI PROCESSORS -SD Card Support ");

    *(pinmux_config_reg) = 0x154000;


#ifdef SD_IOCTL 
	printf("\nDisk IOCTL");
	BYTE read_buffer[16]={};
	BYTE resp=0;
	DWORD read_cc;
	//resp = disk_ioctl(0,GET_SECTOR_COUNT,&read_buffer);
	// printf("\n OCR %x %x %x %x Response %x",read_buffer[0],read_buffer[1], read_buffer[2], read_buffer[3],resp)	;
	resp = disk_ioctl(0,GET_SECTOR_COUNT,&read_cc);
	printf("\n Card Capacity in Sector Size %d",read_cc);
#endif 

#ifdef FMOUNT 

	f_mount_status = (FileMountCntrl(1)) ; 
	printf("\nF_MOUNT Status %d",f_mount_status);
	if(f_mount_status == 0)
	{
		printf("\nMounted the File system");
	
		const char file_path[]="code.mem";
		// printf("\nMounted the File system");
		fileOpenRead(file_path);
		printf("\n\t\t\t 1111----------------");
		
		// fileOpenWrite(file_path);
		// printf("\n\t\t\t 2222----------------");

		// fileOpenRead(file_path);
		// printf("\n\t\t\t 3333----------------");
		// printf("\nTest Fats");
		// testFatfs();
		//printf("\nFopen");
		delay_loop(100,100);
		FileMountCntrl(0);
	}

#endif

	while(1);

}
