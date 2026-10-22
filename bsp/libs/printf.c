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

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ itoa (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ, ಚಿಹ್ನೆರಹಿತ ತಳ)
{
	ಪೂರ್ಣಾಂಕ i = 0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ intermediate = 0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ digits[ಗಾತ್ರ(ಸಂಖ್ಯೆ)*8];

	ಆಗ (1) {
		digits[i] = ಸಂಖ್ಯೆ % ತಳ;

		ಆದರೆ (ಸಂಖ್ಯೆ < ತಳ)
			ನಿಲ್ಲಿಸು;

		ಸಂಖ್ಯೆ /= ತಳ;
		i++;
	}
	i++;
	ಆಗ (i-- > 0)
	{
		ಆದರೆ (digits[i] >= 10)
			intermediate = 'a' - 10;
		ಇಲ್ಲದಿದ್ದರೆ
			intermediate = '0';

		ಅಕ್ಷರ_ಬರೆ(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
ಶೂನ್ಯ _printf_(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ap)
{
	ನೋಂದಣಿ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* p;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* ಕೊನೆಯ_fmt;
	ನೋಂದಣಿ ಪೂರ್ಣಾಂಕ ch;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಅಂಕೆ;
	ಪೂರ್ಣಾಂಕ ತಳ, lflag, i;
	ದಶಮಾಂಶ float_ಅಂಕೆ = 0;
	ಅಕ್ಷರ float_arr[30] = {'\0'};
	ಪೂರ್ಣಾಂಕ backtothebeginning;

	ಗಾಗಿ (;;) {
		ಗಾಗಿ (;(ch = *(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) fmt) != '%'; fmt++) {
			ಆದರೆ (ch == '\0')
				ಹಿಂತಿರುಗಿ;
			ಅಕ್ಷರ_ಬರೆ(ch);
		}
		fmt++;

		// Process a %-escape sequence
		ಕೊನೆಯ_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		ಗಾಗಿ (;;) {

			ಆಯ್ಕೆ (ch = *(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) fmt++) {

				// long flag (doubled for long long)
				ಸ್ಥಿತಿ 'l':
					lflag++;
					backtothebeginning = 1;
					ನಿಲ್ಲಿಸು;

					// character
				ಸ್ಥಿತಿ 'c':
					ಅಕ್ಷರ_ಬರೆ(va_arg(ap, ಪೂರ್ಣಾಂಕ));
					ನಿಲ್ಲಿಸು;

					// string
				ಸ್ಥಿತಿ 's':
					ಆದರೆ ((p = va_arg(ap, ಅಕ್ಷರ *)) == ಖಾಲಿ)
						p = "(null)";
					ಗಾಗಿ (; (ch = *p) != '\0' ;) {
						ಅಕ್ಷರ_ಬರೆ(ch);
						p++;
					}
					ನಿಲ್ಲಿಸು;

					// (signed) decimal
				ಸ್ಥಿತಿ 'd':
					ತಳ = 10;

					ಆದರೆ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, ದೀರ್ಘ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (lflag ==1)
						ಅಂಕೆ = va_arg(ap, ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ
						ಅಂಕೆ = va_arg(ap, ಪೂರ್ಣಾಂಕ);

					ಆದರೆ ((ದೀರ್ಘ ದೀರ್ಘ) ಅಂಕೆ < 0) {
						ಅಕ್ಷರ_ಬರೆ('-');
						ಅಂಕೆ = -(ದೀರ್ಘ ದೀರ್ಘ) ಅಂಕೆ;
					}

					itoa( ಅಂಕೆ, ತಳ);

					ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 'f':
					float_ಅಂಕೆ =  va_arg(ap, ದ್ವಿಗುಣ);

					ftoa(float_ಅಂಕೆ, float_arr, 6);

					ಗಾಗಿ( i = 0; float_arr[i] != '\0'; i++)
					{
						ಅಕ್ಷರ_ಬರೆ(float_arr[i]);
						ಆದರೆ(i > 29) ನಿಲ್ಲಿಸು;
					}
					ನಿಲ್ಲಿಸು;

					// unsigned decimal
				ಸ್ಥಿತಿ 'u':
					ತಳ = 10;

					ಆದರೆ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (lflag)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);

					itoa( ಅಂಕೆ, ತಳ);

					ನಿಲ್ಲಿಸು;

					// (unsigned) octal
				ಸ್ಥಿತಿ 'o':
					// should do something with padding so it's always 3 octits
					ತಳ = 8;

					ಆದರೆ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (lflag)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);

					itoa( ಅಂಕೆ, ತಳ);

					ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 'x':
					ತಳ = 16;

					ಆದರೆ (lflag >= 2)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (lflag)
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ);
					ಇಲ್ಲದಿದ್ದರೆ
						ಅಂಕೆ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);

					itoa( ಅಂಕೆ, ತಳ);

					ನಿಲ್ಲಿಸು;

					// escaped '%' character
				ಸ್ಥಿತಿ '%':
					ಅಕ್ಷರ_ಬರೆ(ch);
					ನಿಲ್ಲಿಸು;

					// unrecognized escape sequence - just print it literally
				ಪೂರ್ವನಿಯೋಜಿತ:
					ಅಕ್ಷರ_ಬರೆ('%');
					fmt = ಕೊನೆಯ_fmt;
					ನಿಲ್ಲಿಸು;
			}

			ಆದರೆ (backtothebeginning)
			{
				backtothebeginning = 0;
				ಮುಂದುವರಿ;
			}
			ಇಲ್ಲದಿದ್ದರೆ
				ನಿಲ್ಲಿಸು;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
ಪೂರ್ಣಾಂಕ ಬರೆ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ಹಿಂತಿರುಗಿ 0;// incorrect return value, but who cares, anyway?
}
