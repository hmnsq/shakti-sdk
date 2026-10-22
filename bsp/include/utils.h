/****************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: utils.h
 * Brief Description of file    : Header file for utils
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
*******************************************************************************/
/**
 * @file utils.h
 * @brief header file for utils
 * @detail This is the header file for util.c
 */

#ifndef UTIL_H
#define UTIL_H
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdint.h>

/* function prototype */
শূন্য waitfor(unsigned পূর্ণসংখ্যা secs);
শূন্য delay(unsigned long seconds);
দশমিক pow_10(unsigned পূর্ণসংখ্যা y);
শূন্য reverse(অক্ষর *str, পূর্ণসংখ্যা len);
শূন্য ftoa( দশমিক, অক্ষর *, unsigned পূর্ণসংখ্যা);
শূন্য delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
শূন্য write_word(uint32_t *addr, unsigned long val);
পূর্ণসংখ্যা int_to_string(পূর্ণসংখ্যা সংখ্যা, অক্ষর str[], unsigned পূর্ণসংখ্যা afterpoint);
শূন্য _printf_(ধ্রুবক অক্ষর *fmt, va_list ap);
পূর্ণসংখ্যা printf(ধ্রুবক অক্ষর* fmt, ...);

#endif
