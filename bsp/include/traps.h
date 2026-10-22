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

#که_نه_تعریف_شوی TRAPS_H
#تعریف_کړه TRAPS_H
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

#تعریف_کړه MAX_MCAUSE_ارزښت               32


/*  Interrupts */
#تعریف_کړه MAX_مداخله_ارزښت            16

#تعریف_کړه USER_SW_مداخله               0
#تعریف_کړه SUPER_SW_مداخله              1
#تعریف_کړه RESERVED_INTERRUPT0             2
#تعریف_کړه MACH_SW_مداخله               3
#تعریف_کړه USER_TIMER_مداخله            4
#تعریف_کړه SUPER_TIMER_مداخله           5
#تعریف_کړه RESERVED_INTERRUPT1             6
#تعریف_کړه MACH_TIMER_مداخله            7
#تعریف_کړه USER_EXT_مداخله              8
#تعریف_کړه SUPERVISOR_EXT_مداخله        9
#تعریف_کړه RESERVED_INTERRUPT2            10
#تعریف_کړه MACH_EXTERNAL_مداخله        11
#تعریف_کړه RESERVED_INTERRUPT3            12
#تعریف_کړه RESERVED_INTERRUPT4            13
#تعریف_کړه RESERVED_INTERRUPT5            14
#تعریف_کړه RESERVED_INTERRUPT6            15

/* Traps */
#تعریف_کړه MAX_TRAP_ارزښت                 16

#تعریف_کړه INSTRUCTION_پته_MISALIGNED  0
#تعریف_کړه INSTRUCTION_ACCESS_FAULT        1
#تعریف_کړه ILLEGAL_INSTRUCTION             2
#تعریف_کړه BREAKPOINT                      3
#تعریف_کړه بارول_پته_MISALIGNED         4
#تعریف_کړه بارول_ACCESS_FAULT               5
#تعریف_کړه STORE_AMO_پته_MISALIGNED    6
#تعریف_کړه STORE_AMO_ACCESS_FAULT          7
#تعریف_کړه ENVIRONMENT_CALL_FROM_U_ډېرپېښ    8
#تعریف_کړه ENVIRONMENT_CALL_FROM_S_ډېرپېښ    9
#تعریف_کړه RESERVED_TRAP1                 10
#تعریف_کړه ENVIRONMENT_CALL_FROM_M_ډېرپېښ   11
#تعریف_کړه INSTRUCTION_پاڼه_FAULT         12
#تعریف_کړه بارول_پاڼه_FAULT                13
#تعریف_کړه RESERVED_TRAP2                 14
#تعریف_کړه STORE_AMO_پاڼه_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

تعريفنوع فراغ (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
خارجي mtrap_fptr_t mcause_trap_جدول[MAX_TRAP_ارزښت];
خارجي mtrap_fptr_t mcause_مداخله_جدول[MAX_مداخله_ارزښت];

فراغ default_handler(uintptr_t cause, uintptr_t epc);
بینښه صحيح ایستل_ie_کوډ(بینښه صحيح عدد);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#د_که_پای
