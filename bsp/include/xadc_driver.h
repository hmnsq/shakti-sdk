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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XADC_DRIVER
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_DRIVER

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SRR_ਵਿੱਥ		0x00  /**< Software Reset Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SR_ਵਿੱਥ		0x04  /**< Status Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AOR_ਵਿੱਥ		0x08  /**< Alarm Output Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_CONVST_ਵਿੱਥ	0x0C  /**< ADC Convert Start Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_ARR_ਵਿੱਥ		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_GIER_ਵਿੱਥ	0x5C  /**< Global Interrupt Enable Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_ISR_ਵਿੱਥ	        0x60  /**< Interrupt Status Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_IER_ਵਿੱਥ		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_ਆਰਜ਼ੀ_ਵਿੱਥ	  (0x200)   /**< On-chip Temperature Reg */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_VCCINT_ਵਿੱਥ	  (0x204)   /**< On-chip VCCINT Data Reg */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_VCCAUX_ਵਿੱਥ	  (0x208)   /**< On-chip VCCAUX Data Reg */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_VPVN_ਵਿੱਥ	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX00_ਵਿੱਥ	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX01_ਵਿੱਥ	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX02_ਵਿੱਥ	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX03_ਵਿੱਥ	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX04_ਵਿੱਥ	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX05_ਵਿੱਥ	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX06_ਵਿੱਥ	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX07_ਵਿੱਥ	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX08_ਵਿੱਥ	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX09_ਵਿੱਥ	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX10_ਵਿੱਥ	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX11_ਵਿੱਥ	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX12_ਵਿੱਥ	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX13_ਵਿੱਥ	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX14_ਵਿੱਥ	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_AUX15_ਵਿੱਥ	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_ਆਰਜ਼ੀ_ਵਿੱਥ	(0x280)   /**< Maximum Temperature Reg */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VCCINT_ਵਿੱਥ	(0x284)   /**< Maximum VCCINT Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VCCAUX_ਵਿੱਥ	(0x288)   /**< Maximum VCCAUX Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VBRAM_ਵਿੱਥ	(0x28C)   /**< Maximum VBRAM Reg / */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_ਆਰਜ਼ੀ_ਵਿੱਥ	(0x290)   /**< Minimum Temperature Reg */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VCCINT_ਵਿੱਥ	(0x294)   /**< Minimum VCCINT Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VCCAUX_ਵਿੱਥ	(0x298)   /**< Minimum VCCAUX Register */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VBRAM_ਵਿੱਥ	(0x29C)   /**< Maximum VBRAM Reg / */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VCCPINT_ਵਿੱਥ	(0x2A0)   /**< Max VCCPINT Register  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VCCPAUX_ਵਿੱਥ	(0x2A4)   /**< Max VCCPAUX Register  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MAX_VCCPDRO_ਵਿੱਥ	(0x2A8)   /**< Max VCCPDRO Register  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VCCPINT_ਵਿੱਥ	(0x2AC)   /**< Min VCCPINT Register  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VCCPAUX_ਵਿੱਥ	(0x2B0)   /**< Min VCCPAUX Register  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_MIN_VCCPDRO_ਵਿੱਥ	(0x2B4)   /**< Min VCCPDRO Register  */


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_FLAG_REG_ਵਿੱਥ	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_CFR0_ਵਿੱਥ		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ00_ਵਿੱਥ	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ01_ਵਿੱਥ	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ02_ਵਿੱਥ	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ03_ਵਿੱਥ	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ04_ਵਿੱਥ	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ05_ਵਿੱਥ	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ06_ਵਿੱਥ	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ07_ਵਿੱਥ	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ08_ਵਿੱਥ	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SEQ09_ਵਿੱਥ	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_SRR_RESET_ਮੁੱਲ	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_ARR_RST_ਨਕਾਬ	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_GIER_GIE_ਨਕਾਬ	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

ਖਾਲੀ xadc_write_ctrl_reg(uint32_t *ਪਤਾ, uint32_t ਅੰਕੜੇ_2);
uint32_t xadc_read_ctrl_reg(uint32_t *ਪਤਾ);
uint32_t xadc_read_ਅੰਕੜੇ(uint32_t *ਪਤਾ);
ਦਸ਼ਮਲਵ xadc_onchip_ਆਰਜ਼ੀ(uint32_t ਮੁੱਲ);
ਦਸ਼ਮਲਵ xadc_onchip_voltage(uint32_t ਮੁੱਲ);
ਦਸ਼ਮਲਵ xadc_dedicated_channel(uint32_t ਮੁੱਲ);

#ਜੇ_ਅੰਤ
