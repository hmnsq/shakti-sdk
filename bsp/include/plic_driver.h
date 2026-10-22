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

#اگر_تعریف_نشده PLIC_DRIVER_H
#تعریف_کن PLIC_DRIVER_H
#ضمن "platform.h"
#ضمن "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#تعریف_کن PLIC_اولویت_جابه_جایی            0x0000UL
#تعریف_کن PLIC_PENDING_جابه_جایی             0x1000UL
#تعریف_کن PLIC_ENABLE_جابه_جایی              0x2000UL
#تعریف_کن PLIC_آستانه_جابه_جایی           0x10000UL
#تعریف_کن PLIC_CLAIM_جابه_جایی               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#تعریف_کن PLIC_اولویت_لغزش_در_هر_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#تعریف_کن PLIC_اولویت_1 0X00
#تعریف_کن PLIC_اولویت_2 0X01
#تعریف_کن PLIC_اولویت_3 0X02
#تعریف_کن PLIC_اولویت_4 0X04
#تعریف_کن PLIC_اولویت_5 0X08
#تعریف_کن PLIC_اولویت_6 0X10
#تعریف_کن PLIC_اولویت_7 0X20

#تعریف_کن PLIC_PENDING_لغزش_در_هر_منبع   0

/* Enumerators */

تعريفنوع تعداد
{
	INACTIVE = 0,
	فعال   = 1,
	SERVICED = 2,
	MASKED
}وقفه_وضعیت_e;

/* Structures and Unions */

تعريفنوع بنية
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t اولویت; /*priority assigned to it*/
	وقفه_وضعیت_e state; /*state of the interrupt*/
	uint32_t شمار; /*number of times this interrupt occured*/
} وقفه_داده_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

تعريفنوع فراغ (*plic_fptr_t) (uint32_t);
خارجي plic_fptr_t isr_جدول[PLIC_MAX_وقفه_SRC];

/* Function prototypes */

فراغ وقفه_complete(uint32_t وقفه_id);
uint32_t وقفه_claim_request(فراغ);
فراغ isr_default(uint32_t وقفه_id);
فراغ وقفه_enable(uint32_t وقفه_id);
فراغ mach_plic_handler(uintptr_t int_id, uintptr_t epc);
فراغ وقفه_disable(uint32_t وقفه_id);
فراغ مجموعه_وقفه_آستانه(uint32_t اولویت_مقدار);
فراغ مجموعه_وقفه_اولویت(uint32_t اولویت_مقدار, uint32_t int_id);
فراغ configure_وقفه_pin(uint32_t pin);
فراغ plic_init(فراغ);
فراغ configure_وقفه(uint32_t int_id);

#پایان_اگر
