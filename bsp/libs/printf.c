/***************************************************************************
 * Project           		:  shakti devt board
 * Name of the file	     	:  printf.c
 * Brief Description of file    :  Print based command and control by uart
 * Name of Author    	        :  Sathya Narayanan N & Balaji venkat
 * Email ID                     :  sathya281@gmail.com

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

***************************************************************************/
/**
@file printf.c
@brief Print based command and control by uart
@detail This file hosts a list of routines that helps in displaying variable's
value based on there data type. Currently, shakti-sdk supports few formatting options.
*/

#include <stdint.h>
#include <stdarg.h>
#include "utils.h"
#include "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

static anta_hstha void itoa (unsigned long long ကိန်းပြည့် number, unsigned base)
{
	ကိန်းပြည့် i = 0;
	unsigned ကိန်းပြည့် intermediate = 0;
	unsigned ကိန်းပြည့် digits[parimaa_na(number)*8];

	နေစဉ် (1) {
		digits[i] = number % base;

		အကယ်၍ (number < base)
			bha_nga;

		number /= base;
		i++;
	}
	i++;
	နေစဉ် (i-- > 0)
	{
		အကယ်၍ (digits[i] >= 10)
			intermediate = 'a' - 10;
		မဟုတ်ပါက
			intermediate = '0';

		putchar(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
void _printf_(const var_na *fmt, va_list ap)
{
	pa_njikaa const var_na* p;
	const var_na* last_fmt;
	pa_njikaa ကိန်းပြည့် ch;
	unsigned long long num;
	ကိန်းပြည့် base, lflag, i;
	float float_num = 0;
	var_na float_arr[30] = {'\0'};
	ကိန်းပြည့် backtothebeginning;

	အတွက် (;;) {
		အတွက် (;(ch = *(unsigned var_na *) fmt) != '%'; fmt++) {
			အကယ်၍ (ch == '\0')
				ပြန်ပေး;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		အတွက် (;;) {

			switch (ch = *(unsigned var_na *) fmt++) {

				// long flag (doubled for long long)
				pak_sa 'l':
					lflag++;
					backtothebeginning = 1;
					bha_nga;

					// character
				pak_sa 'c':
					putchar(va_arg(ap, ကိန်းပြည့်));
					bha_nga;

					// string
				pak_sa 's':
					အကယ်၍ ((p = va_arg(ap, var_na *)) == NULL)
						p = "(null)";
					အတွက် (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					bha_nga;

					// (signed) decimal
				pak_sa 'd':
					base = 10;

					အကယ်၍ (lflag >= 2)
						num = va_arg(ap, long long);
					မဟုတ်ပါက အကယ်၍ (lflag ==1)
						num = va_arg(ap, long);
					မဟုတ်ပါက
						num = va_arg(ap, ကိန်းပြည့်);

					အကယ်၍ ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					bha_nga;

				pak_sa 'f':
					float_num =  va_arg(ap, dviguu_na);

					ftoa(float_num, float_arr, 6);

					အတွက်( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						အကယ်၍(i > 29) bha_nga;
					}
					bha_nga;

					// unsigned decimal
				pak_sa 'u':
					base = 10;

					အကယ်၍ (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					မဟုတ်ပါက အကယ်၍ (lflag)
						num = va_arg(ap, unsigned long);
					မဟုတ်ပါက
						num = va_arg(ap, unsigned ကိန်းပြည့်);

					itoa( num, base);

					bha_nga;

					// (unsigned) octal
				pak_sa 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					အကယ်၍ (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					မဟုတ်ပါက အကယ်၍ (lflag)
						num = va_arg(ap, unsigned long);
					မဟုတ်ပါက
						num = va_arg(ap, unsigned ကိန်းပြည့်);

					itoa( num, base);

					bha_nga;

				pak_sa 'x':
					base = 16;

					အကယ်၍ (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					မဟုတ်ပါက အကယ်၍ (lflag)
						num = va_arg(ap, unsigned long);
					မဟုတ်ပါက
						num = va_arg(ap, unsigned ကိန်းပြည့်);

					itoa( num, base);

					bha_nga;

					// escaped '%' character
				pak_sa '%':
					putchar(ch);
					bha_nga;

					// unrecognized escape sequence - just print it literally
				default:
					putchar('%');
					fmt = last_fmt;
					bha_nga;
			}

			အကယ်၍ (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			မဟုတ်ပါက
				bha_nga;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
ကိန်းပြည့် printf(const var_na* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ပြန်ပေး 0;// incorrect return value, but who cares, anyway?
}
