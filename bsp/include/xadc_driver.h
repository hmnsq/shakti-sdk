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

#यदि_अपरिभाषितम् XADC_DRIVER
#परिभाषय XADC_DRIVER

#अन्तर्भाव "platform.h"
#अन्तर्भाव "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#परिभाषय XADC_SRR_विस्थापनम्		0x00  /**< Software Reset Register */
#परिभाषय XADC_SR_विस्थापनम्		0x04  /**< Status Register */
#परिभाषय XADC_AOR_विस्थापनम्		0x08  /**< Alarm Output Register */
#परिभाषय XADC_CONVST_विस्थापनम्	0x0C  /**< ADC Convert Start Register */
#परिभाषय XADC_ARR_विस्थापनम्		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#परिभाषय XADC_GIER_विस्थापनम्	0x5C  /**< Global Interrupt Enable Register */
#परिभाषय XADC_ISR_विस्थापनम्	        0x60  /**< Interrupt Status Register */
#परिभाषय XADC_IER_विस्थापनम्		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#परिभाषय XADC_अस्थायी_विस्थापनम्	  (0x200)   /**< On-chip Temperature Reg */
#परिभाषय XADC_VCCINT_विस्थापनम्	  (0x204)   /**< On-chip VCCINT Data Reg */
#परिभाषय XADC_VCCAUX_विस्थापनम्	  (0x208)   /**< On-chip VCCAUX Data Reg */
#परिभाषय XADC_VPVN_विस्थापनम्	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#परिभाषय XADC_AUX00_विस्थापनम्	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#परिभाषय XADC_AUX01_विस्थापनम्	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#परिभाषय XADC_AUX02_विस्थापनम्	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#परिभाषय XADC_AUX03_विस्थापनम्	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#परिभाषय XADC_AUX04_विस्थापनम्	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#परिभाषय XADC_AUX05_विस्थापनम्	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#परिभाषय XADC_AUX06_विस्थापनम्	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#परिभाषय XADC_AUX07_विस्थापनम्	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#परिभाषय XADC_AUX08_विस्थापनम्	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#परिभाषय XADC_AUX09_विस्थापनम्	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#परिभाषय XADC_AUX10_विस्थापनम्	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#परिभाषय XADC_AUX11_विस्थापनम्	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#परिभाषय XADC_AUX12_विस्थापनम्	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#परिभाषय XADC_AUX13_विस्थापनम्	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#परिभाषय XADC_AUX14_विस्थापनम्	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#परिभाषय XADC_AUX15_विस्थापनम्	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#परिभाषय XADC_MAX_अस्थायी_विस्थापनम्	(0x280)   /**< Maximum Temperature Reg */
#परिभाषय XADC_MAX_VCCINT_विस्थापनम्	(0x284)   /**< Maximum VCCINT Register */
#परिभाषय XADC_MAX_VCCAUX_विस्थापनम्	(0x288)   /**< Maximum VCCAUX Register */
#परिभाषय XADC_MAX_VBRAM_विस्थापनम्	(0x28C)   /**< Maximum VBRAM Reg / */
#परिभाषय XADC_MIN_अस्थायी_विस्थापनम्	(0x290)   /**< Minimum Temperature Reg */
#परिभाषय XADC_MIN_VCCINT_विस्थापनम्	(0x294)   /**< Minimum VCCINT Register */
#परिभाषय XADC_MIN_VCCAUX_विस्थापनम्	(0x298)   /**< Minimum VCCAUX Register */
#परिभाषय XADC_MIN_VBRAM_विस्थापनम्	(0x29C)   /**< Maximum VBRAM Reg / */
#परिभाषय XADC_MAX_VCCPINT_विस्थापनम्	(0x2A0)   /**< Max VCCPINT Register  */
#परिभाषय XADC_MAX_VCCPAUX_विस्थापनम्	(0x2A4)   /**< Max VCCPAUX Register  */
#परिभाषय XADC_MAX_VCCPDRO_विस्थापनम्	(0x2A8)   /**< Max VCCPDRO Register  */
#परिभाषय XADC_MIN_VCCPINT_विस्थापनम्	(0x2AC)   /**< Min VCCPINT Register  */
#परिभाषय XADC_MIN_VCCPAUX_विस्थापनम्	(0x2B0)   /**< Min VCCPAUX Register  */
#परिभाषय XADC_MIN_VCCPDRO_विस्थापनम्	(0x2B4)   /**< Min VCCPDRO Register  */


#परिभाषय XADC_FLAG_REG_विस्थापनम्	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#परिभाषय XADC_CFR0_विस्थापनम्		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#परिभाषय XADC_SEQ00_विस्थापनम्	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#परिभाषय XADC_SEQ01_विस्थापनम्	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#परिभाषय XADC_SEQ02_विस्थापनम्	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#परिभाषय XADC_SEQ03_विस्थापनम्	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#परिभाषय XADC_SEQ04_विस्थापनम्	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#परिभाषय XADC_SEQ05_विस्थापनम्	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#परिभाषय XADC_SEQ06_विस्थापनम्	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#परिभाषय XADC_SEQ07_विस्थापनम्	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#परिभाषय XADC_SEQ08_विस्थापनम्	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#परिभाषय XADC_SEQ09_विस्थापनम्	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#परिभाषय XADC_SRR_RESET_मानम्	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#परिभाषय XADC_ARR_RST_आवरणम्	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#परिभाषय XADC_GIER_GIE_आवरणम्	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

शून्य xadc_write_ctrl_reg(uint32_t *स्थानाङ्कः, uint32_t दत्त_2);
uint32_t xadc_read_ctrl_reg(uint32_t *स्थानाङ्कः);
uint32_t xadc_read_दत्त(uint32_t *स्थानाङ्कः);
भिन्न xadc_onchip_अस्थायी(uint32_t मानम्);
भिन्न xadc_onchip_voltage(uint32_t मानम्);
भिन्न xadc_dedicated_channel(uint32_t मानम्);

#यदि_अन्तः
