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
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdint.h>

/* function prototype */
শূন্য waitfor(unsigned পূর্ণাঙ্ক secs);
শূন্য delay(unsigned long seconds);
ভিন্ন pow_10(unsigned পূর্ণাঙ্ক y);
শূন্য reverse(ৱর্ণ *str, পূর্ণাঙ্ক len);
শূন্য ftoa( ভিন্ন, ৱর্ণ *, unsigned পূর্ণাঙ্ক);
শূন্য delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
শূন্য write_word(uint32_t *addr, unsigned long val);
পূর্ণাঙ্ক int_to_string(পূর্ণাঙ্ক সংখ্যা, ৱর্ণ str[], unsigned পূর্ণাঙ্ক afterpoint);
শূন্য _printf_(ধ্রুৱ ৱর্ণ *fmt, va_list ap);
পূর্ণাঙ্ক printf(ধ্রুৱ ৱর্ণ* fmt, ...);

#endif
