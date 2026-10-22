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
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

/* function prototype */
ಶೂನ್ಯ waitfor(unsigned ಪೂರ್ಣಾಙ್ಕ secs);
ಶೂನ್ಯ delay(unsigned long seconds);
ಭಿನ್ನ pow_10(unsigned ಪೂರ್ಣಾಙ್ಕ y);
ಶೂನ್ಯ reverse(ವರ್ಣ *str, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ftoa( ಭಿನ್ನ, ವರ್ಣ *, unsigned ಪೂರ್ಣಾಙ್ಕ);
ಶೂನ್ಯ delay_loop(unsigned long cntr1, unsigned long cntr2);
unsigned long read_word(uint32_t *addr);
ಶೂನ್ಯ write_word(uint32_t *addr, unsigned long val);
ಪೂರ್ಣಾಙ್ಕ int_to_string(ಪೂರ್ಣಾಙ್ಕ ಸಂಖ್ಯೆ, ವರ್ಣ str[], unsigned ಪೂರ್ಣಾಙ್ಕ afterpoint);
ಶೂನ್ಯ _printf_(ಧ್ರುವ ವರ್ಣ *fmt, va_list ap);
ಪೂರ್ಣಾಙ್ಕ printf(ಧ್ರುವ ವರ್ಣ* fmt, ...);

#endif
