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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TRAPS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRAPS_H
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_MCAUSE_ਮੁੱਲ               32


/*  Interrupts */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਰੁਕਾਵਟ_ਮੁੱਲ            16

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_SW_ਰੁਕਾਵਟ               0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUPER_SW_ਰੁਕਾਵਟ              1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT0             2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MACH_SW_ਰੁਕਾਵਟ               3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_TIMER_ਰੁਕਾਵਟ            4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUPER_TIMER_ਰੁਕਾਵਟ           5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT1             6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MACH_TIMER_ਰੁਕਾਵਟ            7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USER_EXT_ਰੁਕਾਵਟ              8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUPERVISOR_EXT_ਰੁਕਾਵਟ        9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT2            10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MACH_EXTERNAL_ਰੁਕਾਵਟ        11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT3            12
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT4            13
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT5            14
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_INTERRUPT6            15

/* Traps */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_TRAP_ਮੁੱਲ                 16

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INSTRUCTION_ਪਤਾ_MISALIGNED  0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INSTRUCTION_ACCESS_FAULT        1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILLEGAL_INSTRUCTION             2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BREAKPOINT                      3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_ਪਤਾ_MISALIGNED         4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_ACCESS_FAULT               5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STORE_AMO_ਪਤਾ_MISALIGNED    6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STORE_AMO_ACCESS_FAULT          7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENVIRONMENT_CALL_FROM_U_ਬਹੁਲਕ    8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENVIRONMENT_CALL_FROM_S_ਬਹੁਲਕ    9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_TRAP1                 10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENVIRONMENT_CALL_FROM_M_ਬਹੁਲਕ   11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INSTRUCTION_ਪੰਨਾ_FAULT         12
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_ਪੰਨਾ_FAULT                13
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESERVED_TRAP2                 14
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STORE_AMO_ਪੰਨਾ_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
ਬਾਹਰੀ mtrap_fptr_t mcause_trap_ਸਾਰਣੀ[MAX_TRAP_ਮੁੱਲ];
ਬਾਹਰੀ mtrap_fptr_t mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MAX_ਰੁਕਾਵਟ_ਮੁੱਲ];

ਖਾਲੀ default_handler(uintptr_t cause, uintptr_t epc);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਕੱਢੋ_ie_ਕੋਡ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਅੰਕ);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#ਜੇ_ਅੰਤ
