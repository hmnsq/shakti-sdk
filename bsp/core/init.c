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

#ضمن "traps.h"
#ضمن "plic_driver.h"
#ضمن "clint_driver.h"
#ضمن "log.h"
#ضمن "utils.h"
#ضمن "qspi.h"
#ضمن "platform.h"
#ضمن "defines.h"
#ضمن "uart.h"

خارجي فراغ init(فراغ);
خارجي فراغ trap_داخلا(فراغ);
خارجي uart_struct *uart_instance[MAX_UART_ڳڻپ];

خارجي حرف ڍير_پڇاڙي[];
خارجي حرف ڍير[];
خارجي حرف ڍير_2[];
خارجي حرف ڍير_پڇاڙي_2[];

حرف *ڍير_پڇاڙي_3=(حرف *)&ڍير_پڇاڙي;
حرف *ڍير_شروعات=(حرف *)&ڍير;
حرف *ڍير_شروعات_2=(حرف *)&ڍير_2;
حرف *ڍير_پڇاڙي_4=(حرف *)&ڍير_پڇاڙي_2;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
ساكن فراغ section_init(فراغ)
{
#إذا 0
	/*Enable below code only on need
	 */
	طالما(ڍير_شروعات_2<=ڍير_پڇاڙي_4)
	{
		*ڍير_شروعات_2=0xff;
		ڍير_شروعات_2++;
	}

	طالما(ڍير_پڇاڙي_3>=ڍير_شروعات)
	{
		*ڍير_پڇاڙي_3=0x0;
		ڍير_پڇاڙي_3--;
	}
#جيڪڏهن_پورو

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
ساكن فراغ trap_init(فراغ)
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

	mcause_trap_جدول[INSTRUCTION_پتو_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_جدول[BREAKPOINT] =
		default_handler;
	mcause_trap_جدول[ڀريو_پتو_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[ڀريو_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_پتو_MISALIGNED] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_U_گهڻائي] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_S_گهڻائي] =
		default_handler;
	mcause_trap_جدول[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_جدول[ENVIRONMENT_CALL_FROM_M_گهڻائي] =
		default_handler;
	mcause_trap_جدول[INSTRUCTION_صفحو_FAULT] =
		default_handler;
	mcause_trap_جدول[ڀريو_صفحو_FAULT] =
		default_handler;
	mcause_trap_جدول[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_جدول[STORE_AMO_صفحو_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
فراغ init(فراغ)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#جيڪڏهن_وصف_ٿيل AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#جيڪڏهن_پورو

	trap_init();

	مکيه();

	log_trace("init exited\n");
}
