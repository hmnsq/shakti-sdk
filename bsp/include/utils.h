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

#جے_بنا_تعریف UTIL_H
#تعریف_کرو UTIL_H
#ضمن <stdio.h>
#ضمن <stdint.h>

/* function prototype */
فراغ waitfor(بنانشانی صحيح secs);
فراغ delay(بنانشانی لما seconds);
عائم pow_10(بنانشانی صحيح y);
فراغ الٹ(حرف *str, صحيح len);
فراغ ftoa( عائم, حرف *, بنانشانی صحيح);
فراغ delay_loop(بنانشانی لما cntr1, بنانشانی لما cntr2);
بنانشانی لما read_لفظ(uint32_t *addr);
فراغ write_لفظ(uint32_t *addr, بنانشانی لما val);
صحيح int_منزل_string(صحيح نمبر, حرف str[], بنانشانی صحيح afterpoint);
فراغ _printf_(ثابت حرف *fmt, va_list ap);
صحيح لکھو(ثابت حرف* fmt, ...);

#جے_انت
