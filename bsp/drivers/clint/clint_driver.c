/***************************************************************************
* Project                     : shakti devt board
* Name of the file	      : clint_driver.c
* Brief Description of file   : source file for clint.
* Name of Author    	      : Sathya Narayanan N
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
@file clint_driver.c
@brief source file for clint.
@detail This file is a driver file for clint. The file contains the clint 
interrupt handler, configure the counter and support for e and c class clint timers. 
*/

#ಅನ್ತರ್ಭಾವ "clint_driver.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "defines.h"

ಚಞ್ಚಲ uint64_t* mtime    =  (MTIME);
ಚಞ್ಚಲ uint64_t* mtimecmp =  (MTIMECMP);

/** @fn static unsigned long mtime_low( )
 * @brief return the lower 32bit of mtime.
 * @details return the lower half of mtime. And this is needed mostly in dealing mtime in 32 bit machines.
 * @return unsigned long
 */
ಸ್ಥಿರ uint32_t mtime_ಕೆಳಗಿನ(ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ *(uint32_t *)(MTIME);
}

/*
Get each 32 bit and append for full timer value
*/

/** @fn static uint32_t mtime_high(void)
 * @brief return the upper 32 bit of mtime
 * @details return the upper 32 bit of mtime register. This is very useful incase of 32 bit core.
 *          Incase of 64 bit core this has to be appended with lower 32 bits adn sent.
 * @return unsigned 32bit int
 */
ಸ್ಥಿರ uint32_t mtime_ಮೇಲಿನ(ಶೂನ್ಯ)
{
  ಪ್ರತ್ಯಾಗಮ *(ಚಞ್ಚಲ uint32_t *)(MTIME + 4);
}

/** @fn uint64_t get_timer_value()
 * @brief return the mtime value for a 32 bit or 64 bit machine
 * @details return the mtime value based on the __riscv_xlen. Incase of 64 bit, this joins the upper
 *          and lower 32 bits of mtime and return
 * @return unsigned 64bit int
 */
uint64_t get_timer_ಮೌಲ್ಯ()
{

#ಯದಿ __riscv_xlen == 64
   ಪ್ರತ್ಯಾಗಮ ( ((uint64_t)mtime_ಮೇಲಿನ() << 32) | mtime_ಕೆಳಗಿನ());
#ಅನ್ಯಥಾ
  ಪ್ರತ್ಯಾಗಮ mtime_ಕೆಳಗಿನ();
#endif
}

/** @fn void configure_counter( uint64_t value)
 * @brief sets up the timer
 * @details sets the mtimecmp to current mtime + delta
 * @param unsigned 64bit int (delta value after which interrupt happens)
 */
ಶೂನ್ಯ configure_counter( uint64_t ಮೌಲ್ಯ)
{
	log_trace("\nconfigure_counter entered\n");

	*mtimecmp = *mtime + ಮೌಲ್ಯ;

	log_debug("mtimecmp value = %d\n", *mtimecmp);
	log_debug("mtime value = %d\n", *mtime);

	log_trace("\nconfigure_counter exited\n");
}

/** @fn void mach_clint_handler(uintptr_t int_id, uintptr_t epc)
 * @brief handler for machine timer interrupt
 * @details handler for machine timer interrupt. This handles the timer interrupt and sets mtimecmp to clear timer interrupt.
 * @param unsigned int ptr int_id
 * @param unsigned int ptr epc
 */
ಶೂನ್ಯ mach_clint_handler( __attribute__((unused)) uintptr_t int_id,  __attribute__((unused)) uintptr_t epc)
{
	log_trace("\nmach_clint_handler entered\n");

	//set mtimecmp to some value. On appln reqt basis handle timer interrupt
	*mtimecmp = -1;

	log_info("Timer interrupt handled \n");

	log_trace("mach_clint_handler exited\n");
}
