/************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: qspi.h
 * Brief Description of file    : Header file for qspi.
 * Name of Author    	        : visvesh
 * Email ID                     : vishu.vivek@gmail.com

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
************************************************************************/
/**
 * @file qspi.h
 * @brief Header file for qspi.
 * @detail this is the header file for qspi_micron.c
 */

#ifndef QSPI_H
#define QSPI_H

//#define BOOT
#ifndef BOOT

#অন্তর্ভাব<stdlib.h>
#endif
#অন্তর্ভাব<stdint.h>

#define DEF_TIMEOUT 60
#define BASE_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#define CR      0x00000100                                                      
#define DCR     0x00000104                                                      
#define SR      0x00000108                                                      
#define FCR     0x0000010c                                                      
#define DLR     0x00000110                                                      
#define CCR     0x00000114                                                      
#define AR      0x00000118                                                      
#define ABR     0x0000011c                                                      
#define DR      0x00000120                                                      
#define PSMKR   0x00000124                                                      
#define PSMAR   0x00000128                                                      
#define PIR     0x0000012c                                                      
#define LPRT    0x00000130                                                      
#define STARTMM 0x90000000                                                      
#define ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#define CR_PRESCALER(x)   (x<<24)
#define CR_PMM            (1<<23)
#define CR_APMS           (1<<22)
#define CR_TOIE           (1<<20)
#define CR_SMIE           (1<<19)
#define CR_FTIE           (1<<18)
#define CR_TCIE           (1<<17)
#define CR_TEIE           (1<<16)
#define CR_FTHRES(x)      (x<<8 )
#define CR_FSEL           (1<<7 )
#define CR_DFM            (1<<6 )
#define CR_SSHIFT         (1<<4 )
#define CR_TCEN           (1<<3 )
#define CR_DMAEN          (1<<2 )
#define CR_ABORT          (1<<1 )
#define CR_EN             (1<<0 )

//Bit vectors for DCR 
#define DCR_FSIZE(x)       (x<<16) 
#define DCR_MODE_BYTE(x)   (x<<21)
#define DCR_CSHT(x)        (x<<8 )
#define DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#define SR_FLEVEL(x)      (x<<8) 
#define SR_TOF            (1<<4)
#define SR_SMF            (1<<3)
#define SR_FTF            (1<<2)
#define SR_TCF            (1<<1)
#define SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#define FCR_CTOF (1<<4)
#define FCR_CSMF (1<<3)
#define FCR_CTCF (1<<1)
#define FCR_CTEF (1<<0)

//Bit vectors for DLR
#define DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#define CCR_DDRM                   (1<<31) 
#define CCR_DHHC                   (1<<30)
#define CCR_DUMMY_BIT              (1<<29) // Needed by Micron Flash Memories
#define CCR_SIOO                   (1<<28)
#define CCR_FMODE(x)               (x<<26)
#define CCR_DMODE(x)               (x<<24)
#define CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#define CCR_DCYC(x)                (x<<18)
#define CCR_ABSIZE(x)              (x<<16)
#define CCR_ABMODE(x)              (x<<14)
#define CCR_ADSIZE(x)              (x<<12)
#define CCR_ADMODE(x)              (x<<10)
#define CCR_IMODE(x)               (x<<8 )
#define CCR_INSTRUCTION(x)         (x<<0 )

#define CCR_FMODE_INDWR 0x0
#define CCR_FMODE_INDRD 0x1
#define CCR_FMODE_APOLL 0x2
#define CCR_FMODE_MMAPD 0x3

#define NDATA  0x0
#define SINGLE 0x1
#define DOUBLE 0x2
#define QUAD   0x3

#define BYTE      0x0
#define TWOBYTE   0x1
#define THREEBYTE 0x2
#define FOURBYTE  0x3

বাহ্যিক পূর্ণসংখ্যা* cr      ;
 বাহ্যিক পূর্ণসংখ্যা* dcr    ;
 বাহ্যিক পূর্ণসংখ্যা* sr     ; 
 বাহ্যিক পূর্ণসংখ্যা* fcr    ;
 বাহ্যিক পূর্ণসংখ্যা* ccr    ;
 বাহ্যিক পূর্ণসংখ্যা* ar     ; 
 বাহ্যিক পূর্ণসংখ্যা* abr    ;
 বাহ্যিক পূর্ণসংখ্যা* dr     ; 
 বাহ্যিক পূর্ণসংখ্যা* dlr    ;
 বাহ্যিক পূর্ণসংখ্যা* psmkr  ;
 বাহ্যিক পূর্ণসংখ্যা* pir    ;
 বাহ্যিক পূর্ণসংখ্যা* lprt   ;
 বাহ্যিক পূর্ণসংখ্যা* startmm;
 বাহ্যিক পূর্ণসংখ্যা* endmm ;

শূন্য set_qspi_shakti32(পূর্ণসংখ্যা* addr, ধ্রুবক পূর্ণসংখ্যা val);
শূন্য set_qspi_shakti16(int16_t* addr, int16_t val);
শূন্য set_qspi_shakti8(অক্ষর* addr, অক্ষর val);
পূর্ণসংখ্যা get_qspi_shakti( পূর্ণসংখ্যা* addr);
পূর্ণসংখ্যা check_fail_bit(শূন্য);
শূন্য reset_interrupt_flags(শূন্য);
পূর্ণসংখ্যা micron_write_enable(পূর্ণসংখ্যা status);
পূর্ণসংখ্যা flashSingleSPIDDRXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা wait_for_tcf(পূর্ণসংখ্যা status);
শূন্য qspi_init(পূর্ণসংখ্যা fsize, পূর্ণসংখ্যা csht, পূর্ণসংখ্যা prescaler, পূর্ণসংখ্যা enable_interrupts, পূর্ণসংখ্যা fthreshold, পূর্ণসংখ্যা ck_mode);
পূর্ণসংখ্যা pageProgramSingleSPI(পূর্ণসংখ্যা value1, পূর্ণসংখ্যা value2, পূর্ণসংখ্যা value3, পূর্ণসংখ্যা value4, পূর্ণসংখ্যা address);
পূর্ণসংখ্যা pageProgramQuadSPI(পূর্ণসংখ্যা value1, পূর্ণসংখ্যা value2, পূর্ণসংখ্যা value3, পূর্ণসংখ্যা value4, পূর্ণসংখ্যা address);
পূর্ণসংখ্যা flashReadSingleSPI(পূর্ণসংখ্যা dummy_cycles, পূর্ণসংখ্যা read_address, পূর্ণসংখ্যা instruction, পূর্ণসংখ্যা তথ্য_শব্দগুলি, পূর্ণসংখ্যা adsize);
পূর্ণসংখ্যা flashReadDualSPI(পূর্ণসংখ্যা address, পূর্ণসংখ্যা তথ্য_দৈর্ঘ্য);
পূর্ণসংখ্যা flashReadQuadSPI(পূর্ণসংখ্যা dummy_cycles, পূর্ণসংখ্যা read_address, পূর্ণসংখ্যা instruction, পূর্ণসংখ্যা তথ্য_শব্দগুলি, পূর্ণসংখ্যা adsize);
পূর্ণসংখ্যা micron_disable_xip_volatile(পূর্ণসংখ্যা,পূর্ণসংখ্যা);
পূর্ণসংখ্যা flashSingleSPIXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা flashMemInit(শূন্য);
পূর্ণসংখ্যা flashDualSPIXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা flashDualSPIDDRXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা flashWriteVolatileConfigReg(পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা flashQuadSPIXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা flashQuadSPIDDRXip(পূর্ণসংখ্যা addr, পূর্ণসংখ্যা* dest_addr);
পূর্ণসংখ্যা eraseSector(পূর্ণসংখ্যা command, পূর্ণসংখ্যা address);
পূর্ণসংখ্যা micron_volatile_write_enable(পূর্ণসংখ্যা status);
পূর্ণসংখ্যা micron_enable_4byte_addressing(পূর্ণসংখ্যা status);
পূর্ণসংখ্যা micron_configure_xip_volatile(পূর্ণসংখ্যা status, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা micron_read_configuration_register(পূর্ণসংখ্যা status, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা micron_read_id_cmd(পূর্ণসংখ্যা status, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা wait_for_wip(শূন্য);
পূর্ণসংখ্যা flashIdentificationDevice(শূন্য);
পূর্ণসংখ্যা flashReadFlagRegister(শূন্য);
পূর্ণসংখ্যা flashWriteEnable(শূন্য);
পূর্ণসংখ্যা flashEnable4ByteAddressingMode(শূন্য);
পূর্ণসংখ্যা flash_Write_disable(শূন্য);


#endif
