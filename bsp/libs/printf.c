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

static inline void itoa (unsigned long long 整数 number, unsigned base)
{
	整数 i = 0;
	unsigned 整数 intermediate = 0;
	unsigned 整数 digits[sizeof(number)*8];

	当 (1) {
		digits[i] = number % base;

		如果 (number < base)
			break;

		number /= base;
		i++;
	}
	i++;
	当 (i-- > 0)
	{
		如果 (digits[i] >= 10)
			intermediate = 'a' - 10;
		否则
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
	register 整数 ch;
	unsigned long long num;
	整数 base, lflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	整数 backtothebeginning;

	为 (;;) {
		为 (;(ch = *(unsigned char *) fmt) != '%'; fmt++) {
			如果 (ch == '\0')
				返回;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		为 (;;) {

			switch (ch = *(unsigned char *) fmt++) {

				// long flag (doubled for long long)
				case 'l':
					lflag++;
					backtothebeginning = 1;
					break;

					// character
				case 'c':
					putchar(va_arg(ap, 整数));
					break;

					// string
				case 's':
					如果 ((p = va_arg(ap, char *)) == NULL)
						p = "(null)";
					为 (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					break;

					// (signed) decimal
				case 'd':
					base = 10;

					如果 (lflag >= 2)
						num = va_arg(ap, long long);
					否则 如果 (lflag ==1)
						num = va_arg(ap, long);
					否则
						num = va_arg(ap, 整数);

					如果 ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					break;

				case 'f':
					float_num =  va_arg(ap, double);

					ftoa(float_num, float_arr, 6);

					为( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						如果(i > 29) break;
					}
					break;

					// unsigned decimal
				case 'u':
					base = 10;

					如果 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					否则 如果 (lflag)
						num = va_arg(ap, unsigned long);
					否则
						num = va_arg(ap, unsigned 整数);

					itoa( num, base);

					break;

					// (unsigned) octal
				case 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					如果 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					否则 如果 (lflag)
						num = va_arg(ap, unsigned long);
					否则
						num = va_arg(ap, unsigned 整数);

					itoa( num, base);

					break;

				case 'x':
					base = 16;

					如果 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					否则 如果 (lflag)
						num = va_arg(ap, unsigned long);
					否则
						num = va_arg(ap, unsigned 整数);

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

			如果 (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			否则
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
整数 printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	返回 0;// incorrect return value, but who cares, anyway?
}
