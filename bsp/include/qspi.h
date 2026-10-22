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

#यदि_अपरिभाषितम् QSPI_H
#परिभाषय QSPI_H

//#define BOOT
#यदि_अपरिभाषितम् BOOT

#अन्तर्भाव<stdlib.h>
#यदि_अन्तः
#अन्तर्भाव<stdint.h>

#परिभाषय DEF_TIMEOUT 60
#परिभाषय आधारः_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#परिभाषय CR      0x00000100                                                      
#परिभाषय DCR     0x00000104                                                      
#परिभाषय SR      0x00000108                                                      
#परिभाषय FCR     0x0000010c                                                      
#परिभाषय DLR     0x00000110                                                      
#परिभाषय CCR     0x00000114                                                      
#परिभाषय AR      0x00000118                                                      
#परिभाषय ABR     0x0000011c                                                      
#परिभाषय DR      0x00000120                                                      
#परिभाषय PSMKR   0x00000124                                                      
#परिभाषय PSMAR   0x00000128                                                      
#परिभाषय PIR     0x0000012c                                                      
#परिभाषय LPRT    0x00000130                                                      
#परिभाषय STARTMM 0x90000000                                                      
#परिभाषय ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#परिभाषय CR_PRESCALER(x)   (x<<24)
#परिभाषय CR_PMM            (1<<23)
#परिभाषय CR_APMS           (1<<22)
#परिभाषय CR_TOIE           (1<<20)
#परिभाषय CR_SMIE           (1<<19)
#परिभाषय CR_FTIE           (1<<18)
#परिभाषय CR_TCIE           (1<<17)
#परिभाषय CR_TEIE           (1<<16)
#परिभाषय CR_FTHRES(x)      (x<<8 )
#परिभाषय CR_FSEL           (1<<7 )
#परिभाषय CR_DFM            (1<<6 )
#परिभाषय CR_SSHIFT         (1<<4 )
#परिभाषय CR_TCEN           (1<<3 )
#परिभाषय CR_DMAEN          (1<<2 )
#परिभाषय CR_ABORT          (1<<1 )
#परिभाषय CR_EN             (1<<0 )

//Bit vectors for DCR 
#परिभाषय DCR_FSIZE(x)       (x<<16) 
#परिभाषय DCR_बहुलकम्_BYTE(x)   (x<<21)
#परिभाषय DCR_CSHT(x)        (x<<8 )
#परिभाषय DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#परिभाषय SR_FLEVEL(x)      (x<<8) 
#परिभाषय SR_TOF            (1<<4)
#परिभाषय SR_SMF            (1<<3)
#परिभाषय SR_FTF            (1<<2)
#परिभाषय SR_TCF            (1<<1)
#परिभाषय SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#परिभाषय FCR_CTOF (1<<4)
#परिभाषय FCR_CSMF (1<<3)
#परिभाषय FCR_CTCF (1<<1)
#परिभाषय FCR_CTEF (1<<0)

//Bit vectors for DLR
#परिभाषय DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#परिभाषय CCR_DDRM                   (1<<31) 
#परिभाषय CCR_DHHC                   (1<<30)
#परिभाषय CCR_DUMMY_BIT              (1<<29) // Needed by Micron Flash Memories
#परिभाषय CCR_SIOO                   (1<<28)
#परिभाषय CCR_FMODE(x)               (x<<26)
#परिभाषय CCR_DMODE(x)               (x<<24)
#परिभाषय CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#परिभाषय CCR_DCYC(x)                (x<<18)
#परिभाषय CCR_ABSIZE(x)              (x<<16)
#परिभाषय CCR_ABMODE(x)              (x<<14)
#परिभाषय CCR_ADSIZE(x)              (x<<12)
#परिभाषय CCR_ADMODE(x)              (x<<10)
#परिभाषय CCR_IMODE(x)               (x<<8 )
#परिभाषय CCR_INSTRUCTION(x)         (x<<0 )

#परिभाषय CCR_FMODE_INDWR 0x0
#परिभाषय CCR_FMODE_INDRD 0x1
#परिभाषय CCR_FMODE_APOLL 0x2
#परिभाषय CCR_FMODE_MMAPD 0x3

#परिभाषय NDATA  0x0
#परिभाषय SINGLE 0x1
#परिभाषय DOUBLE 0x2
#परिभाषय QUAD   0x3

#परिभाषय BYTE      0x0
#परिभाषय TWOBYTE   0x1
#परिभाषय THREEBYTE 0x2
#परिभाषय FOURBYTE  0x3

बाह्य पूर्णाङ्क* cr      ;
 बाह्य पूर्णाङ्क* dcr    ;
 बाह्य पूर्णाङ्क* sr     ; 
 बाह्य पूर्णाङ्क* fcr    ;
 बाह्य पूर्णाङ्क* ccr    ;
 बाह्य पूर्णाङ्क* ar     ; 
 बाह्य पूर्णाङ्क* abr    ;
 बाह्य पूर्णाङ्क* dr     ; 
 बाह्य पूर्णाङ्क* dlr    ;
 बाह्य पूर्णाङ्क* psmkr  ;
 बाह्य पूर्णाङ्क* pir    ;
 बाह्य पूर्णाङ्क* lprt   ;
 बाह्य पूर्णाङ्क* startmm;
 बाह्य पूर्णाङ्क* endmm ;

शून्य समुच्चयः_qspi_shakti32(पूर्णाङ्क* addr, ध्रुव पूर्णाङ्क val);
शून्य समुच्चयः_qspi_shakti16(int16_t* addr, int16_t val);
शून्य समुच्चयः_qspi_shakti8(वर्ण* addr, वर्ण val);
पूर्णाङ्क get_qspi_shakti( पूर्णाङ्क* addr);
पूर्णाङ्क check_fail_bit(शून्य);
शून्य reset_व्यवधानम्_flags(शून्य);
पूर्णाङ्क micron_write_enable(पूर्णाङ्क स्थितिः_2);
पूर्णाङ्क flashSingleSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क wait_for_tcf(पूर्णाङ्क स्थितिः_2);
शून्य qspi_init(पूर्णाङ्क fsize, पूर्णाङ्क csht, पूर्णाङ्क prescaler, पूर्णाङ्क enable_interrupts, पूर्णाङ्क fthreshold, पूर्णाङ्क ck_बहुलकम्);
पूर्णाङ्क page_क्रमादेशः_Single_SPI(पूर्णाङ्क value1, पूर्णाङ्क value2, पूर्णाङ्क value3, पूर्णाङ्क value4, पूर्णाङ्क स्थानाङ्कः);
पूर्णाङ्क page_क्रमादेशः_Quad_SPI(पूर्णाङ्क value1, पूर्णाङ्क value2, पूर्णाङ्क value3, पूर्णाङ्क value4, पूर्णाङ्क स्थानाङ्कः);
पूर्णाङ्क flashReadSingleSPI(पूर्णाङ्क dummy_आवृत्तयः, पूर्णाङ्क read_स्थानाङ्कः, पूर्णाङ्क instruction, पूर्णाङ्क दत्त_शब्दाः, पूर्णाङ्क adsize);
पूर्णाङ्क flashReadDualSPI(पूर्णाङ्क स्थानाङ्कः, पूर्णाङ्क दत्त_दीर्घता);
पूर्णाङ्क flashReadQuadSPI(पूर्णाङ्क dummy_आवृत्तयः, पूर्णाङ्क read_स्थानाङ्कः, पूर्णाङ्क instruction, पूर्णाङ्क दत्त_शब्दाः, पूर्णाङ्क adsize);
पूर्णाङ्क micron_disable_xip_volatile(पूर्णाङ्क,पूर्णाङ्क);
पूर्णाङ्क flashSingleSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क flashMemInit(शून्य);
पूर्णाङ्क flashDualSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क flashDualSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क flashWriteVolatileConfigReg(पूर्णाङ्क मानम्);
पूर्णाङ्क flashQuadSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क flashQuadSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr);
पूर्णाङ्क eraseSector(पूर्णाङ्क command, पूर्णाङ्क स्थानाङ्कः);
पूर्णाङ्क micron_volatile_write_enable(पूर्णाङ्क स्थितिः_2);
पूर्णाङ्क micron_enable_4byte_addressing(पूर्णाङ्क स्थितिः_2);
पूर्णाङ्क micron_configure_xip_volatile(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्);
पूर्णाङ्क micron_read_configuration_पञ्जिकाकोशः(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्);
पूर्णाङ्क micron_read_id_cmd(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्);
पूर्णाङ्क wait_for_wip(शून्य);
पूर्णाङ्क flashIdentificationDevice(शून्य);
पूर्णाङ्क flash_Read_Flag_पञ्जिकाकोशः(शून्य);
पूर्णाङ्क flashWriteEnable(शून्य);
पूर्णाङ्क flash_Enable4_Byte_Addressing_बहुलकम्(शून्य);
पूर्णाङ्क flash_Write_disable(शून्य);


#यदि_अन्तः
