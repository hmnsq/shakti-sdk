/***************************************************************************
 * Project               	: shakti devt board
 * Name of the file	        : sys_brk.c
 * Brief Description of file   	: System BRK
 * Name of Author    	        : Abhinav Ramnath
 * Email ID                     : abhinavramnath13@gmail.com

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
@file sys_brk.c
@brief System BRK
@detail This file is used to the set the brk which specifies the start of the heap and the end of the text section.
*/ 

#ضمن "platform.h"

خارجي حرف پای_ټکی[];                /* _end is set in the linker file */
خارجي حرف ډېرۍ_پای_ټکی[];	   /* _heap_end is set in the linker file */

حرف *ډېرۍ_ptr=(حرف *)&پای_ټکی;
حرف *پای_ټکی_د_ډېرۍ=(حرف *)&ډېرۍ_پای_ټکی;

/* OS LESS IMPLEMENTATION OF SBRK
 * sbrk -- changes heap size. Get nbytes more RAM.
 *         We just increment a pointer in what's
 *         left of memory on the board.
 */

/** @fn  char * m_sbrk (nbytes)
 * @brief this function is used to allocate the heap
 * @detail this function is used to allocate the heap and returns the end of the text section or start of heap  
 * @param int nbytes - specifies the size of the heap 
 * @return  returns a pointer to the start of the heap
 */
حرف * m_sbrk (nbytes)
	صحيح nbytes;
{
	حرف *بنسټ;

	log_debug("\nHeap pointer is %x",ډېرۍ_ptr);

	إذا(!ډېرۍ_ptr)
		ډېرۍ_ptr = (حرف *)&پای_ټکی;

	بنسټ = ډېرۍ_ptr;
	ډېرۍ_ptr += nbytes;

	log_debug("\nNew System BRK: %x %x %x",بنسټ,ډېرۍ_ptr,پای_ټکی_د_ډېرۍ);

	إذا(ډېرۍ_ptr>پای_ټکی_د_ډېرۍ)
	{
		log_error("\nMemory allocation error: Insufficient Space");
		أرجع -1;
	}
	أرجع بنسټ;
}
