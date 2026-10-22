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

#اگر_غیر_تعریف_شدہ PLIC_DRIVER_H
#تعریف_کرو PLIC_DRIVER_H
#شامل "platform.h"
#شامل "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#تعریف_کرو PLIC_ترجیح_انحراف            0x0000UL
#تعریف_کرو PLIC_PENDING_انحراف             0x1000UL
#تعریف_کرو PLIC_ENABLE_انحراف              0x2000UL
#تعریف_کرو PLIC_حد_انحراف           0x10000UL
#تعریف_کرو PLIC_CLAIM_انحراف               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#تعریف_کرو PLIC_ترجیح_سرکاؤ_فی_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#تعریف_کرو PLIC_ترجیح_1 0X00
#تعریف_کرو PLIC_ترجیح_2 0X01
#تعریف_کرو PLIC_ترجیح_3 0X02
#تعریف_کرو PLIC_ترجیح_4 0X04
#تعریف_کرو PLIC_ترجیح_5 0X08
#تعریف_کرو PLIC_ترجیح_6 0X10
#تعریف_کرو PLIC_ترجیح_7 0X20

#تعریف_کرو PLIC_PENDING_سرکاؤ_فی_ماخذ   0

/* Enumerators */

قسمتعریف شمار
{
	INACTIVE = 0,
	فعال   = 1,
	SERVICED = 2,
	MASKED
}مداخلت_حالت_e;

/* Structures and Unions */

قسمتعریف ساخت
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ترجیح; /*priority assigned to it*/
	مداخلت_حالت_e state; /*state of the interrupt*/
	uint32_t گنتی; /*number of times this interrupt occured*/
} مداخلت_ڈیٹا_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

قسمتعریف خالی (*plic_fptr_t) (uint32_t);
خارجی plic_fptr_t isr_جدول[PLIC_MAX_مداخلت_SRC];

/* Function prototypes */

خالی مداخلت_complete(uint32_t مداخلت_id);
uint32_t مداخلت_claim_request(خالی);
خالی isr_default(uint32_t مداخلت_id);
خالی مداخلت_enable(uint32_t مداخلت_id);
خالی mach_plic_handler(uintptr_t int_id, uintptr_t epc);
خالی مداخلت_disable(uint32_t مداخلت_id);
خالی سیٹ_مداخلت_حد(uint32_t ترجیح_قدر);
خالی سیٹ_مداخلت_ترجیح(uint32_t ترجیح_قدر, uint32_t int_id);
خالی configure_مداخلت_pin(uint32_t pin);
خالی plic_init(خالی);
خالی configure_مداخلت(uint32_t int_id);

#اگر_ختم
