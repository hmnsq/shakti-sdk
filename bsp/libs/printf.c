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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdarg.h>
#অন্তর্ভাৱ "utils.h"
#অন্তর্ভাৱ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

স্থির অন্তঃস্থ শূন্য itoa (unsigned long long পূর্ণাঙ্ক সংখ্যা, unsigned base)
{
	পূর্ণাঙ্ক i = 0;
	unsigned পূর্ণাঙ্ক intermediate = 0;
	unsigned পূর্ণাঙ্ক digits[পরিমাণ(সংখ্যা)*8];

	যেতিয়ালৈ (1) {
		digits[i] = সংখ্যা % base;

		যদি (সংখ্যা < base)
			ভঙ্গ;

		সংখ্যা /= base;
		i++;
	}
	i++;
	যেতিয়ালৈ (i-- > 0)
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
শূন্য _printf_(ধ্রুৱ ৱর্ণ *fmt, va_list ap)
{
	পঞ্জিকা ধ্রুৱ ৱর্ণ* p;
	ধ্রুৱ ৱর্ণ* last_fmt;
	পঞ্জিকা পূর্ণাঙ্ক ch;
	unsigned long long অঙ্ক;
	পূর্ণাঙ্ক base, lflag, i;
	ভিন্ন float_অঙ্ক = 0;
	ৱর্ণ float_arr[30] = {'\0'};
	পূর্ণাঙ্ক backtothebeginning;

	বাবে (;;) {
		বাবে (;(ch = *(unsigned ৱর্ণ *) fmt) != '%'; fmt++) {
			যদি (ch == '\0')
				ঘূৰাই;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		বাবে (;;) {

			ৱিকল্প (ch = *(unsigned ৱর্ণ *) fmt++) {

				// long flag (doubled for long long)
				পক্ষ 'l':
					lflag++;
					backtothebeginning = 1;
					ভঙ্গ;

					// character
				পক্ষ 'c':
					putchar(va_arg(ap, পূর্ণাঙ্ক));
					ভঙ্গ;

					// string
				পক্ষ 's':
					যদি ((p = va_arg(ap, ৱর্ণ *)) == রিক্ত)
						p = "(null)";
					বাবে (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					ভঙ্গ;

					// (signed) decimal
				পক্ষ 'd':
					base = 10;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, long long);
					অন্যথা যদি (lflag ==1)
						অঙ্ক = va_arg(ap, long);
					অন্যথা
						অঙ্ক = va_arg(ap, পূর্ণাঙ্ক);

					যদি ((long long) অঙ্ক < 0) {
						putchar('-');
						অঙ্ক = -(long long) অঙ্ক;
					}

					itoa( অঙ্ক, base);

					ভঙ্গ;

				পক্ষ 'f':
					float_অঙ্ক =  va_arg(ap, দ্ৱিগুণ);

					ftoa(float_অঙ্ক, float_arr, 6);

					বাবে( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						যদি(i > 29) ভঙ্গ;
					}
					ভঙ্গ;

					// unsigned decimal
				পক্ষ 'u':
					base = 10;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণাঙ্ক);

					itoa( অঙ্ক, base);

					ভঙ্গ;

					// (unsigned) octal
				পক্ষ 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণাঙ্ক);

					itoa( অঙ্ক, base);

					ভঙ্গ;

				পক্ষ 'x':
					base = 16;

					যদি (lflag >= 2)
						অঙ্ক = va_arg(ap, unsigned long long);
					অন্যথা যদি (lflag)
						অঙ্ক = va_arg(ap, unsigned long);
					অন্যথা
						অঙ্ক = va_arg(ap, unsigned পূর্ণাঙ্ক);

					itoa( অঙ্ক, base);

					ভঙ্গ;

					// escaped '%' character
				পক্ষ '%':
					putchar(ch);
					ভঙ্গ;

					// unrecognized escape sequence - just print it literally
				স্ৱভাৱ:
					putchar('%');
					fmt = last_fmt;
					ভঙ্গ;
			}

			যদি (backtothebeginning)
			{
				backtothebeginning = 0;
				অনুৱর্ত;
			}
			অন্যথা
				ভঙ্গ;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
পূর্ণাঙ্ক printf(ধ্রুৱ ৱর্ণ* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ঘূৰাই 0;// incorrect return value, but who cares, anyway?
}
