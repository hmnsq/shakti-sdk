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

#અન્તર્ભાવ "traps.h"
#અન્તર્ભાવ "plic_driver.h"
#અન્તર્ભાવ "clint_driver.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "utils.h"
#અન્તર્ભાવ "qspi.h"
#અન્તર્ભાવ "platform.h"
#અન્તર્ભાવ "defines.h"
#અન્તર્ભાવ "uart.h"

બાહ્ય શૂન્ય init(શૂન્ય);
બાહ્ય શૂન્ય trap_entry(શૂન્ય);
બાહ્ય uart_struct *uart_instance[MAX_UART_ગણતરી];

બાહ્ય અક્ષર ઢગલો_end[];
બાહ્ય અક્ષર ઢગલો[];
બાહ્ય અક્ષર _heap[];
બાહ્ય અક્ષર _heap_end[];

અક્ષર *ઢગલો_end_2=(અક્ષર *)&ઢગલો_end;
અક્ષર *ઢગલો_start=(અક્ષર *)&ઢગલો;
અક્ષર *heap_start=(અક્ષર *)&_heap;
અક્ષર *heap_end=(અક્ષર *)&_heap_end;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
સ્થિર શૂન્ય section_init(શૂન્ય)
{
#જો 0
	/*Enable below code only on need
	 */
	જ્યારે(heap_start<=heap_end)
	{
		*heap_start=0xff;
		heap_start++;
	}

	જ્યારે(ઢગલો_end_2>=ઢગલો_start)
	{
		*ઢગલો_end_2=0x0;
		ઢગલો_end_2--;
	}
#endif

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
સ્થિર શૂન્ય trap_init(શૂન્ય)
{
	log_trace("trap_init entered \n ");

	mcause_interrupt_table[USER_SW_INTERRUPT]        = default_handler;
	mcause_interrupt_table[SUPER_SW_INTERRUPT]       = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT0]      = default_handler;
	mcause_interrupt_table[MACH_SW_INTERRUPT]        = default_handler;
	mcause_interrupt_table[USER_TIMER_INTERRUPT]     = default_handler;
	mcause_interrupt_table[SUPER_TIMER_INTERRUPT]    = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT1]      = default_handler;
	mcause_interrupt_table[MACH_TIMER_INTERRUPT]     = mach_clint_handler;
	mcause_interrupt_table[USER_EXT_INTERRUPT]       = default_handler;
	mcause_interrupt_table[SUPERVISOR_EXT_INTERRUPT] = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT2]      = default_handler;
	mcause_interrupt_table[MACH_EXTERNAL_INTERRUPT]  = mach_plic_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT3]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT4]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT5]      = default_handler;
	mcause_interrupt_table[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_table[INSTRUCTION_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_table[BREAKPOINT] =
		default_handler;
	mcause_trap_table[LOAD_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[LOAD_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[STORE_AMO_ADDRESS_MISALIGNED] =
		default_handler;
	mcause_trap_table[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_U_MODE] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_S_MODE] =
		default_handler;
	mcause_trap_table[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_table[ENVIRONMENT_CALL_FROM_M_MODE] =
		default_handler;
	mcause_trap_table[INSTRUCTION_PAGE_FAULT] =
		default_handler;
	mcause_trap_table[LOAD_PAGE_FAULT] =
		default_handler;
	mcause_trap_table[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_table[STORE_AMO_PAGE_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
શૂન્ય init(શૂન્ય)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#ifdef AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#endif

	trap_init();

	મુખ્ય();

	log_trace("init exited\n");
}
