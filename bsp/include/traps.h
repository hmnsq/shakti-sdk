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

#నిర్వచితం_కాకపోతే TRAPS_H
#నిర్వచించు TRAPS_H
#అన్తర్భావ <stdint.h>

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

#నిర్వచించు MAX_MCAUSE_విలువ               32


/*  Interrupts */
#నిర్వచించు MAX_అంతరాయం_విలువ            16

#నిర్వచించు USER_SW_అంతరాయం               0
#నిర్వచించు SUPER_SW_అంతరాయం              1
#నిర్వచించు RESERVED_INTERRUPT0             2
#నిర్వచించు MACH_SW_అంతరాయం               3
#నిర్వచించు USER_TIMER_అంతరాయం            4
#నిర్వచించు SUPER_TIMER_అంతరాయం           5
#నిర్వచించు RESERVED_INTERRUPT1             6
#నిర్వచించు MACH_TIMER_అంతరాయం            7
#నిర్వచించు USER_EXT_అంతరాయం              8
#నిర్వచించు SUPERVISOR_EXT_అంతరాయం        9
#నిర్వచించు RESERVED_INTERRUPT2            10
#నిర్వచించు MACH_EXTERNAL_అంతరాయం        11
#నిర్వచించు RESERVED_INTERRUPT3            12
#నిర్వచించు RESERVED_INTERRUPT4            13
#నిర్వచించు RESERVED_INTERRUPT5            14
#నిర్వచించు RESERVED_INTERRUPT6            15

/* Traps */
#నిర్వచించు MAX_TRAP_విలువ                 16

#నిర్వచించు INSTRUCTION_చిరునామా_MISALIGNED  0
#నిర్వచించు INSTRUCTION_ACCESS_FAULT        1
#నిర్వచించు ILLEGAL_INSTRUCTION             2
#నిర్వచించు BREAKPOINT                      3
#నిర్వచించు ఎక్కించు_చిరునామా_MISALIGNED         4
#నిర్వచించు ఎక్కించు_ACCESS_FAULT               5
#నిర్వచించు STORE_AMO_చిరునామా_MISALIGNED    6
#నిర్వచించు STORE_AMO_ACCESS_FAULT          7
#నిర్వచించు ENVIRONMENT_CALL_FROM_U_బహుళకం    8
#నిర్వచించు ENVIRONMENT_CALL_FROM_S_బహుళకం    9
#నిర్వచించు RESERVED_TRAP1                 10
#నిర్వచించు ENVIRONMENT_CALL_FROM_M_బహుళకం   11
#నిర్వచించు INSTRUCTION_పుట_FAULT         12
#నిర్వచించు ఎక్కించు_పుట_FAULT                13
#నిర్వచించు RESERVED_TRAP2                 14
#నిర్వచించు STORE_AMO_పుట_FAULT           15

/*
   Trap table -  Each entry in the table corresponds to a service routine for a Trap
 */

రకనిర్వచనం శూన్య (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);
బాహ్య mtrap_fptr_t mcause_trap_పట్టిక[MAX_TRAP_విలువ];
బాహ్య mtrap_fptr_t mcause_అంతరాయం_పట్టిక[MAX_అంతరాయం_విలువ];

శూన్య default_handler(uintptr_t cause, uintptr_t epc);
గుర్తులేని పూర్ణాంకం వెలికితీయి_ie_సంకేతం(గుర్తులేని పూర్ణాంకం అంకె);
uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);

#అయితే_ముగింపు
