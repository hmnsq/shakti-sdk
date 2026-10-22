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

#অন্তর্ভাৱ<stdlib.h>
#endif
#অন্তর্ভাৱ<stdint.h>

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

বাহ্য পূর্ণাঙ্ক* cr      ;
 বাহ্য পূর্ণাঙ্ক* dcr    ;
 বাহ্য পূর্ণাঙ্ক* sr     ; 
 বাহ্য পূর্ণাঙ্ক* fcr    ;
 বাহ্য পূর্ণাঙ্ক* ccr    ;
 বাহ্য পূর্ণাঙ্ক* ar     ; 
 বাহ্য পূর্ণাঙ্ক* abr    ;
 বাহ্য পূর্ণাঙ্ক* dr     ; 
 বাহ্য পূর্ণাঙ্ক* dlr    ;
 বাহ্য পূর্ণাঙ্ক* psmkr  ;
 বাহ্য পূর্ণাঙ্ক* pir    ;
 বাহ্য পূর্ণাঙ্ক* lprt   ;
 বাহ্য পূর্ণাঙ্ক* startmm;
 বাহ্য পূর্ণাঙ্ক* endmm ;

শূন্য set_qspi_shakti32(পূর্ণাঙ্ক* addr, ধ্রুৱ পূর্ণাঙ্ক val);
শূন্য set_qspi_shakti16(int16_t* addr, int16_t val);
শূন্য set_qspi_shakti8(ৱর্ণ* addr, ৱর্ণ val);
পূর্ণাঙ্ক get_qspi_shakti( পূর্ণাঙ্ক* addr);
পূর্ণাঙ্ক check_fail_bit(শূন্য);
শূন্য reset_interrupt_flags(শূন্য);
পূর্ণাঙ্ক micron_write_enable(পূর্ণাঙ্ক status);
পূর্ণাঙ্ক flashSingleSPIDDRXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক wait_for_tcf(পূর্ণাঙ্ক status);
শূন্য qspi_init(পূর্ণাঙ্ক fsize, পূর্ণাঙ্ক csht, পূর্ণাঙ্ক prescaler, পূর্ণাঙ্ক enable_interrupts, পূর্ণাঙ্ক fthreshold, পূর্ণাঙ্ক ck_mode);
পূর্ণাঙ্ক pageProgramSingleSPI(পূর্ণাঙ্ক value1, পূর্ণাঙ্ক value2, পূর্ণাঙ্ক value3, পূর্ণাঙ্ক value4, পূর্ণাঙ্ক address);
পূর্ণাঙ্ক pageProgramQuadSPI(পূর্ণাঙ্ক value1, পূর্ণাঙ্ক value2, পূর্ণাঙ্ক value3, পূর্ণাঙ্ক value4, পূর্ণাঙ্ক address);
পূর্ণাঙ্ক flashReadSingleSPI(পূর্ণাঙ্ক dummy_cycles, পূর্ণাঙ্ক read_address, পূর্ণাঙ্ক instruction, পূর্ণাঙ্ক data_শব্দগুলি, পূর্ণাঙ্ক adsize);
পূর্ণাঙ্ক flashReadDualSPI(পূর্ণাঙ্ক address, পূর্ণাঙ্ক data_length);
পূর্ণাঙ্ক flashReadQuadSPI(পূর্ণাঙ্ক dummy_cycles, পূর্ণাঙ্ক read_address, পূর্ণাঙ্ক instruction, পূর্ণাঙ্ক data_শব্দগুলি, পূর্ণাঙ্ক adsize);
পূর্ণাঙ্ক micron_disable_xip_volatile(পূর্ণাঙ্ক,পূর্ণাঙ্ক);
পূর্ণাঙ্ক flashSingleSPIXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক flashMemInit(শূন্য);
পূর্ণাঙ্ক flashDualSPIXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক flashDualSPIDDRXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক flashWriteVolatileConfigReg(পূর্ণাঙ্ক মান);
পূর্ণাঙ্ক flashQuadSPIXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক flashQuadSPIDDRXip(পূর্ণাঙ্ক addr, পূর্ণাঙ্ক* dest_addr);
পূর্ণাঙ্ক eraseSector(পূর্ণাঙ্ক command, পূর্ণাঙ্ক address);
পূর্ণাঙ্ক micron_volatile_write_enable(পূর্ণাঙ্ক status);
পূর্ণাঙ্ক micron_enable_4byte_addressing(পূর্ণাঙ্ক status);
পূর্ণাঙ্ক micron_configure_xip_volatile(পূর্ণাঙ্ক status, পূর্ণাঙ্ক মান);
পূর্ণাঙ্ক micron_read_configuration_register(পূর্ণাঙ্ক status, পূর্ণাঙ্ক মান);
পূর্ণাঙ্ক micron_read_id_cmd(পূর্ণাঙ্ক status, পূর্ণাঙ্ক মান);
পূর্ণাঙ্ক wait_for_wip(শূন্য);
পূর্ণাঙ্ক flashIdentificationDevice(শূন্য);
পূর্ণাঙ্ক flashReadFlagRegister(শূন্য);
পূর্ণাঙ্ক flashWriteEnable(শূন্য);
পূর্ণাঙ্ক flashEnable4ByteAddressingMode(শূন্য);
পূর্ণাঙ্ক flash_Write_disable(শূন্য);


#endif
