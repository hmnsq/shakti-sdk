/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: memory.c
 * Brief Description of file    : A library to display the memory contents
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
@file memory.c
@brief A library to display the memory contents at byte and word level.
*/

#ضمن "log.h"
#ضمن "memory.h"
#ضمن <stdint.h>

/** @fn void dump_word_memory(uint32_t* start, uint32_t word_length)
 * @brief dump contents of word addressabe location in the memory,
 *	 starting from the start address.
 * @param uint32_t* start
 * @param uint32_t word_length
 */

فراغ dump_کلمه_حافظه(uint32_t* شروع, uint32_t کلمه_درازی)
{
	uint32_t i=0;
	فراغ *آدرس;

	آدرس = (uint32_t *) شروع;

	طالما(i++< کلمه_درازی)
	{
		log_info("address = %x data = %x\n", آدرس, *(uint32_t *) آدرس);
		آدرس += 4;
	}
}

/** @fn void dump_byte_memory(uint32_t* start, uint32_t word_length)
 * @brief dump contents of byte addressabe location in the memory,
 *	 starting from the start address.
 * @param uint32_t* start
 * @param uint32_t word_length
 */

فراغ dump_byte_حافظه(uint32_t* شروع, uint32_t کلمه_درازی)
{
	uint32_t i=0;
	فراغ *آدرس;

	آدرس = (بیعلامت حرف *) شروع;

	طالما(i++< کلمه_درازی)
	{
		log_info("address = %x data = %x\n", آدرس, *(بیعلامت حرف
							       *) آدرس);
		آدرس += 1;
	}
}
