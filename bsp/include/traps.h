/***************************************************************************
 * Project                          : shakti devt board
 * Name of the file                 : traps.h
 * Brief Description of file        : Header file for handling traps
 * Name of Author                   : Sathya Narayanan N
 * Email ID                         : sathya281@gmail.com

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
*******************************************************************************/
/**
 * @file traps.h
 * @brief Header file for handling traps
 * @detail This is the header file for traps.c. Here the definitions for
 * handling traps are declared.
 */

#अगर_अघोषित TRAPS_H
#घोषणा TRAPS_H
#समावेश <stdint.h>

/*
   Table 3.6 risc v priv spec v1.10 chapter 7

   -------------------------------------------------------------
   Interrupt  Exception Code   Description
   -------------------------------------------------------------
   1           0                User software interrupt
   1           1                Supervisor software interrupt
   1           2                Reserved
   1           3                Machine software interrupt
   1           4                User timer interrupt
   1           5                Supervisor timer interrupt
   1           6                Reserved
   1           7                Machine timer interrupt
   1           8                User external interrupt
   1           9                Supervisor external interrupt
   1           10               Reserved
   1           11               Machine external interrupt
   1           ≥12              Reserved
   0           0                Instruction address misaligned
   0           1                Instruction access fault
   0           2                Illegal instruction
   0           3                Breakpoint
   0           4                Load address misaligned
   0           5                Load access fault
   0           6                Store/AMO address misaligned
   0           7                Store/AMO access fault
   0           8                Environment call from U-mode
   0           9                Environment call from S-mode
   0           10               Reserved
   0           11               Environment call from M-mode
   0           12               Instruction page fault
   0           13               Load page fault
   0           14               Reserved
   0           15               Store/AMO page fault
   0           ≥16              Reserved
   ---------------------------------------------------------------

   Off the 32 entries in the table, some index positions reserved for future use
 */

#घोषणा MAX_MCAUSE_मूल्य               32


/*  Interrupts */
#घोषणा MAX_INTERRUPT_मूल्य            16

#घोषणा USER_SW_INTERRUPT               0
#घोषणा SUPER_SW_INTERRUPT              1
#घोषणा RESERVED_INTERRUPT0             2
#घोषणा MACH_SW_INTERRUPT               3
#घोषणा USER_TIMER_INTERRUPT            4
#घोषणा SUPER_TIMER_INTERRUPT           5
#घोषणा RESERVED_INTERRUPT1             6
#घोषणा MACH_TIMER_INTERRUPT            7
#घोषणा USER_EXT_INTERRUPT              8
#घोषणा SUPERVISOR_EXT_INTERRUPT        9
#घोषणा RESERVED_INTERRUPT2            10
#घोषणा MACH_EXTERNAL_INTERRUPT        11
#घोषणा RESERVED_INTERRUPT3            12
#घोषणा RESERVED_INTERRUPT4            13
#घोषणा RESERVED_INTERRUPT5            14
#घोषणा RESERVED_INTERRUPT6            15

/* Traps */
#घोषणा MAX_TRAP_मूल्य                 16

#घोषणा INSTRUCTION_ADDRESS_MISALIGNED  0
#घोषणा INSTRUCTION_ACCESS_FAULT        1
#घोषणा ILLEGAL_INSTRUCTION             2
#घोषणा BREAKPOINT                      3
#घोषणा LOAD_ADDRESS_MISALIGNED         4
#घोषणा LOAD_ACCESS_FAULT               5
#घोषणा STORE_AMO_ADDRESS_MISALIGNED    6
#घोषणा STORE_AMO_ACCESS_FAULT          7
#घोषणा ENVIRONMENT_CALL_FROM_U_MODE    8
#घोषणा ENVIRONMENT_CALL_FROM_S_MODE    9
#घोषणा RESERVED_TRAP1                 10
#घोषणा ENVIRONMENT_CALL_FROM_M_MODE   11
#घोषणा INSTRUCTION_PAGE_FAULT         12
#घोषणा LOAD_PAGE_FAULT                13
#घोषणा RESERVED_TRAP2                 14
#घोषणा STORE_AMO_PAGE_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

प्रकार व्योम (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
बाह्य mtrap_fptr_t mcause_trap_table[MAX_TRAP_मूल्य];
बाह्य mtrap_fptr_t mcause_interrupt_table[MAX_INTERRUPT_मूल्य];

व्योम default_handler(uintptr_t cause, uintptr_t epc);
अचिन्हित पूर्णांक extract_ie_code(अचिन्हित पूर्णांक अंक);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#पूर्ण_अगर
