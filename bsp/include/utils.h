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
#include <stdio.h>
#include <stdint.h>

/* function prototype */
void waitfor(unsigned ຈຳນວນເຕັມ secs);
void delay(unsigned long seconds);
float pow_10(unsigned ຈຳນວນເຕັມ y);
void reverse(var_na *str, ຈຳນວນເຕັມ len);
void ftoa( float, var_na *, unsigned ຈຳນວນເຕັມ);
void delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
void write_word(uint32_t *addr, unsigned long val);
ຈຳນວນເຕັມ int_to_string(ຈຳນວນເຕັມ number, var_na str[], unsigned ຈຳນວນເຕັມ afterpoint);
void _printf_(const var_na *fmt, va_list ap);
ຈຳນວນເຕັມ printf(const var_na* fmt, ...);

#endif
