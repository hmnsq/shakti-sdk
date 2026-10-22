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

#અન્તર્ભાવ<stdlib.h>
#endif
#અન્તર્ભાવ<stdint.h>

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

બાહ્ય પૂર્ણાંક* cr      ;
 બાહ્ય પૂર્ણાંક* dcr    ;
 બાહ્ય પૂર્ણાંક* sr     ; 
 બાહ્ય પૂર્ણાંક* fcr    ;
 બાહ્ય પૂર્ણાંક* ccr    ;
 બાહ્ય પૂર્ણાંક* ar     ; 
 બાહ્ય પૂર્ણાંક* abr    ;
 બાહ્ય પૂર્ણાંક* dr     ; 
 બાહ્ય પૂર્ણાંક* dlr    ;
 બાહ્ય પૂર્ણાંક* psmkr  ;
 બાહ્ય પૂર્ણાંક* pir    ;
 બાહ્ય પૂર્ણાંક* lprt   ;
 બાહ્ય પૂર્ણાંક* startmm;
 બાહ્ય પૂર્ણાંક* endmm ;

શૂન્ય set_qspi_shakti32(પૂર્ણાંક* addr, અચલ પૂર્ણાંક val);
શૂન્ય set_qspi_shakti16(int16_t* addr, int16_t val);
શૂન્ય set_qspi_shakti8(અક્ષર* addr, અક્ષર val);
પૂર્ણાંક get_qspi_shakti( પૂર્ણાંક* addr);
પૂર્ણાંક check_fail_bit(શૂન્ય);
શૂન્ય reset_interrupt_flags(શૂન્ય);
પૂર્ણાંક micron_write_enable(પૂર્ણાંક status);
પૂર્ણાંક flashSingleSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક wait_for_tcf(પૂર્ણાંક status);
શૂન્ય qspi_init(પૂર્ણાંક fsize, પૂર્ણાંક csht, પૂર્ણાંક prescaler, પૂર્ણાંક enable_interrupts, પૂર્ણાંક fthreshold, પૂર્ણાંક ck_mode);
પૂર્ણાંક pageProgramSingleSPI(પૂર્ણાંક value1, પૂર્ણાંક value2, પૂર્ણાંક value3, પૂર્ણાંક value4, પૂર્ણાંક address);
પૂર્ણાંક pageProgramQuadSPI(પૂર્ણાંક value1, પૂર્ણાંક value2, પૂર્ણાંક value3, પૂર્ણાંક value4, પૂર્ણાંક address);
પૂર્ણાંક flashReadSingleSPI(પૂર્ણાંક dummy_cycles, પૂર્ણાંક read_address, પૂર્ણાંક instruction, પૂર્ણાંક data_શબ્દો, પૂર્ણાંક adsize);
પૂર્ણાંક flashReadDualSPI(પૂર્ણાંક address, પૂર્ણાંક data_length);
પૂર્ણાંક flashReadQuadSPI(પૂર્ણાંક dummy_cycles, પૂર્ણાંક read_address, પૂર્ણાંક instruction, પૂર્ણાંક data_શબ્દો, પૂર્ણાંક adsize);
પૂર્ણાંક micron_disable_xip_volatile(પૂર્ણાંક,પૂર્ણાંક);
પૂર્ણાંક flashSingleSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક flashMemInit(શૂન્ય);
પૂર્ણાંક flashDualSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક flashDualSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક flashWriteVolatileConfigReg(પૂર્ણાંક કિંમત);
પૂર્ણાંક flashQuadSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક flashQuadSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr);
પૂર્ણાંક eraseSector(પૂર્ણાંક command, પૂર્ણાંક address);
પૂર્ણાંક micron_volatile_write_enable(પૂર્ણાંક status);
પૂર્ણાંક micron_enable_4byte_addressing(પૂર્ણાંક status);
પૂર્ણાંક micron_configure_xip_volatile(પૂર્ણાંક status, પૂર્ણાંક કિંમત);
પૂર્ણાંક micron_read_configuration_register(પૂર્ણાંક status, પૂર્ણાંક કિંમત);
પૂર્ણાંક micron_read_id_cmd(પૂર્ણાંક status, પૂર્ણાંક કિંમત);
પૂર્ણાંક wait_for_wip(શૂન્ય);
પૂર્ણાંક flashIdentificationDevice(શૂન્ય);
પૂર્ણાંક flashReadFlagRegister(શૂન્ય);
પૂર્ણાંક flashWriteEnable(શૂન્ય);
પૂર્ણાંક flashEnable4ByteAddressingMode(શૂન્ય);
પૂર્ણાંક flash_Write_disable(શૂન્ય);


#endif
