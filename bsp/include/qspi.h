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

#अन्तर्भाव<stdlib.h>
#endif
#अन्तर्भाव<stdint.h>

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

बाह्य पूर्णांक* cr      ;
 बाह्य पूर्णांक* dcr    ;
 बाह्य पूर्णांक* sr     ; 
 बाह्य पूर्णांक* fcr    ;
 बाह्य पूर्णांक* ccr    ;
 बाह्य पूर्णांक* ar     ; 
 बाह्य पूर्णांक* abr    ;
 बाह्य पूर्णांक* dr     ; 
 बाह्य पूर्णांक* dlr    ;
 बाह्य पूर्णांक* psmkr  ;
 बाह्य पूर्णांक* pir    ;
 बाह्य पूर्णांक* lprt   ;
 बाह्य पूर्णांक* startmm;
 बाह्य पूर्णांक* endmm ;

शून्य set_qspi_shakti32(पूर्णांक* addr, स्थिरांक पूर्णांक val);
शून्य set_qspi_shakti16(int16_t* addr, int16_t val);
शून्य set_qspi_shakti8(अक्षर* addr, अक्षर val);
पूर्णांक get_qspi_shakti( पूर्णांक* addr);
पूर्णांक check_fail_bit(शून्य);
शून्य reset_interrupt_flags(शून्य);
पूर्णांक micron_write_enable(पूर्णांक status);
पूर्णांक flashSingleSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक wait_for_tcf(पूर्णांक status);
शून्य qspi_init(पूर्णांक fsize, पूर्णांक csht, पूर्णांक prescaler, पूर्णांक enable_interrupts, पूर्णांक fthreshold, पूर्णांक ck_mode);
पूर्णांक pageProgramSingleSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address);
पूर्णांक pageProgramQuadSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address);
पूर्णांक flashReadSingleSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक data_शब्द, पूर्णांक adsize);
पूर्णांक flashReadDualSPI(पूर्णांक address, पूर्णांक data_length);
पूर्णांक flashReadQuadSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक data_शब्द, पूर्णांक adsize);
पूर्णांक micron_disable_xip_volatile(पूर्णांक,पूर्णांक);
पूर्णांक flashSingleSPIXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक flashMemInit(शून्य);
पूर्णांक flashDualSPIXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक flashDualSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक flashWriteVolatileConfigReg(पूर्णांक मूल्य);
पूर्णांक flashQuadSPIXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक flashQuadSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक eraseSector(पूर्णांक command, पूर्णांक address);
पूर्णांक micron_volatile_write_enable(पूर्णांक status);
पूर्णांक micron_enable_4byte_addressing(पूर्णांक status);
पूर्णांक micron_configure_xip_volatile(पूर्णांक status, पूर्णांक मूल्य);
पूर्णांक micron_read_configuration_register(पूर्णांक status, पूर्णांक मूल्य);
पूर्णांक micron_read_id_cmd(पूर्णांक status, पूर्णांक मूल्य);
पूर्णांक wait_for_wip(शून्य);
पूर्णांक flashIdentificationDevice(शून्य);
पूर्णांक flashReadFlagRegister(शून्य);
पूर्णांक flashWriteEnable(शून्य);
पूर्णांक flashEnable4ByteAddressingMode(शून्य);
पूर्णांक flash_Write_disable(शून्य);


#endif
