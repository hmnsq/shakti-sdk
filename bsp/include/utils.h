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

#اگر_تعریف_نشده UTIL_H
#تعریف_کن UTIL_H
#ضمن <stdio.h>
#ضمن <stdint.h>

/* function prototype */
فراغ waitfor(بیعلامت صحيح secs);
فراغ delay(بیعلامت دراز seconds);
عائم pow_10(بیعلامت صحيح y);
فراغ معکوس(حرف *str, صحيح len);
فراغ ftoa( عائم, حرف *, بیعلامت صحيح);
فراغ delay_loop(بیعلامت دراز cntr1, بیعلامت دراز cntr2);
بیعلامت دراز read_کلمه(uint32_t *addr);
فراغ write_کلمه(uint32_t *addr, بیعلامت دراز val);
صحيح int_مقصد_string(صحيح عدد, حرف str[], بیعلامت صحيح afterpoint);
فراغ _printf_(ثابت حرف *fmt, va_list ap);
صحيح چاپ_کن(ثابت حرف* fmt, ...);

#پایان_اگر
