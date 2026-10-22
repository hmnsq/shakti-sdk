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

static inline void itoa (unsigned long long số_nguyên number, unsigned base)
{
	số_nguyên i = 0;
	unsigned số_nguyên intermediate = 0;
	unsigned số_nguyên digits[sizeof(number)*8];

	trong_khi (1) {
		digits[i] = number % base;

		nếu (number < base)
			break;

		number /= base;
		i++;
	}
	i++;
	trong_khi (i-- > 0)
	{
		nếu (digits[i] >= 10)
			intermediate = 'a' - 10;
		không_thì
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
void _printf_(const char *fmt, va_list ap)
{
	register const char* p;
	const char* last_fmt;
	register số_nguyên ch;
	unsigned long long num;
	số_nguyên base, lflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	số_nguyên backtothebeginning;

	cho (;;) {
		cho (;(ch = *(unsigned char *) fmt) != '%'; fmt++) {
			nếu (ch == '\0')
				trả_về;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		cho (;;) {

			switch (ch = *(unsigned char *) fmt++) {

				// long flag (doubled for long long)
				case 'l':
					lflag++;
					backtothebeginning = 1;
					break;

					// character
				case 'c':
					putchar(va_arg(ap, số_nguyên));
					break;

					// string
				case 's':
					nếu ((p = va_arg(ap, char *)) == NULL)
						p = "(null)";
					cho (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					break;

					// (signed) decimal
				case 'd':
					base = 10;

					nếu (lflag >= 2)
						num = va_arg(ap, long long);
					không_thì nếu (lflag ==1)
						num = va_arg(ap, long);
					không_thì
						num = va_arg(ap, số_nguyên);

					nếu ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					break;

				case 'f':
					float_num =  va_arg(ap, double);

					ftoa(float_num, float_arr, 6);

					cho( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						nếu(i > 29) break;
					}
					break;

					// unsigned decimal
				case 'u':
					base = 10;

					nếu (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					không_thì nếu (lflag)
						num = va_arg(ap, unsigned long);
					không_thì
						num = va_arg(ap, unsigned số_nguyên);

					itoa( num, base);

					break;

					// (unsigned) octal
				case 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					nếu (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					không_thì nếu (lflag)
						num = va_arg(ap, unsigned long);
					không_thì
						num = va_arg(ap, unsigned số_nguyên);

					itoa( num, base);

					break;

				case 'x':
					base = 16;

					nếu (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					không_thì nếu (lflag)
						num = va_arg(ap, unsigned long);
					không_thì
						num = va_arg(ap, unsigned số_nguyên);

					itoa( num, base);

					break;

					// escaped '%' character
				case '%':
					putchar(ch);
					break;

					// unrecognized escape sequence - just print it literally
				default:
					putchar('%');
					fmt = last_fmt;
					break;
			}

			nếu (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			không_thì
				break;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
số_nguyên printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	trả_về 0;// incorrect return value, but who cares, anyway?
}
