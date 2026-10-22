/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: init.c
 * Brief Description of file    : source file for system initialization.
 * Name of Author    	        : Sathya Narayanan N & Abhinav Ramnath
 * Email ID                     : sathya281@gmail.com

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

 ****************************************************************************/
/**
@file init.c
@brief source file for system initialization
@detail This is the beginning part of a application beginning.
Different sections are initialized. main function is called. 
uart is initialized. Trap handler is initialized. 
Disable Xip for Aardonyx
*/

#شامل "traps.h"
#شامل "plic_driver.h"
#شامل "clint_driver.h"
#شامل "log.h"
#شامل "utils.h"
#شامل "qspi.h"
#شامل "platform.h"
#شامل "defines.h"
#شامل "uart.h"

خارجی خالی init(خالی);
خارجی خالی trap_اندراج(خالی);
خارجی uart_struct *uart_instance[MAX_UART_گنتی];

خارجی حرف ڈھیر_انتہا[];
خارجی حرف ڈھیر[];
خارجی حرف ڈھیر_2[];
خارجی حرف ڈھیر_انتہا_2[];

حرف *ڈھیر_انتہا_3=(حرف *)&ڈھیر_انتہا;
حرف *ڈھیر_آغاز=(حرف *)&ڈھیر;
حرف *ڈھیر_آغاز_2=(حرف *)&ڈھیر_2;
حرف *ڈھیر_انتہا_4=(حرف *)&ڈھیر_انتہا_2;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
ساکن خالی section_init(خالی)
{
#اگر 0
	/*Enable below code only on need
	 */
	جب(ڈھیر_آغاز_2<=ڈھیر_انتہا_4)
	{
		*ڈھیر_آغاز_2=0xff;
		ڈھیر_آغاز_2++;
	}

	جب(ڈھیر_انتہا_3>=ڈھیر_آغاز)
	{
		*ڈھیر_انتہا_3=0x0;
		ڈھیر_انتہا_3--;
	}
#اگر_ختم

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
ساکن خالی trap_init(خالی)
{
	log_trace("trap_init entered \n ");

	mcause_مداخلت_جدول[USER_SW_مداخلت]        = default_handler;
	mcause_مداخلت_جدول[SUPER_SW_مداخلت]       = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT0]      = default_handler;
	mcause_مداخلت_جدول[MACH_SW_مداخلت]        = default_handler;
	mcause_مداخلت_جدول[USER_TIMER_مداخلت]     = default_handler;
	mcause_مداخلت_جدول[SUPER_TIMER_مداخلت]    = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT1]      = default_handler;
	mcause_مداخلت_جدول[MACH_TIMER_مداخلت]     = mach_clint_handler;
	mcause_مداخلت_جدول[USER_EXT_مداخلت]       = default_handler;
	mcause_مداخلت_جدول[SUPERVISOR_EXT_مداخلت] = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT2]      = default_handler;
	mcause_مداخلت_جدول[MACH_EXTERNAL_مداخلت]  = mach_plic_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT3]      = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT4]      = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT5]      = default_handler;
	mcause_مداخلت_جدول[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_جدول[INSTRUCTION_پتہ_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_جدول[BREAKPOINT] =
		default_handler;
	mcause_trap_جدول[بھرو_پتہ_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[بھرو_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_پتہ_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_U_منوال] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_S_منوال] =
		default_handler;
	mcause_trap_جدول[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_M_منوال] =
		default_handler;
	mcause_trap_جدول[INSTRUCTION_صفحہ_FAULT] =
		default_handler;
	mcause_trap_جدول[بھرو_صفحہ_FAULT] =
		default_handler;
	mcause_trap_جدول[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_صفحہ_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
خالی init(خالی)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#اگر_تعریف_شدہ AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#اگر_ختم

	trap_init();

	مین();

	log_trace("init exited\n");
}
