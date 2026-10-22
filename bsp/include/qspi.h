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

#include<stdlib.h>
#endif
#include<stdint.h>

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

extern ကိန်းပြည့်* cr      ;
 extern ကိန်းပြည့်* dcr    ;
 extern ကိန်းပြည့်* sr     ; 
 extern ကိန်းပြည့်* fcr    ;
 extern ကိန်းပြည့်* ccr    ;
 extern ကိန်းပြည့်* ar     ; 
 extern ကိန်းပြည့်* abr    ;
 extern ကိန်းပြည့်* dr     ; 
 extern ကိန်းပြည့်* dlr    ;
 extern ကိန်းပြည့်* psmkr  ;
 extern ကိန်းပြည့်* pir    ;
 extern ကိန်းပြည့်* lprt   ;
 extern ကိန်းပြည့်* startmm;
 extern ကိန်းပြည့်* endmm ;

void set_qspi_shakti32(ကိန်းပြည့်* addr, const ကိန်းပြည့် val);
void set_qspi_shakti16(int16_t* addr, int16_t val);
void set_qspi_shakti8(var_na* addr, var_na val);
ကိန်းပြည့် get_qspi_shakti( ကိန်းပြည့်* addr);
ကိန်းပြည့် check_fail_bit(void);
void reset_interrupt_flags(void);
ကိန်းပြည့် micron_write_enable(ကိန်းပြည့် status);
ကိန်းပြည့် flashSingleSPIDDRXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် wait_for_tcf(ကိန်းပြည့် status);
void qspi_init(ကိန်းပြည့် fsize, ကိန်းပြည့် csht, ကိန်းပြည့် prescaler, ကိန်းပြည့် enable_interrupts, ကိန်းပြည့် fthreshold, ကိန်းပြည့် ck_mode);
ကိန်းပြည့် pageProgramSingleSPI(ကိန်းပြည့် value1, ကိန်းပြည့် value2, ကိန်းပြည့် value3, ကိန်းပြည့် value4, ကိန်းပြည့် address);
ကိန်းပြည့် pageProgramQuadSPI(ကိန်းပြည့် value1, ကိန်းပြည့် value2, ကိန်းပြည့် value3, ကိန်းပြည့် value4, ကိန်းပြည့် address);
ကိန်းပြည့် flashReadSingleSPI(ကိန်းပြည့် dummy_cycles, ကိန်းပြည့် read_address, ကိန်းပြည့် instruction, ကိန်းပြည့် data_words, ကိန်းပြည့် adsize);
ကိန်းပြည့် flashReadDualSPI(ကိန်းပြည့် address, ကိန်းပြည့် data_length);
ကိန်းပြည့် flashReadQuadSPI(ကိန်းပြည့် dummy_cycles, ကိန်းပြည့် read_address, ကိန်းပြည့် instruction, ကိန်းပြည့် data_words, ကိန်းပြည့် adsize);
ကိန်းပြည့် micron_disable_xip_volatile(ကိန်းပြည့်,ကိန်းပြည့်);
ကိန်းပြည့် flashSingleSPIXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် flashMemInit(void);
ကိန်းပြည့် flashDualSPIXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် flashDualSPIDDRXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် flashWriteVolatileConfigReg(ကိန်းပြည့် value);
ကိန်းပြည့် flashQuadSPIXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် flashQuadSPIDDRXip(ကိန်းပြည့် addr, ကိန်းပြည့်* dest_addr);
ကိန်းပြည့် eraseSector(ကိန်းပြည့် command, ကိန်းပြည့် address);
ကိန်းပြည့် micron_volatile_write_enable(ကိန်းပြည့် status);
ကိန်းပြည့် micron_enable_4byte_addressing(ကိန်းပြည့် status);
ကိန်းပြည့် micron_configure_xip_volatile(ကိန်းပြည့် status, ကိန်းပြည့် value);
ကိန်းပြည့် micron_read_configuration_register(ကိန်းပြည့် status, ကိန်းပြည့် value);
ကိန်းပြည့် micron_read_id_cmd(ကိန်းပြည့် status, ကိန်းပြည့် value);
ကိန်းပြည့် wait_for_wip(void);
ကိန်းပြည့် flashIdentificationDevice(void);
ကိန်းပြည့် flashReadFlagRegister(void);
ကိန်းပြည့် flashWriteEnable(void);
ကိန်းပြည့် flashEnable4ByteAddressingMode(void);
ကိန်းပြည့် flash_Write_disable(void);


#endif
