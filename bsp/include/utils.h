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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ UTIL_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UTIL_H
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* function prototype */
ਖਾਲੀ waitfor(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ secs);
ਖਾਲੀ delay(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ seconds);
ਦਸ਼ਮਲਵ pow_10(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ y);
ਖਾਲੀ ਉਲਟ(ਅੱਖਰ *str, ਪੂਰਨ len);
ਖਾਲੀ ftoa( ਦਸ਼ਮਲਵ, ਅੱਖਰ *, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);
ਖਾਲੀ delay_loop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ cntr1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ cntr2);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਸ਼ਬਦ(uint32_t *addr);
ਖਾਲੀ write_ਸ਼ਬਦ(uint32_t *addr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ val);
ਪੂਰਨ int_ਮੰਜ਼ਿਲ_string(ਪੂਰਨ ਸੰਖਿਆ, ਅੱਖਰ str[], ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ afterpoint);
ਖਾਲੀ _printf_(ਅਚਲ ਅੱਖਰ *fmt, va_list ap);
ਪੂਰਨ ਲਿਖੋ(ਅਚਲ ਅੱਖਰ* fmt, ...);

#ਜੇ_ਅੰਤ
