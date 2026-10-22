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

#جے_بنا_تعریف QSPI_H
#تعریف_کرو QSPI_H

//#define BOOT
#جے_بنا_تعریف BOOT

#ضمن<stdlib.h>
#جے_انت
#ضمن<stdint.h>

#تعریف_کرو DEF_TIMEOUT 60
#تعریف_کرو ادھار_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#تعریف_کرو CR      0x00000100                                                      
#تعریف_کرو DCR     0x00000104                                                      
#تعریف_کرو SR      0x00000108                                                      
#تعریف_کرو FCR     0x0000010c                                                      
#تعریف_کرو DLR     0x00000110                                                      
#تعریف_کرو CCR     0x00000114                                                      
#تعریف_کرو AR      0x00000118                                                      
#تعریف_کرو ABR     0x0000011c                                                      
#تعریف_کرو DR      0x00000120                                                      
#تعریف_کرو PSMKR   0x00000124                                                      
#تعریف_کرو PSMAR   0x00000128                                                      
#تعریف_کرو PIR     0x0000012c                                                      
#تعریف_کرو LPRT    0x00000130                                                      
#تعریف_کرو STARTMM 0x90000000                                                      
#تعریف_کرو ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#تعریف_کرو CR_PRESCALER(x)   (x<<24)
#تعریف_کرو CR_PMM            (1<<23)
#تعریف_کرو CR_APMS           (1<<22)
#تعریف_کرو CR_TOIE           (1<<20)
#تعریف_کرو CR_SMIE           (1<<19)
#تعریف_کرو CR_FTIE           (1<<18)
#تعریف_کرو CR_TCIE           (1<<17)
#تعریف_کرو CR_TEIE           (1<<16)
#تعریف_کرو CR_FTHRES(x)      (x<<8 )
#تعریف_کرو CR_FSEL           (1<<7 )
#تعریف_کرو CR_DFM            (1<<6 )
#تعریف_کرو CR_SSHIFT         (1<<4 )
#تعریف_کرو CR_TCEN           (1<<3 )
#تعریف_کرو CR_DMAEN          (1<<2 )
#تعریف_کرو CR_ABORT          (1<<1 )
#تعریف_کرو CR_EN             (1<<0 )

//Bit vectors for DCR 
#تعریف_کرو DCR_FSIZE(x)       (x<<16) 
#تعریف_کرو DCR_منوال_BYTE(x)   (x<<21)
#تعریف_کرو DCR_CSHT(x)        (x<<8 )
#تعریف_کرو DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#تعریف_کرو SR_FLEVEL(x)      (x<<8) 
#تعریف_کرو SR_TOF            (1<<4)
#تعریف_کرو SR_SMF            (1<<3)
#تعریف_کرو SR_FTF            (1<<2)
#تعریف_کرو SR_TCF            (1<<1)
#تعریف_کرو SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#تعریف_کرو FCR_CTOF (1<<4)
#تعریف_کرو FCR_CSMF (1<<3)
#تعریف_کرو FCR_CTCF (1<<1)
#تعریف_کرو FCR_CTEF (1<<0)

//Bit vectors for DLR
#تعریف_کرو DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#تعریف_کرو CCR_DDRM                   (1<<31) 
#تعریف_کرو CCR_DHHC                   (1<<30)
#تعریف_کرو CCR_DUMMY_ثنائی_ہندسہ              (1<<29) // Needed by Micron Flash Memories
#تعریف_کرو CCR_SIOO                   (1<<28)
#تعریف_کرو CCR_FMODE(x)               (x<<26)
#تعریف_کرو CCR_DMODE(x)               (x<<24)
#تعریف_کرو CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#تعریف_کرو CCR_DCYC(x)                (x<<18)
#تعریف_کرو CCR_ABSIZE(x)              (x<<16)
#تعریف_کرو CCR_ABMODE(x)              (x<<14)
#تعریف_کرو CCR_ADSIZE(x)              (x<<12)
#تعریف_کرو CCR_ADMODE(x)              (x<<10)
#تعریف_کرو CCR_IMODE(x)               (x<<8 )
#تعریف_کرو CCR_INSTRUCTION(x)         (x<<0 )

#تعریف_کرو CCR_FMODE_INDWR 0x0
#تعریف_کرو CCR_FMODE_INDRD 0x1
#تعریف_کرو CCR_FMODE_APOLL 0x2
#تعریف_کرو CCR_FMODE_MMAPD 0x3

#تعریف_کرو NDATA  0x0
#تعریف_کرو SINGLE 0x1
#تعریف_کرو DOUBLE 0x2
#تعریف_کرو QUAD   0x3

#تعریف_کرو BYTE      0x0
#تعریف_کرو TWOBYTE   0x1
#تعریف_کرو THREEBYTE 0x2
#تعریف_کرو FOURBYTE  0x3

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

فراغ سیٹ_qspi_shakti32(صحيح* addr, ثابت صحيح val);
فراغ سیٹ_qspi_shakti16(int16_t* addr, int16_t val);
فراغ سیٹ_qspi_shakti8(حرف* addr, حرف val);
صحيح get_qspi_shakti( صحيح* addr);
صحيح check_fail_ثنائی_ہندسہ(فراغ);
فراغ reset_رکاوٹ_flags(فراغ);
صحيح micron_write_enable(صحيح حالت_2);
صحيح flashSingleSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح wait_for_tcf(صحيح حالت_2);
فراغ qspi_init(صحيح fsize, صحيح csht, صحيح prescaler, صحيح enable_interrupts, صحيح fthreshold, صحيح ck_منوال);
صحيح ورقہ_پروگرام_Single_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پتہ);
صحيح ورقہ_پروگرام_Quad_SPI(صحيح value1, صحيح value2, صحيح value3, صحيح value4, صحيح پتہ);
صحيح flashReadSingleSPI(صحيح dummy_چکراں, صحيح read_پتہ, صحيح instruction, صحيح انکڑے_الفاظ, صحيح adsize);
صحيح flashReadDualSPI(صحيح پتہ, صحيح انکڑے_لمائی);
صحيح flashReadQuadSPI(صحيح dummy_چکراں, صحيح read_پتہ, صحيح instruction, صحيح انکڑے_الفاظ, صحيح adsize);
صحيح micron_disable_xip_volatile(صحيح,صحيح);
صحيح flashSingleSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashMemInit(فراغ);
صحيح flashDualSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashDualSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح flashWriteVolatileConfigReg(صحيح قدر);
صحيح flashQuadSPIXip(صحيح addr, صحيح* dest_addr);
صحيح flashQuadSPIDDRXip(صحيح addr, صحيح* dest_addr);
صحيح eraseSector(صحيح command, صحيح پتہ);
صحيح micron_volatile_write_enable(صحيح حالت_2);
صحيح micron_enable_4byte_addressing(صحيح حالت_2);
صحيح micron_configure_xip_volatile(صحيح حالت_2, صحيح قدر);
صحيح micron_read_configuration_رجسٹر(صحيح حالت_2, صحيح قدر);
صحيح micron_read_id_cmd(صحيح حالت_2, صحيح قدر);
صحيح wait_for_wip(فراغ);
صحيح flashIdentificationDevice(فراغ);
صحيح flash_Read_Flag_رجسٹر(فراغ);
صحيح flashWriteEnable(فراغ);
صحيح flash_Enable4_Byte_Addressing_منوال(فراغ);
صحيح flash_Write_disable(فراغ);


#جے_انت
