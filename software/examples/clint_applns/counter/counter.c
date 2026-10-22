/***************************************************************************
 * Project                     : shakti devt board
 * Name of the file	       : counter.c
 * Brief Description of file   : source file for mtime counter
 * Name of Author    	       : Sathya Narayanan N & Raghav
 * Email ID                    : sathya281@gmail.com

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
@file counter.c
@brief source file for mtime counter example
@detail This file contains an application to use clint counters. The counter
 is configured for a time period and on expiry the timer interrupt handler
 handles the interrupt. Subsequently the clint counter is configured for 
 subsequent operation.
*/ 

#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "traps.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "clint_driver.h"
#ಅನ್ತರ್ಭಾವ "log.h"

/** @fn int main(void)
 * @brief A simple application to use clint (mtime)
 */
ಶೂನ್ಯ ಮುಖ್ಯ(ಶೂನ್ಯ){

	uint64_t ಮೌಲ್ಯ = 50000000;

	asm ಅಸ್ಥಿರ("li      t0, 0x80\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm ಅಸ್ಥಿರ("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	configure_counter(ಮೌಲ್ಯ);

	ಆಗ(1);
}
