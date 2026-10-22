/***************************************************************************
* Project           	     : shakti devt board
* Name of the file	     : xadc_driver.h
* Brief Description of file  : Header file for xadc driver.
* Name of Author    	     : Sathya Narayanan N
* Email ID                   : sathya281@gmail.com

  Copyright (C) 2020  IIT Madras. All rights reserved.

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
***************************************************************************/
/**
 * @file xadc_driver.h
 * @brief  Header file for xadc driver.c
 * @detail This file contains the definitions for xadc driver. The memory map
 * for the xadc registers are also defined here.
 */

#నిర్వచితం_కాకపోతే XADC_DRIVER
#నిర్వచించు XADC_DRIVER

#అన్తర్భావ "platform.h"
#అన్తర్భావ "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#నిర్వచించు XADC_SRR_స్థానభ్రంశం		0x00  /**< Software Reset Register */
#నిర్వచించు XADC_SR_స్థానభ్రంశం		0x04  /**< Status Register */
#నిర్వచించు XADC_AOR_స్థానభ్రంశం		0x08  /**< Alarm Output Register */
#నిర్వచించు XADC_CONVST_స్థానభ్రంశం	0x0C  /**< ADC Convert Start Register */
#నిర్వచించు XADC_ARR_స్థానభ్రంశం		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#నిర్వచించు XADC_GIER_స్థానభ్రంశం	0x5C  /**< Global Interrupt Enable Register */
#నిర్వచించు XADC_ISR_స్థానభ్రంశం	        0x60  /**< Interrupt Status Register */
#నిర్వచించు XADC_IER_స్థానభ్రంశం		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#నిర్వచించు XADC_తాత్కాలిక_స్థానభ్రంశం	  (0x200)   /**< On-chip Temperature Reg */
#నిర్వచించు XADC_VCCINT_స్థానభ్రంశం	  (0x204)   /**< On-chip VCCINT Data Reg */
#నిర్వచించు XADC_VCCAUX_స్థానభ్రంశం	  (0x208)   /**< On-chip VCCAUX Data Reg */
#నిర్వచించు XADC_VPVN_స్థానభ్రంశం	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#నిర్వచించు XADC_AUX00_స్థానభ్రంశం	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#నిర్వచించు XADC_AUX01_స్థానభ్రంశం	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#నిర్వచించు XADC_AUX02_స్థానభ్రంశం	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#నిర్వచించు XADC_AUX03_స్థానభ్రంశం	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#నిర్వచించు XADC_AUX04_స్థానభ్రంశం	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#నిర్వచించు XADC_AUX05_స్థానభ్రంశం	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#నిర్వచించు XADC_AUX06_స్థానభ్రంశం	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#నిర్వచించు XADC_AUX07_స్థానభ్రంశం	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#నిర్వచించు XADC_AUX08_స్థానభ్రంశం	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#నిర్వచించు XADC_AUX09_స్థానభ్రంశం	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#నిర్వచించు XADC_AUX10_స్థానభ్రంశం	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#నిర్వచించు XADC_AUX11_స్థానభ్రంశం	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#నిర్వచించు XADC_AUX12_స్థానభ్రంశం	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#నిర్వచించు XADC_AUX13_స్థానభ్రంశం	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#నిర్వచించు XADC_AUX14_స్థానభ్రంశం	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#నిర్వచించు XADC_AUX15_స్థానభ్రంశం	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#నిర్వచించు XADC_MAX_తాత్కాలిక_స్థానభ్రంశం	(0x280)   /**< Maximum Temperature Reg */
#నిర్వచించు XADC_MAX_VCCINT_స్థానభ్రంశం	(0x284)   /**< Maximum VCCINT Register */
#నిర్వచించు XADC_MAX_VCCAUX_స్థానభ్రంశం	(0x288)   /**< Maximum VCCAUX Register */
#నిర్వచించు XADC_MAX_VBRAM_స్థానభ్రంశం	(0x28C)   /**< Maximum VBRAM Reg / */
#నిర్వచించు XADC_MIN_తాత్కాలిక_స్థానభ్రంశం	(0x290)   /**< Minimum Temperature Reg */
#నిర్వచించు XADC_MIN_VCCINT_స్థానభ్రంశం	(0x294)   /**< Minimum VCCINT Register */
#నిర్వచించు XADC_MIN_VCCAUX_స్థానభ్రంశం	(0x298)   /**< Minimum VCCAUX Register */
#నిర్వచించు XADC_MIN_VBRAM_స్థానభ్రంశం	(0x29C)   /**< Maximum VBRAM Reg / */
#నిర్వచించు XADC_MAX_VCCPINT_స్థానభ్రంశం	(0x2A0)   /**< Max VCCPINT Register  */
#నిర్వచించు XADC_MAX_VCCPAUX_స్థానభ్రంశం	(0x2A4)   /**< Max VCCPAUX Register  */
#నిర్వచించు XADC_MAX_VCCPDRO_స్థానభ్రంశం	(0x2A8)   /**< Max VCCPDRO Register  */
#నిర్వచించు XADC_MIN_VCCPINT_స్థానభ్రంశం	(0x2AC)   /**< Min VCCPINT Register  */
#నిర్వచించు XADC_MIN_VCCPAUX_స్థానభ్రంశం	(0x2B0)   /**< Min VCCPAUX Register  */
#నిర్వచించు XADC_MIN_VCCPDRO_స్థానభ్రంశం	(0x2B4)   /**< Min VCCPDRO Register  */


#నిర్వచించు XADC_FLAG_REG_స్థానభ్రంశం	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#నిర్వచించు XADC_CFR0_స్థానభ్రంశం		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#నిర్వచించు XADC_SEQ00_స్థానభ్రంశం	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#నిర్వచించు XADC_SEQ01_స్థానభ్రంశం	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#నిర్వచించు XADC_SEQ02_స్థానభ్రంశం	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#నిర్వచించు XADC_SEQ03_స్థానభ్రంశం	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#నిర్వచించు XADC_SEQ04_స్థానభ్రంశం	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#నిర్వచించు XADC_SEQ05_స్థానభ్రంశం	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#నిర్వచించు XADC_SEQ06_స్థానభ్రంశం	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#నిర్వచించు XADC_SEQ07_స్థానభ్రంశం	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#నిర్వచించు XADC_SEQ08_స్థానభ్రంశం	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#నిర్వచించు XADC_SEQ09_స్థానభ్రంశం	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#నిర్వచించు XADC_SRR_RESET_విలువ	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#నిర్వచించు XADC_ARR_RST_ముసుగు	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#నిర్వచించు XADC_GIER_GIE_ముసుగు	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

శూన్య xadc_write_ctrl_reg(uint32_t *చిరునామా, uint32_t దత్తాంశం_2);
uint32_t xadc_read_ctrl_reg(uint32_t *చిరునామా);
uint32_t xadc_read_దత్తాంశం(uint32_t *చిరునామా);
దశాంశం xadc_onchip_తాత్కాలిక(uint32_t విలువ);
దశాంశం xadc_onchip_voltage(uint32_t విలువ);
దశాంశం xadc_dedicated_channel(uint32_t విలువ);

#అయితే_ముగింపు
