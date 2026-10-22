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

#جے_بنا_تعریف PLIC_DRIVER_H
#تعریف_کرو PLIC_DRIVER_H
#ضمن "platform.h"
#ضمن "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#تعریف_کرو PLIC_ترجیح_وتھ            0x0000UL
#تعریف_کرو PLIC_PENDING_وتھ             0x1000UL
#تعریف_کرو PLIC_ENABLE_وتھ              0x2000UL
#تعریف_کرو PLIC_حد_وتھ           0x10000UL
#تعریف_کرو PLIC_CLAIM_وتھ               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#تعریف_کرو PLIC_ترجیح_کھسکاؤ_فی_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#تعریف_کرو PLIC_ترجیح_1 0X00
#تعریف_کرو PLIC_ترجیح_2 0X01
#تعریف_کرو PLIC_ترجیح_3 0X02
#تعریف_کرو PLIC_ترجیح_4 0X04
#تعریف_کرو PLIC_ترجیح_5 0X08
#تعریف_کرو PLIC_ترجیح_6 0X10
#تعریف_کرو PLIC_ترجیح_7 0X20

#تعریف_کرو PLIC_PENDING_کھسکاؤ_فی_سروت   0

/* Enumerators */

تعريفنوع تعداد
{
	INACTIVE = 0,
	سرگرم   = 1,
	SERVICED = 2,
	MASKED
}رکاوٹ_حالت_e;

/* Structures and Unions */

تعريفنوع بنية
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ترجیح; /*priority assigned to it*/
	رکاوٹ_حالت_e state; /*state of the interrupt*/
	uint32_t گنتی; /*number of times this interrupt occured*/
} رکاوٹ_انکڑے_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

تعريفنوع فراغ (*plic_fptr_t) (uint32_t);
خارجي plic_fptr_t isr_جدول[PLIC_MAX_رکاوٹ_SRC];

/* Function prototypes */

فراغ رکاوٹ_complete(uint32_t رکاوٹ_id);
uint32_t رکاوٹ_claim_request(فراغ);
فراغ isr_default(uint32_t رکاوٹ_id);
فراغ رکاوٹ_enable(uint32_t رکاوٹ_id);
فراغ mach_plic_handler(uintptr_t int_id, uintptr_t epc);
فراغ رکاوٹ_disable(uint32_t رکاوٹ_id);
فراغ سیٹ_رکاوٹ_حد(uint32_t ترجیح_قدر);
فراغ سیٹ_رکاوٹ_ترجیح(uint32_t ترجیح_قدر, uint32_t int_id);
فراغ configure_رکاوٹ_pin(uint32_t pin);
فراغ plic_init(فراغ);
فراغ configure_رکاوٹ(uint32_t int_id);

#جے_انت
