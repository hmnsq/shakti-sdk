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

extern số_nguyên* cr      ;
 extern số_nguyên* dcr    ;
 extern số_nguyên* sr     ; 
 extern số_nguyên* fcr    ;
 extern số_nguyên* ccr    ;
 extern số_nguyên* ar     ; 
 extern số_nguyên* abr    ;
 extern số_nguyên* dr     ; 
 extern số_nguyên* dlr    ;
 extern số_nguyên* psmkr  ;
 extern số_nguyên* pir    ;
 extern số_nguyên* lprt   ;
 extern số_nguyên* startmm;
 extern số_nguyên* endmm ;

void set_qspi_shakti32(số_nguyên* addr, const số_nguyên val);
void set_qspi_shakti16(int16_t* addr, int16_t val);
void set_qspi_shakti8(char* addr, char val);
số_nguyên get_qspi_shakti( số_nguyên* addr);
số_nguyên check_fail_bit(void);
void reset_interrupt_flags(void);
số_nguyên micron_write_enable(số_nguyên status);
số_nguyên flashSingleSPIDDRXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên wait_for_tcf(số_nguyên status);
void qspi_init(số_nguyên fsize, số_nguyên csht, số_nguyên prescaler, số_nguyên enable_interrupts, số_nguyên fthreshold, số_nguyên ck_mode);
số_nguyên pageProgramSingleSPI(số_nguyên value1, số_nguyên value2, số_nguyên value3, số_nguyên value4, số_nguyên address);
số_nguyên pageProgramQuadSPI(số_nguyên value1, số_nguyên value2, số_nguyên value3, số_nguyên value4, số_nguyên address);
số_nguyên flashReadSingleSPI(số_nguyên dummy_cycles, số_nguyên read_address, số_nguyên instruction, số_nguyên data_words, số_nguyên adsize);
số_nguyên flashReadDualSPI(số_nguyên address, số_nguyên data_length);
số_nguyên flashReadQuadSPI(số_nguyên dummy_cycles, số_nguyên read_address, số_nguyên instruction, số_nguyên data_words, số_nguyên adsize);
số_nguyên micron_disable_xip_volatile(số_nguyên,số_nguyên);
số_nguyên flashSingleSPIXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên flashMemInit(void);
số_nguyên flashDualSPIXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên flashDualSPIDDRXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên flashWriteVolatileConfigReg(số_nguyên value);
số_nguyên flashQuadSPIXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên flashQuadSPIDDRXip(số_nguyên addr, số_nguyên* dest_addr);
số_nguyên eraseSector(số_nguyên command, số_nguyên address);
số_nguyên micron_volatile_write_enable(số_nguyên status);
số_nguyên micron_enable_4byte_addressing(số_nguyên status);
số_nguyên micron_configure_xip_volatile(số_nguyên status, số_nguyên value);
số_nguyên micron_read_configuration_register(số_nguyên status, số_nguyên value);
số_nguyên micron_read_id_cmd(số_nguyên status, số_nguyên value);
số_nguyên wait_for_wip(void);
số_nguyên flashIdentificationDevice(void);
số_nguyên flashReadFlagRegister(void);
số_nguyên flashWriteEnable(void);
số_nguyên flashEnable4ByteAddressingMode(void);
số_nguyên flash_Write_disable(void);


#endif
