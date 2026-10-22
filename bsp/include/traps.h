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

#اگر_تعریف_نشده TRAPS_H
#تعریف_کن TRAPS_H
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

#تعریف_کن MAX_MCAUSE_مقدار               32


/*  Interrupts */
#تعریف_کن MAX_وقفه_مقدار            16

#تعریف_کن USER_SW_وقفه               0
#تعریف_کن SUPER_SW_وقفه              1
#تعریف_کن RESERVED_INTERRUPT0             2
#تعریف_کن MACH_SW_وقفه               3
#تعریف_کن USER_TIMER_وقفه            4
#تعریف_کن SUPER_TIMER_وقفه           5
#تعریف_کن RESERVED_INTERRUPT1             6
#تعریف_کن MACH_TIMER_وقفه            7
#تعریف_کن USER_EXT_وقفه              8
#تعریف_کن SUPERVISOR_EXT_وقفه        9
#تعریف_کن RESERVED_INTERRUPT2            10
#تعریف_کن MACH_EXTERNAL_وقفه        11
#تعریف_کن RESERVED_INTERRUPT3            12
#تعریف_کن RESERVED_INTERRUPT4            13
#تعریف_کن RESERVED_INTERRUPT5            14
#تعریف_کن RESERVED_INTERRUPT6            15

/* Traps */
#تعریف_کن MAX_TRAP_مقدار                 16

#تعریف_کن INSTRUCTION_آدرس_MISALIGNED  0
#تعریف_کن INSTRUCTION_ACCESS_FAULT        1
#تعریف_کن ILLEGAL_INSTRUCTION             2
#تعریف_کن BREAKPOINT                      3
#تعریف_کن بارگیری_آدرس_MISALIGNED         4
#تعریف_کن بارگیری_ACCESS_FAULT               5
#تعریف_کن STORE_AMO_آدرس_MISALIGNED    6
#تعریف_کن STORE_AMO_ACCESS_FAULT          7
#تعریف_کن ENVIRONMENT_CALL_FROM_U_نما    8
#تعریف_کن ENVIRONMENT_CALL_FROM_S_نما    9
#تعریف_کن RESERVED_TRAP1                 10
#تعریف_کن ENVIRONMENT_CALL_FROM_M_نما   11
#تعریف_کن INSTRUCTION_صفحه_FAULT         12
#تعریف_کن بارگیری_صفحه_FAULT                13
#تعریف_کن RESERVED_TRAP2                 14
#تعریف_کن STORE_AMO_صفحه_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

تعريفنوع فراغ (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
خارجي mtrap_fptr_t mcause_trap_جدول[MAX_TRAP_مقدار];
خارجي mtrap_fptr_t mcause_وقفه_جدول[MAX_وقفه_مقدار];

فراغ default_handler(uintptr_t cause, uintptr_t epc);
بیعلامت صحيح استخراج_ie_کد(بیعلامت صحيح رقم);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#پایان_اگر
