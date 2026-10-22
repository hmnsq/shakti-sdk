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

#ଅନ୍ତର୍ଭାଵ<stdlib.h>
#endif
#ଅନ୍ତର୍ଭାଵ<stdint.h>

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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* cr      ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dcr    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* sr     ; 
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* fcr    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* ccr    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* ar     ; 
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* abr    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dr     ; 
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dlr    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* psmkr  ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* pir    ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* lprt   ;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* startmm;
 ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା* endmm ;

ଶୂନ୍ୟ set_qspi_shakti32(ପୂର୍ଣ୍ଣସଂଖ୍ୟା* addr, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା val);
ଶୂନ୍ୟ set_qspi_shakti16(int16_t* addr, int16_t val);
ଶୂନ୍ୟ set_qspi_shakti8(ଅକ୍ଷର* addr, ଅକ୍ଷର val);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_qspi_shakti( ପୂର୍ଣ୍ଣସଂଖ୍ୟା* addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_fail_bit(ଶୂନ୍ୟ);
ଶୂନ୍ୟ reset_interrupt_flags(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_write_enable(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashSingleSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା wait_for_tcf(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status);
ଶୂନ୍ୟ qspi_init(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fsize, ପୂର୍ଣ୍ଣସଂଖ୍ୟା csht, ପୂର୍ଣ୍ଣସଂଖ୍ୟା prescaler, ପୂର୍ଣ୍ଣସଂଖ୍ୟା enable_interrupts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fthreshold, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ck_mode);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା pageProgramSingleSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା value1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value3, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value4, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା pageProgramQuadSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା value1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value3, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value4, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadSingleSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy_cycles, ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା instruction, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_ଶବ୍ଦଗୁଡ଼ିକ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା adsize);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadDualSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_length);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadQuadSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy_cycles, ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା instruction, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_ଶବ୍ଦଗୁଡ଼ିକ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା adsize);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_disable_xip_volatile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashSingleSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashMemInit(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashDualSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashDualSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashWriteVolatileConfigReg(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashQuadSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashQuadSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା eraseSector(ପୂର୍ଣ୍ଣସଂଖ୍ୟା command, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_volatile_write_enable(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_enable_4byte_addressing(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_configure_xip_volatile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_read_configuration_register(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_read_id_cmd(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା wait_for_wip(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashIdentificationDevice(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadFlagRegister(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashWriteEnable(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashEnable4ByteAddressingMode(ଶୂନ୍ୟ);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flash_Write_disable(ଶୂନ୍ୟ);


#endif
