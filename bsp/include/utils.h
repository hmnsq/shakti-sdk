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
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>

/* function prototype */
ଶୂନ୍ୟ waitfor(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା secs);
ଶୂନ୍ୟ delay(unsigned long seconds);
ଦଶମିକ pow_10(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା y);
ଶୂନ୍ୟ reverse(ଅକ୍ଷର *str, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ftoa( ଦଶମିକ, ଅକ୍ଷର *, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ଶୂନ୍ୟ delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
ଶୂନ୍ୟ write_word(uint32_t *addr, unsigned long val);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା int_to_string(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସଂଖ୍ୟା, ଅକ୍ଷର str[], unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା afterpoint);
ଶୂନ୍ୟ _printf_(ଅଚଳ ଅକ୍ଷର *fmt, va_list ap);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା printf(ଅଚଳ ଅକ୍ଷର* fmt, ...);

#endif
