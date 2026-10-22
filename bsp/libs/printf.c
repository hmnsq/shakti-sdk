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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব "utils.h"
#অন্তর্ভাব "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

স্থির অন্তঃরেখ শূন্য itoa (unsigned long long পূর্ণসংখ্যা সংখ্যা, unsigned base)
{
	পূর্ণসংখ্যা i = 0;
	unsigned পূর্ণসংখ্যা intermediate = 0;
	unsigned পূর্ণসংখ্যা digits[আকার(সংখ্যা)*8];

	যখন (1) {
		digits[i] = সংখ্যা % base;

		যদি (সংখ্যা < base)
			বিরতি;

		সংখ্যা /= base;
		i++;
	}
	i++;
	যখন (i-- > 0)
	{
		যদি (digits[i] >= 10)
			intermediate = 'a' - 10;
		অন্যথা
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
শূন্য _printf_(ধ্রুবক অক্ষর *fmt, va_list ap)
{
	নিবন্ধ ধ্রুবক অক্ষর* p;
	ধ্রুবক অক্ষর* last_fmt;
	নিবন্ধ পূর্ণসংখ্যা ch;
	unsigned long long অঙ্ক;
	পূর্ণসংখ্যা base, lflag, i;
	দশমিক float_অঙ্ক = 0;
	অক্ষর float_arr[30] = {'\0'};
	পূর্ণসংখ্যা backtothebeginning;

	জন্য (;;) {
		জন্য (;(ch = *(unsigned অক্ষর *) fmt) != '%'; fmt++) {
			যদি (ch == '\0')
				ফেরত;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		জন্য (;;) {

			নির্বাচন (ch = *(unsigned অক্ষর *) fmt++) {

				// long flag (doubled for long long)
				ক্ষেত্র 'l':
					lflag++;
					backtothebeginning = 1;
					বিরতি;

					// character
				ক্ষেত্র 'c':
					putchar(va_arg(ap, পূর্ণসংখ্যা));
					বিরতি;

					// string
				ক্ষেত্র 's':
					যদি ((p = va_arg(ap, অক্ষর *)) == ফাঁকা)
						p = "(null)";
					জন্য (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					বিরতি;

					// (signed) decimal
				ক্ষেত্র 'd':
					base = 10;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, long long);
					অন্যথা যদি (lflag ==1)
						অঙ্ক = va_arg(ap, long);
					অন্যথা
						অঙ্ক = va_arg(ap, পূর্ণসংখ্যা);

					যদি ((long long) অঙ্ক < 0) {
						putchar('-');
						অঙ্ক = -(long long) অঙ্ক;
					}

					itoa( অঙ্ক, base);

					বিরতি;

				ক্ষেত্র 'f':
					float_অঙ্ক =  va_arg(ap, দ্বিগুণ);

					ftoa(float_অঙ্ক, float_arr, 6);

					জন্য( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						যদি(i > 29) বিরতি;
					}
					বিরতি;

					// unsigned decimal
				ক্ষেত্র 'u':
					base = 10;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণসংখ্যা);

					itoa( অঙ্ক, base);

					বিরতি;

					// (unsigned) octal
				ক্ষেত্র 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণসংখ্যা);

					itoa( অঙ্ক, base);

					বিরতি;

				ক্ষেত্র 'x':
					base = 16;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণসংখ্যা);

					itoa( অঙ্ক, base);

					বিরতি;

					// escaped '%' character
				ক্ষেত্র '%':
					putchar(ch);
					বিরতি;

					// unrecognized escape sequence - just print it literally
				পূর্বনির্ধারিত:
					putchar('%');
					fmt = last_fmt;
					বিরতি;
			}

			যদি (backtothebeginning)
			{
				backtothebeginning = 0;
				চালু;
			}
			অন্যথা
				বিরতি;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
পূর্ণসংখ্যা printf(ধ্রুবক অক্ষর* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ফেরত 0;// incorrect return value, but who cares, anyway?
}
