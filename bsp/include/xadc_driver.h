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

#اگر_تعریف_نشده XADC_DRIVER
#تعریف_کن XADC_DRIVER

#ضمن "platform.h"
#ضمن "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#تعریف_کن XADC_SRR_جابه_جایی		0x00  /**< Software Reset Register */
#تعریف_کن XADC_SR_جابه_جایی		0x04  /**< Status Register */
#تعریف_کن XADC_AOR_جابه_جایی		0x08  /**< Alarm Output Register */
#تعریف_کن XADC_CONVST_جابه_جایی	0x0C  /**< ADC Convert Start Register */
#تعریف_کن XADC_ARR_جابه_جایی		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#تعریف_کن XADC_GIER_جابه_جایی	0x5C  /**< Global Interrupt Enable Register */
#تعریف_کن XADC_ISR_جابه_جایی	        0x60  /**< Interrupt Status Register */
#تعریف_کن XADC_IER_جابه_جایی		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#تعریف_کن XADC_موقت_جابه_جایی	  (0x200)   /**< On-chip Temperature Reg */
#تعریف_کن XADC_VCCINT_جابه_جایی	  (0x204)   /**< On-chip VCCINT Data Reg */
#تعریف_کن XADC_VCCAUX_جابه_جایی	  (0x208)   /**< On-chip VCCAUX Data Reg */
#تعریف_کن XADC_VPVN_جابه_جایی	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#تعریف_کن XADC_AUX00_جابه_جایی	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#تعریف_کن XADC_AUX01_جابه_جایی	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#تعریف_کن XADC_AUX02_جابه_جایی	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#تعریف_کن XADC_AUX03_جابه_جایی	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#تعریف_کن XADC_AUX04_جابه_جایی	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#تعریف_کن XADC_AUX05_جابه_جایی	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#تعریف_کن XADC_AUX06_جابه_جایی	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#تعریف_کن XADC_AUX07_جابه_جایی	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#تعریف_کن XADC_AUX08_جابه_جایی	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#تعریف_کن XADC_AUX09_جابه_جایی	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#تعریف_کن XADC_AUX10_جابه_جایی	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#تعریف_کن XADC_AUX11_جابه_جایی	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#تعریف_کن XADC_AUX12_جابه_جایی	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#تعریف_کن XADC_AUX13_جابه_جایی	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#تعریف_کن XADC_AUX14_جابه_جایی	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#تعریف_کن XADC_AUX15_جابه_جایی	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#تعریف_کن XADC_MAX_موقت_جابه_جایی	(0x280)   /**< Maximum Temperature Reg */
#تعریف_کن XADC_MAX_VCCINT_جابه_جایی	(0x284)   /**< Maximum VCCINT Register */
#تعریف_کن XADC_MAX_VCCAUX_جابه_جایی	(0x288)   /**< Maximum VCCAUX Register */
#تعریف_کن XADC_MAX_VBRAM_جابه_جایی	(0x28C)   /**< Maximum VBRAM Reg / */
#تعریف_کن XADC_MIN_موقت_جابه_جایی	(0x290)   /**< Minimum Temperature Reg */
#تعریف_کن XADC_MIN_VCCINT_جابه_جایی	(0x294)   /**< Minimum VCCINT Register */
#تعریف_کن XADC_MIN_VCCAUX_جابه_جایی	(0x298)   /**< Minimum VCCAUX Register */
#تعریف_کن XADC_MIN_VBRAM_جابه_جایی	(0x29C)   /**< Maximum VBRAM Reg / */
#تعریف_کن XADC_MAX_VCCPINT_جابه_جایی	(0x2A0)   /**< Max VCCPINT Register  */
#تعریف_کن XADC_MAX_VCCPAUX_جابه_جایی	(0x2A4)   /**< Max VCCPAUX Register  */
#تعریف_کن XADC_MAX_VCCPDRO_جابه_جایی	(0x2A8)   /**< Max VCCPDRO Register  */
#تعریف_کن XADC_MIN_VCCPINT_جابه_جایی	(0x2AC)   /**< Min VCCPINT Register  */
#تعریف_کن XADC_MIN_VCCPAUX_جابه_جایی	(0x2B0)   /**< Min VCCPAUX Register  */
#تعریف_کن XADC_MIN_VCCPDRO_جابه_جایی	(0x2B4)   /**< Min VCCPDRO Register  */


#تعریف_کن XADC_FLAG_REG_جابه_جایی	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#تعریف_کن XADC_CFR0_جابه_جایی		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#تعریف_کن XADC_SEQ00_جابه_جایی	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#تعریف_کن XADC_SEQ01_جابه_جایی	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#تعریف_کن XADC_SEQ02_جابه_جایی	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#تعریف_کن XADC_SEQ03_جابه_جایی	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#تعریف_کن XADC_SEQ04_جابه_جایی	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#تعریف_کن XADC_SEQ05_جابه_جایی	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#تعریف_کن XADC_SEQ06_جابه_جایی	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#تعریف_کن XADC_SEQ07_جابه_جایی	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#تعریف_کن XADC_SEQ08_جابه_جایی	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#تعریف_کن XADC_SEQ09_جابه_جایی	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#تعریف_کن XADC_SRR_RESET_مقدار	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#تعریف_کن XADC_ARR_RST_ماسک	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#تعریف_کن XADC_GIER_GIE_ماسک	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

فراغ xadc_write_ctrl_reg(uint32_t *آدرس, uint32_t داده_2);
uint32_t xadc_read_ctrl_reg(uint32_t *آدرس);
uint32_t xadc_read_داده(uint32_t *آدرس);
عائم xadc_onchip_موقت(uint32_t مقدار);
عائم xadc_onchip_voltage(uint32_t مقدار);
عائم xadc_dedicated_channel(uint32_t مقدار);

#پایان_اگر
