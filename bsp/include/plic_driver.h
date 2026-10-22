/***************************************************************************
* Project           	     : shakti devt board
* Name of the file	     : plic_driver.h
* Brief Description of file  : Header file for plic driver.
* Name of Author    	     : Sathya Narayanan N
* Email ID                   : sathya281@gmail.com

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
***************************************************************************/
/**
 * @file plic_driver.h
 * @brief  Header file for plic driver.c
 * @detail This file contains the definitions for plic driver. The memory map
 * for the plic module is also defined here.
 */

#यदि_अपरिभाषितम् PLIC_DRIVER_H
#परिभाषय PLIC_DRIVER_H
#अन्तर्भाव "platform.h"
#अन्तर्भाव "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#परिभाषय PLIC_प्राथमिकता_विस्थापनम्            0x0000UL
#परिभाषय PLIC_PENDING_विस्थापनम्             0x1000UL
#परिभाषय PLIC_ENABLE_विस्थापनम्              0x2000UL
#परिभाषय PLIC_देहली_विस्थापनम्           0x10000UL
#परिभाषय PLIC_CLAIM_विस्थापनम्               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#परिभाषय PLIC_प्राथमिकता_सरणम्_प्रत्येकम्_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#परिभाषय PLIC_प्राथमिकता_1 0X00
#परिभाषय PLIC_प्राथमिकता_2 0X01
#परिभाषय PLIC_प्राथमिकता_3 0X02
#परिभाषय PLIC_प्राथमिकता_4 0X04
#परिभाषय PLIC_प्राथमिकता_5 0X08
#परिभाषय PLIC_प्राथमिकता_6 0X10
#परिभाषय PLIC_प्राथमिकता_7 0X20

#परिभाषय PLIC_PENDING_सरणम्_प्रत्येकम्_SOURCE   0

/* Enumerators */

प्रकारनिर्देश गणना
{
	INACTIVE = 0,
	सक्रिय   = 1,
	SERVICED = 2,
	MASKED
}व्यवधानम्_स्थितिः_e;

/* Structures and Unions */

प्रकारनिर्देश संरचना
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t प्राथमिकता; /*priority assigned to it*/
	व्यवधानम्_स्थितिः_e state; /*state of the interrupt*/
	uint32_t गणनम्; /*number of times this interrupt occured*/
} व्यवधानम्_दत्त_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

प्रकारनिर्देश शून्य (*plic_fptr_t) (uint32_t);
बाह्य plic_fptr_t isr_सारणी[PLIC_MAX_व्यवधानम्_SRC];

/* Function prototypes */

शून्य व्यवधानम्_complete(uint32_t व्यवधानम्_id);
uint32_t व्यवधानम्_claim_request(शून्य);
शून्य isr_default(uint32_t व्यवधानम्_id);
शून्य व्यवधानम्_enable(uint32_t व्यवधानम्_id);
शून्य mach_plic_handler(uintptr_t int_id, uintptr_t epc);
शून्य व्यवधानम्_disable(uint32_t व्यवधानम्_id);
शून्य समुच्चयः_व्यवधानम्_देहली(uint32_t प्राथमिकता_मानम्);
शून्य समुच्चयः_व्यवधानम्_प्राथमिकता(uint32_t प्राथमिकता_मानम्, uint32_t int_id);
शून्य configure_व्यवधानम्_pin(uint32_t pin);
शून्य plic_init(शून्य);
शून्य configure_व्यवधानम्(uint32_t int_id);

#यदि_अन्तः
