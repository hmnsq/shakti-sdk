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

#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "clint_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "qspi.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "defines.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

ਬਾਹਰੀ ਖਾਲੀ init(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ trap_ਇੰਦਰਾਜ(ਖਾਲੀ);
ਬਾਹਰੀ uart_struct *uart_instance[MAX_UART_ਗਿਣਤੀ];

ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਸਿਰਾ[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_2[];
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਸਿਰਾ_2[];

ਅੱਖਰ *ਢੇਰ_ਸਿਰਾ_3=(ਅੱਖਰ *)&ਢੇਰ_ਸਿਰਾ;
ਅੱਖਰ *ਢੇਰ_ਸ਼ੁਰੂ=(ਅੱਖਰ *)&ਢੇਰ;
ਅੱਖਰ *ਢੇਰ_ਸ਼ੁਰੂ_2=(ਅੱਖਰ *)&ਢੇਰ_2;
ਅੱਖਰ *ਢੇਰ_ਸਿਰਾ_4=(ਅੱਖਰ *)&ਢੇਰ_ਸਿਰਾ_2;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
ਸਥਿਰ ਖਾਲੀ section_init(ਖਾਲੀ)
{
#ਜੇ 0
	/*Enable below code only on need
	 */
	ਜਦੋਂ(ਢੇਰ_ਸ਼ੁਰੂ_2<=ਢੇਰ_ਸਿਰਾ_4)
	{
		*ਢੇਰ_ਸ਼ੁਰੂ_2=0xff;
		ਢੇਰ_ਸ਼ੁਰੂ_2++;
	}

	ਜਦੋਂ(ਢੇਰ_ਸਿਰਾ_3>=ਢੇਰ_ਸ਼ੁਰੂ)
	{
		*ਢੇਰ_ਸਿਰਾ_3=0x0;
		ਢੇਰ_ਸਿਰਾ_3--;
	}
#ਜੇ_ਅੰਤ

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
ਸਥਿਰ ਖਾਲੀ trap_init(ਖਾਲੀ)
{
	log_trace("trap_init entered \n ");

	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[USER_SW_ਰੁਕਾਵਟ]        = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[SUPER_SW_ਰੁਕਾਵਟ]       = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT0]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MACH_SW_ਰੁਕਾਵਟ]        = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[USER_TIMER_ਰੁਕਾਵਟ]     = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[SUPER_TIMER_ਰੁਕਾਵਟ]    = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT1]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MACH_TIMER_ਰੁਕਾਵਟ]     = mach_clint_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[USER_EXT_ਰੁਕਾਵਟ]       = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[SUPERVISOR_EXT_ਰੁਕਾਵਟ] = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT2]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MACH_EXTERNAL_ਰੁਕਾਵਟ]  = mach_plic_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT3]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT4]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT5]      = default_handler;
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_ਸਾਰਣੀ[INSTRUCTION_ਪਤਾ_MISALIGNED] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[BREAKPOINT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ਲੱਦੋ_ਪਤਾ_MISALIGNED] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ਲੱਦੋ_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[STORE_AMO_ਪਤਾ_MISALIGNED] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ENVIRONMENT_CALL_FROM_U_ਬਹੁਲਕ] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ENVIRONMENT_CALL_FROM_S_ਬਹੁਲਕ] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ENVIRONMENT_CALL_FROM_M_ਬਹੁਲਕ] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[INSTRUCTION_ਪੰਨਾ_FAULT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[ਲੱਦੋ_ਪੰਨਾ_FAULT] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_ਸਾਰਣੀ[STORE_AMO_ਪੰਨਾ_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
ਖਾਲੀ init(ਖਾਲੀ)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#ਜੇ_ਅੰਤ

	trap_init();

	ਮੁੱਖ();

	log_trace("init exited\n");
}
