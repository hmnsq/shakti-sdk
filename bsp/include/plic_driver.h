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

#నిర్వచితం_కాకపోతే PLIC_DRIVER_H
#నిర్వచించు PLIC_DRIVER_H
#అన్తర్భావ "platform.h"
#అన్తర్భావ "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#నిర్వచించు PLIC_ప్రాధాన్యత_స్థానభ్రంశం            0x0000UL
#నిర్వచించు PLIC_PENDING_స్థానభ్రంశం             0x1000UL
#నిర్వచించు PLIC_ENABLE_స్థానభ్రంశం              0x2000UL
#నిర్వచించు PLIC_పరిమితి_స్థానభ్రంశం           0x10000UL
#నిర్వచించు PLIC_CLAIM_స్థానభ్రంశం               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#నిర్వచించు PLIC_ప్రాధాన్యత_జరుపు_చొప్పున_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#నిర్వచించు PLIC_ప్రాధాన్యత_1 0X00
#నిర్వచించు PLIC_ప్రాధాన్యత_2 0X01
#నిర్వచించు PLIC_ప్రాధాన్యత_3 0X02
#నిర్వచించు PLIC_ప్రాధాన్యత_4 0X04
#నిర్వచించు PLIC_ప్రాధాన్యత_5 0X08
#నిర్వచించు PLIC_ప్రాధాన్యత_6 0X10
#నిర్వచించు PLIC_ప్రాధాన్యత_7 0X20

#నిర్వచించు PLIC_PENDING_జరుపు_చొప్పున_ఆధారం   0

/* Enumerators */

రకనిర్వచనం గణన
{
	INACTIVE = 0,
	చురుకైన   = 1,
	SERVICED = 2,
	MASKED
}అంతరాయం_స్థితి_e;

/* Structures and Unions */

రకనిర్వచనం నిర్మాణం
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ప్రాధాన్యత; /*priority assigned to it*/
	అంతరాయం_స్థితి_e state; /*state of the interrupt*/
	uint32_t లెక్క; /*number of times this interrupt occured*/
} అంతరాయం_దత్తాంశం_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

రకనిర్వచనం శూన్య (*plic_fptr_t) (uint32_t);
బాహ్య plic_fptr_t isr_పట్టిక[PLIC_MAX_అంతరాయం_SRC];

/* Function prototypes */

శూన్య అంతరాయం_complete(uint32_t అంతరాయం_id);
uint32_t అంతరాయం_claim_request(శూన్య);
శూన్య isr_default(uint32_t అంతరాయం_id);
శూన్య అంతరాయం_enable(uint32_t అంతరాయం_id);
శూన్య mach_plic_handler(uintptr_t int_id, uintptr_t epc);
శూన్య అంతరాయం_disable(uint32_t అంతరాయం_id);
శూన్య సమితి_అంతరాయం_పరిమితి(uint32_t ప్రాధాన్యత_విలువ);
శూన్య సమితి_అంతరాయం_ప్రాధాన్యత(uint32_t ప్రాధాన్యత_విలువ, uint32_t int_id);
శూన్య configure_అంతరాయం_pin(uint32_t pin);
శూన్య plic_init(శూన్య);
శూన్య configure_అంతరాయం(uint32_t int_id);

#అయితే_ముగింపు
