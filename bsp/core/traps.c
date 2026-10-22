/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: traps.c
 * Brief Description of file    : source file for first level of trap handling.
 * Name of Author    	        : Sathya Narayanan N
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
 ***************************************************************************/
/**
@file traps.c
@brief source file for first level of trap handling.
@detail This file contains Trap handler routines.
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"

mtrap_fptr_t mcause_trap_ਸਾਰਣੀ[MAX_TRAP_ਮੁੱਲ];
mtrap_fptr_t mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MAX_ਰੁਕਾਵਟ_ਮੁੱਲ];

/** @fn unsigned int extract_ie_code(unsigned int num)
 * @brief Extract the exception code from the mcause value
 * @details Extract the exception code from the mcause value
 *	    by masking the most significant bit and return
 *	    the exception code.
 * @param unsigned int num - mcause value
 * @return unsigned int
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਕੱਢੋ_ie_ਕੋਡ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਅੰਕ)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ exception_ਕੋਡ;

	log_trace("\nextract_ie_code entered\n");

	exception_ਕੋਡ = (ਅੰਕ & 0X7FFFFFFF);

	log_debug("exception code = %x\n",exception_ਕੋਡ);

	log_trace("extract_ie_code exited\n");

	ਵਾਪਸ exception_ਕੋਡ;
}

/** @fn void default_handler(uintptr_t mcause, uintptr_t epc)
 * @brief default handler that loops infinitely 
 * @param unsigned int ptr mcause
 * @param unsigned int ptr epc
 */
ਖਾਲੀ default_handler(__attribute__((ਅਣਵਰਤਿਆ)) uintptr_t mcause, __attribute__((ਅਣਵਰਤਿਆ)) uintptr_t epc)
{
	log_trace("\ndefault_handler entered\n");

	ਜਦੋਂ(1);

	log_trace("default_handler exited\n");
}

/** @fn uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
 * @brief Handles the trap, exception or interrupt is determined here
 * @details Trap handler routine, which identifies the cause of trap 
 *	    and calls the respective trap handler.
 * @param unsigned int ptr mcause
 * @param unsigned int ptr epc
 * @return unsigned int ptr
 */
uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ie_ਇੰਦਰਾਜ = 0;;
	uint32_t ਖਿਸਕਾਓ_ਲੰਮਾਈ = 0;

	log_trace("\nhandle_trap entered\n");

	/*
	   risc v priv spec v1.10 section 3.1.20 Machine Cause Register (mcause)

	   XLEN -1   XLEN-2                                           0
	   ------------------------------------------------------------
	   | Interrupt |    Exception code                            |
	   ------------------------------------------------------------
	   1                            XLEN-1

	   The mcause register is an XLEN-bit read-write register formatted as shown in Figure 3.2
	   1. When a trap is taken into M-mode, mcause is written with a code indicating the event that caused the trap.
	   Otherwise, mcause is never written by the implementation, though it may be explicitly written by software.
	 */


	/*
	   The Interrupt bit in the mcause register is set if the trap was caused by an interrupt.
	   The Exception Code field contains a code identifying the last exception
	 */

	log_debug("sizeof(uintptr)  = %d \n",ਆਕਾਰ(uintptr_t));
	ਖਿਸਕਾਓ_ਲੰਮਾਈ = __riscv_xlen - 1;

	 /* checking for type of trap */
	ਜੇ (mcause & (1 << (ਖਿਸਕਾਓ_ਲੰਮਾਈ))){

		ie_ਇੰਦਰਾਜ = ਕੱਢੋ_ie_ਕੋਡ(mcause);

		log_info("\nInterrupt: mcause = %x, epc = %x\n", mcause, epc);

		mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[ie_ਇੰਦਰਾਜ](mcause, epc);
	}
	ਨਹੀਂਤਾਂ{
		log_info("\nException: mcause = %x, epc = %x\n", mcause, epc);

		mcause_trap_ਸਾਰਣੀ[mcause](mcause, epc);
	}

	log_trace("handle_trap exited\n");

ਵਾਪਸ epc;
}
