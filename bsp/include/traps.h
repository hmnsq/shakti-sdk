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

#यदि_अपरिभाषितम् TRAPS_H
#परिभाषय TRAPS_H
#अन्तर्भाव <stdint.h>

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

#परिभाषय MAX_MCAUSE_मानम्               32


/*  Interrupts */
#परिभाषय MAX_व्यवधानम्_मानम्            16

#परिभाषय USER_SW_व्यवधानम्               0
#परिभाषय SUPER_SW_व्यवधानम्              1
#परिभाषय RESERVED_INTERRUPT0             2
#परिभाषय MACH_SW_व्यवधानम्               3
#परिभाषय USER_TIMER_व्यवधानम्            4
#परिभाषय SUPER_TIMER_व्यवधानम्           5
#परिभाषय RESERVED_INTERRUPT1             6
#परिभाषय MACH_TIMER_व्यवधानम्            7
#परिभाषय USER_EXT_व्यवधानम्              8
#परिभाषय SUPERVISOR_EXT_व्यवधानम्        9
#परिभाषय RESERVED_INTERRUPT2            10
#परिभाषय MACH_EXTERNAL_व्यवधानम्        11
#परिभाषय RESERVED_INTERRUPT3            12
#परिभाषय RESERVED_INTERRUPT4            13
#परिभाषय RESERVED_INTERRUPT5            14
#परिभाषय RESERVED_INTERRUPT6            15

/* Traps */
#परिभाषय MAX_TRAP_मानम्                 16

#परिभाषय INSTRUCTION_स्थानाङ्कः_MISALIGNED  0
#परिभाषय INSTRUCTION_ACCESS_FAULT        1
#परिभाषय ILLEGAL_INSTRUCTION             2
#परिभाषय BREAKPOINT                      3
#परिभाषय आरोपय_स्थानाङ्कः_MISALIGNED         4
#परिभाषय आरोपय_ACCESS_FAULT               5
#परिभाषय STORE_AMO_स्थानाङ्कः_MISALIGNED    6
#परिभाषय STORE_AMO_ACCESS_FAULT          7
#परिभाषय ENVIRONMENT_CALL_FROM_U_बहुलकम्    8
#परिभाषय ENVIRONMENT_CALL_FROM_S_बहुलकम्    9
#परिभाषय RESERVED_TRAP1                 10
#परिभाषय ENVIRONMENT_CALL_FROM_M_बहुलकम्   11
#परिभाषय INSTRUCTION_PAGE_FAULT         12
#परिभाषय आरोपय_PAGE_FAULT                13
#परिभाषय RESERVED_TRAP2                 14
#परिभाषय STORE_AMO_PAGE_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

प्रकारनिर्देश शून्य (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
बाह्य mtrap_fptr_t mcause_trap_सारणी[MAX_TRAP_मानम्];
बाह्य mtrap_fptr_t mcause_व्यवधानम्_सारणी[MAX_व्यवधानम्_मानम्];

शून्य default_handler(uintptr_t cause, uintptr_t epc);
अचिह्नित पूर्णाङ्क extract_ie_संहिता(अचिह्नित पूर्णाङ्क अङ्कः);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#यदि_अन्तः
