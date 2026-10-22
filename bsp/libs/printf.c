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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ itoa (unsigned long long ಪೂರ್ಣಾಙ್ಕ ಸಂಖ್ಯೆ, unsigned base)
{
	ಪೂರ್ಣಾಙ್ಕ i = 0;
	unsigned ಪೂರ್ಣಾಙ್ಕ intermediate = 0;
	unsigned ಪೂರ್ಣಾಙ್ಕ digits[ಪರಿಮಾಣ(ಸಂಖ್ಯೆ)*8];

	ಯಾವತ್ (1) {
		digits[i] = ಸಂಖ್ಯೆ % base;

		ಯದಿ (ಸಂಖ್ಯೆ < base)
			ಭಙ್ಗ;

		ಸಂಖ್ಯೆ /= base;
		i++;
	}
	i++;
	ಯಾವತ್ (i-- > 0)
	{
		ಯದಿ (digits[i] >= 10)
			intermediate = 'a' - 10;
		ಅನ್ಯಥಾ
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
ಶೂನ್ಯ _printf_(ಧ್ರುವ ವರ್ಣ *fmt, va_list ap)
{
	ಪಞ್ಜಿಕಾ ಧ್ರುವ ವರ್ಣ* p;
	ಧ್ರುವ ವರ್ಣ* last_fmt;
	ಪಞ್ಜಿಕಾ ಪೂರ್ಣಾಙ್ಕ ch;
	unsigned long long ಅಂಕೆ;
	ಪೂರ್ಣಾಙ್ಕ base, lflag, i;
	ಭಿನ್ನ float_ಅಂಕೆ = 0;
	ವರ್ಣ float_arr[30] = {'\0'};
	ಪೂರ್ಣಾಙ್ಕ backtothebeginning;

	ಪ್ರತಿ (;;) {
		ಪ್ರತಿ (;(ch = *(unsigned ವರ್ಣ *) fmt) != '%'; fmt++) {
			ಯದಿ (ch == '\0')
				ಪ್ರತ್ಯಾಗಮ;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		ಪ್ರತಿ (;;) {

			ವಿಕಲ್ಪ (ch = *(unsigned ವರ್ಣ *) fmt++) {

				// long flag (doubled for long long)
				ಪಕ್ಷ 'l':
					lflag++;
					backtothebeginning = 1;
					ಭಙ್ಗ;

					// character
				ಪಕ್ಷ 'c':
					putchar(va_arg(ap, ಪೂರ್ಣಾಙ್ಕ));
					ಭಙ್ಗ;

					// string
				ಪಕ್ಷ 's':
					ಯದಿ ((p = va_arg(ap, ವರ್ಣ *)) == ರಿಕ್ತ)
						p = "(null)";
					ಪ್ರತಿ (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					ಭಙ್ಗ;

					// (signed) decimal
				ಪಕ್ಷ 'd':
					base = 10;

					ಯದಿ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, long long);
					ಅನ್ಯಥಾ ಯದಿ (lflag ==1)
						ಅಂಕೆ = va_arg(ap, long);
					ಅನ್ಯಥಾ
						ಅಂಕೆ = va_arg(ap, ಪೂರ್ಣಾಙ್ಕ);

					ಯದಿ ((long long) ಅಂಕೆ < 0) {
						putchar('-');
						ಅಂಕೆ = -(long long) ಅಂಕೆ;
					}

					itoa( ಅಂಕೆ, base);

					ಭಙ್ಗ;

				ಪಕ್ಷ 'f':
					float_ಅಂಕೆ =  va_arg(ap, ದ್ವಿಗುಣ);

					ftoa(float_ಅಂಕೆ, float_arr, 6);

					ಪ್ರತಿ( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						ಯದಿ(i > 29) ಭಙ್ಗ;
					}
					ಭಙ್ಗ;

					// unsigned decimal
				ಪಕ್ಷ 'u':
					base = 10;

					ಯದಿ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, unsigned long long);
					ಅನ್ಯಥಾ ಯದಿ (lflag)
						ಅಂಕೆ = va_arg(ap, unsigned long);
					ಅನ್ಯಥಾ
						ಅಂಕೆ = va_arg(ap, unsigned ಪೂರ್ಣಾಙ್ಕ);

					itoa( ಅಂಕೆ, base);

					ಭಙ್ಗ;

					// (unsigned) octal
				ಪಕ್ಷ 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					ಯದಿ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, unsigned long long);
					ಅನ್ಯಥಾ ಯದಿ (lflag)
						ಅಂಕೆ = va_arg(ap, unsigned long);
					ಅನ್ಯಥಾ
						ಅಂಕೆ = va_arg(ap, unsigned ಪೂರ್ಣಾಙ್ಕ);

					itoa( ಅಂಕೆ, base);

					ಭಙ್ಗ;

				ಪಕ್ಷ 'x':
					base = 16;

					ಯದಿ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, unsigned long long);
					ಅನ್ಯಥಾ ಯದಿ (lflag)
						ಅಂಕೆ = va_arg(ap, unsigned long);
					ಅನ್ಯಥಾ
						ಅಂಕೆ = va_arg(ap, unsigned ಪೂರ್ಣಾಙ್ಕ);

					itoa( ಅಂಕೆ, base);

					ಭಙ್ಗ;

					// escaped '%' character
				ಪಕ್ಷ '%':
					putchar(ch);
					ಭಙ್ಗ;

					// unrecognized escape sequence - just print it literally
				ಸ್ವಭಾವ:
					putchar('%');
					fmt = last_fmt;
					ಭಙ್ಗ;
			}

			ಯದಿ (backtothebeginning)
			{
				backtothebeginning = 0;
				ಅನುವರ್ತ;
			}
			ಅನ್ಯಥಾ
				ಭಙ್ಗ;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
ಪೂರ್ಣಾಙ್ಕ printf(ಧ್ರುವ ವರ್ಣ* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ಪ್ರತ್ಯಾಗಮ 0;// incorrect return value, but who cares, anyway?
}
