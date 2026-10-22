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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ "utils.h"
#અન્તર્ભાવ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

સ્થિર અંતઃરેખ શૂન્ય itoa (unsigned long long પૂર્ણાંક સંખ્યા, unsigned base)
{
	પૂર્ણાંક i = 0;
	unsigned પૂર્ણાંક intermediate = 0;
	unsigned પૂર્ણાંક digits[કદ(સંખ્યા)*8];

	જ્યારે (1) {
		digits[i] = સંખ્યા % base;

		જો (સંખ્યા < base)
			તોડો;

		સંખ્યા /= base;
		i++;
	}
	i++;
	જ્યારે (i-- > 0)
	{
		જો (digits[i] >= 10)
			intermediate = 'a' - 10;
		નહીંતર
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
શૂન્ય _printf_(અચલ અક્ષર *fmt, va_list ap)
{
	નોંધણી અચલ અક્ષર* p;
	અચલ અક્ષર* last_fmt;
	નોંધણી પૂર્ણાંક ch;
	unsigned long long અંક;
	પૂર્ણાંક base, lflag, i;
	દશાંશ float_અંક = 0;
	અક્ષર float_arr[30] = {'\0'};
	પૂર્ણાંક backtothebeginning;

	માટે (;;) {
		માટે (;(ch = *(unsigned અક્ષર *) fmt) != '%'; fmt++) {
			જો (ch == '\0')
				પાછા;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		માટે (;;) {

			પસંદગી (ch = *(unsigned અક્ષર *) fmt++) {

				// long flag (doubled for long long)
				સ્થિતિ 'l':
					lflag++;
					backtothebeginning = 1;
					તોડો;

					// character
				સ્થિતિ 'c':
					putchar(va_arg(ap, પૂર્ણાંક));
					તોડો;

					// string
				સ્થિતિ 's':
					જો ((p = va_arg(ap, અક્ષર *)) == ખાલી)
						p = "(null)";
					માટે (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					તોડો;

					// (signed) decimal
				સ્થિતિ 'd':
					base = 10;

					જો (lflag >= 2)
						અંક = va_arg(ap, long long);
					નહીંતર જો (lflag ==1)
						અંક = va_arg(ap, long);
					નહીંતર
						અંક = va_arg(ap, પૂર્ણાંક);

					જો ((long long) અંક < 0) {
						putchar('-');
						અંક = -(long long) અંક;
					}

					itoa( અંક, base);

					તોડો;

				સ્થિતિ 'f':
					float_અંક =  va_arg(ap, દ્વિગુણ);

					ftoa(float_અંક, float_arr, 6);

					માટે( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						જો(i > 29) તોડો;
					}
					તોડો;

					// unsigned decimal
				સ્થિતિ 'u':
					base = 10;

					જો (lflag >= 2)
						અંક = va_arg(ap, unsigned long long);
					નહીંતર જો (lflag)
						અંક = va_arg(ap, unsigned long);
					નહીંતર
						અંક = va_arg(ap, unsigned પૂર્ણાંક);

					itoa( અંક, base);

					તોડો;

					// (unsigned) octal
				સ્થિતિ 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					જો (lflag >= 2)
						અંક = va_arg(ap, unsigned long long);
					નહીંતર જો (lflag)
						અંક = va_arg(ap, unsigned long);
					નહીંતર
						અંક = va_arg(ap, unsigned પૂર્ણાંક);

					itoa( અંક, base);

					તોડો;

				સ્થિતિ 'x':
					base = 16;

					જો (lflag >= 2)
						અંક = va_arg(ap, unsigned long long);
					નહીંતર જો (lflag)
						અંક = va_arg(ap, unsigned long);
					નહીંતર
						અંક = va_arg(ap, unsigned પૂર્ણાંક);

					itoa( અંક, base);

					તોડો;

					// escaped '%' character
				સ્થિતિ '%':
					putchar(ch);
					તોડો;

					// unrecognized escape sequence - just print it literally
				મૂળભૂત:
					putchar('%');
					fmt = last_fmt;
					તોડો;
			}

			જો (backtothebeginning)
			{
				backtothebeginning = 0;
				ચાલુ;
			}
			નહીંતર
				તોડો;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
પૂર્ણાંક printf(અચલ અક્ષર* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	પાછા 0;// incorrect return value, but who cares, anyway?
}
