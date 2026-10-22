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

static inline void itoa (unsigned long long 정수 number, unsigned base)
{
	정수 i = 0;
	unsigned 정수 intermediate = 0;
	unsigned 정수 digits[sizeof(number)*8];

	동안 (1) {
		digits[i] = number % base;

		만약 (number < base)
			break;

		number /= base;
		i++;
	}
	i++;
	동안 (i-- > 0)
	{
		만약 (digits[i] >= 10)
			intermediate = 'a' - 10;
		아니면
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
	register 정수 ch;
	unsigned long long num;
	정수 base, lflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	정수 backtothebeginning;

	위해 (;;) {
		위해 (;(ch = *(unsigned char *) fmt) != '%'; fmt++) {
			만약 (ch == '\0')
				반환;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		위해 (;;) {

			switch (ch = *(unsigned char *) fmt++) {

				// long flag (doubled for long long)
				case 'l':
					lflag++;
					backtothebeginning = 1;
					break;

					// character
				case 'c':
					putchar(va_arg(ap, 정수));
					break;

					// string
				case 's':
					만약 ((p = va_arg(ap, char *)) == NULL)
						p = "(null)";
					위해 (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					break;

					// (signed) decimal
				case 'd':
					base = 10;

					만약 (lflag >= 2)
						num = va_arg(ap, long long);
					아니면 만약 (lflag ==1)
						num = va_arg(ap, long);
					아니면
						num = va_arg(ap, 정수);

					만약 ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					break;

				case 'f':
					float_num =  va_arg(ap, double);

					ftoa(float_num, float_arr, 6);

					위해( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						만약(i > 29) break;
					}
					break;

					// unsigned decimal
				case 'u':
					base = 10;

					만약 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					아니면 만약 (lflag)
						num = va_arg(ap, unsigned long);
					아니면
						num = va_arg(ap, unsigned 정수);

					itoa( num, base);

					break;

					// (unsigned) octal
				case 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					만약 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					아니면 만약 (lflag)
						num = va_arg(ap, unsigned long);
					아니면
						num = va_arg(ap, unsigned 정수);

					itoa( num, base);

					break;

				case 'x':
					base = 16;

					만약 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					아니면 만약 (lflag)
						num = va_arg(ap, unsigned long);
					아니면
						num = va_arg(ap, unsigned 정수);

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

			만약 (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			아니면
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
정수 printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	반환 0;// incorrect return value, but who cares, anyway?
}
