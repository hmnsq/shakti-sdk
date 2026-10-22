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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ "utils.h"
#ଅନ୍ତର୍ଭାଵ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ itoa (unsigned long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସଂଖ୍ୟା, unsigned base)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା intermediate = 0;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା digits[ଆକାର(ସଂଖ୍ୟା)*8];

	ଯେତେବେଳେ (1) {
		digits[i] = ସଂଖ୍ୟା % base;

		ଯଦି (ସଂଖ୍ୟା < base)
			ଭାଙ୍ଗ;

		ସଂଖ୍ୟା /= base;
		i++;
	}
	i++;
	ଯେତେବେଳେ (i-- > 0)
	{
		ଯଦି (digits[i] >= 10)
			intermediate = 'a' - 10;
		ଅନ୍ୟଥା
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
ଶୂନ୍ୟ _printf_(ଅଚଳ ଅକ୍ଷର *fmt, va_list ap)
{
	ପଞ୍ଜିକରଣ ଅଚଳ ଅକ୍ଷର* p;
	ଅଚଳ ଅକ୍ଷର* last_fmt;
	ପଞ୍ଜିକରଣ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ch;
	unsigned long long ଅଙ୍କ;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା base, lflag, i;
	ଦଶମିକ float_ଅଙ୍କ = 0;
	ଅକ୍ଷର float_arr[30] = {'\0'};
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା backtothebeginning;

	ପାଇଁ (;;) {
		ପାଇଁ (;(ch = *(unsigned ଅକ୍ଷର *) fmt) != '%'; fmt++) {
			ଯଦି (ch == '\0')
				ଫେରନ୍ତୁ;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		ପାଇଁ (;;) {

			ବାଛ (ch = *(unsigned ଅକ୍ଷର *) fmt++) {

				// long flag (doubled for long long)
				ସ୍ଥିତି 'l':
					lflag++;
					backtothebeginning = 1;
					ଭାଙ୍ଗ;

					// character
				ସ୍ଥିତି 'c':
					putchar(va_arg(ap, ପୂର୍ଣ୍ଣସଂଖ୍ୟା));
					ଭାଙ୍ଗ;

					// string
				ସ୍ଥିତି 's':
					ଯଦି ((p = va_arg(ap, ଅକ୍ଷର *)) == ଖାଲି)
						p = "(null)";
					ପାଇଁ (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					ଭାଙ୍ଗ;

					// (signed) decimal
				ସ୍ଥିତି 'd':
					base = 10;

					ଯଦି (lflag >= 2)
						ଅଙ୍କ = va_arg(ap, long long);
					ଅନ୍ୟଥା ଯଦି (lflag ==1)
						ଅଙ୍କ = va_arg(ap, long);
					ଅନ୍ୟଥା
						ଅଙ୍କ = va_arg(ap, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

					ଯଦି ((long long) ଅଙ୍କ < 0) {
						putchar('-');
						ଅଙ୍କ = -(long long) ଅଙ୍କ;
					}

					itoa( ଅଙ୍କ, base);

					ଭାଙ୍ଗ;

				ସ୍ଥିତି 'f':
					float_ଅଙ୍କ =  va_arg(ap, ଦ୍ୱିଗୁଣ);

					ftoa(float_ଅଙ୍କ, float_arr, 6);

					ପାଇଁ( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						ଯଦି(i > 29) ଭାଙ୍ଗ;
					}
					ଭାଙ୍ଗ;

					// unsigned decimal
				ସ୍ଥିତି 'u':
					base = 10;

					ଯଦି (lflag >= 2)
						ଅଙ୍କ = va_arg(ap, unsigned long long);
					ଅନ୍ୟଥା ଯଦି (lflag)
						ଅଙ୍କ = va_arg(ap, unsigned long);
					ଅନ୍ୟଥା
						ଅଙ୍କ = va_arg(ap, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

					itoa( ଅଙ୍କ, base);

					ଭାଙ୍ଗ;

					// (unsigned) octal
				ସ୍ଥିତି 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					ଯଦି (lflag >= 2)
						ଅଙ୍କ = va_arg(ap, unsigned long long);
					ଅନ୍ୟଥା ଯଦି (lflag)
						ଅଙ୍କ = va_arg(ap, unsigned long);
					ଅନ୍ୟଥା
						ଅଙ୍କ = va_arg(ap, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

					itoa( ଅଙ୍କ, base);

					ଭାଙ୍ଗ;

				ସ୍ଥିତି 'x':
					base = 16;

					ଯଦି (lflag >= 2)
						ଅଙ୍କ = va_arg(ap, unsigned long long);
					ଅନ୍ୟଥା ଯଦି (lflag)
						ଅଙ୍କ = va_arg(ap, unsigned long);
					ଅନ୍ୟଥା
						ଅଙ୍କ = va_arg(ap, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

					itoa( ଅଙ୍କ, base);

					ଭାଙ୍ଗ;

					// escaped '%' character
				ସ୍ଥିତି '%':
					putchar(ch);
					ଭାଙ୍ଗ;

					// unrecognized escape sequence - just print it literally
				ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
					putchar('%');
					fmt = last_fmt;
					ଭାଙ୍ଗ;
			}

			ଯଦି (backtothebeginning)
			{
				backtothebeginning = 0;
				ଜାରି;
			}
			ଅନ୍ୟଥା
				ଭାଙ୍ଗ;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା printf(ଅଚଳ ଅକ୍ଷର* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ଫେରନ୍ତୁ 0;// incorrect return value, but who cares, anyway?
}
