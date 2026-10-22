/***************************************************************************
 * Project                     : shakti devt board
 * Name of the file	       : 1_second
 * Brief Description of file   : Generating timer interrupt in 1 second
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
@file 1_second.c
@brief source file for mtime 1_second example
@detail This file contains an application to use clint counters, clint divisor and generating interrupt in 1 second.
 The counter is configured for a time period and on expiry the timer interrupt handler
 handles the interrupt. Subsequently the clint counter is configured for subsequent operation.
*/ 

#समावेश "uart.h"
#समावेश "traps.h"
#समावेश "platform.h"
#समावेश "clint_driver.h"
#समावेश "log.h"

/** @fn int main(void)
 * @brief A simple application to use clint (mtime) and clint clock divisor to generate interrupt in 1 second. 
 */
व्योम मुख्य(व्योम){

	uint64_t मूल्य = ( CLOCK_FREQUENCY / CLINT_भाजक );

	यंत्र अस्थिर("li      t0, 0x80\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	यंत्र अस्थिर("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );
	म_लिखो("Configuring 1 second timer interrupt\n");
	configure_गणक(मूल्य);

	जबतक(1);
}
