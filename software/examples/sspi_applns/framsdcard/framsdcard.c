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
#include "eth_driver.h"
#include "poll_eg.h"
#include "clint_driver.h"

#define PIN_MUX_DRIVER 1
// #define PINMUX_CONF_REG 0x41510

// #define SD_IOCTL		1
#define FMOUNT		1
#define EMAC_DEVICE_ID			240

//FatFs Objects
FATFS FatFs;	/* FatFs work area needed for each volume */
//
#define TOTAL_SIZE_BYTES (2*1024*1024 / 8)
//#define TOTAL_SIZE_WORDS (TOTAL_SIZE_BYTES / (4 * 512))
#define TOTAL_SIZE_WORDS 1

#define WRITE_SIZE 128

BYTE f_mount_status =1;

FRESULT FileMountCntrl(unsigned char mntCntrl)
{
	#ifdef SD_WRITE_DEBUG
	printf("\n mountctrl called");
	#endif

   // FRESULT status = FR_DISK_ERR;
      FRESULT status;
    // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
    if(1 == mntCntrl)
    {
        status = f_mount(&FatFs, "", 1);
        if(FR_OK != status )
        {
            printf("\n\t\t\r Mounting failed status - %d",status);
            // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
            //return status;
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
            // return status;
        }
        else
        {
            printf("\n\t\t\r Unmounting Success.");
            // LPC_GPIO_PORT->CLR1 = (1 << LED1_PIN) ;
        }
    }
	uint8_t e=status;
	//printf("mount flag= %d",e);
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
	
    while (f_gets(line, sizeof line, &fil))
	{
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
	uint32_t total_bytes_read = 0;

    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
	if(f_mount_status)
	f_mount_status = FileMountCntrl(1);
    /* Open a text file */
	#ifdef SD_WRITE_DEBUG
	printf("\nfileOpenRead:%s--------------------------------------------------", path);
	#endif

    fr = f_open(&fil, path, FA_READ | FA_OPEN_EXISTING);
	printf("\n File Size: %d", f_size(&fil));
	//  fr = f_open(&fil, path, FA_READ | FA_OPEN_ALWAYS);
	printf("\nf_open resp %d",fr);
    if (fr) return (int)fr;
	printf("\nfileOpenRead -fread \n");
	do{
		fr = f_read(&fil, buffer, 1000, &br);
		printf("\nfr: %d; br: %d\n", fr, br);
	//		for(int i = 0; i < br; i++)
	//		printf("%c", buffer[i]);
		if(FR_OK == fr)
		{
			if (0 == br)
			break;
			printf("\n File read bytes: %d", br);
			total_bytes_read += br;
			Emaclite_send_sd_packet(buffer, br);
		}
		else 
			break;
		printf("\n Total bytes read: %d", total_bytes_read);
		//	}while(!f_eof(&fil));//br == 0  - eof
		}while(!total_bytes_read <= f_size(&fil));//br == 0  - eof
	printf("\n Total bytes read on exit: %d", total_bytes_read);

    /* Close the file */
    fr=f_close(&fil);
	if(fr)
	printf("\nFile did not close resp %d \n",fr);

    return 0;
}


BYTE fileOpenWrite( char *path)
{
	FIL fil;        /* File object */
    BYTE buffer[4096]; /* Line buffer */

    FRESULT fr;     /* FatFs return code */
	UINT br, bw, count;         /* File read/write count */
	UINT i, j;
	UINT read_address = 0x0, size = 512/4;


    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
	if(f_mount_status)
	FileMountCntrl(1);
    /* Open a text file */
	fr=f_open(&fil, path,  FA_WRITE | FA_OPEN_ALWAYS ) ;
   // printf("\n\t\tf_open resp %d",fr);
    if (fr) return (int)fr;
    // printf("\nfile opened successfully");
	printf("\nfile opened");
	// printf("\n\t\tf_sync1 %d",f_sync(&fil));
	// printf("\n\t\tf_lseek eof resp %d sizeof fil %d",f_lseek(&fil,sizeof(fil)),sizeof(&fil));
	// printf("\n\t\tfileOpenWrite -f_write\n");
	// printf("\n File Size before write: %d", f_size(&fil));
//	for(int j = 0; j < 5000; j++)
//	{
//		printf("\n j:%d", j);
		count = 0;
#if 0
		while(count < 500)
		{
			for(int i = 0; i < 10; i++)
			{
				buffer[count++] = i + '0';
			}
			for(int i = 0; i<26; i++){
				buffer[count++]=i + 'A';
			}

			for(int i = 0; i < 26; i++){
				buffer[count++]=i + 'a';
			}
		}
#else
//		read_address = 0x00000000;
		for(j = 0; j < TOTAL_SIZE_WORDS * 4; j++) //tsw=128*4=512
//		for(j = 0; j < TOTAL_SIZE_WORDS; j++) //tsw=128*4=512
		{
			read_fram_locations(&buffer, read_address, size);//&buffer” - is a “pointer to whole array of 4096 byte buffer”
			fr = f_write(&fil, buffer, 512, &bw );
		//	printf("\n File Write Status fr =  %d; Bytes Written: %d", fr, bw);
			if(FR_OK != fr)
			{
				printf("\n Error in Writing: Error: %x", fr) ;
				exit(-1);
			}				
			Emaclite_send_sd_packet(buffer, bw);
			//printf("\n File Size during write: %d", f_size(&fil));
			read_address += (size * 4);//next 512 data
			// Trying to read the value from it.
			fr = f_sync(&fil);
			// printf("\n F_Size after write: %d", f_size(&fil));
			//printf("\n F_Size: %d", f_size(&fil));
			if(! (j % 10) )
			{
			//	printf("\n\n F_Write resp %d",(f_write(&fil, "To workie\r\n", 11, &bw) ));
				fr = f_sync(&fil);
				if(FR_OK != fr)
				{
					printf("\n Error in Syncing; Error: %x", fr);
					exit(-1);
				}
				// printf("\nf_sync resp %d",fr);
				// printf("\n File Size after sync: %d", f_size(&fil));
			}
		}
//	}
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
#endif
	waitfor(5000);

    /* Close the file */
    fr = f_close(&fil);
	if( fr )
	 printf("\nFile did not close %d\n",fr);

	printf("\nExiting the fileOpenWrite");
    return 0;
}


void main()	
{
	// set_baud_rate(uart_instance[0], 115200);
	BYTE read_count = FF_MAX_SS *2;
	delay_loop(200,200);
	BYTE readBuff[1024]={}; 
	int i=0;
	printf("\n\n\n\t\t\tSHAKTI PROCESSORS -SD Card Support\n  ");
 //   *(pinmux_config_reg) = 0x154000;
	*pinmux_config_reg = 0x154000;
	sspi_init();
	flash_init();
	Emaclite_init(EMAC_DEVICE_ID);

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
		//printf("\nF_MOUNT Status %d",f_mount_status);
		if(f_mount_status == 0)
		{
			//printf("\nMounted the File system");
	//		const char file_path[]="arty.log";
			uint64_t t0 = 0, t1 = 0,diff = 0;

			t0=*mtime;
			//printf("--------\n before write start time t0: %lx", t0);

			const char file_path[]="demo5.mem";
			f_unlink(file_path);
			fileOpenWrite(file_path);

			t1 = *mtime;
			diff = t1 - t0;
			printf("\n start time t0: %lx", t0);
			printf("\n end time t1: %lx", t1);
			printf("\n diff value t1-to = %lx", diff);

	//		fileOpenRead(file_path);
			delay_loop(100,100);
			FileMountCntrl(0);
		}

		//else
		//{
		//	sspi_read_registers(sspi_instance[2]);
		//}

	#endif

	while(1);
}
