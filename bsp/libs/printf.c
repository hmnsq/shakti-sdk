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

ساكن مضمن فراغ itoa (بنانشان ڊگهو ڊگهو صحيح عدد, بنانشان بنياد)
{
	صحيح i = 0;
	بنانشان صحيح intermediate = 0;
	بنانشان صحيح digits[حجم(عدد)*8];

	طالما (1) {
		digits[i] = عدد % بنياد;

		إذا (عدد < بنياد)
			اكسر;

		عدد /= بنياد;
		i++;
	}
	i++;
	طالما (i-- > 0)
	{
		إذا (digits[i] >= 10)
			intermediate = 'a' - 10;
		وإلا
			intermediate = '0';

		اکر_لکو(digits[i] + intermediate);
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
	ثابت حرف* آخري_fmt;
	سجل صحيح ch;
	بنانشان ڊگهو ڊگهو انگ;
	صحيح بنياد, lflag, i;
	عائم float_انگ = 0;
	حرف float_arr[30] = {'\0'};
	صحيح backtothebeginning;

	لكل (;;) {
		لكل (;(ch = *(بنانشان حرف *) fmt) != '%'; fmt++) {
			إذا (ch == '\0')
				أرجع;
			اکر_لکو(ch);
		}
		fmt++;

		// Process a %-escape sequence
		آخري_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		لكل (;;) {

			بدل (ch = *(بنانشان حرف *) fmt++) {

				// long flag (doubled for long long)
				حالة 'l':
					lflag++;
					backtothebeginning = 1;
					اكسر;

					// character
				حالة 'c':
					اکر_لکو(va_arg(ap, صحيح));
					اكسر;

					// string
				حالة 's':
					إذا ((p = va_arg(ap, حرف *)) == عدم)
						p = "(null)";
					لكل (; (ch = *p) != '\0' ;) {
						اکر_لکو(ch);
						p++;
					}
					اكسر;

					// (signed) decimal
				حالة 'd':
					بنياد = 10;

					إذا (lflag >= 2)
						انگ = va_arg(ap, ڊگهو ڊگهو);
					وإلا إذا (lflag ==1)
						انگ = va_arg(ap, ڊگهو);
					وإلا
						انگ = va_arg(ap, صحيح);

					إذا ((ڊگهو ڊگهو) انگ < 0) {
						اکر_لکو('-');
						انگ = -(ڊگهو ڊگهو) انگ;
					}

					itoa( انگ, بنياد);

					اكسر;

				حالة 'f':
					float_انگ =  va_arg(ap, مزدوج);

					ftoa(float_انگ, float_arr, 6);

					لكل( i = 0; float_arr[i] != '\0'; i++)
					{
						اکر_لکو(float_arr[i]);
						إذا(i > 29) اكسر;
					}
					اكسر;

					// unsigned decimal
				حالة 'u':
					بنياد = 10;

					إذا (lflag >= 2)
						انگ = va_arg(ap, بنانشان ڊگهو ڊگهو);
					وإلا إذا (lflag)
						انگ = va_arg(ap, بنانشان ڊگهو);
					وإلا
						انگ = va_arg(ap, بنانشان صحيح);

					itoa( انگ, بنياد);

					اكسر;

					// (unsigned) octal
				حالة 'o':
					// should do something with padding so it's always 3 octits
					بنياد = 8;

					إذا (lflag >= 2)
						انگ = va_arg(ap, بنانشان ڊگهو ڊگهو);
					وإلا إذا (lflag)
						انگ = va_arg(ap, بنانشان ڊگهو);
					وإلا
						انگ = va_arg(ap, بنانشان صحيح);

					itoa( انگ, بنياد);

					اكسر;

				حالة 'x':
					بنياد = 16;

					إذا (lflag >= 2)
						انگ = va_arg(ap, بنانشان ڊگهو ڊگهو);
					وإلا إذا (lflag)
						انگ = va_arg(ap, بنانشان ڊگهو);
					وإلا
						انگ = va_arg(ap, بنانشان صحيح);

					itoa( انگ, بنياد);

					اكسر;

					// escaped '%' character
				حالة '%':
					اکر_لکو(ch);
					اكسر;

					// unrecognized escape sequence - just print it literally
				افتراضي:
					اکر_لکو('%');
					fmt = آخري_fmt;
					اكسر;
			}

			إذا (backtothebeginning)
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
صحيح لکو(ثابت حرف* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	أرجع 0;// incorrect return value, but who cares, anyway?
}
