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

#اگر_تعریف_نشده QSPI_H
#تعریف_کن QSPI_H

//#define BOOT
#اگر_تعریف_نشده BOOT

#ضمن<stdlib.h>
#پایان_اگر
#ضمن<stdint.h>

#تعریف_کن DEF_TIMEOUT 60
#تعریف_کن پایه_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#تعریف_کن CR      0x00000100                                                      
#تعریف_کن DCR     0x00000104                                                      
#تعریف_کن SR      0x00000108                                                      
#تعریف_کن FCR     0x0000010c                                                      
#تعریف_کن DLR     0x00000110                                                      
#تعریف_کن CCR     0x00000114                                                      
#تعریف_کن AR      0x00000118                                                      
#تعریف_کن ABR     0x0000011c                                                      
#تعریف_کن DR      0x00000120                                                      
#تعریف_کن PSMKR   0x00000124                                                      
#تعریف_کن PSMAR   0x00000128                                                      
#تعریف_کن PIR     0x0000012c                                                      
#تعریف_کن LPRT    0x00000130                                                      
#تعریف_کن STARTMM 0x90000000                                                      
#تعریف_کن ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#تعریف_کن CR_PRESCALER(x)   (x<<24)
#تعریف_کن CR_PMM            (1<<23)
#تعریف_کن CR_APMS           (1<<22)
#تعریف_کن CR_TOIE           (1<<20)
#تعریف_کن CR_SMIE           (1<<19)
#تعریف_کن CR_FTIE           (1<<18)
#تعریف_کن CR_TCIE           (1<<17)
#تعریف_کن CR_TEIE           (1<<16)
#تعریف_کن CR_FTHRES(x)      (x<<8 )
#تعریف_کن CR_FSEL           (1<<7 )
#تعریف_کن CR_DFM            (1<<6 )
#تعریف_کن CR_SSHIFT         (1<<4 )
#تعریف_کن CR_TCEN           (1<<3 )
#تعریف_کن CR_DMAEN          (1<<2 )
#تعریف_کن CR_ABORT          (1<<1 )
#تعریف_کن CR_EN             (1<<0 )

//Bit vectors for DCR 
#تعریف_کن DCR_FSIZE(x)       (x<<16) 
#تعریف_کن DCR_نما_BYTE(x)   (x<<21)
#تعریف_کن DCR_CSHT(x)        (x<<8 )
#تعریف_کن DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#تعریف_کن SR_FLEVEL(x)      (x<<8) 
#تعریف_کن SR_TOF            (1<<4)
#تعریف_کن SR_SMF            (1<<3)
#تعریف_کن SR_FTF            (1<<2)
#تعریف_کن SR_TCF            (1<<1)
#تعریف_کن SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#تعریف_کن FCR_CTOF (1<<4)
#تعریف_کن FCR_CSMF (1<<3)
#تعریف_کن FCR_CTCF (1<<1)
#تعریف_کن FCR_CTEF (1<<0)

//Bit vectors for DLR
#تعریف_کن DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#تعریف_کن CCR_DDRM                   (1<<31) 
#تعریف_کن CCR_DHHC                   (1<<30)
#تعریف_کن CCR_DUMMY_بیت              (1<<29) // Needed by Micron Flash Memories
#تعریف_کن CCR_SIOO                   (1<<28)
#تعریف_کن CCR_FMODE(x)               (x<<26)
#تعریف_کن CCR_DMODE(x)               (x<<24)
#تعریف_کن CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#تعریف_کن CCR_DCYC(x)                (x<<18)
#تعریف_کن CCR_ABSIZE(x)              (x<<16)
#تعریف_کن CCR_ABMODE(x)              (x<<14)
#تعریف_کن CCR_ADSIZE(x)              (x<<12)
#تعریف_کن CCR_ADMODE(x)              (x<<10)
#تعریف_کن CCR_IMODE(x)               (x<<8 )
#تعریف_کن CCR_INSTRUCTION(x)         (x<<0 )

#تعریف_کن CCR_FMODE_INDWR 0x0
#تعریف_کن CCR_FMODE_INDRD 0x1
#تعریف_کن CCR_FMODE_APOLL 0x2
#تعریف_کن CCR_FMODE_MMAPD 0x3

#تعریف_کن NDATA  0x0
#تعریف_کن SINGLE 0x1
#تعریف_کن DOUBLE 0x2
#تعریف_کن QUAD   0x3

#تعریف_کن BYTE      0x0
#تعریف_کن TWOBYTE   0x1
#تعریف_کن THREEBYTE 0x2
#تعریف_کن FOURBYTE  0x3

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

فراغ مجموعه_qspi_shakti32(صحيح* addr, ثابت صحيح val);
فراغ مجموعه_qspi_shakti16(int16_t* addr, int16_t val);
فراغ مجموعه_qspi_shakti8(حرف* addr, حرف val);
صحيح get_qspi_shakti( صحيح* addr);
صحيح check_fail_بیت(فراغ);
فراغ reset_وقفه_flags(فراغ);
صحيح micron_write_enable(صحيح وضعیت_2);
صحيح flashSingleSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح wait_for_tcf(صحيح وضعیت_2);
فراغ qspi_init(صحيح fsize, صحيح csht, صحيح prescaler, صحيح enable_interrupts, صحيح fthreshold, صحيح ck_نما);
صحيح صفحه_برنامه_Single_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح آدرس);
صحيح صفحه_برنامه_Quad_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح آدرس);
صحيح flashReadSingleSPI(صحيح dummy_چرخهها, صحيح read_آدرس, صحيح instruction, صحيح داده_واژگان, صحيح adsize);
صحيح flashReadDualSPI(صحيح آدرس, صحيح داده_درازی);
صحيح flashReadQuadSPI(صحيح dummy_چرخهها, صحيح read_آدرس, صحيح instruction, صحيح داده_واژگان, صحيح adsize);
صحيح micron_disable_xip_volatile(صحيح,صحيح);
صحيح flashSingleSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashMemInit(فراغ);
صحيح flashDualSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashDualSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح flashWriteVolatileConfigReg(صحيح مقدار);
صحيح flashQuadSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashQuadSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح eraseSector(صحيح command, صحيح آدرس);
صحيح micron_volatile_write_enable(صحيح وضعیت_2);
صحيح micron_enable_4byte_addressing(صحيح وضعیت_2);
صحيح micron_configure_xip_volatile(صحيح وضعیت_2, صحيح مقدار);
صحيح micron_read_configuration_ثبات(صحيح وضعیت_2, صحيح مقدار);
صحيح micron_read_id_cmd(صحيح وضعیت_2, صحيح مقدار);
صحيح wait_for_wip(فراغ);
صحيح flashIdentificationDevice(فراغ);
صحيح flash_Read_Flag_ثبات(فراغ);
صحيح flashWriteEnable(فراغ);
صحيح flash_Enable4_Byte_Addressing_نما(فراغ);
صحيح flash_Write_disable(فراغ);


#پایان_اگر
