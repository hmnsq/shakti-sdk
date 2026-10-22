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

#నిర్వచితం_కాకపోతే QSPI_H
#నిర్వచించు QSPI_H

//#define BOOT
#నిర్వచితం_కాకపోతే BOOT

#అన్తర్భావ<stdlib.h>
#అయితే_ముగింపు
#అన్తర్భావ<stdint.h>

#నిర్వచించు DEF_TIMEOUT 60
#నిర్వచించు పునాది_ADDR 0x00000100 
                                                                                
//Memory Maps                                                                                       
#నిర్వచించు CR      0x00000100                                                      
#నిర్వచించు DCR     0x00000104                                                      
#నిర్వచించు SR      0x00000108                                                      
#నిర్వచించు FCR     0x0000010c                                                      
#నిర్వచించు DLR     0x00000110                                                      
#నిర్వచించు CCR     0x00000114                                                      
#నిర్వచించు AR      0x00000118                                                      
#నిర్వచించు ABR     0x0000011c                                                      
#నిర్వచించు DR      0x00000120                                                      
#నిర్వచించు PSMKR   0x00000124                                                      
#నిర్వచించు PSMAR   0x00000128                                                      
#నిర్వచించు PIR     0x0000012c                                                      
#నిర్వచించు LPRT    0x00000130                                                      
#నిర్వచించు STARTMM 0x90000000                                                      
#నిర్వచించు ENDMM   0x9FFFFFFF     

//Defines for configuring the registers at ease
//Bit vectors for all the parameters in the CR
#నిర్వచించు CR_PRESCALER(x)   (x<<24)
#నిర్వచించు CR_PMM            (1<<23)
#నిర్వచించు CR_APMS           (1<<22)
#నిర్వచించు CR_TOIE           (1<<20)
#నిర్వచించు CR_SMIE           (1<<19)
#నిర్వచించు CR_FTIE           (1<<18)
#నిర్వచించు CR_TCIE           (1<<17)
#నిర్వచించు CR_TEIE           (1<<16)
#నిర్వచించు CR_FTHRES(x)      (x<<8 )
#నిర్వచించు CR_FSEL           (1<<7 )
#నిర్వచించు CR_DFM            (1<<6 )
#నిర్వచించు CR_SSHIFT         (1<<4 )
#నిర్వచించు CR_TCEN           (1<<3 )
#నిర్వచించు CR_DMAEN          (1<<2 )
#నిర్వచించు CR_ABORT          (1<<1 )
#నిర్వచించు CR_EN             (1<<0 )

//Bit vectors for DCR 
#నిర్వచించు DCR_FSIZE(x)       (x<<16) 
#నిర్వచించు DCR_బహుళకం_BYTE(x)   (x<<21)
#నిర్వచించు DCR_CSHT(x)        (x<<8 )
#నిర్వచించు DCR_CKMODE(x)        (x) 

//Bit vectors for status register
#నిర్వచించు SR_FLEVEL(x)      (x<<8) 
#నిర్వచించు SR_TOF            (1<<4)
#నిర్వచించు SR_SMF            (1<<3)
#నిర్వచించు SR_FTF            (1<<2)
#నిర్వచించు SR_TCF            (1<<1)
#నిర్వచించు SR_TEF            (1<<0)

//Bit vectors for flag clear register 
#నిర్వచించు FCR_CTOF (1<<4)
#నిర్వచించు FCR_CSMF (1<<3)
#నిర్వచించు FCR_CTCF (1<<1)
#నిర్వచించు FCR_CTEF (1<<0)

//Bit vectors for DLR
#నిర్వచించు DL(x)  x  //Useless -- but for better readability of the code

//Bit vectors for CCR
#నిర్వచించు CCR_DDRM                   (1<<31) 
#నిర్వచించు CCR_DHHC                   (1<<30)
#నిర్వచించు CCR_DUMMY_బిట్టు              (1<<29) // Needed by Micron Flash Memories
#నిర్వచించు CCR_SIOO                   (1<<28)
#నిర్వచించు CCR_FMODE(x)               (x<<26)
#నిర్వచించు CCR_DMODE(x)               (x<<24)
#నిర్వచించు CCR_DUMMY_CONFIRMATION     (1<<23) // Needed by Micron Flash Memories
#నిర్వచించు CCR_DCYC(x)                (x<<18)
#నిర్వచించు CCR_ABSIZE(x)              (x<<16)
#నిర్వచించు CCR_ABMODE(x)              (x<<14)
#నిర్వచించు CCR_ADSIZE(x)              (x<<12)
#నిర్వచించు CCR_ADMODE(x)              (x<<10)
#నిర్వచించు CCR_IMODE(x)               (x<<8 )
#నిర్వచించు CCR_INSTRUCTION(x)         (x<<0 )

#నిర్వచించు CCR_FMODE_INDWR 0x0
#నిర్వచించు CCR_FMODE_INDRD 0x1
#నిర్వచించు CCR_FMODE_APOLL 0x2
#నిర్వచించు CCR_FMODE_MMAPD 0x3

#నిర్వచించు NDATA  0x0
#నిర్వచించు SINGLE 0x1
#నిర్వచించు DOUBLE 0x2
#నిర్వచించు QUAD   0x3

#నిర్వచించు BYTE      0x0
#నిర్వచించు TWOBYTE   0x1
#నిర్వచించు THREEBYTE 0x2
#నిర్వచించు FOURBYTE  0x3

బాహ్య పూర్ణాంకం* cr      ;
 బాహ్య పూర్ణాంకం* dcr    ;
 బాహ్య పూర్ణాంకం* sr     ; 
 బాహ్య పూర్ణాంకం* fcr    ;
 బాహ్య పూర్ణాంకం* ccr    ;
 బాహ్య పూర్ణాంకం* ar     ; 
 బాహ్య పూర్ణాంకం* abr    ;
 బాహ్య పూర్ణాంకం* dr     ; 
 బాహ్య పూర్ణాంకం* dlr    ;
 బాహ్య పూర్ణాంకం* psmkr  ;
 బాహ్య పూర్ణాంకం* pir    ;
 బాహ్య పూర్ణాంకం* lprt   ;
 బాహ్య పూర్ణాంకం* startmm;
 బాహ్య పూర్ణాంకం* endmm ;

శూన్య సమితి_qspi_shakti32(పూర్ణాంకం* addr, స్థిరరాశి పూర్ణాంకం val);
శూన్య సమితి_qspi_shakti16(int16_t* addr, int16_t val);
శూన్య సమితి_qspi_shakti8(అక్షరం* addr, అక్షరం val);
పూర్ణాంకం get_qspi_shakti( పూర్ణాంకం* addr);
పూర్ణాంకం check_fail_బిట్టు(శూన్య);
శూన్య reset_అంతరాయం_flags(శూన్య);
పూర్ణాంకం micron_write_enable(పూర్ణాంకం స్థితి_3);
పూర్ణాంకం flashSingleSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం wait_for_tcf(పూర్ణాంకం స్థితి_3);
శూన్య qspi_init(పూర్ణాంకం fsize, పూర్ణాంకం csht, పూర్ణాంకం prescaler, పూర్ణాంకం enable_interrupts, పూర్ణాంకం fthreshold, పూర్ణాంకం ck_బహుళకం);
పూర్ణాంకం పుట_కార్యక్రమం_Single_SPI(పూర్ణాంకం value1, పూర్ణాంకం value2, పూర్ణాంకం value3, పూర్ణాంకం value4, పూర్ణాంకం చిరునామా);
పూర్ణాంకం పుట_కార్యక్రమం_Quad_SPI(పూర్ణాంకం value1, పూర్ణాంకం value2, పూర్ణాంకం value3, పూర్ణాంకం value4, పూర్ణాంకం చిరునామా);
పూర్ణాంకం flashReadSingleSPI(పూర్ణాంకం dummy_చక్రాలు, పూర్ణాంకం read_చిరునామా, పూర్ణాంకం instruction, పూర్ణాంకం దత్తాంశం_పదాలు, పూర్ణాంకం adsize);
పూర్ణాంకం flashReadDualSPI(పూర్ణాంకం చిరునామా, పూర్ణాంకం దత్తాంశం_నిడివి);
పూర్ణాంకం flashReadQuadSPI(పూర్ణాంకం dummy_చక్రాలు, పూర్ణాంకం read_చిరునామా, పూర్ణాంకం instruction, పూర్ణాంకం దత్తాంశం_పదాలు, పూర్ణాంకం adsize);
పూర్ణాంకం micron_disable_xip_volatile(పూర్ణాంకం,పూర్ణాంకం);
పూర్ణాంకం flashSingleSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం flashMemInit(శూన్య);
పూర్ణాంకం flashDualSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం flashDualSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం flashWriteVolatileConfigReg(పూర్ణాంకం విలువ);
పూర్ణాంకం flashQuadSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం flashQuadSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr);
పూర్ణాంకం eraseSector(పూర్ణాంకం command, పూర్ణాంకం చిరునామా);
పూర్ణాంకం micron_volatile_write_enable(పూర్ణాంకం స్థితి_3);
పూర్ణాంకం micron_enable_4byte_addressing(పూర్ణాంకం స్థితి_3);
పూర్ణాంకం micron_configure_xip_volatile(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ);
పూర్ణాంకం micron_read_configuration_రిజిస్టరు(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ);
పూర్ణాంకం micron_read_id_cmd(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ);
పూర్ణాంకం wait_for_wip(శూన్య);
పూర్ణాంకం flashIdentificationDevice(శూన్య);
పూర్ణాంకం flash_Read_Flag_రిజిస్టరు(శూన్య);
పూర్ణాంకం flashWriteEnable(శూన్య);
పూర్ణాంకం flash_Enable4_Byte_Addressing_బహుళకం(శూన్య);
పూర్ణాంకం flash_Write_disable(శూన్య);


#అయితే_ముగింపు
