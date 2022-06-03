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
/*

*/

#include <stdint.h>
#include <stddef.h>//Includes the definitions of standard input/output functions//
#include "sspi.h"
#include "log.h"
#include "platform.h"
#include "gpio.h"
 #include "uart.h"
#include "pinmux.h"



#include "integer.h"
#include "diskio.h"
#include "ff.h"

//#include "audio.h"
#ifdef AUDIO
//#include "audio.h"
//int read_MP3_Header(uint8_t *data, size_t len)
int  read_MP3_Header(uint8_t* data, size_t len);
int sendBytes(uint8_t* data, size_t len)

#else
extern int read_MP3_Header(uint8_t *data, size_t len);
int sendBytes(uint8_t* data, size_t len);
#endif
//#include "audio.h"

 //#define PINMUX_CONF_REG 0x41510

#define SD_WRITE		1
#define SD_READ		1
// #define SD_IOCTL		1
#define FMOUNT		1

//FatFs Objects
FATFS FatFs;	/* FatFs work area needed for each volume */
FIL fil;    /* File object */
//

#define SPI1_SCLK 	GPIO13
#define SPI1_MOSI 	GPIO11
#define SPI1_MISO 	GPIO12
#define SPI1_SS 	GPIO10

BYTE f_mount_status =1;


FRESULT  FileMountCntrl(unsigned char mntCntrl)
{
       printf("mountctrl called");
      FRESULT status;
    // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;

    if(1 == mntCntrl)
    {
        status = f_mount(&FatFs, "", 1);
        if(FR_OK != status )
        {
            printf("\n\t\t\r (initial)Mounting failed status - %d",status);
            // LPC_GPIO_PORT->SET1 = (1 << LED1_PIN) ;
 //           return;
        }
        else
        {
            printf("\n\t\t\r (initial)Mounting Success.");
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
//            return;
        }
        else
        {
            printf("\n\t\t\r Unmounting Success.");
            // LPC_GPIO_PORT->CLR1 = (1 << LED1_PIN) ;
        }
    }
	
    return status;//0 
}

BYTE fileOpenGet()
{   
         printf("write function start \n");
	//FIL fil;        /* File object */
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
send_to_mp3decoder(uint8_t *adata,uint8_t alen)
{
printf("  \n inside of mp3decoder");
return alen;
}

nextframe_handler(uint8_t  *membuf)

{
	UINT br; uint8_t fr;
	unsigned char  newbuff[4096];
	printf(" \n b4. %x",*(membuf+272));
	static const int header_size_in_bytes = 4;
	memcpy(newbuff, membuf, 271);
	int res= parse_mp3_headers(newbuff);
	printf("res=%d",res);
// 	memcpy(buff1, temp_ptr, 271);
// fread(&fil, buff1+272, 564)+ 4

	fr=f_read(&fil,(newbuff+272),563,&br);
	if(!fr)
		{
		 
               printf(" 2fread\n ");
			//    do{
		       for(int i=0;i <br;i++)
		       {
			   printf(" %x",newbuff[i]);
			  // process_mp3_headers(buffer);
		       }	
			//    }while(br);
		   }
}
int parse_mp3_headers(uint8_t *parsebuf)
{
	int bitrateindex=0,samplefreq,paddingbit=0,framelength;
	// version check MPEG 1/2..
					switch((*(parsebuf+1) & 0x18) >> 3)
					{ 
					case 0:
					printf("\n 1.MPEG Version 2.5 \n ");
					break;
                    case 1:
                    printf("\n 1.reserved \n");
					break;
                    case 2:
                    printf("\n 1.MPEG Version 2 \n ");
					break;
                    case 3:
                    printf("\n 1.MPEG Version 1\n ");
					break;
					} 
                   			// version check MPEG 1/2..
					switch((*(parsebuf+1) & 0x18) >> 3)
					{ 
					case 0:
					printf("\n 1.MPEG Version 2.5 \n ");
					break;
                    case 1:
                    printf("\n 1.reserved \n");
					break;
                    case 2:
                    printf("\n 1.MPEG Version 2 \n ");
					break;
                    case 3:
                    printf("\n 1.MPEG Version 1\n ");
					break;
					} 
					// layer check....
					switch((*(parsebuf+1) & 0x06) >> 1)
					{ 
					case 0:
					printf(" 2.reserved \n ");
					break;
                    case 1:
                    printf("2.layer Version 3 \n");
					break;
                    case 2:
                    printf("2.layer Version 2 \n ");
					break;
                    case 3:
                    printf("2.layer Version 1\n ");
					break;
					}
					// bitrate info.......
					switch((*(parsebuf+2) & 0xf0 )>> 4)
					{ 
                       case 1:
                          printf("3.bitrate value is 32\n");
					bitrateindex=3200;
					break;
                    case 2:
                    printf("3.bitrate value is 40\n ");
					bitrateindex=4000;
					break;
                    case 3:
                    printf("3.bitrate value is  48\n ");
					bitrateindex=4800;
					break;
					case 4:
					printf(" 3.bitrate value is 56 ");
					bitrateindex=56000;
					break;
                    case 5:
                    printf("3.bitrate value is 64 \n");
					bitrateindex=64000;
					break;
                    case 6:
                    printf("3.bitrate value is 80 \n ");
					bitrateindex=80000;
					break;
                    case 7:
                    printf("3.bitrate value is 96 \n");
					bitrateindex=96000;
					break;
					case 8:
					printf(" 3.bitrate value is 112");
					bitrateindex=112000;
					break;
                    case 9:
                    printf("3.bitrate value is 128 \n");
					bitrateindex=128000;
					break;
                    case 10:
                    printf("3.bitrate value is 160 \n ");
					bitrateindex=160000;
					break;
                    case 11:
                    printf("3.bitrate value is 192 \n");
					bitrateindex=192000;
					break;
                    case 12:
					printf("3. bitrate value is 224 \n ");
					bitrateindex=224000;
					break;
                    case 13:
                    printf("3,bitrate value is 256 \n ");
					bitrateindex=256000;
					break;
                    case 14:
                    printf("3.bitrate value is 320 \n ");
					bitrateindex=320000;
					break;
					case 0:
					case 15:
					printf("3. bitrate value is free or bad value");
					}
					//sampling frequency info
					switch((*(parsebuf+2) & 0x0c) >> 2)
					{ 
					case 0:
					printf("sampling freuency is 44100\n ");
					samplefreq=44100;
					break;
                    case 1:
                    printf("sampling freuency is 48000 \n");
					samplefreq=48000;
					break;
                    case 2:
                    printf("sampling freuency is 32000\n ");
					samplefreq=32000;
					break;
                    case 3:
                    printf("reserved\n ");
					break;
				
					}
					// padding bit
					switch((*(parsebuf+2) & 0x02) >> 1)
					{ 
					case 0:
					printf("frame is not padded\n ");
					paddingbit=0;
					break;
                    case 1:
                    printf("frame is  padded \n");
					paddingbit=1;
					break;
					}
					//channel type
					switch((*(parsebuf+3) & 0xc0) >> 6)
					{ 
					case 0:
					printf(" audio file channel is stereo \n ");
				    break;
                    case 1:
                    printf("audio file channel is  joint stereo \n");
					break;
					case 2:
                    printf("audio file channel is  dual \n");
					break;
					case 3:
                    printf(" audio file channel is  mono  \n");
					break;
					}
					//frame length formula
					framelength = ((144 * bitrateindex / samplefreq)+ paddingbit);
	 				printf("audio data length is =%d \n ",framelength);
					 return framelength;

}
 process_mp3_headers(uint8_t *buf)
 { 
	 uint8_t flresponse,prevfl=0,id3endpos;
	 unsigned char * temp_ptr = NULL;
	 unsigned char * audio_ptr = NULL;
	printf("ID3 meta data in audio:\n");
	for(int i=0;i<512;i++){
		printf(" %x", *buf++);
		// position of first frame header......
	if((*buf)==0xff)
	{
if((*(buf+1) & 0xf0) == 0xf0)
				 {
					 id3endpos=i+1;
                 printf("\n id3metadata ends at =%d",id3endpos);
				printf(" \n 1. %x",*(buf+1));
	 			printf(" \n 2. %x",*(buf+2));
                  flresponse= parse_mp3_headers(buf);
				 printf("res=%d",flresponse);
				 prevfl=flresponse;	
                    
					 audio_ptr=(buf+4);
                printf(" first frames audio data:\n ");
					  
					  
					  for (i=0;i<flresponse-4;i++){
					 
					  printf(" %x", *(audio_ptr++));}
                      
					 
					  uint8_t value=send_to_mp3decoder(audio_ptr,flresponse);
					   printf("a =%d \n ",value);
					  

					    //temp_ptr = (temp_ptr+1 + value);
						temp_ptr = (buf + flresponse);
						printf(" \n 12. %x",*(temp_ptr+1));
						nextframe_handler(temp_ptr);
					   
					  //i=i+value;
					//   printf(" \n second frames complete data:\n "); 
					//   for(int i=0;i<512;i++)
		            //    printf(" %x", *temp_ptr++);
					  //process_mp3_headers(temp_ptr);
					  

				     break;
                }
				
			}
			
	}
 }

BYTE fileOpenRead(char *path)
{
	//FIL fil;        /* File object */
    BYTE buffer[4096]; UINT readcount=512;
    //BYTE buffer[1600];/* Line buffer */
    FRESULT fr;     /* FatFs return code */
	UINT br, bw;         /* File read/write count */
	int fstatus;

    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
    
	if(f_mount_status)
		fstatus=FileMountCntrl(1);
	
	if(fstatus)
	{
	printf("\nreadfstatus2");
		return fstatus; 
	}
    /* Open a text file */
	printf("\nfileOpenRead--------------------------------------------------");
    fr = f_open(&fil, path, FA_READ | FA_OPEN_ALWAYS);
	printf("\nf_open resp %d",fr);
    if (fr) return (int)fr;
	printf("\n fileOpenRead -fread \n");
		 uint32_t size = f_size(&fil);
	  printf("\n\t\t file size  %d",size);
//do{
		fr=f_read(&fil,buffer,readcount,&br); //FIL,path,buffer,
		printf("\n 3Data Read br - %d \n ",fr);
		if(!fr)
		{
		   if(startsWith(buffer, "ID3")) 
		   {
               printf("------GIVEN AUDIO FILE CONTAINS ID3 DATA  ----- \n ");
		    //    for(int i=0;i <br;i++)
		    //    {
			//    printf("%x",buffer[i]);
			   process_mp3_headers(buffer);
		       //}	
		   }
		   else
		   {
			    printf("------ THERE IS NO ID3 META DATA IN AUDIO FILE ---- \n ");
                process_mp3_headers(buffer);
		   }
		}
		//read_MP3_Header(buffer,sizeof buffer ); 
	// }while(br);
	
	
    fr=f_close(&fil);
	if(fr)
		printf("\n read File did not close resp %d \n",fr);
		// printf("\nresponse %d",res);
	
    return 0;//*/
}

#ifdef SD_WRITE

BYTE fileOpenWrite( char *path) 
{
	//FIL fil;        /* File object */
    //BYTE buffer[4096]; /* Line buffer */
	
	BYTE buffer[1600];
    //BYTE read_buffer[4096]; /* Line buffer */

    FRESULT fr;     /* FatFs return code */
	UINT br, bw;         /* File read/write count  */


    /* Gives a work area to the default drive */
    // f_mount(&FatFs, "", 0);
	printf("\n\t\tfileOpenWrite");

	if(f_mount_status)
		FileMountCntrl(1);
    /* Open a text file */
	fr=f_open(&fil, path,  FA_WRITE | FA_OPEN_ALWAYS | FA_READ) ;
    printf("\n\t\t write f_open resp %d",fr);
    if (fr) return (int)fr;

	// printf("\n\t\tf_sync1 %d",f_sync(&fil));
	// printf("\n\t\tf_lseek eof resp %d sizeof fil %d",f_lseek(&fil,sizeof(fil)),sizeof(&fil));
	printf("\n\t\tfileOpenWrite -f_write\n");

	for(int i = 0; i<5;i++){
		buffer[i]=i+49;
	}

 //printf("\n\t\tf_write resp %d bw - %d ", (f_write(&fil,buffer,5,&bw)) ,bw);
	

	//added by suganthi
//char myData[] = "Hello from arty100t\0";
 //if(f_write(&fil, myData, strlen(myData), &bw) == FR_OK)
         //  {
             //   if(f_sync(&fil) == FR_OK){
              //  waitfor(5000);    
             //   }
          //  }
			//added by suganthi
			printf("\n\n F_Write resp %d bw - %d",(f_write(&fil, "write success",20, &bw)) ,bw);
		//	fr=f_write(&fil, myData, strlen(myData), &bw);
			printf("\n\t\tf_write resp %d",fr);
			waitfor(10000);
	fr = f_sync(&fil);
	printf("\nf_sync resp %d",fr);
	 
	// printf("\n\t\tf_sync2 %d",f_sync(&fil));
	 //if( fr )
	 	//printf("\n\t\tFile did not write \n",fr);
	// printf("\nReading Data");
	// do{
	// 	f_read(&fil,read_buffer,sizeof read_buffer,&br); //FIL,path,buffer,
	// 	printf("\nData Read br - %d",br);
	// 	for(int i=0;i < br;i++)
	// 	{
	// 		printf("%c",buffer[i]);
	// 	}
	// }while(br);br == 0  - eof

	waitfor(10000);
    /* Close the file */
    fr = f_close(&fil);
	printf("\nf_close resp %d",fr);
	waitfor(5000);
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

# ifdef FMOUNT 

	f_mount_status = (FileMountCntrl(1)) ; 
	printf("\n 2F_MOUNT Status %d",f_mount_status);
	if(f_mount_status == 0)
	{
		printf("\n2Mounted  the File system,done");
	
		const char file_path[]="test2.txt";
		const char file_name[]="getfile.txt";
		const char mp3file_path[]="wobble.mp3";
		 printf("\nMounted the File system");
		  printf("\n\t\t\t -----mp3read----------------");
         printf("\n\t\t\t textfile read----------------");
		 fileOpenRead(mp3file_path); 
		//fileOpenRead(file_path);
		
		
		
		//printf("\n\t\t\t 2222----------------");
		//fileOpenWrite(file_name);
		 

		// fileOpenRead(file_name);
		 //printf("\n\t\t\t 3333----------------");
        

         //tolower(mp3file_path);
          // if(endsWith(mp3file_path,".mp3")) {        // MP3 section
         // m_codec = CODEC_MP3;
		
		//processLocalFile();
		 
		 
		// printf("\nTest Fats");
		// testFatfs();
		//printf("\nFopen");
		delay_loop(100,100);
		FileMountCntrl(0);
	}

#endif

	while(1);

}
