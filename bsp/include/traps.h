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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TRAPS_H
#ವ್ಯಾಖ್ಯಾನಿಸು TRAPS_H
#ಅನ್ತರ್ಭಾವ <stdint.h>

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

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_MCAUSE_ಮೌಲ್ಯ               32


/*  Interrupts */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಅಡಚಣೆ_ಮೌಲ್ಯ            16

#ವ್ಯಾಖ್ಯಾನಿಸು USER_SW_ಅಡಚಣೆ               0
#ವ್ಯಾಖ್ಯಾನಿಸು SUPER_SW_ಅಡಚಣೆ              1
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT0             2
#ವ್ಯಾಖ್ಯಾನಿಸು MACH_SW_ಅಡಚಣೆ               3
#ವ್ಯಾಖ್ಯಾನಿಸು USER_TIMER_ಅಡಚಣೆ            4
#ವ್ಯಾಖ್ಯಾನಿಸು SUPER_TIMER_ಅಡಚಣೆ           5
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT1             6
#ವ್ಯಾಖ್ಯಾನಿಸು MACH_TIMER_ಅಡಚಣೆ            7
#ವ್ಯಾಖ್ಯಾನಿಸು USER_EXT_ಅಡಚಣೆ              8
#ವ್ಯಾಖ್ಯಾನಿಸು SUPERVISOR_EXT_ಅಡಚಣೆ        9
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT2            10
#ವ್ಯಾಖ್ಯಾನಿಸು MACH_EXTERNAL_ಅಡಚಣೆ        11
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT3            12
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT4            13
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT5            14
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_INTERRUPT6            15

/* Traps */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_TRAP_ಮೌಲ್ಯ                 16

#ವ್ಯಾಖ್ಯಾನಿಸು INSTRUCTION_ವಿಳಾಸ_MISALIGNED  0
#ವ್ಯಾಖ್ಯಾನಿಸು INSTRUCTION_ACCESS_FAULT        1
#ವ್ಯಾಖ್ಯಾನಿಸು ILLEGAL_INSTRUCTION             2
#ವ್ಯಾಖ್ಯಾನಿಸು BREAKPOINT                      3
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_ವಿಳಾಸ_MISALIGNED         4
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_ACCESS_FAULT               5
#ವ್ಯಾಖ್ಯಾನಿಸು STORE_AMO_ವಿಳಾಸ_MISALIGNED    6
#ವ್ಯಾಖ್ಯಾನಿಸು STORE_AMO_ACCESS_FAULT          7
#ವ್ಯಾಖ್ಯಾನಿಸು ENVIRONMENT_CALL_FROM_U_ಬಹುಲಕ    8
#ವ್ಯಾಖ್ಯಾನಿಸು ENVIRONMENT_CALL_FROM_S_ಬಹುಲಕ    9
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_TRAP1                 10
#ವ್ಯಾಖ್ಯಾನಿಸು ENVIRONMENT_CALL_FROM_M_ಬಹುಲಕ   11
#ವ್ಯಾಖ್ಯಾನಿಸು INSTRUCTION_ಪುಟ_FAULT         12
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_ಪುಟ_FAULT                13
#ವ್ಯಾಖ್ಯಾನಿಸು RESERVED_TRAP2                 14
#ವ್ಯಾಖ್ಯಾನಿಸು STORE_AMO_ಪುಟ_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
ಬಾಹ್ಯ mtrap_fptr_t mcause_trap_ಕೋಷ್ಟಕ[MAX_TRAP_ಮೌಲ್ಯ];
ಬಾಹ್ಯ mtrap_fptr_t mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[MAX_ಅಡಚಣೆ_ಮೌಲ್ಯ];

ಶೂನ್ಯ default_handler(uintptr_t cause, uintptr_t epc);
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಹೊರತೆಗೆ_ie_ಸಂಕೇತ(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಂಕೆ);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#ಆದರೆ_ಅಂತ್ಯ
