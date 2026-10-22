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
#ضمن <stdio.h>
#ضمن <stdint.h>

/* function prototype */
فراغ waitfor(unsigned صحيح secs);
فراغ delay(unsigned long seconds);
عائم pow_10(unsigned صحيح y);
فراغ reverse(حرف *str, صحيح len);
فراغ ftoa( عائم, حرف *, unsigned صحيح);
فراغ delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
فراغ write_word(uint32_t *addr, unsigned long val);
صحيح int_to_string(صحيح رقم_2, حرف str[], unsigned صحيح afterpoint);
فراغ _printf_(ثابت حرف *fmt, va_list ap);
صحيح printf(ثابت حرف* fmt, ...);

#endif
