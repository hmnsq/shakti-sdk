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

#جيڪڏهن_وصف_نه_ٿيل XADC_DRIVER
#وصف_ڪريو XADC_DRIVER

#ضمن "platform.h"
#ضمن "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#وصف_ڪريو XADC_SRR_وٿي		0x00  /**< Software Reset Register */
#وصف_ڪريو XADC_SR_وٿي		0x04  /**< Status Register */
#وصف_ڪريو XADC_AOR_وٿي		0x08  /**< Alarm Output Register */
#وصف_ڪريو XADC_CONVST_وٿي	0x0C  /**< ADC Convert Start Register */
#وصف_ڪريو XADC_ARR_وٿي		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#وصف_ڪريو XADC_GIER_وٿي	0x5C  /**< Global Interrupt Enable Register */
#وصف_ڪريو XADC_ISR_وٿي	        0x60  /**< Interrupt Status Register */
#وصف_ڪريو XADC_IER_وٿي		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#وصف_ڪريو XADC_عارضي_وٿي	  (0x200)   /**< On-chip Temperature Reg */
#وصف_ڪريو XADC_VCCINT_وٿي	  (0x204)   /**< On-chip VCCINT Data Reg */
#وصف_ڪريو XADC_VCCAUX_وٿي	  (0x208)   /**< On-chip VCCAUX Data Reg */
#وصف_ڪريو XADC_VPVN_وٿي	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#وصف_ڪريو XADC_AUX00_وٿي	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#وصف_ڪريو XADC_AUX01_وٿي	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#وصف_ڪريو XADC_AUX02_وٿي	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#وصف_ڪريو XADC_AUX03_وٿي	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#وصف_ڪريو XADC_AUX04_وٿي	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#وصف_ڪريو XADC_AUX05_وٿي	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#وصف_ڪريو XADC_AUX06_وٿي	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#وصف_ڪريو XADC_AUX07_وٿي	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#وصف_ڪريو XADC_AUX08_وٿي	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#وصف_ڪريو XADC_AUX09_وٿي	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#وصف_ڪريو XADC_AUX10_وٿي	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#وصف_ڪريو XADC_AUX11_وٿي	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#وصف_ڪريو XADC_AUX12_وٿي	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#وصف_ڪريو XADC_AUX13_وٿي	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#وصف_ڪريو XADC_AUX14_وٿي	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#وصف_ڪريو XADC_AUX15_وٿي	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#وصف_ڪريو XADC_MAX_عارضي_وٿي	(0x280)   /**< Maximum Temperature Reg */
#وصف_ڪريو XADC_MAX_VCCINT_وٿي	(0x284)   /**< Maximum VCCINT Register */
#وصف_ڪريو XADC_MAX_VCCAUX_وٿي	(0x288)   /**< Maximum VCCAUX Register */
#وصف_ڪريو XADC_MAX_VBRAM_وٿي	(0x28C)   /**< Maximum VBRAM Reg / */
#وصف_ڪريو XADC_MIN_عارضي_وٿي	(0x290)   /**< Minimum Temperature Reg */
#وصف_ڪريو XADC_MIN_VCCINT_وٿي	(0x294)   /**< Minimum VCCINT Register */
#وصف_ڪريو XADC_MIN_VCCAUX_وٿي	(0x298)   /**< Minimum VCCAUX Register */
#وصف_ڪريو XADC_MIN_VBRAM_وٿي	(0x29C)   /**< Maximum VBRAM Reg / */
#وصف_ڪريو XADC_MAX_VCCPINT_وٿي	(0x2A0)   /**< Max VCCPINT Register  */
#وصف_ڪريو XADC_MAX_VCCPAUX_وٿي	(0x2A4)   /**< Max VCCPAUX Register  */
#وصف_ڪريو XADC_MAX_VCCPDRO_وٿي	(0x2A8)   /**< Max VCCPDRO Register  */
#وصف_ڪريو XADC_MIN_VCCPINT_وٿي	(0x2AC)   /**< Min VCCPINT Register  */
#وصف_ڪريو XADC_MIN_VCCPAUX_وٿي	(0x2B0)   /**< Min VCCPAUX Register  */
#وصف_ڪريو XADC_MIN_VCCPDRO_وٿي	(0x2B4)   /**< Min VCCPDRO Register  */


#وصف_ڪريو XADC_FLAG_REG_وٿي	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#وصف_ڪريو XADC_CFR0_وٿي		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#وصف_ڪريو XADC_SEQ00_وٿي	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#وصف_ڪريو XADC_SEQ01_وٿي	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#وصف_ڪريو XADC_SEQ02_وٿي	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#وصف_ڪريو XADC_SEQ03_وٿي	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#وصف_ڪريو XADC_SEQ04_وٿي	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#وصف_ڪريو XADC_SEQ05_وٿي	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#وصف_ڪريو XADC_SEQ06_وٿي	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#وصف_ڪريو XADC_SEQ07_وٿي	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#وصف_ڪريو XADC_SEQ08_وٿي	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#وصف_ڪريو XADC_SEQ09_وٿي	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#وصف_ڪريو XADC_SRR_RESET_قدر	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#وصف_ڪريو XADC_ARR_RST_نقاب	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#وصف_ڪريو XADC_GIER_GIE_نقاب	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

فراغ xadc_write_ctrl_reg(uint32_t *پتو, uint32_t معلومات_2);
uint32_t xadc_read_ctrl_reg(uint32_t *پتو);
uint32_t xadc_read_معلومات(uint32_t *پتو);
عائم xadc_onchip_عارضي(uint32_t قدر);
عائم xadc_onchip_voltage(uint32_t قدر);
عائم xadc_dedicated_channel(uint32_t قدر);

#جيڪڏهن_پورو
