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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ QSPI_H
#ವ್ಯಾಖ್ಯಾನಿಸು QSPI_H

//#define BOOT
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ BOOT

#ಅನ್ತರ್ಭಾವ<stdlib.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ<stdint.h>

#ವ್ಯಾಖ್ಯಾನಿಸು DEF_TIMEOUT 60
#ವ್ಯಾಖ್ಯಾನಿಸು ತಳ_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#ವ್ಯಾಖ್ಯಾನಿಸು CR      0x00000100                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು DCR     0x00000104                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು SR      0x00000108                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು FCR     0x0000010c                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು DLR     0x00000110                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು CCR     0x00000114                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು AR      0x00000118                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು ABR     0x0000011c                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು DR      0x00000120                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು PSMKR   0x00000124                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು PSMAR   0x00000128                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು PIR     0x0000012c                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು LPRT    0x00000130                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು STARTMM 0x90000000                                                      
#ವ್ಯಾಖ್ಯಾನಿಸು ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#ವ್ಯಾಖ್ಯಾನಿಸು CR_PRESCALER(x)   (x<<24)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_PMM            (1<<23)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_APMS           (1<<22)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_TOIE           (1<<20)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_SMIE           (1<<19)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_FTIE           (1<<18)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_TCIE           (1<<17)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_TEIE           (1<<16)
#ವ್ಯಾಖ್ಯಾನಿಸು CR_FTHRES(x)      (x<<8 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_FSEL           (1<<7 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_DFM            (1<<6 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_SSHIFT         (1<<4 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_TCEN           (1<<3 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_DMAEN          (1<<2 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_ABORT          (1<<1 )
#ವ್ಯಾಖ್ಯಾನಿಸು CR_EN             (1<<0 )

//Bit vectors for DCR 
#ವ್ಯಾಖ್ಯಾನಿಸು DCR_FSIZE(x)       (x<<16) 
#ವ್ಯಾಖ್ಯಾನಿಸು DCR_ಬಹುಲಕ_BYTE(x)   (x<<21)
#ವ್ಯಾಖ್ಯಾನಿಸು DCR_CSHT(x)        (x<<8 )
#ವ್ಯಾಖ್ಯಾನಿಸು DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#ವ್ಯಾಖ್ಯಾನಿಸು SR_FLEVEL(x)      (x<<8) 
#ವ್ಯಾಖ್ಯಾನಿಸು SR_TOF            (1<<4)
#ವ್ಯಾಖ್ಯಾನಿಸು SR_SMF            (1<<3)
#ವ್ಯಾಖ್ಯಾನಿಸು SR_FTF            (1<<2)
#ವ್ಯಾಖ್ಯಾನಿಸು SR_TCF            (1<<1)
#ವ್ಯಾಖ್ಯಾನಿಸು SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#ವ್ಯಾಖ್ಯಾನಿಸು FCR_CTOF (1<<4)
#ವ್ಯಾಖ್ಯಾನಿಸು FCR_CSMF (1<<3)
#ವ್ಯಾಖ್ಯಾನಿಸು FCR_CTCF (1<<1)
#ವ್ಯಾಖ್ಯಾನಿಸು FCR_CTEF (1<<0)

//Bit vectors for DLR
#ವ್ಯಾಖ್ಯಾನಿಸು DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DDRM                   (1<<31) 
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DHHC                   (1<<30)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DUMMY_ಬಿಟ್              (1<<29) // Needed by Micron Flash Memories
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_SIOO                   (1<<28)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_FMODE(x)               (x<<26)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DMODE(x)               (x<<24)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_DCYC(x)                (x<<18)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_ABSIZE(x)              (x<<16)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_ABMODE(x)              (x<<14)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_ADSIZE(x)              (x<<12)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_ADMODE(x)              (x<<10)
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_IMODE(x)               (x<<8 )
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_INSTRUCTION(x)         (x<<0 )

#ವ್ಯಾಖ್ಯಾನಿಸು CCR_FMODE_INDWR 0x0
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_FMODE_INDRD 0x1
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_FMODE_APOLL 0x2
#ವ್ಯಾಖ್ಯಾನಿಸು CCR_FMODE_MMAPD 0x3

#ವ್ಯಾಖ್ಯಾನಿಸು NDATA  0x0
#ವ್ಯಾಖ್ಯಾನಿಸು SINGLE 0x1
#ವ್ಯಾಖ್ಯಾನಿಸು DOUBLE 0x2
#ವ್ಯಾಖ್ಯಾನಿಸು QUAD   0x3

#ವ್ಯಾಖ್ಯಾನಿಸು BYTE      0x0
#ವ್ಯಾಖ್ಯಾನಿಸು TWOBYTE   0x1
#ವ್ಯಾಖ್ಯಾನಿಸು THREEBYTE 0x2
#ವ್ಯಾಖ್ಯಾನಿಸು FOURBYTE  0x3

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* cr      ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* dcr    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* sr     ; 
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* fcr    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* ccr    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* ar     ; 
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* abr    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* dr     ; 
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* dlr    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* psmkr  ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* pir    ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* lprt   ;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* startmm;
 ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ* endmm ;

ಶೂನ್ಯ ಗಣ_qspi_shakti32(ಪೂರ್ಣಾಂಕ* addr, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ val);
ಶೂನ್ಯ ಗಣ_qspi_shakti16(int16_t* addr, int16_t val);
ಶೂನ್ಯ ಗಣ_qspi_shakti8(ಅಕ್ಷರ* addr, ಅಕ್ಷರ val);
ಪೂರ್ಣಾಂಕ get_qspi_shakti( ಪೂರ್ಣಾಂಕ* addr);
ಪೂರ್ಣಾಂಕ check_fail_ಬಿಟ್(ಶೂನ್ಯ);
ಶೂನ್ಯ reset_ಅಡಚಣೆ_flags(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ micron_write_enable(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3);
ಪೂರ್ಣಾಂಕ flashSingleSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ wait_for_tcf(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3);
ಶೂನ್ಯ qspi_init(ಪೂರ್ಣಾಂಕ fsize, ಪೂರ್ಣಾಂಕ csht, ಪೂರ್ಣಾಂಕ prescaler, ಪೂರ್ಣಾಂಕ enable_interrupts, ಪೂರ್ಣಾಂಕ fthreshold, ಪೂರ್ಣಾಂಕ ck_ಬಹುಲಕ);
ಪೂರ್ಣಾಂಕ ಪುಟ_ಕಾರ್ಯಕ್ರಮ_Single_SPI(ಪೂರ್ಣಾಂಕ value1, ಪೂರ್ಣಾಂಕ value2, ಪೂರ್ಣಾಂಕ value3, ಪೂರ್ಣಾಂಕ value4, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ ಪುಟ_ಕಾರ್ಯಕ್ರಮ_Quad_SPI(ಪೂರ್ಣಾಂಕ value1, ಪೂರ್ಣಾಂಕ value2, ಪೂರ್ಣಾಂಕ value3, ಪೂರ್ಣಾಂಕ value4, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ flashReadSingleSPI(ಪೂರ್ಣಾಂಕ dummy_ಚಕ್ರಗಳು, ಪೂರ್ಣಾಂಕ read_ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ instruction, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಪದಗಳು, ಪೂರ್ಣಾಂಕ adsize);
ಪೂರ್ಣಾಂಕ flashReadDualSPI(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಉದ್ದಳತೆ);
ಪೂರ್ಣಾಂಕ flashReadQuadSPI(ಪೂರ್ಣಾಂಕ dummy_ಚಕ್ರಗಳು, ಪೂರ್ಣಾಂಕ read_ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ instruction, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಪದಗಳು, ಪೂರ್ಣಾಂಕ adsize);
ಪೂರ್ಣಾಂಕ micron_disable_xip_volatile(ಪೂರ್ಣಾಂಕ,ಪೂರ್ಣಾಂಕ);
ಪೂರ್ಣಾಂಕ flashSingleSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ flashMemInit(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flashDualSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ flashDualSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ flashWriteVolatileConfigReg(ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ flashQuadSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ flashQuadSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr);
ಪೂರ್ಣಾಂಕ eraseSector(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ micron_volatile_write_enable(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3);
ಪೂರ್ಣಾಂಕ micron_enable_4byte_addressing(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3);
ಪೂರ್ಣಾಂಕ micron_configure_xip_volatile(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ micron_read_configuration_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ micron_read_id_cmd(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ wait_for_wip(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flashIdentificationDevice(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_Read_Flag_ರಿಜಿಸ್ಟರ್(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flashWriteEnable(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_Enable4_Byte_Addressing_ಬಹುಲಕ(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_Write_disable(ಶೂನ್ಯ);


#ಆದರೆ_ಅಂತ್ಯ
