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

#شامل "log.h"
#شامل "memory.h"
#شامل <stdint.h>

/** @fn void dump_word_memory(uint32_t* start, uint32_t word_length)
 * @brief dump contents of word addressabe location in the memory,
 *	 starting from the start address.
 * @param uint32_t* start
 * @param uint32_t word_length
 */

خالی dump_لفظ_حافظہ(uint32_t* آغاز, uint32_t لفظ_لمبائی)
{
	uint32_t i=0;
	خالی *پتہ;

	پتہ = (uint32_t *) آغاز;

	جب(i++< لفظ_لمبائی)
	{
		log_info("address = %x data = %x\n", پتہ, *(uint32_t *) پتہ);
		پتہ += 4;
	}
}

/** @fn void dump_byte_memory(uint32_t* start, uint32_t word_length)
 * @brief dump contents of byte addressabe location in the memory,
 *	 starting from the start address.
 * @param uint32_t* start
 * @param uint32_t word_length
 */

خالی dump_byte_حافظہ(uint32_t* آغاز, uint32_t لفظ_لمبائی)
{
	uint32_t i=0;
	خالی *پتہ;

	پتہ = (غیرعلامتی حرف *) آغاز;

	جب(i++< لفظ_لمبائی)
	{
		log_info("address = %x data = %x\n", پتہ, *(غیرعلامتی حرف
							       *) پتہ);
		پتہ += 1;
	}
}
