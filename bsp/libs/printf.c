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

ساكن مضمن فراغ itoa (بیعلامت دراز دراز صحيح عدد, بیعلامت پایه)
{
	صحيح i = 0;
	بیعلامت صحيح intermediate = 0;
	بیعلامت صحيح digits[حجم(عدد)*8];

	طالما (1) {
		digits[i] = عدد % پایه;

		إذا (عدد < پایه)
			اكسر;

		عدد /= پایه;
		i++;
	}
	i++;
	طالما (i-- > 0)
	{
		إذا (digits[i] >= 10)
			intermediate = 'a' - 10;
		وإلا
			intermediate = '0';

		حرف_چاپ_کن(digits[i] + intermediate);
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
	ثابت حرف* آخرین_fmt;
	سجل صحيح ch;
	بیعلامت دراز دراز رقم;
	صحيح پایه, lflag, i;
	عائم float_رقم = 0;
	حرف float_arr[30] = {'\0'};
	صحيح backtothebeginning;

	لكل (;;) {
		لكل (;(ch = *(بیعلامت حرف *) fmt) != '%'; fmt++) {
			إذا (ch == '\0')
				أرجع;
			حرف_چاپ_کن(ch);
		}
		fmt++;

		// Process a %-escape sequence
		آخرین_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		لكل (;;) {

			بدل (ch = *(بیعلامت حرف *) fmt++) {

				// long flag (doubled for long long)
				حالة 'l':
					lflag++;
					backtothebeginning = 1;
					اكسر;

					// character
				حالة 'c':
					حرف_چاپ_کن(va_arg(ap, صحيح));
					اكسر;

					// string
				حالة 's':
					إذا ((p = va_arg(ap, حرف *)) == عدم)
						p = "(null)";
					لكل (; (ch = *p) != '\0' ;) {
						حرف_چاپ_کن(ch);
						p++;
					}
					اكسر;

					// (signed) decimal
				حالة 'd':
					پایه = 10;

					إذا (lflag >= 2)
						رقم = va_arg(ap, دراز دراز);
					وإلا إذا (lflag ==1)
						رقم = va_arg(ap, دراز);
					وإلا
						رقم = va_arg(ap, صحيح);

					إذا ((دراز دراز) رقم < 0) {
						حرف_چاپ_کن('-');
						رقم = -(دراز دراز) رقم;
					}

					itoa( رقم, پایه);

					اكسر;

				حالة 'f':
					float_رقم =  va_arg(ap, مزدوج);

					ftoa(float_رقم, float_arr, 6);

					لكل( i = 0; float_arr[i] != '\0'; i++)
					{
						حرف_چاپ_کن(float_arr[i]);
						إذا(i > 29) اكسر;
					}
					اكسر;

					// unsigned decimal
				حالة 'u':
					پایه = 10;

					إذا (lflag >= 2)
						رقم = va_arg(ap, بیعلامت دراز دراز);
					وإلا إذا (lflag)
						رقم = va_arg(ap, بیعلامت دراز);
					وإلا
						رقم = va_arg(ap, بیعلامت صحيح);

					itoa( رقم, پایه);

					اكسر;

					// (unsigned) octal
				حالة 'o':
					// should do something with padding so it's always 3 octits
					پایه = 8;

					إذا (lflag >= 2)
						رقم = va_arg(ap, بیعلامت دراز دراز);
					وإلا إذا (lflag)
						رقم = va_arg(ap, بیعلامت دراز);
					وإلا
						رقم = va_arg(ap, بیعلامت صحيح);

					itoa( رقم, پایه);

					اكسر;

				حالة 'x':
					پایه = 16;

					إذا (lflag >= 2)
						رقم = va_arg(ap, بیعلامت دراز دراز);
					وإلا إذا (lflag)
						رقم = va_arg(ap, بیعلامت دراز);
					وإلا
						رقم = va_arg(ap, بیعلامت صحيح);

					itoa( رقم, پایه);

					اكسر;

					// escaped '%' character
				حالة '%':
					حرف_چاپ_کن(ch);
					اكسر;

					// unrecognized escape sequence - just print it literally
				افتراضي:
					حرف_چاپ_کن('%');
					fmt = آخرین_fmt;
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
صحيح چاپ_کن(ثابت حرف* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	أرجع 0;// incorrect return value, but who cares, anyway?
}
