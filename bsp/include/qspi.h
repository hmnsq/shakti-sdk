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

extern цео* cr      ;
 extern цео* dcr    ;
 extern цео* sr     ; 
 extern цео* fcr    ;
 extern цео* ccr    ;
 extern цео* ar     ; 
 extern цео* abr    ;
 extern цео* dr     ; 
 extern цео* dlr    ;
 extern цео* psmkr  ;
 extern цео* pir    ;
 extern цео* lprt   ;
 extern цео* startmm;
 extern цео* endmm ;

void set_qspi_shakti32(цео* addr, const цео val);
void set_qspi_shakti16(int16_t* addr, int16_t val);
void set_qspi_shakti8(char* addr, char val);
цео get_qspi_shakti( цео* addr);
цео check_fail_bit(void);
void reset_interrupt_flags(void);
цео micron_write_enable(цео status);
цео flashSingleSPIDDRXip(цео addr, цео* dest_addr);
цео wait_for_tcf(цео status);
void qspi_init(цео fsize, цео csht, цео prescaler, цео enable_interrupts, цео fthreshold, цео ck_mode);
цео pageProgramSingleSPI(цео value1, цео value2, цео value3, цео value4, цео address);
цео pageProgramQuadSPI(цео value1, цео value2, цео value3, цео value4, цео address);
цео flashReadSingleSPI(цео dummy_cycles, цео read_address, цео instruction, цео data_words, цео adsize);
цео flashReadDualSPI(цео address, цео data_length);
цео flashReadQuadSPI(цео dummy_cycles, цео read_address, цео instruction, цео data_words, цео adsize);
цео micron_disable_xip_volatile(цео,цео);
цео flashSingleSPIXip(цео addr, цео* dest_addr);
цео flashMemInit(void);
цео flashDualSPIXip(цео addr, цео* dest_addr);
цео flashDualSPIDDRXip(цео addr, цео* dest_addr);
цео flashWriteVolatileConfigReg(цео value);
цео flashQuadSPIXip(цео addr, цео* dest_addr);
цео flashQuadSPIDDRXip(цео addr, цео* dest_addr);
цео eraseSector(цео command, цео address);
цео micron_volatile_write_enable(цео status);
цео micron_enable_4byte_addressing(цео status);
цео micron_configure_xip_volatile(цео status, цео value);
цео micron_read_configuration_register(цео status, цео value);
цео micron_read_id_cmd(цео status, цео value);
цео wait_for_wip(void);
цео flashIdentificationDevice(void);
цео flashReadFlagRegister(void);
цео flashWriteEnable(void);
цео flashEnable4ByteAddressingMode(void);
цео flash_Write_disable(void);


#endif
