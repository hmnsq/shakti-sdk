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

#अगर_अघोषित QSPI_H
#घोषणा QSPI_H

//#define BOOT
#अगर_अघोषित BOOT

#समावेश<stdlib.h>
#पूर्ण_अगर
#समावेश<stdint.h>

#घोषणा DEF_TIMEOUT 60
#घोषणा BASE_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#घोषणा CR      0x00000100                                                      
#घोषणा DCR     0x00000104                                                      
#घोषणा SR      0x00000108                                                      
#घोषणा FCR     0x0000010c                                                      
#घोषणा DLR     0x00000110                                                      
#घोषणा CCR     0x00000114                                                      
#घोषणा AR      0x00000118                                                      
#घोषणा ABR     0x0000011c                                                      
#घोषणा DR      0x00000120                                                      
#घोषणा PSMKR   0x00000124                                                      
#घोषणा PSMAR   0x00000128                                                      
#घोषणा PIR     0x0000012c                                                      
#घोषणा LPRT    0x00000130                                                      
#घोषणा STARTMM 0x90000000                                                      
#घोषणा ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#घोषणा CR_PRESCALER(x)   (x<<24)
#घोषणा CR_PMM            (1<<23)
#घोषणा CR_APMS           (1<<22)
#घोषणा CR_TOIE           (1<<20)
#घोषणा CR_SMIE           (1<<19)
#घोषणा CR_FTIE           (1<<18)
#घोषणा CR_TCIE           (1<<17)
#घोषणा CR_TEIE           (1<<16)
#घोषणा CR_FTHRES(x)      (x<<8 )
#घोषणा CR_FSEL           (1<<7 )
#घोषणा CR_DFM            (1<<6 )
#घोषणा CR_SSHIFT         (1<<4 )
#घोषणा CR_TCEN           (1<<3 )
#घोषणा CR_DMAEN          (1<<2 )
#घोषणा CR_ABORT          (1<<1 )
#घोषणा CR_EN             (1<<0 )

//Bit vectors for DCR 
#घोषणा DCR_FSIZE(x)       (x<<16) 
#घोषणा DCR_MODE_BYTE(x)   (x<<21)
#घोषणा DCR_CSHT(x)        (x<<8 )
#घोषणा DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#घोषणा SR_FLEVEL(x)      (x<<8) 
#घोषणा SR_TOF            (1<<4)
#घोषणा SR_SMF            (1<<3)
#घोषणा SR_FTF            (1<<2)
#घोषणा SR_TCF            (1<<1)
#घोषणा SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#घोषणा FCR_CTOF (1<<4)
#घोषणा FCR_CSMF (1<<3)
#घोषणा FCR_CTCF (1<<1)
#घोषणा FCR_CTEF (1<<0)

//Bit vectors for DLR
#घोषणा DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#घोषणा CCR_DDRM                   (1<<31) 
#घोषणा CCR_DHHC                   (1<<30)
#घोषणा CCR_DUMMY_BIT              (1<<29) // Needed by Micron Flash Memories
#घोषणा CCR_SIOO                   (1<<28)
#घोषणा CCR_FMODE(x)               (x<<26)
#घोषणा CCR_DMODE(x)               (x<<24)
#घोषणा CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#घोषणा CCR_DCYC(x)                (x<<18)
#घोषणा CCR_ABSIZE(x)              (x<<16)
#घोषणा CCR_ABMODE(x)              (x<<14)
#घोषणा CCR_ADSIZE(x)              (x<<12)
#घोषणा CCR_ADMODE(x)              (x<<10)
#घोषणा CCR_IMODE(x)               (x<<8 )
#घोषणा CCR_INSTRUCTION(x)         (x<<0 )

#घोषणा CCR_FMODE_INDWR 0x0
#घोषणा CCR_FMODE_INDRD 0x1
#घोषणा CCR_FMODE_APOLL 0x2
#घोषणा CCR_FMODE_MMAPD 0x3

#घोषणा NDATA  0x0
#घोषणा SINGLE 0x1
#घोषणा DOUBLE 0x2
#घोषणा QUAD   0x3

#घोषणा BYTE      0x0
#घोषणा TWOBYTE   0x1
#घोषणा THREEBYTE 0x2
#घोषणा FOURBYTE  0x3

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

व्योम set_qspi_shakti32(पूर्णांक* addr, स्थिर पूर्णांक val);
व्योम set_qspi_shakti16(int16_t* addr, int16_t val);
व्योम set_qspi_shakti8(अक्षर* addr, अक्षर val);
पूर्णांक get_qspi_shakti( पूर्णांक* addr);
पूर्णांक check_fail_bit(व्योम);
व्योम reset_interrupt_flags(व्योम);
पूर्णांक micron_write_enable(पूर्णांक status);
पूर्णांक flashSingleSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक wait_for_tcf(पूर्णांक status);
व्योम qspi_init(पूर्णांक fsize, पूर्णांक csht, पूर्णांक prescaler, पूर्णांक enable_interrupts, पूर्णांक fthreshold, पूर्णांक ck_mode);
पूर्णांक pageProgramSingleSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address);
पूर्णांक pageProgramQuadSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address);
पूर्णांक flashReadSingleSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक तथ्य_शब्दगण, पूर्णांक adsize);
पूर्णांक flashReadDualSPI(पूर्णांक address, पूर्णांक तथ्य_लंबाई);
पूर्णांक flashReadQuadSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक तथ्य_शब्दगण, पूर्णांक adsize);
पूर्णांक micron_disable_xip_volatile(पूर्णांक,पूर्णांक);
पूर्णांक flashSingleSPIXip(पूर्णांक addr, पूर्णांक* dest_addr);
पूर्णांक flashMemInit(व्योम);
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
पूर्णांक wait_for_wip(व्योम);
पूर्णांक flashIdentificationDevice(व्योम);
पूर्णांक flashReadFlagRegister(व्योम);
पूर्णांक flashWriteEnable(व्योम);
पूर्णांक flashEnable4ByteAddressingMode(व्योम);
पूर्णांक flash_Write_disable(व्योम);


#पूर्ण_अगर
