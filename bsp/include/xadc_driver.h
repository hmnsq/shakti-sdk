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

#جے_بنا_تعریف XADC_DRIVER
#تعریف_کرو XADC_DRIVER

#ضمن "platform.h"
#ضمن "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#تعریف_کرو XADC_SRR_وتھ		0x00  /**< Software Reset Register */
#تعریف_کرو XADC_SR_وتھ		0x04  /**< Status Register */
#تعریف_کرو XADC_AOR_وتھ		0x08  /**< Alarm Output Register */
#تعریف_کرو XADC_CONVST_وتھ	0x0C  /**< ADC Convert Start Register */
#تعریف_کرو XADC_ARR_وتھ		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#تعریف_کرو XADC_GIER_وتھ	0x5C  /**< Global Interrupt Enable Register */
#تعریف_کرو XADC_ISR_وتھ	        0x60  /**< Interrupt Status Register */
#تعریف_کرو XADC_IER_وتھ		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#تعریف_کرو XADC_عارضی_وتھ	  (0x200)   /**< On-chip Temperature Reg */
#تعریف_کرو XADC_VCCINT_وتھ	  (0x204)   /**< On-chip VCCINT Data Reg */
#تعریف_کرو XADC_VCCAUX_وتھ	  (0x208)   /**< On-chip VCCAUX Data Reg */
#تعریف_کرو XADC_VPVN_وتھ	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#تعریف_کرو XADC_AUX00_وتھ	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#تعریف_کرو XADC_AUX01_وتھ	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#تعریف_کرو XADC_AUX02_وتھ	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#تعریف_کرو XADC_AUX03_وتھ	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#تعریف_کرو XADC_AUX04_وتھ	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#تعریف_کرو XADC_AUX05_وتھ	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#تعریف_کرو XADC_AUX06_وتھ	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#تعریف_کرو XADC_AUX07_وتھ	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#تعریف_کرو XADC_AUX08_وتھ	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#تعریف_کرو XADC_AUX09_وتھ	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#تعریف_کرو XADC_AUX10_وتھ	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#تعریف_کرو XADC_AUX11_وتھ	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#تعریف_کرو XADC_AUX12_وتھ	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#تعریف_کرو XADC_AUX13_وتھ	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#تعریف_کرو XADC_AUX14_وتھ	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#تعریف_کرو XADC_AUX15_وتھ	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#تعریف_کرو XADC_MAX_عارضی_وتھ	(0x280)   /**< Maximum Temperature Reg */
#تعریف_کرو XADC_MAX_VCCINT_وتھ	(0x284)   /**< Maximum VCCINT Register */
#تعریف_کرو XADC_MAX_VCCAUX_وتھ	(0x288)   /**< Maximum VCCAUX Register */
#تعریف_کرو XADC_MAX_VBRAM_وتھ	(0x28C)   /**< Maximum VBRAM Reg / */
#تعریف_کرو XADC_MIN_عارضی_وتھ	(0x290)   /**< Minimum Temperature Reg */
#تعریف_کرو XADC_MIN_VCCINT_وتھ	(0x294)   /**< Minimum VCCINT Register */
#تعریف_کرو XADC_MIN_VCCAUX_وتھ	(0x298)   /**< Minimum VCCAUX Register */
#تعریف_کرو XADC_MIN_VBRAM_وتھ	(0x29C)   /**< Maximum VBRAM Reg / */
#تعریف_کرو XADC_MAX_VCCPINT_وتھ	(0x2A0)   /**< Max VCCPINT Register  */
#تعریف_کرو XADC_MAX_VCCPAUX_وتھ	(0x2A4)   /**< Max VCCPAUX Register  */
#تعریف_کرو XADC_MAX_VCCPDRO_وتھ	(0x2A8)   /**< Max VCCPDRO Register  */
#تعریف_کرو XADC_MIN_VCCPINT_وتھ	(0x2AC)   /**< Min VCCPINT Register  */
#تعریف_کرو XADC_MIN_VCCPAUX_وتھ	(0x2B0)   /**< Min VCCPAUX Register  */
#تعریف_کرو XADC_MIN_VCCPDRO_وتھ	(0x2B4)   /**< Min VCCPDRO Register  */


#تعریف_کرو XADC_FLAG_REG_وتھ	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#تعریف_کرو XADC_CFR0_وتھ		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#تعریف_کرو XADC_SEQ00_وتھ	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#تعریف_کرو XADC_SEQ01_وتھ	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#تعریف_کرو XADC_SEQ02_وتھ	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#تعریف_کرو XADC_SEQ03_وتھ	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#تعریف_کرو XADC_SEQ04_وتھ	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#تعریف_کرو XADC_SEQ05_وتھ	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#تعریف_کرو XADC_SEQ06_وتھ	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#تعریف_کرو XADC_SEQ07_وتھ	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#تعریف_کرو XADC_SEQ08_وتھ	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#تعریف_کرو XADC_SEQ09_وتھ	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#تعریف_کرو XADC_SRR_RESET_قدر	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#تعریف_کرو XADC_ARR_RST_نقاب	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#تعریف_کرو XADC_GIER_GIE_نقاب	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

فراغ xadc_write_ctrl_reg(uint32_t *پتہ, uint32_t انکڑے_2);
uint32_t xadc_read_ctrl_reg(uint32_t *پتہ);
uint32_t xadc_read_انکڑے(uint32_t *پتہ);
عائم xadc_onchip_عارضی(uint32_t قدر);
عائم xadc_onchip_voltage(uint32_t قدر);
عائم xadc_dedicated_channel(uint32_t قدر);

#جے_انت
