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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ "utils.h"
#அந்தர்பாவ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

நிலையான உள்வரி வெறுமை itoa (unsigned long long முழு எண், unsigned base)
{
	முழு i = 0;
	unsigned முழு intermediate = 0;
	unsigned முழு digits[அளவு(எண்)*8];

	போது (1) {
		digits[i] = எண் % base;

		எனில் (எண் < base)
			நிறுத்து;

		எண் /= base;
		i++;
	}
	i++;
	போது (i-- > 0)
	{
		எனில் (digits[i] >= 10)
			intermediate = 'a' - 10;
		இல்லையெனில்
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
வெறுமை _printf_(மாறிலி எழுத்து *fmt, va_list ap)
{
	பதிவு மாறிலி எழுத்து* p;
	மாறிலி எழுத்து* last_fmt;
	பதிவு முழு ch;
	unsigned long long இலக்கம்;
	முழு base, lflag, i;
	தசம float_இலக்கம் = 0;
	எழுத்து float_arr[30] = {'\0'};
	முழு backtothebeginning;

	க்கு (;;) {
		க்கு (;(ch = *(unsigned எழுத்து *) fmt) != '%'; fmt++) {
			எனில் (ch == '\0')
				திரும்பு;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		க்கு (;;) {

			தேர்வு (ch = *(unsigned எழுத்து *) fmt++) {

				// long flag (doubled for long long)
				நிலை 'l':
					lflag++;
					backtothebeginning = 1;
					நிறுத்து;

					// character
				நிலை 'c':
					putchar(va_arg(ap, முழு));
					நிறுத்து;

					// string
				நிலை 's':
					எனில் ((p = va_arg(ap, எழுத்து *)) == வெற்று)
						p = "(null)";
					க்கு (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					நிறுத்து;

					// (signed) decimal
				நிலை 'd':
					base = 10;

					எனில் (lflag >= 2)
						இலக்கம் = va_arg(ap, long long);
					இல்லையெனில் எனில் (lflag ==1)
						இலக்கம் = va_arg(ap, long);
					இல்லையெனில்
						இலக்கம் = va_arg(ap, முழு);

					எனில் ((long long) இலக்கம் < 0) {
						putchar('-');
						இலக்கம் = -(long long) இலக்கம்;
					}

					itoa( இலக்கம், base);

					நிறுத்து;

				நிலை 'f':
					float_இலக்கம் =  va_arg(ap, இரட்டை);

					ftoa(float_இலக்கம், float_arr, 6);

					க்கு( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						எனில்(i > 29) நிறுத்து;
					}
					நிறுத்து;

					// unsigned decimal
				நிலை 'u':
					base = 10;

					எனில் (lflag >= 2)
						இலக்கம் = va_arg(ap, unsigned long long);
					இல்லையெனில் எனில் (lflag)
						இலக்கம் = va_arg(ap, unsigned long);
					இல்லையெனில்
						இலக்கம் = va_arg(ap, unsigned முழு);

					itoa( இலக்கம், base);

					நிறுத்து;

					// (unsigned) octal
				நிலை 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					எனில் (lflag >= 2)
						இலக்கம் = va_arg(ap, unsigned long long);
					இல்லையெனில் எனில் (lflag)
						இலக்கம் = va_arg(ap, unsigned long);
					இல்லையெனில்
						இலக்கம் = va_arg(ap, unsigned முழு);

					itoa( இலக்கம், base);

					நிறுத்து;

				நிலை 'x':
					base = 16;

					எனில் (lflag >= 2)
						இலக்கம் = va_arg(ap, unsigned long long);
					இல்லையெனில் எனில் (lflag)
						இலக்கம் = va_arg(ap, unsigned long);
					இல்லையெனில்
						இலக்கம் = va_arg(ap, unsigned முழு);

					itoa( இலக்கம், base);

					நிறுத்து;

					// escaped '%' character
				நிலை '%':
					putchar(ch);
					நிறுத்து;

					// unrecognized escape sequence - just print it literally
				இயல்பு:
					putchar('%');
					fmt = last_fmt;
					நிறுத்து;
			}

			எனில் (backtothebeginning)
			{
				backtothebeginning = 0;
				தொடர்;
			}
			இல்லையெனில்
				நிறுத்து;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
முழு printf(மாறிலி எழுத்து* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	திரும்பு 0;// incorrect return value, but who cares, anyway?
}
