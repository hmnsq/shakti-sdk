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

#که_نه_تعریف_شوی XADC_DRIVER
#تعریف_کړه XADC_DRIVER

#ضمن "platform.h"
#ضمن "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#تعریف_کړه XADC_SRR_دننه_واټن		0x00  /**< Software Reset Register */
#تعریف_کړه XADC_SR_دننه_واټن		0x04  /**< Status Register */
#تعریف_کړه XADC_AOR_دننه_واټن		0x08  /**< Alarm Output Register */
#تعریف_کړه XADC_CONVST_دننه_واټن	0x0C  /**< ADC Convert Start Register */
#تعریف_کړه XADC_ARR_دننه_واټن		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#تعریف_کړه XADC_GIER_دننه_واټن	0x5C  /**< Global Interrupt Enable Register */
#تعریف_کړه XADC_ISR_دننه_واټن	        0x60  /**< Interrupt Status Register */
#تعریف_کړه XADC_IER_دننه_واټن		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#تعریف_کړه XADC_لنډمهاله_دننه_واټن	  (0x200)   /**< On-chip Temperature Reg */
#تعریف_کړه XADC_VCCINT_دننه_واټن	  (0x204)   /**< On-chip VCCINT Data Reg */
#تعریف_کړه XADC_VCCAUX_دننه_واټن	  (0x208)   /**< On-chip VCCAUX Data Reg */
#تعریف_کړه XADC_VPVN_دننه_واټن	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#تعریف_کړه XADC_AUX00_دننه_واټن	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#تعریف_کړه XADC_AUX01_دننه_واټن	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#تعریف_کړه XADC_AUX02_دننه_واټن	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#تعریف_کړه XADC_AUX03_دننه_واټن	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#تعریف_کړه XADC_AUX04_دننه_واټن	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#تعریف_کړه XADC_AUX05_دننه_واټن	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#تعریف_کړه XADC_AUX06_دننه_واټن	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#تعریف_کړه XADC_AUX07_دننه_واټن	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#تعریف_کړه XADC_AUX08_دننه_واټن	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#تعریف_کړه XADC_AUX09_دننه_واټن	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#تعریف_کړه XADC_AUX10_دننه_واټن	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#تعریف_کړه XADC_AUX11_دننه_واټن	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#تعریف_کړه XADC_AUX12_دننه_واټن	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#تعریف_کړه XADC_AUX13_دننه_واټن	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#تعریف_کړه XADC_AUX14_دننه_واټن	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#تعریف_کړه XADC_AUX15_دننه_واټن	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#تعریف_کړه XADC_MAX_لنډمهاله_دننه_واټن	(0x280)   /**< Maximum Temperature Reg */
#تعریف_کړه XADC_MAX_VCCINT_دننه_واټن	(0x284)   /**< Maximum VCCINT Register */
#تعریف_کړه XADC_MAX_VCCAUX_دننه_واټن	(0x288)   /**< Maximum VCCAUX Register */
#تعریف_کړه XADC_MAX_VBRAM_دننه_واټن	(0x28C)   /**< Maximum VBRAM Reg / */
#تعریف_کړه XADC_MIN_لنډمهاله_دننه_واټن	(0x290)   /**< Minimum Temperature Reg */
#تعریف_کړه XADC_MIN_VCCINT_دننه_واټن	(0x294)   /**< Minimum VCCINT Register */
#تعریف_کړه XADC_MIN_VCCAUX_دننه_واټن	(0x298)   /**< Minimum VCCAUX Register */
#تعریف_کړه XADC_MIN_VBRAM_دننه_واټن	(0x29C)   /**< Maximum VBRAM Reg / */
#تعریف_کړه XADC_MAX_VCCPINT_دننه_واټن	(0x2A0)   /**< Max VCCPINT Register  */
#تعریف_کړه XADC_MAX_VCCPAUX_دننه_واټن	(0x2A4)   /**< Max VCCPAUX Register  */
#تعریف_کړه XADC_MAX_VCCPDRO_دننه_واټن	(0x2A8)   /**< Max VCCPDRO Register  */
#تعریف_کړه XADC_MIN_VCCPINT_دننه_واټن	(0x2AC)   /**< Min VCCPINT Register  */
#تعریف_کړه XADC_MIN_VCCPAUX_دننه_واټن	(0x2B0)   /**< Min VCCPAUX Register  */
#تعریف_کړه XADC_MIN_VCCPDRO_دننه_واټن	(0x2B4)   /**< Min VCCPDRO Register  */


#تعریف_کړه XADC_FLAG_REG_دننه_واټن	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#تعریف_کړه XADC_CFR0_دننه_واټن		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#تعریف_کړه XADC_SEQ00_دننه_واټن	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#تعریف_کړه XADC_SEQ01_دننه_واټن	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#تعریف_کړه XADC_SEQ02_دننه_واټن	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#تعریف_کړه XADC_SEQ03_دننه_واټن	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#تعریف_کړه XADC_SEQ04_دننه_واټن	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#تعریف_کړه XADC_SEQ05_دننه_واټن	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#تعریف_کړه XADC_SEQ06_دننه_واټن	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#تعریف_کړه XADC_SEQ07_دننه_واټن	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#تعریف_کړه XADC_SEQ08_دننه_واټن	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#تعریف_کړه XADC_SEQ09_دننه_واټن	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#تعریف_کړه XADC_SRR_RESET_ارزښت	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#تعریف_کړه XADC_ARR_RST_ماسک	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#تعریف_کړه XADC_GIER_GIE_ماسک	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

فراغ xadc_write_ctrl_reg(uint32_t *پته, uint32_t معلومات_2);
uint32_t xadc_read_ctrl_reg(uint32_t *پته);
uint32_t xadc_read_معلومات(uint32_t *پته);
عائم xadc_onchip_لنډمهاله(uint32_t ارزښت);
عائم xadc_onchip_voltage(uint32_t ارزښت);
عائم xadc_dedicated_channel(uint32_t ارزښت);

#د_که_پای
