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

#அந்தர்பாவ "clint_driver.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "platform.h"
#அந்தர்பாவ "defines.h"

நிலையற்ற uint64_t* mtime    =  (MTIME);
நிலையற்ற uint64_t* mtimecmp =  (MTIMECMP);

/** @fn static unsigned long mtime_low( )
 * @brief return the lower 32bit of mtime.
 * @details return the lower half of mtime. And this is needed mostly in dealing mtime in 32 bit machines.
 * @return unsigned long
 */
நிலையான uint32_t mtime_கீழ்(வெறுமை)
{
  திரும்பு *(uint32_t *)(MTIME);
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
நிலையான uint32_t mtime_உயர்வு(வெறுமை)
{
  திரும்பு *(நிலையற்ற uint32_t *)(MTIME + 4);
}

/** @fn uint64_t get_timer_value()
 * @brief return the mtime value for a 32 bit or 64 bit machine
 * @details return the mtime value based on the __riscv_xlen. Incase of 64 bit, this joins the upper
 *          and lower 32 bits of mtime and return
 * @return unsigned 64bit int
 */
uint64_t get_timer_மதிப்பு()
{

#எனில் __riscv_xlen == 64
   திரும்பு ( ((uint64_t)mtime_உயர்வு() << 32) | mtime_கீழ்());
#இல்லையெனில்
  திரும்பு mtime_கீழ்();
#endif
}

/** @fn void configure_counter( uint64_t value)
 * @brief sets up the timer
 * @details sets the mtimecmp to current mtime + delta
 * @param unsigned 64bit int (delta value after which interrupt happens)
 */
வெறுமை configure_counter( uint64_t மதிப்பு)
{
	log_trace("\nconfigure_counter entered\n");

	*mtimecmp = *mtime + மதிப்பு;

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
வெறுமை mach_clint_handler( __attribute__((unused)) uintptr_t int_id,  __attribute__((unused)) uintptr_t epc)
{
	log_trace("\nmach_clint_handler entered\n");

	//set mtimecmp to some value. On appln reqt basis handle timer interrupt
	*mtimecmp = -1;

	log_info("Timer interrupt handled \n");

	log_trace("mach_clint_handler exited\n");
}
