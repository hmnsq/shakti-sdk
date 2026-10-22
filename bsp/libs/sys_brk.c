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

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"

ਬਾਹਰੀ ਅੱਖਰ ਸਿਰਾ[];                /* _end is set in the linker file */
ਬਾਹਰੀ ਅੱਖਰ ਢੇਰ_ਸਿਰਾ_2[];	   /* _heap_end is set in the linker file */

ਅੱਖਰ *ਢੇਰ_ptr=(ਅੱਖਰ *)&ਸਿਰਾ;
ਅੱਖਰ *ਸਿਰਾ_ਦਾ_ਢੇਰ=(ਅੱਖਰ *)&ਢੇਰ_ਸਿਰਾ_2;

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
ਅੱਖਰ * m_sbrk (nbytes)
	ਪੂਰਨ nbytes;
{
	ਅੱਖਰ *ਅਧਾਰ;

	log_debug("\nHeap pointer is %x",ਢੇਰ_ptr);

	ਜੇ(!ਢੇਰ_ptr)
		ਢੇਰ_ptr = (ਅੱਖਰ *)&ਸਿਰਾ;

	ਅਧਾਰ = ਢੇਰ_ptr;
	ਢੇਰ_ptr += nbytes;

	log_debug("\nNew System BRK: %x %x %x",ਅਧਾਰ,ਢੇਰ_ptr,ਸਿਰਾ_ਦਾ_ਢੇਰ);

	ਜੇ(ਢੇਰ_ptr>ਸਿਰਾ_ਦਾ_ਢੇਰ)
	{
		log_error("\nMemory allocation error: Insufficient Space");
		ਵਾਪਸ -1;
	}
	ਵਾਪਸ ਅਧਾਰ;
}
