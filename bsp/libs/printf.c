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

static inline void itoa (unsigned long long ціле number, unsigned base)
{
	ціле i = 0;
	unsigned ціле intermediate = 0;
	unsigned ціле digits[sizeof(number)*8];

	поки (1) {
		digits[i] = number % base;

		якщо (number < base)
			break;

		number /= base;
		i++;
	}
	i++;
	поки (i-- > 0)
	{
		якщо (digits[i] >= 10)
			intermediate = 'a' - 10;
		інакше
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
	register ціле ch;
	unsigned long long num;
	ціле base, lflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	ціле backtothebeginning;

	для (;;) {
		для (;(ch = *(unsigned char *) fmt) != '%'; fmt++) {
			якщо (ch == '\0')
				повернути;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		для (;;) {

			switch (ch = *(unsigned char *) fmt++) {

				// long flag (doubled for long long)
				case 'l':
					lflag++;
					backtothebeginning = 1;
					break;

					// character
				case 'c':
					putchar(va_arg(ap, ціле));
					break;

					// string
				case 's':
					якщо ((p = va_arg(ap, char *)) == NULL)
						p = "(null)";
					для (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					break;

					// (signed) decimal
				case 'd':
					base = 10;

					якщо (lflag >= 2)
						num = va_arg(ap, long long);
					інакше якщо (lflag ==1)
						num = va_arg(ap, long);
					інакше
						num = va_arg(ap, ціле);

					якщо ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					break;

				case 'f':
					float_num =  va_arg(ap, double);

					ftoa(float_num, float_arr, 6);

					для( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						якщо(i > 29) break;
					}
					break;

					// unsigned decimal
				case 'u':
					base = 10;

					якщо (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					інакше якщо (lflag)
						num = va_arg(ap, unsigned long);
					інакше
						num = va_arg(ap, unsigned ціле);

					itoa( num, base);

					break;

					// (unsigned) octal
				case 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					якщо (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					інакше якщо (lflag)
						num = va_arg(ap, unsigned long);
					інакше
						num = va_arg(ap, unsigned ціле);

					itoa( num, base);

					break;

				case 'x':
					base = 16;

					якщо (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					інакше якщо (lflag)
						num = va_arg(ap, unsigned long);
					інакше
						num = va_arg(ap, unsigned ціле);

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

			якщо (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			інакше
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
ціле printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	повернути 0;// incorrect return value, but who cares, anyway?
}
