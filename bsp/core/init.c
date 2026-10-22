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

#ಅನ್ತರ್ಭಾವ "traps.h"
#ಅನ್ತರ್ಭಾವ "plic_driver.h"
#ಅನ್ತರ್ಭಾವ "clint_driver.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "qspi.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "defines.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

ಬಾಹ್ಯ ಶೂನ್ಯ init(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ trap_ನಮೂದು(ಶೂನ್ಯ);
ಬಾಹ್ಯ uart_struct *uart_instance[MAX_UART_ಎಣಿಕೆ];

ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಕೊನೆ[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_2[];
ಬಾಹ್ಯ ಅಕ್ಷರ ರಾಶಿ_ಕೊನೆ_2[];

ಅಕ್ಷರ *ರಾಶಿ_ಕೊನೆ_3=(ಅಕ್ಷರ *)&ರಾಶಿ_ಕೊನೆ;
ಅಕ್ಷರ *ರಾಶಿ_ಆರಂಭ=(ಅಕ್ಷರ *)&ರಾಶಿ;
ಅಕ್ಷರ *ರಾಶಿ_ಆರಂಭ_2=(ಅಕ್ಷರ *)&ರಾಶಿ_2;
ಅಕ್ಷರ *ರಾಶಿ_ಕೊನೆ_4=(ಅಕ್ಷರ *)&ರಾಶಿ_ಕೊನೆ_2;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
ಸ್ಥಿರ ಶೂನ್ಯ section_init(ಶೂನ್ಯ)
{
#ಆದರೆ 0
	/*Enable below code only on need
	 */
	ಆಗ(ರಾಶಿ_ಆರಂಭ_2<=ರಾಶಿ_ಕೊನೆ_4)
	{
		*ರಾಶಿ_ಆರಂಭ_2=0xff;
		ರಾಶಿ_ಆರಂಭ_2++;
	}

	ಆಗ(ರಾಶಿ_ಕೊನೆ_3>=ರಾಶಿ_ಆರಂಭ)
	{
		*ರಾಶಿ_ಕೊನೆ_3=0x0;
		ರಾಶಿ_ಕೊನೆ_3--;
	}
#ಆದರೆ_ಅಂತ್ಯ

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
ಸ್ಥಿರ ಶೂನ್ಯ trap_init(ಶೂನ್ಯ)
{
	log_trace("trap_init entered \n ");

	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[USER_SW_ಅಡಚಣೆ]        = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[SUPER_SW_ಅಡಚಣೆ]       = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT0]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[MACH_SW_ಅಡಚಣೆ]        = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[USER_TIMER_ಅಡಚಣೆ]     = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[SUPER_TIMER_ಅಡಚಣೆ]    = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT1]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[MACH_TIMER_ಅಡಚಣೆ]     = mach_clint_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[USER_EXT_ಅಡಚಣೆ]       = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[SUPERVISOR_EXT_ಅಡಚಣೆ] = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT2]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[MACH_EXTERNAL_ಅಡಚಣೆ]  = mach_plic_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT3]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT4]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT5]      = default_handler;
	mcause_ಅಡಚಣೆ_ಕೋಷ್ಟಕ[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_ಕೋಷ್ಟಕ[INSTRUCTION_ವಿಳಾಸ_MISALIGNED] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[BREAKPOINT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ತುಂಬು_ವಿಳಾಸ_MISALIGNED] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ತುಂಬು_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[STORE_AMO_ವಿಳಾಸ_MISALIGNED] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ENVIRONMENT_CALL_FROM_U_ಬಹುಲಕ] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ENVIRONMENT_CALL_FROM_S_ಬಹುಲಕ] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ENVIRONMENT_CALL_FROM_M_ಬಹುಲಕ] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[INSTRUCTION_ಪುಟ_FAULT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[ತುಂಬು_ಪುಟ_FAULT] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_ಕೋಷ್ಟಕ[STORE_AMO_ಪುಟ_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
ಶೂನ್ಯ init(ಶೂನ್ಯ)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#ಆದರೆ_ಅಂತ್ಯ

	trap_init();

	ಮುಖ್ಯ();

	log_trace("init exited\n");
}
