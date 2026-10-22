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

#جيڪڏهن_وصف_نه_ٿيل UTIL_H
#وصف_ڪريو UTIL_H
#ضمن <stdio.h>
#ضمن <stdint.h>

/* function prototype */
فراغ waitfor(بنانشان صحيح secs);
فراغ delay(بنانشان ڊگهو seconds);
عائم pow_10(بنانشان صحيح y);
فراغ ابتو(حرف *str, صحيح len);
فراغ ftoa( عائم, حرف *, بنانشان صحيح);
فراغ delay_loop(بنانشان ڊگهو cntr1, بنانشان ڊگهو cntr2);
بنانشان ڊگهو read_لفظ(uint32_t *addr);
فراغ write_لفظ(uint32_t *addr, بنانشان ڊگهو val);
صحيح int_منزل_string(صحيح عدد, حرف str[], بنانشان صحيح afterpoint);
فراغ _printf_(ثابت حرف *fmt, va_list ap);
صحيح لکو(ثابت حرف* fmt, ...);

#جيڪڏهن_پورو
