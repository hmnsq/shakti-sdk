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

#अगर_अघोषित PLIC_DRIVER_H
#घोषणा PLIC_DRIVER_H
#समावेश "platform.h"
#समावेश "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#घोषणा PLIC_PRIORITY_OFFSET            0x0000UL
#घोषणा PLIC_PENDING_OFFSET             0x1000UL
#घोषणा PLIC_ENABLE_OFFSET              0x2000UL
#घोषणा PLIC_THRESHOLD_OFFSET           0x10000UL
#घोषणा PLIC_CLAIM_OFFSET               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#घोषणा PLIC_PRIORITY_SHIFT_PER_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#घोषणा PLIC_PRIORITY_1 0X00
#घोषणा PLIC_PRIORITY_2 0X01
#घोषणा PLIC_PRIORITY_3 0X02
#घोषणा PLIC_PRIORITY_4 0X04
#घोषणा PLIC_PRIORITY_5 0X08
#घोषणा PLIC_PRIORITY_6 0X10
#घोषणा PLIC_PRIORITY_7 0X20

#घोषणा PLIC_PENDING_SHIFT_PER_SOURCE   0

/* Enumerators */

प्रकार क्रमागत
{
	INACTIVE = 0,
	ACTIVE   = 1,
	SERVICED = 2,
	MASKED
}interrupt_status_e;

/* Structures and Unions */

प्रकार काष्ठा
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t priority; /*priority assigned to it*/
	interrupt_status_e state; /*state of the interrupt*/
	uint32_t गिनती; /*number of times this interrupt occured*/
} interrupt_तथ्य_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

प्रकार व्योम (*plic_fptr_t) (uint32_t);
बाह्य plic_fptr_t isr_table[PLIC_MAX_INTERRUPT_SRC];

/* Function prototypes */

व्योम interrupt_complete(uint32_t interrupt_id);
uint32_t interrupt_claim_request(व्योम);
व्योम isr_default(uint32_t interrupt_id);
व्योम interrupt_enable(uint32_t interrupt_id);
व्योम mach_plic_handler(uintptr_t int_id, uintptr_t epc);
व्योम interrupt_disable(uint32_t interrupt_id);
व्योम set_interrupt_threshold(uint32_t priority_मूल्य);
व्योम set_interrupt_priority(uint32_t priority_मूल्य, uint32_t int_id);
व्योम configure_interrupt_pin(uint32_t pin);
व्योम plic_init(व्योम);
व्योम configure_interrupt(uint32_t int_id);

#पूर्ण_अगर
