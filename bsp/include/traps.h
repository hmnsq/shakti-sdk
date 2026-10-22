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

#جيڪڏهن_وصف_نه_ٿيل TRAPS_H
#وصف_ڪريو TRAPS_H
#ضمن <stdint.h>

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

#وصف_ڪريو MAX_MCAUSE_قدر               32


/*  Interrupts */
#وصف_ڪريو MAX_مداخلت_قدر            16

#وصف_ڪريو USER_SW_مداخلت               0
#وصف_ڪريو SUPER_SW_مداخلت              1
#وصف_ڪريو RESERVED_INTERRUPT0             2
#وصف_ڪريو MACH_SW_مداخلت               3
#وصف_ڪريو USER_TIMER_مداخلت            4
#وصف_ڪريو SUPER_TIMER_مداخلت           5
#وصف_ڪريو RESERVED_INTERRUPT1             6
#وصف_ڪريو MACH_TIMER_مداخلت            7
#وصف_ڪريو USER_EXT_مداخلت              8
#وصف_ڪريو SUPERVISOR_EXT_مداخلت        9
#وصف_ڪريو RESERVED_INTERRUPT2            10
#وصف_ڪريو MACH_EXTERNAL_مداخلت        11
#وصف_ڪريو RESERVED_INTERRUPT3            12
#وصف_ڪريو RESERVED_INTERRUPT4            13
#وصف_ڪريو RESERVED_INTERRUPT5            14
#وصف_ڪريو RESERVED_INTERRUPT6            15

/* Traps */
#وصف_ڪريو MAX_TRAP_قدر                 16

#وصف_ڪريو INSTRUCTION_پتو_MISALIGNED  0
#وصف_ڪريو INSTRUCTION_ACCESS_FAULT        1
#وصف_ڪريو ILLEGAL_INSTRUCTION             2
#وصف_ڪريو BREAKPOINT                      3
#وصف_ڪريو ڀريو_پتو_MISALIGNED         4
#وصف_ڪريو ڀريو_ACCESS_FAULT               5
#وصف_ڪريو STORE_AMO_پتو_MISALIGNED    6
#وصف_ڪريو STORE_AMO_ACCESS_FAULT          7
#وصف_ڪريو ENVIRONMENT_CALL_FROM_U_گهڻائي    8
#وصف_ڪريو ENVIRONMENT_CALL_FROM_S_گهڻائي    9
#وصف_ڪريو RESERVED_TRAP1                 10
#وصف_ڪريو ENVIRONMENT_CALL_FROM_M_گهڻائي   11
#وصف_ڪريو INSTRUCTION_صفحو_FAULT         12
#وصف_ڪريو ڀريو_صفحو_FAULT                13
#وصف_ڪريو RESERVED_TRAP2                 14
#وصف_ڪريو STORE_AMO_صفحو_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

تعريفنوع فراغ (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
خارجي mtrap_fptr_t mcause_trap_جدول[MAX_TRAP_قدر];
خارجي mtrap_fptr_t mcause_مداخلت_جدول[MAX_مداخلت_قدر];

فراغ default_handler(uintptr_t cause, uintptr_t epc);
بنانشان صحيح ڪڍو_ie_ڪوڊ(بنانشان صحيح انگ);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#جيڪڏهن_پورو
