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
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdint.h>

/* function prototype */
શૂન્ય waitfor(unsigned પૂર્ણાંક secs);
શૂન્ય delay(unsigned long seconds);
દશાંશ pow_10(unsigned પૂર્ણાંક y);
શૂન્ય reverse(અક્ષર *str, પૂર્ણાંક len);
શૂન્ય ftoa( દશાંશ, અક્ષર *, unsigned પૂર્ણાંક);
શૂન્ય delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
શૂન્ય write_word(uint32_t *addr, unsigned long val);
પૂર્ણાંક int_to_string(પૂર્ણાંક સંખ્યા, અક્ષર str[], unsigned પૂર્ણાંક afterpoint);
શૂન્ય _printf_(અચલ અક્ષર *fmt, va_list ap);
પૂર્ણાંક printf(અચલ અક્ષર* fmt, ...);

#endif
