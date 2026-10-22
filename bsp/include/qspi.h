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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ QSPI_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QSPI_H

//#define BOOT
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ BOOT

#ਅਨ੍ਤਰ੍ਭਾਵ<stdlib.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ<stdint.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEF_TIMEOUT 60
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅਧਾਰ_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR      0x00000100                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCR     0x00000104                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR      0x00000108                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FCR     0x0000010c                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DLR     0x00000110                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR     0x00000114                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AR      0x00000118                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ABR     0x0000011c                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DR      0x00000120                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PSMKR   0x00000124                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PSMAR   0x00000128                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIR     0x0000012c                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LPRT    0x00000130                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STARTMM 0x90000000                                                      
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_PRESCALER(x)   (x<<24)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_PMM            (1<<23)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_APMS           (1<<22)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_TOIE           (1<<20)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_SMIE           (1<<19)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_FTIE           (1<<18)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_TCIE           (1<<17)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_TEIE           (1<<16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_FTHRES(x)      (x<<8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_FSEL           (1<<7 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_DFM            (1<<6 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_SSHIFT         (1<<4 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_TCEN           (1<<3 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_DMAEN          (1<<2 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_ABORT          (1<<1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CR_EN             (1<<0 )

//Bit vectors for DCR 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCR_FSIZE(x)       (x<<16) 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCR_ਬਹੁਲਕ_BYTE(x)   (x<<21)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCR_CSHT(x)        (x<<8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_FLEVEL(x)      (x<<8) 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_TOF            (1<<4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_SMF            (1<<3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_FTF            (1<<2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_TCF            (1<<1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FCR_CTOF (1<<4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FCR_CSMF (1<<3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FCR_CTCF (1<<1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FCR_CTEF (1<<0)

//Bit vectors for DLR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DDRM                   (1<<31) 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DHHC                   (1<<30)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DUMMY_ਦੋਆਧਾਰੀ_ਅੰਕ              (1<<29) // Needed by Micron Flash Memories
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_SIOO                   (1<<28)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_FMODE(x)               (x<<26)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DMODE(x)               (x<<24)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_DCYC(x)                (x<<18)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_ABSIZE(x)              (x<<16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_ABMODE(x)              (x<<14)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_ADSIZE(x)              (x<<12)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_ADMODE(x)              (x<<10)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_IMODE(x)               (x<<8 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_INSTRUCTION(x)         (x<<0 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_FMODE_INDWR 0x0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_FMODE_INDRD 0x1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_FMODE_APOLL 0x2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCR_FMODE_MMAPD 0x3

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NDATA  0x0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SINGLE 0x1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOUBLE 0x2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QUAD   0x3

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BYTE      0x0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TWOBYTE   0x1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ THREEBYTE 0x2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FOURBYTE  0x3

ਬਾਹਰੀ ਪੂਰਨ* cr      ;
 ਬਾਹਰੀ ਪੂਰਨ* dcr    ;
 ਬਾਹਰੀ ਪੂਰਨ* sr     ; 
 ਬਾਹਰੀ ਪੂਰਨ* fcr    ;
 ਬਾਹਰੀ ਪੂਰਨ* ccr    ;
 ਬਾਹਰੀ ਪੂਰਨ* ar     ; 
 ਬਾਹਰੀ ਪੂਰਨ* abr    ;
 ਬਾਹਰੀ ਪੂਰਨ* dr     ; 
 ਬਾਹਰੀ ਪੂਰਨ* dlr    ;
 ਬਾਹਰੀ ਪੂਰਨ* psmkr  ;
 ਬਾਹਰੀ ਪੂਰਨ* pir    ;
 ਬਾਹਰੀ ਪੂਰਨ* lprt   ;
 ਬਾਹਰੀ ਪੂਰਨ* startmm;
 ਬਾਹਰੀ ਪੂਰਨ* endmm ;

ਖਾਲੀ ਸੈੱਟ_qspi_shakti32(ਪੂਰਨ* addr, ਅਚਲ ਪੂਰਨ val);
ਖਾਲੀ ਸੈੱਟ_qspi_shakti16(int16_t* addr, int16_t val);
ਖਾਲੀ ਸੈੱਟ_qspi_shakti8(ਅੱਖਰ* addr, ਅੱਖਰ val);
ਪੂਰਨ get_qspi_shakti( ਪੂਰਨ* addr);
ਪੂਰਨ check_fail_ਦੋਆਧਾਰੀ_ਅੰਕ(ਖਾਲੀ);
ਖਾਲੀ reset_ਰੁਕਾਵਟ_flags(ਖਾਲੀ);
ਪੂਰਨ micron_write_enable(ਪੂਰਨ ਸਥਿਤੀ_2);
ਪੂਰਨ flashSingleSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ wait_for_tcf(ਪੂਰਨ ਸਥਿਤੀ_2);
ਖਾਲੀ qspi_init(ਪੂਰਨ fsize, ਪੂਰਨ csht, ਪੂਰਨ prescaler, ਪੂਰਨ enable_interrupts, ਪੂਰਨ fthreshold, ਪੂਰਨ ck_ਬਹੁਲਕ);
ਪੂਰਨ ਪੰਨਾ_ਪ੍ਰੋਗਰਾਮ_Single_SPI(ਪੂਰਨ value1, ਪੂਰਨ value2, ਪੂਰਨ value3, ਪੂਰਨ value4, ਪੂਰਨ ਪਤਾ);
ਪੂਰਨ ਪੰਨਾ_ਪ੍ਰੋਗਰਾਮ_Quad_SPI(ਪੂਰਨ value1, ਪੂਰਨ value2, ਪੂਰਨ value3, ਪੂਰਨ value4, ਪੂਰਨ ਪਤਾ);
ਪੂਰਨ flashReadSingleSPI(ਪੂਰਨ dummy_ਚੱਕਰਾਂ, ਪੂਰਨ read_ਪਤਾ, ਪੂਰਨ instruction, ਪੂਰਨ ਅੰਕੜੇ_ਸ਼ਬਦ, ਪੂਰਨ adsize);
ਪੂਰਨ flashReadDualSPI(ਪੂਰਨ ਪਤਾ, ਪੂਰਨ ਅੰਕੜੇ_ਲੰਮਾਈ);
ਪੂਰਨ flashReadQuadSPI(ਪੂਰਨ dummy_ਚੱਕਰਾਂ, ਪੂਰਨ read_ਪਤਾ, ਪੂਰਨ instruction, ਪੂਰਨ ਅੰਕੜੇ_ਸ਼ਬਦ, ਪੂਰਨ adsize);
ਪੂਰਨ micron_disable_xip_volatile(ਪੂਰਨ,ਪੂਰਨ);
ਪੂਰਨ flashSingleSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ flashMemInit(ਖਾਲੀ);
ਪੂਰਨ flashDualSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ flashDualSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ flashWriteVolatileConfigReg(ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ flashQuadSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ flashQuadSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr);
ਪੂਰਨ eraseSector(ਪੂਰਨ command, ਪੂਰਨ ਪਤਾ);
ਪੂਰਨ micron_volatile_write_enable(ਪੂਰਨ ਸਥਿਤੀ_2);
ਪੂਰਨ micron_enable_4byte_addressing(ਪੂਰਨ ਸਥਿਤੀ_2);
ਪੂਰਨ micron_configure_xip_volatile(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ micron_read_configuration_ਰਜਿਸਟਰ(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ micron_read_id_cmd(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ wait_for_wip(ਖਾਲੀ);
ਪੂਰਨ flashIdentificationDevice(ਖਾਲੀ);
ਪੂਰਨ flash_Read_Flag_ਰਜਿਸਟਰ(ਖਾਲੀ);
ਪੂਰਨ flashWriteEnable(ਖਾਲੀ);
ਪੂਰਨ flash_Enable4_Byte_Addressing_ਬਹੁਲਕ(ਖਾਲੀ);
ਪੂਰਨ flash_Write_disable(ਖਾਲੀ);


#ਜੇ_ਅੰਤ
