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

#ضمن <stdint.h>
#ضمن <stdarg.h>
#ضمن "utils.h"
#ضمن "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ساكن مضمن فراغ itoa (unsigned long long صحيح number, unsigned base)
{
	صحيح i = 0;
	unsigned صحيح intermediate = 0;
	unsigned صحيح digits[حجم(number)*8];

	طالما (1) {
		digits[i] = number % base;

		𐤀𐤌 (number < base)
			اكسر;

		number /= base;
		i++;
	}
	i++;
	طالما (i-- > 0)
	{
		𐤀𐤌 (digits[i] >= 10)
			intermediate = 'a' - 10;
		وإلا
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
فراغ _printf_(ثابت حرف *fmt, va_list ap)
{
	سجل ثابت حرف* p;
	ثابت حرف* last_fmt;
	سجل صحيح ch;
	unsigned long long num;
	صحيح base, lflag, i;
	عائم float_num = 0;
	حرف float_arr[30] = {'\0'};
	صحيح backtothebeginning;

	لكل (;;) {
		لكل (;(ch = *(unsigned حرف *) fmt) != '%'; fmt++) {
			𐤀𐤌 (ch == '\0')
				أرجع;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		لكل (;;) {

			بدل (ch = *(unsigned حرف *) fmt++) {

				// long flag (doubled for long long)
				حالة 'l':
					lflag++;
					backtothebeginning = 1;
					اكسر;

					// character
				حالة 'c':
					putchar(va_arg(ap, صحيح));
					اكسر;

					// string
				حالة 's':
					𐤀𐤌 ((p = va_arg(ap, حرف *)) == عدم)
						p = "(null)";
					لكل (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					اكسر;

					// (signed) decimal
				حالة 'd':
					base = 10;

					𐤀𐤌 (lflag >= 2)
						num = va_arg(ap, long long);
					وإلا 𐤀𐤌 (lflag ==1)
						num = va_arg(ap, long);
					وإلا
						num = va_arg(ap, صحيح);

					𐤀𐤌 ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					اكسر;

				حالة 'f':
					float_num =  va_arg(ap, مزدوج);

					ftoa(float_num, float_arr, 6);

					لكل( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						𐤀𐤌(i > 29) اكسر;
					}
					اكسر;

					// unsigned decimal
				حالة 'u':
					base = 10;

					𐤀𐤌 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					وإلا 𐤀𐤌 (lflag)
						num = va_arg(ap, unsigned long);
					وإلا
						num = va_arg(ap, unsigned صحيح);

					itoa( num, base);

					اكسر;

					// (unsigned) octal
				حالة 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					𐤀𐤌 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					وإلا 𐤀𐤌 (lflag)
						num = va_arg(ap, unsigned long);
					وإلا
						num = va_arg(ap, unsigned صحيح);

					itoa( num, base);

					اكسر;

				حالة 'x':
					base = 16;

					𐤀𐤌 (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					وإلا 𐤀𐤌 (lflag)
						num = va_arg(ap, unsigned long);
					وإلا
						num = va_arg(ap, unsigned صحيح);

					itoa( num, base);

					اكسر;

					// escaped '%' character
				حالة '%':
					putchar(ch);
					اكسر;

					// unrecognized escape sequence - just print it literally
				افتراضي:
					putchar('%');
					fmt = last_fmt;
					اكسر;
			}

			𐤀𐤌 (backtothebeginning)
			{
				backtothebeginning = 0;
				استمر;
			}
			وإلا
				اكسر;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
صحيح printf(ثابت حرف* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	أرجع 0;// incorrect return value, but who cares, anyway?
}
