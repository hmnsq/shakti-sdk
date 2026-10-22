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
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdint.h>

/* function prototype */
ശൂന്യം waitfor(unsigned പൂർണ്ണസംഖ്യ secs);
ശൂന്യം delay(unsigned long seconds);
ദശാംശം pow_10(unsigned പൂർണ്ണസംഖ്യ y);
ശൂന്യം reverse(അക്ഷരം *str, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ftoa( ദശാംശം, അക്ഷരം *, unsigned പൂർണ്ണസംഖ്യ);
ശൂന്യം delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
ശൂന്യം write_word(uint32_t *addr, unsigned long val);
പൂർണ്ണസംഖ്യ int_to_string(പൂർണ്ണസംഖ്യ സംഖ്യ, അക്ഷരം str[], unsigned പൂർണ്ണസംഖ്യ afterpoint);
ശൂന്യം _printf_(സ്ഥിരം അക്ഷരം *fmt, va_list ap);
പൂർണ്ണസംഖ്യ printf(സ്ഥിരം അക്ഷരം* fmt, ...);

#endif
