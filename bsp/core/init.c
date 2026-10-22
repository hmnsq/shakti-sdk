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

#अन्तर्भाव "traps.h"
#अन्तर्भाव "plic_driver.h"
#अन्तर्भाव "clint_driver.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "utils.h"
#अन्तर्भाव "qspi.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "defines.h"
#अन्तर्भाव "uart.h"

बाह्य शून्य init(शून्य);
बाह्य शून्य trap_प्रविष्टिः(शून्य);
बाह्य uart_struct *uart_instance[MAX_UART_गणनम्];

बाह्य वर्ण राशिः_अन्तः[];
बाह्य वर्ण राशिः[];
बाह्य वर्ण _heap[];
बाह्य वर्ण heap_अन्तः[];

वर्ण *राशिः_अन्तः_2=(वर्ण *)&राशिः_अन्तः;
वर्ण *राशिः_start=(वर्ण *)&राशिः;
वर्ण *heap_start=(वर्ण *)&_heap;
वर्ण *heap_अन्तः_2=(वर्ण *)&heap_अन्तः;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
स्थिर शून्य section_init(शून्य)
{
#यदि 0
	/*Enable below code only on need
	 */
	यावत्(heap_start<=heap_अन्तः_2)
	{
		*heap_start=0xff;
		heap_start++;
	}

	यावत्(राशिः_अन्तः_2>=राशिः_start)
	{
		*राशिः_अन्तः_2=0x0;
		राशिः_अन्तः_2--;
	}
#यदि_अन्तः

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
स्थिर शून्य trap_init(शून्य)
{
	log_trace("trap_init entered \n ");

	mcause_व्यवधानम्_सारणी[USER_SW_व्यवधानम्]        = default_handler;
	mcause_व्यवधानम्_सारणी[SUPER_SW_व्यवधानम्]       = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT0]      = default_handler;
	mcause_व्यवधानम्_सारणी[MACH_SW_व्यवधानम्]        = default_handler;
	mcause_व्यवधानम्_सारणी[USER_TIMER_व्यवधानम्]     = default_handler;
	mcause_व्यवधानम्_सारणी[SUPER_TIMER_व्यवधानम्]    = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT1]      = default_handler;
	mcause_व्यवधानम्_सारणी[MACH_TIMER_व्यवधानम्]     = mach_clint_handler;
	mcause_व्यवधानम्_सारणी[USER_EXT_व्यवधानम्]       = default_handler;
	mcause_व्यवधानम्_सारणी[SUPERVISOR_EXT_व्यवधानम्] = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT2]      = default_handler;
	mcause_व्यवधानम्_सारणी[MACH_EXTERNAL_व्यवधानम्]  = mach_plic_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT3]      = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT4]      = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT5]      = default_handler;
	mcause_व्यवधानम्_सारणी[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_सारणी[INSTRUCTION_स्थानाङ्कः_MISALIGNED] =
		default_handler;
	mcause_trap_सारणी[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_सारणी[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_सारणी[BREAKPOINT] =
		default_handler;
	mcause_trap_सारणी[आरोपय_स्थानाङ्कः_MISALIGNED] =
		default_handler;
	mcause_trap_सारणी[आरोपय_ACCESS_FAULT] =
		default_handler;
	mcause_trap_सारणी[STORE_AMO_स्थानाङ्कः_MISALIGNED] =
		default_handler;
	mcause_trap_सारणी[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_सारणी[ENVIRONMENT_CALL_FROM_U_बहुलकम्] =
		default_handler;
	mcause_trap_सारणी[ENVIRONMENT_CALL_FROM_S_बहुलकम्] =
		default_handler;
	mcause_trap_सारणी[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_सारणी[ENVIRONMENT_CALL_FROM_M_बहुलकम्] =
		default_handler;
	mcause_trap_सारणी[INSTRUCTION_PAGE_FAULT] =
		default_handler;
	mcause_trap_सारणी[आरोपय_PAGE_FAULT] =
		default_handler;
	mcause_trap_सारणी[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_सारणी[STORE_AMO_PAGE_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
शून्य init(शून्य)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#यदि_परिभाषितम् AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#यदि_अन्तः

	trap_init();

	मुख्यम्();

	log_trace("init exited\n");
}
