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

#که_نه_تعریف_شوی QSPI_H
#تعریف_کړه QSPI_H

//#define BOOT
#که_نه_تعریف_شوی BOOT

#ضمن<stdlib.h>
#د_که_پای
#ضمن<stdint.h>

#تعریف_کړه DEF_TIMEOUT 60
#تعریف_کړه بنسټ_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#تعریف_کړه CR      0x00000100                                                      
#تعریف_کړه DCR     0x00000104                                                      
#تعریف_کړه SR      0x00000108                                                      
#تعریف_کړه FCR     0x0000010c                                                      
#تعریف_کړه DLR     0x00000110                                                      
#تعریف_کړه CCR     0x00000114                                                      
#تعریف_کړه AR      0x00000118                                                      
#تعریف_کړه ABR     0x0000011c                                                      
#تعریف_کړه DR      0x00000120                                                      
#تعریف_کړه PSMKR   0x00000124                                                      
#تعریف_کړه PSMAR   0x00000128                                                      
#تعریف_کړه PIR     0x0000012c                                                      
#تعریف_کړه LPRT    0x00000130                                                      
#تعریف_کړه STARTMM 0x90000000                                                      
#تعریف_کړه ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#تعریف_کړه CR_PRESCALER(x)   (x<<24)
#تعریف_کړه CR_PMM            (1<<23)
#تعریف_کړه CR_APMS           (1<<22)
#تعریف_کړه CR_TOIE           (1<<20)
#تعریف_کړه CR_SMIE           (1<<19)
#تعریف_کړه CR_FTIE           (1<<18)
#تعریف_کړه CR_TCIE           (1<<17)
#تعریف_کړه CR_TEIE           (1<<16)
#تعریف_کړه CR_FTHRES(x)      (x<<8 )
#تعریف_کړه CR_FSEL           (1<<7 )
#تعریف_کړه CR_DFM            (1<<6 )
#تعریف_کړه CR_SSHIFT         (1<<4 )
#تعریف_کړه CR_TCEN           (1<<3 )
#تعریف_کړه CR_DMAEN          (1<<2 )
#تعریف_کړه CR_ABORT          (1<<1 )
#تعریف_کړه CR_EN             (1<<0 )

//Bit vectors for DCR 
#تعریف_کړه DCR_FSIZE(x)       (x<<16) 
#تعریف_کړه DCR_ډېرپېښ_BYTE(x)   (x<<21)
#تعریف_کړه DCR_CSHT(x)        (x<<8 )
#تعریف_کړه DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#تعریف_کړه SR_FLEVEL(x)      (x<<8) 
#تعریف_کړه SR_TOF            (1<<4)
#تعریف_کړه SR_SMF            (1<<3)
#تعریف_کړه SR_FTF            (1<<2)
#تعریف_کړه SR_TCF            (1<<1)
#تعریف_کړه SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#تعریف_کړه FCR_CTOF (1<<4)
#تعریف_کړه FCR_CSMF (1<<3)
#تعریف_کړه FCR_CTCF (1<<1)
#تعریف_کړه FCR_CTEF (1<<0)

//Bit vectors for DLR
#تعریف_کړه DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#تعریف_کړه CCR_DDRM                   (1<<31) 
#تعریف_کړه CCR_DHHC                   (1<<30)
#تعریف_کړه CCR_DUMMY_بټ              (1<<29) // Needed by Micron Flash Memories
#تعریف_کړه CCR_SIOO                   (1<<28)
#تعریف_کړه CCR_FMODE(x)               (x<<26)
#تعریف_کړه CCR_DMODE(x)               (x<<24)
#تعریف_کړه CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#تعریف_کړه CCR_DCYC(x)                (x<<18)
#تعریف_کړه CCR_ABSIZE(x)              (x<<16)
#تعریف_کړه CCR_ABMODE(x)              (x<<14)
#تعریف_کړه CCR_ADSIZE(x)              (x<<12)
#تعریف_کړه CCR_ADMODE(x)              (x<<10)
#تعریف_کړه CCR_IMODE(x)               (x<<8 )
#تعریف_کړه CCR_INSTRUCTION(x)         (x<<0 )

#تعریف_کړه CCR_FMODE_INDWR 0x0
#تعریف_کړه CCR_FMODE_INDRD 0x1
#تعریف_کړه CCR_FMODE_APOLL 0x2
#تعریف_کړه CCR_FMODE_MMAPD 0x3

#تعریف_کړه NDATA  0x0
#تعریف_کړه SINGLE 0x1
#تعریف_کړه DOUBLE 0x2
#تعریف_کړه QUAD   0x3

#تعریف_کړه BYTE      0x0
#تعریف_کړه TWOBYTE   0x1
#تعریف_کړه THREEBYTE 0x2
#تعریف_کړه FOURBYTE  0x3

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

فراغ سېټ_qspi_shakti32(صحيح* addr, ثابت صحيح val);
فراغ سېټ_qspi_shakti16(int16_t* addr, int16_t val);
فراغ سېټ_qspi_shakti8(حرف* addr, حرف val);
صحيح get_qspi_shakti( صحيح* addr);
صحيح check_fail_بټ(فراغ);
فراغ reset_مداخله_flags(فراغ);
صحيح micron_write_enable(صحيح حالت_2);
صحيح flashSingleSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح wait_for_tcf(صحيح حالت_2);
فراغ qspi_init(صحيح fsize, صحيح csht, صحيح prescaler, صحيح enable_interrupts, صحيح fthreshold, صحيح ck_ډېرپېښ);
صحيح پاڼه_پروګرام_Single_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پته);
صحيح پاڼه_پروګرام_Quad_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پته);
صحيح flashReadSingleSPI(صحيح dummy_دورې, صحيح read_پته, صحيح instruction, صحيح معلومات_ټکي, صحيح adsize);
صحيح flashReadDualSPI(صحيح پته, صحيح معلومات_اوږدتیا);
صحيح flashReadQuadSPI(صحيح dummy_دورې, صحيح read_پته, صحيح instruction, صحيح معلومات_ټکي, صحيح adsize);
صحيح micron_disable_xip_volatile(صحيح,صحيح);
صحيح flashSingleSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashMemInit(فراغ);
صحيح flashDualSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashDualSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح flashWriteVolatileConfigReg(صحيح ارزښت);
صحيح flashQuadSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashQuadSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح eraseSector(صحيح command, صحيح پته);
صحيح micron_volatile_write_enable(صحيح حالت_2);
صحيح micron_enable_4byte_addressing(صحيح حالت_2);
صحيح micron_configure_xip_volatile(صحيح حالت_2, صحيح ارزښت);
صحيح micron_read_configuration_ثبتوونکی(صحيح حالت_2, صحيح ارزښت);
صحيح micron_read_id_cmd(صحيح حالت_2, صحيح ارزښت);
صحيح wait_for_wip(فراغ);
صحيح flashIdentificationDevice(فراغ);
صحيح flash_Read_Flag_ثبتوونکی(فراغ);
صحيح flashWriteEnable(فراغ);
صحيح flash_Enable4_Byte_Addressing_ډېرپېښ(فراغ);
صحيح flash_Write_disable(فراغ);


#د_که_پای
