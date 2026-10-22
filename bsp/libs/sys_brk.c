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

#அந்தர்பாவ "platform.h"

வெளி எழுத்து _end[];                /* _end is set in the linker file */
வெளி எழுத்து _heap_end[];	   /* _heap_end is set in the linker file */

எழுத்து *heap_ptr=(எழுத்து *)&_end;
எழுத்து *end_of_heap=(எழுத்து *)&_heap_end;

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
எழுத்து * m_sbrk (nbytes)
	முழு nbytes;
{
	எழுத்து *base;

	log_debug("\nHeap pointer is %x",heap_ptr);

	எனில்(!heap_ptr)
		heap_ptr = (எழுத்து *)&_end;

	base = heap_ptr;
	heap_ptr += nbytes;

	log_debug("\nNew System BRK: %x %x %x",base,heap_ptr,end_of_heap);

	எனில்(heap_ptr>end_of_heap)
	{
		log_error("\nMemory allocation error: Insufficient Space");
		திரும்பு -1;
	}
	திரும்பு base;
}
