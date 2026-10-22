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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ itoa (ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ ਸੰਖਿਆ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅਧਾਰ)
{
	ਪੂਰਨ i = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ intermediate = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ digits[ਆਕਾਰ(ਸੰਖਿਆ)*8];

	ਜਦੋਂ (1) {
		digits[i] = ਸੰਖਿਆ % ਅਧਾਰ;

		ਜੇ (ਸੰਖਿਆ < ਅਧਾਰ)
			ਰੋਕੋ;

		ਸੰਖਿਆ /= ਅਧਾਰ;
		i++;
	}
	i++;
	ਜਦੋਂ (i-- > 0)
	{
		ਜੇ (digits[i] >= 10)
			intermediate = 'a' - 10;
		ਨਹੀਂਤਾਂ
			intermediate = '0';

		ਅੱਖਰ_ਲਿਖੋ(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
ਖਾਲੀ _printf_(ਅਚਲ ਅੱਖਰ *fmt, va_list ap)
{
	ਰਜਿਸਟਰ ਅਚਲ ਅੱਖਰ* p;
	ਅਚਲ ਅੱਖਰ* ਆਖਰੀ_fmt;
	ਰਜਿਸਟਰ ਪੂਰਨ ch;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ ਅੰਕ;
	ਪੂਰਨ ਅਧਾਰ, lflag, i;
	ਦਸ਼ਮਲਵ float_ਅੰਕ = 0;
	ਅੱਖਰ float_arr[30] = {'\0'};
	ਪੂਰਨ backtothebeginning;

	ਲਈ (;;) {
		ਲਈ (;(ch = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) fmt) != '%'; fmt++) {
			ਜੇ (ch == '\0')
				ਵਾਪਸ;
			ਅੱਖਰ_ਲਿਖੋ(ch);
		}
		fmt++;

		// Process a %-escape sequence
		ਆਖਰੀ_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		ਲਈ (;;) {

			ਚੋਣ (ch = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) fmt++) {

				// long flag (doubled for long long)
				ਹਾਲਤ 'l':
					lflag++;
					backtothebeginning = 1;
					ਰੋਕੋ;

					// character
				ਹਾਲਤ 'c':
					ਅੱਖਰ_ਲਿਖੋ(va_arg(ap, ਪੂਰਨ));
					ਰੋਕੋ;

					// string
				ਹਾਲਤ 's':
					ਜੇ ((p = va_arg(ap, ਅੱਖਰ *)) == ਨਿਰਾ)
						p = "(null)";
					ਲਈ (; (ch = *p) != '\0' ;) {
						ਅੱਖਰ_ਲਿਖੋ(ch);
						p++;
					}
					ਰੋਕੋ;

					// (signed) decimal
				ਹਾਲਤ 'd':
					ਅਧਾਰ = 10;

					ਜੇ (lflag >= 2)
						ਅੰਕ = va_arg(ap, ਲੰਮਾ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ ਜੇ (lflag ==1)
						ਅੰਕ = va_arg(ap, ਲੰਮਾ);
					ਨਹੀਂਤਾਂ
						ਅੰਕ = va_arg(ap, ਪੂਰਨ);

					ਜੇ ((ਲੰਮਾ ਲੰਮਾ) ਅੰਕ < 0) {
						ਅੱਖਰ_ਲਿਖੋ('-');
						ਅੰਕ = -(ਲੰਮਾ ਲੰਮਾ) ਅੰਕ;
					}

					itoa( ਅੰਕ, ਅਧਾਰ);

					ਰੋਕੋ;

				ਹਾਲਤ 'f':
					float_ਅੰਕ =  va_arg(ap, ਦੁੱਗਣਾ);

					ftoa(float_ਅੰਕ, float_arr, 6);

					ਲਈ( i = 0; float_arr[i] != '\0'; i++)
					{
						ਅੱਖਰ_ਲਿਖੋ(float_arr[i]);
						ਜੇ(i > 29) ਰੋਕੋ;
					}
					ਰੋਕੋ;

					// unsigned decimal
				ਹਾਲਤ 'u':
					ਅਧਾਰ = 10;

					ਜੇ (lflag >= 2)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ ਜੇ (lflag)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);

					itoa( ਅੰਕ, ਅਧਾਰ);

					ਰੋਕੋ;

					// (unsigned) octal
				ਹਾਲਤ 'o':
					// should do something with padding so it's always 3 octits
					ਅਧਾਰ = 8;

					ਜੇ (lflag >= 2)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ ਜੇ (lflag)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);

					itoa( ਅੰਕ, ਅਧਾਰ);

					ਰੋਕੋ;

				ਹਾਲਤ 'x':
					ਅਧਾਰ = 16;

					ਜੇ (lflag >= 2)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ ਜੇ (lflag)
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ);
					ਨਹੀਂਤਾਂ
						ਅੰਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);

					itoa( ਅੰਕ, ਅਧਾਰ);

					ਰੋਕੋ;

					// escaped '%' character
				ਹਾਲਤ '%':
					ਅੱਖਰ_ਲਿਖੋ(ch);
					ਰੋਕੋ;

					// unrecognized escape sequence - just print it literally
				ਮੂਲ:
					ਅੱਖਰ_ਲਿਖੋ('%');
					fmt = ਆਖਰੀ_fmt;
					ਰੋਕੋ;
			}

			ਜੇ (backtothebeginning)
			{
				backtothebeginning = 0;
				ਜਾਰੀ;
			}
			ਨਹੀਂਤਾਂ
				ਰੋਕੋ;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
ਪੂਰਨ ਲਿਖੋ(ਅਚਲ ਅੱਖਰ* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ਵਾਪਸ 0;// incorrect return value, but who cares, anyway?
}
