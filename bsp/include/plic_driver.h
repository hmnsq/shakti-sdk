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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PLIC_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_DRIVER_H
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_ਵਿੱਥ            0x0000UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_PENDING_ਵਿੱਥ             0x1000UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ENABLE_ਵਿੱਥ              0x2000UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਹੱਦ_ਵਿੱਥ           0x10000UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_CLAIM_ਵਿੱਥ               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_ਖਿਸਕਾਓ_ਪ੍ਰਤੀ_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_1 0X00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_2 0X01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_3 0X02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_4 0X04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_5 0X08
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_6 0X10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਤਰਜੀਹ_7 0X20

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_PENDING_ਖਿਸਕਾਓ_ਪ੍ਰਤੀ_ਸਰੋਤ   0

/* Enumerators */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
	INACTIVE = 0,
	ਸਰਗਰਮ   = 1,
	SERVICED = 2,
	MASKED
}ਰੁਕਾਵਟ_ਸਥਿਤੀ_e;

/* Structures and Unions */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ਤਰਜੀਹ; /*priority assigned to it*/
	ਰੁਕਾਵਟ_ਸਥਿਤੀ_e state; /*state of the interrupt*/
	uint32_t ਗਿਣਤੀ_2; /*number of times this interrupt occured*/
} ਰੁਕਾਵਟ_ਅੰਕੜੇ_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*plic_fptr_t) (uint32_t);
ਬਾਹਰੀ plic_fptr_t isr_ਸਾਰਣੀ[PLIC_MAX_ਰੁਕਾਵਟ_SRC];

/* Function prototypes */

ਖਾਲੀ ਰੁਕਾਵਟ_complete(uint32_t ਰੁਕਾਵਟ_id);
uint32_t ਰੁਕਾਵਟ_claim_request(ਖਾਲੀ);
ਖਾਲੀ isr_default(uint32_t ਰੁਕਾਵਟ_id);
ਖਾਲੀ ਰੁਕਾਵਟ_enable(uint32_t ਰੁਕਾਵਟ_id);
ਖਾਲੀ mach_plic_handler(uintptr_t int_id, uintptr_t epc);
ਖਾਲੀ ਰੁਕਾਵਟ_disable(uint32_t ਰੁਕਾਵਟ_id);
ਖਾਲੀ ਸੈੱਟ_ਰੁਕਾਵਟ_ਹੱਦ(uint32_t ਤਰਜੀਹ_ਮੁੱਲ);
ਖਾਲੀ ਸੈੱਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ(uint32_t ਤਰਜੀਹ_ਮੁੱਲ, uint32_t int_id);
ਖਾਲੀ configure_ਰੁਕਾਵਟ_pin(uint32_t pin);
ਖਾਲੀ plic_init(ਖਾਲੀ);
ਖਾਲੀ configure_ਰੁਕਾਵਟ(uint32_t int_id);

#ਜੇ_ਅੰਤ
