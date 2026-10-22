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

#جيڪڏهن_وصف_نه_ٿيل PLIC_DRIVER_H
#وصف_ڪريو PLIC_DRIVER_H
#ضمن "platform.h"
#ضمن "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#وصف_ڪريو PLIC_ترجيح_وٿي            0x0000UL
#وصف_ڪريو PLIC_PENDING_وٿي             0x1000UL
#وصف_ڪريو PLIC_ENABLE_وٿي              0x2000UL
#وصف_ڪريو PLIC_حد_وٿي           0x10000UL
#وصف_ڪريو PLIC_CLAIM_وٿي               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#وصف_ڪريو PLIC_ترجيح_سرڪايو_في_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#وصف_ڪريو PLIC_ترجيح_1 0X00
#وصف_ڪريو PLIC_ترجيح_2 0X01
#وصف_ڪريو PLIC_ترجيح_3 0X02
#وصف_ڪريو PLIC_ترجيح_4 0X04
#وصف_ڪريو PLIC_ترجيح_5 0X08
#وصف_ڪريو PLIC_ترجيح_6 0X10
#وصف_ڪريو PLIC_ترجيح_7 0X20

#وصف_ڪريو PLIC_PENDING_سرڪايو_في_ذريعو   0

/* Enumerators */

تعريفنوع تعداد
{
	INACTIVE = 0,
	سرگرم   = 1,
	SERVICED = 2,
	MASKED
}مداخلت_حالت_e;

/* Structures and Unions */

تعريفنوع بنية
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ترجيح; /*priority assigned to it*/
	مداخلت_حالت_e state; /*state of the interrupt*/
	uint32_t ڳڻپ; /*number of times this interrupt occured*/
} مداخلت_معلومات_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

تعريفنوع فراغ (*plic_fptr_t) (uint32_t);
خارجي plic_fptr_t isr_جدول[PLIC_MAX_مداخلت_SRC];

/* Function prototypes */

فراغ مداخلت_complete(uint32_t مداخلت_id);
uint32_t مداخلت_claim_request(فراغ);
فراغ isr_default(uint32_t مداخلت_id);
فراغ مداخلت_enable(uint32_t مداخلت_id);
فراغ mach_plic_handler(uintptr_t int_id, uintptr_t epc);
فراغ مداخلت_disable(uint32_t مداخلت_id);
فراغ سيٽ_مداخلت_حد(uint32_t ترجيح_قدر);
فراغ سيٽ_مداخلت_ترجيح(uint32_t ترجيح_قدر, uint32_t int_id);
فراغ configure_مداخلت_pin(uint32_t pin);
فراغ plic_init(فراغ);
فراغ configure_مداخلت(uint32_t int_id);

#جيڪڏهن_پورو
