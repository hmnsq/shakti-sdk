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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XADC_DRIVER
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_DRIVER

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "traps.h"

/**@name Register offsets
 * The following constants provide access to each of the registers of the
 * System Monitor/ADC device.
 */

/* System Monitor/ADC Local Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SRR_ಸ್ಥಾನಾಂತರ		0x00  /**< Software Reset Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SR_ಸ್ಥಾನಾಂತರ		0x04  /**< Status Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AOR_ಸ್ಥಾನಾಂತರ		0x08  /**< Alarm Output Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_CONVST_ಸ್ಥಾನಾಂತರ	0x0C  /**< ADC Convert Start Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_ARR_ಸ್ಥಾನಾಂತರ		0x10  /**< ADC Reset Register */

/* System Monitor/ADC Interrupt Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_GIER_ಸ್ಥಾನಾಂತರ	0x5C  /**< Global Interrupt Enable Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_ISR_ಸ್ಥಾನಾಂತರ	        0x60  /**< Interrupt Status Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_IER_ಸ್ಥಾನಾಂತರ		0x68  /**< Interrupt Enable register */

/* System Monitor/ADC Internal Channel Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_ತಾತ್ಕಾಲಿಕ_ಸ್ಥಾನಾಂತರ	  (0x200)   /**< On-chip Temperature Reg */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_VCCINT_ಸ್ಥಾನಾಂತರ	  (0x204)   /**< On-chip VCCINT Data Reg */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_VCCAUX_ಸ್ಥಾನಾಂತರ	  (0x208)   /**< On-chip VCCAUX Data Reg */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_VPVN_ಸ್ಥಾನಾಂತರ	  (0x20C)   /**< ADC out of VP/VN	   */

/* System Monitor/ADC External Channel Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX00_ಸ್ಥಾನಾಂತರ	(0x240)   /**< ADC out of VAUXP0/VAUXN0 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX01_ಸ್ಥಾನಾಂತರ	(0x244)   /**< ADC out of VAUXP1/VAUXN1 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX02_ಸ್ಥಾನಾಂತರ	(0x248)   /**< ADC out of VAUXP2/VAUXN2 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX03_ಸ್ಥಾನಾಂತರ	(0x24C)   /**< ADC out of VAUXP3/VAUXN3 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX04_ಸ್ಥಾನಾಂತರ	(0x250)   /**< ADC out of VAUXP4/VAUXN4 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX05_ಸ್ಥಾನಾಂತರ	(0x254)   /**< ADC out of VAUXP5/VAUXN5 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX06_ಸ್ಥಾನಾಂತರ	(0x258)   /**< ADC out of VAUXP6/VAUXN6 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX07_ಸ್ಥಾನಾಂತರ	(0x25C)   /**< ADC out of VAUXP7/VAUXN7 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX08_ಸ್ಥಾನಾಂತರ	(0x260)   /**< ADC out of VAUXP8/VAUXN8 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX09_ಸ್ಥಾನಾಂತರ	(0x264)   /**< ADC out of VAUXP9/VAUXN9 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX10_ಸ್ಥಾನಾಂತರ	(0x268)   /**< ADC out of VAUXP10/VAUXN10 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX11_ಸ್ಥಾನಾಂತರ	(0x26C)   /**< ADC out of VAUXP11/VAUXN11 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX12_ಸ್ಥಾನಾಂತರ	(0x270)   /**< ADC out of VAUXP12/VAUXN12 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX13_ಸ್ಥಾನಾಂತರ	(0x274)   /**< ADC out of VAUXP13/VAUXN13 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX14_ಸ್ಥಾನಾಂತರ	(0x278)   /**< ADC out of VAUXP14/VAUXN14 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_AUX15_ಸ್ಥಾನಾಂತರ	(0x27C)   /**< ADC out of VAUXP15/VAUXN15 */

/*
 * System Monitor/ADC Registers for Maximum/Minimum data captured for the
 * on chip Temperature/VCCINT/VCCAUX data. 
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_ತಾತ್ಕಾಲಿಕ_ಸ್ಥಾನಾಂತರ	(0x280)   /**< Maximum Temperature Reg */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VCCINT_ಸ್ಥಾನಾಂತರ	(0x284)   /**< Maximum VCCINT Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VCCAUX_ಸ್ಥಾನಾಂತರ	(0x288)   /**< Maximum VCCAUX Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VBRAM_ಸ್ಥಾನಾಂತರ	(0x28C)   /**< Maximum VBRAM Reg / */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_ತಾತ್ಕಾಲಿಕ_ಸ್ಥಾನಾಂತರ	(0x290)   /**< Minimum Temperature Reg */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VCCINT_ಸ್ಥಾನಾಂತರ	(0x294)   /**< Minimum VCCINT Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VCCAUX_ಸ್ಥಾನಾಂತರ	(0x298)   /**< Minimum VCCAUX Register */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VBRAM_ಸ್ಥಾನಾಂತರ	(0x29C)   /**< Maximum VBRAM Reg / */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VCCPINT_ಸ್ಥಾನಾಂತರ	(0x2A0)   /**< Max VCCPINT Register  */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VCCPAUX_ಸ್ಥಾನಾಂತರ	(0x2A4)   /**< Max VCCPAUX Register  */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MAX_VCCPDRO_ಸ್ಥಾನಾಂತರ	(0x2A8)   /**< Max VCCPDRO Register  */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VCCPINT_ಸ್ಥಾನಾಂತರ	(0x2AC)   /**< Min VCCPINT Register  */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VCCPAUX_ಸ್ಥಾನಾಂತರ	(0x2B0)   /**< Min VCCPAUX Register  */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_MIN_VCCPDRO_ಸ್ಥಾನಾಂತರ	(0x2B4)   /**< Min VCCPDRO Register  */


#ವ್ಯಾಖ್ಯಾನಿಸು XADC_FLAG_REG_ಸ್ಥಾನಾಂತರ	(0x2FC) /**< General Status */

/* System Monitor/ADC Configuration Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_CFR0_ಸ್ಥಾನಾಂತರ		(0x300)   /**< Configuration Register 0 */

/* System Monitor/ADC Sequence Registers */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ00_ಸ್ಥಾನಾಂತರ	(0x320)   /**< Seq Reg 00 Adc Channel Selection */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ01_ಸ್ಥಾನಾಂತರ	(0x324)   /**< Seq Reg 01 Adc Channel Selection */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ02_ಸ್ಥಾನಾಂತರ	(0x328)   /**< Seq Reg 02 Adc Average Enable */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ03_ಸ್ಥಾನಾಂತರ	(0x32C)   /**< Seq Reg 03 Adc Average Enable */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ04_ಸ್ಥಾನಾಂತರ	(0x330)   /**< Seq Reg 04 Adc Input Mode Select */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ05_ಸ್ಥಾನಾಂತರ	(0x334)   /**< Seq Reg 05 Adc Input Mode Select */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ06_ಸ್ಥಾನಾಂತರ	(0x338)   /**< Seq Reg 06 Adc Acquisition Select */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ07_ಸ್ಥಾನಾಂತರ	(0x33C)   /**< Seq Reg 07 Adc Acquisition Select */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ08_ಸ್ಥಾನಾಂತರ	(0x318)   /**< Seq Reg 08 Adc Channel Selection */
#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SEQ09_ಸ್ಥಾನಾಂತರ	(0x31C)   /**< Seq Reg 09 Adc Average Enable */

/* @name System Monitor/ADC Software Reset Register (SRR) mask(s) */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_SRR_RESET_ಮೌಲ್ಯ	0x0000000A   /**< Device Reset Mask */

/* @name System Monitor/ADC Reset Register (ARR) mask(s) */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_ARR_RST_ಮುಖವಾಡ	0x00000001 /**< ADC Reset bit mask */

/* @name Global Interrupt Enable Register (GIER) mask(s) */

#ವ್ಯಾಖ್ಯಾನಿಸು XADC_GIER_GIE_ಮುಖವಾಡ	0x80000000 /**< Global interrupt enable */

/************************** Function Prototypes ******************************/

ಶೂನ್ಯ xadc_write_ctrl_reg(uint32_t *ವಿಳಾಸ, uint32_t ದತ್ತಾಂಶ_2);
uint32_t xadc_read_ctrl_reg(uint32_t *ವಿಳಾಸ);
uint32_t xadc_read_ದತ್ತಾಂಶ(uint32_t *ವಿಳಾಸ);
ದಶಮಾಂಶ xadc_onchip_ತಾತ್ಕಾಲಿಕ(uint32_t ಮೌಲ್ಯ);
ದಶಮಾಂಶ xadc_onchip_voltage(uint32_t ಮೌಲ್ಯ);
ದಶಮಾಂಶ xadc_dedicated_channel(uint32_t ಮೌಲ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ
