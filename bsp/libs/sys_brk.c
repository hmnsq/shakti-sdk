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

#అన్తర్భావ "platform.h"

బాహ్య అక్షరం చివర[];                /* _end is set in the linker file */
బాహ్య అక్షరం కుప్ప_చివర[];	   /* _heap_end is set in the linker file */

అక్షరం *కుప్ప_ptr=(అక్షరం *)&చివర;
అక్షరం *చివర_యొక్క_కుప్ప=(అక్షరం *)&కుప్ప_చివర;

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
అక్షరం * m_sbrk (nbytes)
	పూర్ణాంకం nbytes;
{
	అక్షరం *పునాది;

	log_debug("\nHeap pointer is %x",కుప్ప_ptr);

	ఒకవేళ(!కుప్ప_ptr)
		కుప్ప_ptr = (అక్షరం *)&చివర;

	పునాది = కుప్ప_ptr;
	కుప్ప_ptr += nbytes;

	log_debug("\nNew System BRK: %x %x %x",పునాది,కుప్ప_ptr,చివర_యొక్క_కుప్ప);

	ఒకవేళ(కుప్ప_ptr>చివర_యొక్క_కుప్ప)
	{
		log_error("\nMemory allocation error: Insufficient Space");
		తిరిగి -1;
	}
	తిరిగి పునాది;
}
