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

#اگر_غیر_تعریف_شدہ UTIL_H
#تعریف_کرو UTIL_H
#شامل <stdio.h>
#شامل <stdint.h>

/* function prototype */
خالی waitfor(غیرعلامتی صحیح secs);
خالی delay(غیرعلامتی طویل seconds);
اعشاری pow_10(غیرعلامتی صحیح y);
خالی الٹ(حرف *str, صحیح len);
خالی ftoa( اعشاری, حرف *, غیرعلامتی صحیح);
خالی delay_loop(غیرعلامتی طویل cntr1, غیرعلامتی طویل cntr2);
غیرعلامتی طویل read_لفظ(uint32_t *addr);
خالی write_لفظ(uint32_t *addr, غیرعلامتی طویل val);
صحیح int_مقصد_string(صحیح نمبر, حرف str[], غیرعلامتی صحیح afterpoint);
خالی _printf_(ثابت حرف *fmt, va_list ap);
صحیح لکھو(ثابت حرف* fmt, ...);

#اگر_ختم
