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

#جيڪڏهن_وصف_نه_ٿيل QSPI_H
#وصف_ڪريو QSPI_H

//#define BOOT
#جيڪڏهن_وصف_نه_ٿيل BOOT

#ضمن<stdlib.h>
#جيڪڏهن_پورو
#ضمن<stdint.h>

#وصف_ڪريو DEF_TIMEOUT 60
#وصف_ڪريو بنياد_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#وصف_ڪريو CR      0x00000100                                                      
#وصف_ڪريو DCR     0x00000104                                                      
#وصف_ڪريو SR      0x00000108                                                      
#وصف_ڪريو FCR     0x0000010c                                                      
#وصف_ڪريو DLR     0x00000110                                                      
#وصف_ڪريو CCR     0x00000114                                                      
#وصف_ڪريو AR      0x00000118                                                      
#وصف_ڪريو ABR     0x0000011c                                                      
#وصف_ڪريو DR      0x00000120                                                      
#وصف_ڪريو PSMKR   0x00000124                                                      
#وصف_ڪريو PSMAR   0x00000128                                                      
#وصف_ڪريو PIR     0x0000012c                                                      
#وصف_ڪريو LPRT    0x00000130                                                      
#وصف_ڪريو STARTMM 0x90000000                                                      
#وصف_ڪريو ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#وصف_ڪريو CR_PRESCALER(x)   (x<<24)
#وصف_ڪريو CR_PMM            (1<<23)
#وصف_ڪريو CR_APMS           (1<<22)
#وصف_ڪريو CR_TOIE           (1<<20)
#وصف_ڪريو CR_SMIE           (1<<19)
#وصف_ڪريو CR_FTIE           (1<<18)
#وصف_ڪريو CR_TCIE           (1<<17)
#وصف_ڪريو CR_TEIE           (1<<16)
#وصف_ڪريو CR_FTHRES(x)      (x<<8 )
#وصف_ڪريو CR_FSEL           (1<<7 )
#وصف_ڪريو CR_DFM            (1<<6 )
#وصف_ڪريو CR_SSHIFT         (1<<4 )
#وصف_ڪريو CR_TCEN           (1<<3 )
#وصف_ڪريو CR_DMAEN          (1<<2 )
#وصف_ڪريو CR_ABORT          (1<<1 )
#وصف_ڪريو CR_EN             (1<<0 )

//Bit vectors for DCR 
#وصف_ڪريو DCR_FSIZE(x)       (x<<16) 
#وصف_ڪريو DCR_گهڻائي_BYTE(x)   (x<<21)
#وصف_ڪريو DCR_CSHT(x)        (x<<8 )
#وصف_ڪريو DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#وصف_ڪريو SR_FLEVEL(x)      (x<<8) 
#وصف_ڪريو SR_TOF            (1<<4)
#وصف_ڪريو SR_SMF            (1<<3)
#وصف_ڪريو SR_FTF            (1<<2)
#وصف_ڪريو SR_TCF            (1<<1)
#وصف_ڪريو SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#وصف_ڪريو FCR_CTOF (1<<4)
#وصف_ڪريو FCR_CSMF (1<<3)
#وصف_ڪريو FCR_CTCF (1<<1)
#وصف_ڪريو FCR_CTEF (1<<0)

//Bit vectors for DLR
#وصف_ڪريو DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#وصف_ڪريو CCR_DDRM                   (1<<31) 
#وصف_ڪريو CCR_DHHC                   (1<<30)
#وصف_ڪريو CCR_DUMMY_ٻٽو_انگ              (1<<29) // Needed by Micron Flash Memories
#وصف_ڪريو CCR_SIOO                   (1<<28)
#وصف_ڪريو CCR_FMODE(x)               (x<<26)
#وصف_ڪريو CCR_DMODE(x)               (x<<24)
#وصف_ڪريو CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#وصف_ڪريو CCR_DCYC(x)                (x<<18)
#وصف_ڪريو CCR_ABSIZE(x)              (x<<16)
#وصف_ڪريو CCR_ABMODE(x)              (x<<14)
#وصف_ڪريو CCR_ADSIZE(x)              (x<<12)
#وصف_ڪريو CCR_ADMODE(x)              (x<<10)
#وصف_ڪريو CCR_IMODE(x)               (x<<8 )
#وصف_ڪريو CCR_INSTRUCTION(x)         (x<<0 )

#وصف_ڪريو CCR_FMODE_INDWR 0x0
#وصف_ڪريو CCR_FMODE_INDRD 0x1
#وصف_ڪريو CCR_FMODE_APOLL 0x2
#وصف_ڪريو CCR_FMODE_MMAPD 0x3

#وصف_ڪريو NDATA  0x0
#وصف_ڪريو SINGLE 0x1
#وصف_ڪريو DOUBLE 0x2
#وصف_ڪريو QUAD   0x3

#وصف_ڪريو BYTE      0x0
#وصف_ڪريو TWOBYTE   0x1
#وصف_ڪريو THREEBYTE 0x2
#وصف_ڪريو FOURBYTE  0x3

خارجي صحيح* cr      ;
 خارجي صحيح* dcr    ;
 خارجي صحيح* sr     ; 
 خارجي صحيح* fcr    ;
 خارجي صحيح* ccr    ;
 خارجي صحيح* ar     ; 
 خارجي صحيح* abr    ;
 خارجي صحيح* dr     ; 
 خارجي صحيح* dlr    ;
 خارجي صحيح* psmkr  ;
 خارجي صحيح* pir    ;
 خارجي صحيح* lprt   ;
 خارجي صحيح* startmm;
 خارجي صحيح* endmm ;

فراغ سيٽ_qspi_shakti32(صحيح* addr, ثابت صحيح val);
فراغ سيٽ_qspi_shakti16(int16_t* addr, int16_t val);
فراغ سيٽ_qspi_shakti8(حرف* addr, حرف val);
صحيح get_qspi_shakti( صحيح* addr);
صحيح check_fail_ٻٽو_انگ(فراغ);
فراغ reset_مداخلت_flags(فراغ);
صحيح micron_write_enable(صحيح حالت_2);
صحيح flashSingleSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح wait_for_tcf(صحيح حالت_2);
فراغ qspi_init(صحيح fsize, صحيح csht, صحيح prescaler, صحيح enable_interrupts, صحيح fthreshold, صحيح ck_گهڻائي);
صحيح صفحو_پروگرام_Single_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پتو);
صحيح صفحو_پروگرام_Quad_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پتو);
صحيح flashReadSingleSPI(صحيح dummy_چڪرن, صحيح read_پتو, صحيح instruction, صحيح معلومات_لفظ, صحيح adsize);
صحيح flashReadDualSPI(صحيح پتو, صحيح معلومات_ڊيگهائي);
صحيح flashReadQuadSPI(صحيح dummy_چڪرن, صحيح read_پتو, صحيح instruction, صحيح معلومات_لفظ, صحيح adsize);
صحيح micron_disable_xip_volatile(صحيح,صحيح);
صحيح flashSingleSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashMemInit(فراغ);
صحيح flashDualSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashDualSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح flashWriteVolatileConfigReg(صحيح قدر);
صحيح flashQuadSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashQuadSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح eraseSector(صحيح command, صحيح پتو);
صحيح micron_volatile_write_enable(صحيح حالت_2);
صحيح micron_enable_4byte_addressing(صحيح حالت_2);
صحيح micron_configure_xip_volatile(صحيح حالت_2, صحيح قدر);
صحيح micron_read_configuration_رجسٽر(صحيح حالت_2, صحيح قدر);
صحيح micron_read_id_cmd(صحيح حالت_2, صحيح قدر);
صحيح wait_for_wip(فراغ);
صحيح flashIdentificationDevice(فراغ);
صحيح flash_Read_Flag_رجسٽر(فراغ);
صحيح flashWriteEnable(فراغ);
صحيح flash_Enable4_Byte_Addressing_گهڻائي(فراغ);
صحيح flash_Write_disable(فراغ);


#جيڪڏهن_پورو
