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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PLIC_DRIVER_H
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_DRIVER_H
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "traps.h"

/* Macros */

/* Offsets for different registers in plic */

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_ಸ್ಥಾನಾಂತರ            0x0000UL
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_PENDING_ಸ್ಥಾನಾಂತರ             0x1000UL
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ENABLE_ಸ್ಥಾನಾಂತರ              0x2000UL
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಮಿತಿ_ಸ್ಥಾನಾಂತರ           0x10000UL
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_CLAIM_ಸ್ಥಾನಾಂತರ               0x10010UL

/* The priority value for each int src can be found at addresses 4 bytes apart
   starting from base address + priority offset */

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_ಸರಿಸು_ಪ್ರತಿ_INT  2

/* 7 priority levels are supported.
   PLIC_PRIORITY_1 means 'no interrupt */

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_1 0X00
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_2 0X01
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_3 0X02
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_4 0X04
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_5 0X08
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_6 0X10
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಆದ್ಯತೆ_7 0X20

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_PENDING_ಸರಿಸು_ಪ್ರತಿ_ಮೂಲ   0

/* Enumerators */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
	INACTIVE = 0,
	ಸಕ್ರಿಯ   = 1,
	SERVICED = 2,
	MASKED
}ಅಡಚಣೆ_ಸ್ಥಿತಿ_e;

/* Structures and Unions */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
	uint32_t id; /*id of the interrupt target source*/
	uint32_t ಆದ್ಯತೆ; /*priority assigned to it*/
	ಅಡಚಣೆ_ಸ್ಥಿತಿ_e state; /*state of the interrupt*/
	uint32_t ಎಣಿಕೆ_2; /*number of times this interrupt occured*/
} ಅಡಚಣೆ_ದತ್ತಾಂಶ_t;

/* Platform Level Interrupt Controller (PLIC) table
   Each entry in the table corresponds to an interrupt service routine */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*plic_fptr_t) (uint32_t);
ಬಾಹ್ಯ plic_fptr_t isr_ಕೋಷ್ಟಕ[PLIC_MAX_ಅಡಚಣೆ_SRC];

/* Function prototypes */

ಶೂನ್ಯ ಅಡಚಣೆ_complete(uint32_t ಅಡಚಣೆ_id);
uint32_t ಅಡಚಣೆ_claim_request(ಶೂನ್ಯ);
ಶೂನ್ಯ isr_default(uint32_t ಅಡಚಣೆ_id);
ಶೂನ್ಯ ಅಡಚಣೆ_enable(uint32_t ಅಡಚಣೆ_id);
ಶೂನ್ಯ mach_plic_handler(uintptr_t int_id, uintptr_t epc);
ಶೂನ್ಯ ಅಡಚಣೆ_disable(uint32_t ಅಡಚಣೆ_id);
ಶೂನ್ಯ ಗಣ_ಅಡಚಣೆ_ಮಿತಿ(uint32_t ಆದ್ಯತೆ_ಮೌಲ್ಯ);
ಶೂನ್ಯ ಗಣ_ಅಡಚಣೆ_ಆದ್ಯತೆ(uint32_t ಆದ್ಯತೆ_ಮೌಲ್ಯ, uint32_t int_id);
ಶೂನ್ಯ configure_ಅಡಚಣೆ_pin(uint32_t pin);
ಶೂನ್ಯ plic_init(ಶೂನ್ಯ);
ಶೂನ್ಯ configure_ಅಡಚಣೆ(uint32_t int_id);

#ಆದರೆ_ಅಂತ್ಯ
