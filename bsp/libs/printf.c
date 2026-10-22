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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ "utils.h"
#അന്തര്ഭാവ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

സ്ഥിതം വരിയിൽ ശൂന്യം itoa (unsigned long long പൂർണ്ണസംഖ്യ സംഖ്യ, unsigned base)
{
	പൂർണ്ണസംഖ്യ i = 0;
	unsigned പൂർണ്ണസംഖ്യ intermediate = 0;
	unsigned പൂർണ്ണസംഖ്യ digits[വലുപ്പം(സംഖ്യ)*8];

	ആകുമ്പോൾ (1) {
		digits[i] = സംഖ്യ % base;

		എങ്കിൽ (സംഖ്യ < base)
			നിർത്തുക;

		സംഖ്യ /= base;
		i++;
	}
	i++;
	ആകുമ്പോൾ (i-- > 0)
	{
		എങ്കിൽ (digits[i] >= 10)
			intermediate = 'a' - 10;
		അല്ലെങ്കിൽ
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
ശൂന്യം _printf_(സ്ഥിരം അക്ഷരം *fmt, va_list ap)
{
	രജിസ്റ്റർ സ്ഥിരം അക്ഷരം* p;
	സ്ഥിരം അക്ഷരം* last_fmt;
	രജിസ്റ്റർ പൂർണ്ണസംഖ്യ ch;
	unsigned long long അക്കം;
	പൂർണ്ണസംഖ്യ base, lflag, i;
	ദശാംശം float_അക്കം = 0;
	അക്ഷരം float_arr[30] = {'\0'};
	പൂർണ്ണസംഖ്യ backtothebeginning;

	വേണ്ടി (;;) {
		വേണ്ടി (;(ch = *(unsigned അക്ഷരം *) fmt) != '%'; fmt++) {
			എങ്കിൽ (ch == '\0')
				തിരികെ;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		വേണ്ടി (;;) {

			തിരഞ്ഞെടുപ്പ് (ch = *(unsigned അക്ഷരം *) fmt++) {

				// long flag (doubled for long long)
				അവസ്ഥ 'l':
					lflag++;
					backtothebeginning = 1;
					നിർത്തുക;

					// character
				അവസ്ഥ 'c':
					putchar(va_arg(ap, പൂർണ്ണസംഖ്യ));
					നിർത്തുക;

					// string
				അവസ്ഥ 's':
					എങ്കിൽ ((p = va_arg(ap, അക്ഷരം *)) == ശൂന്യ)
						p = "(null)";
					വേണ്ടി (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					നിർത്തുക;

					// (signed) decimal
				അവസ്ഥ 'd':
					base = 10;

					എങ്കിൽ (lflag >= 2)
						അക്കം = va_arg(ap, long long);
					അല്ലെങ്കിൽ എങ്കിൽ (lflag ==1)
						അക്കം = va_arg(ap, long);
					അല്ലെങ്കിൽ
						അക്കം = va_arg(ap, പൂർണ്ണസംഖ്യ);

					എങ്കിൽ ((long long) അക്കം < 0) {
						putchar('-');
						അക്കം = -(long long) അക്കം;
					}

					itoa( അക്കം, base);

					നിർത്തുക;

				അവസ്ഥ 'f':
					float_അക്കം =  va_arg(ap, ഇരട്ട);

					ftoa(float_അക്കം, float_arr, 6);

					വേണ്ടി( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						എങ്കിൽ(i > 29) നിർത്തുക;
					}
					നിർത്തുക;

					// unsigned decimal
				അവസ്ഥ 'u':
					base = 10;

					എങ്കിൽ (lflag >= 2)
						അക്കം = va_arg(ap, unsigned long long);
					അല്ലെങ്കിൽ എങ്കിൽ (lflag)
						അക്കം = va_arg(ap, unsigned long);
					അല്ലെങ്കിൽ
						അക്കം = va_arg(ap, unsigned പൂർണ്ണസംഖ്യ);

					itoa( അക്കം, base);

					നിർത്തുക;

					// (unsigned) octal
				അവസ്ഥ 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					എങ്കിൽ (lflag >= 2)
						അക്കം = va_arg(ap, unsigned long long);
					അല്ലെങ്കിൽ എങ്കിൽ (lflag)
						അക്കം = va_arg(ap, unsigned long);
					അല്ലെങ്കിൽ
						അക്കം = va_arg(ap, unsigned പൂർണ്ണസംഖ്യ);

					itoa( അക്കം, base);

					നിർത്തുക;

				അവസ്ഥ 'x':
					base = 16;

					എങ്കിൽ (lflag >= 2)
						അക്കം = va_arg(ap, unsigned long long);
					അല്ലെങ്കിൽ എങ്കിൽ (lflag)
						അക്കം = va_arg(ap, unsigned long);
					അല്ലെങ്കിൽ
						അക്കം = va_arg(ap, unsigned പൂർണ്ണസംഖ്യ);

					itoa( അക്കം, base);

					നിർത്തുക;

					// escaped '%' character
				അവസ്ഥ '%':
					putchar(ch);
					നിർത്തുക;

					// unrecognized escape sequence - just print it literally
				സ്ഥിരസ്ഥിതി:
					putchar('%');
					fmt = last_fmt;
					നിർത്തുക;
			}

			എങ്കിൽ (backtothebeginning)
			{
				backtothebeginning = 0;
				തുടരുക;
			}
			അല്ലെങ്കിൽ
				നിർത്തുക;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
പൂർണ്ണസംഖ്യ printf(സ്ഥിരം അക്ഷരം* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	തിരികെ 0;// incorrect return value, but who cares, anyway?
}
