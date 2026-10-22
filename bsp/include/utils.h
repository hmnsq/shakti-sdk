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

#که_نه_تعریف_شوی UTIL_H
#تعریف_کړه UTIL_H
#ضمن <stdio.h>
#ضمن <stdint.h>

/* function prototype */
فراغ waitfor(بینښه صحيح secs);
فراغ delay(بینښه اوږد seconds);
عائم pow_10(بینښه صحيح y);
فراغ سرچپه(حرف *str, صحيح len);
فراغ ftoa( عائم, حرف *, بینښه صحيح);
فراغ delay_loop(بینښه اوږد cntr1, بینښه اوږد cntr2);
بینښه اوږد read_کلمه(uint32_t *addr);
فراغ write_کلمه(uint32_t *addr, بینښه اوږد val);
صحيح int_منزل_string(صحيح شمېره, حرف str[], بینښه صحيح afterpoint);
فراغ _printf_(ثابت حرف *fmt, va_list ap);
صحيح چاپ_کړه(ثابت حرف* fmt, ...);

#د_که_پای
