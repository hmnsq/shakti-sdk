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

#include <stdint.h>
#include <stdarg.h>
#include "utils.h"
#include "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

static anta_hstha void itoa (unsigned long long puur_naa_nka number, unsigned base)
{
	puur_naa_nka i = 0;
	unsigned puur_naa_nka intermediate = 0;
	unsigned puur_naa_nka digits[parimaa_na(number)*8];

	ၶၢဝ်း (1) {
		digits[i] = number % base;

		ပေႃး (number < base)
			bha_nga;

		number /= base;
		i++;
	}
	i++;
	ၶၢဝ်း (i-- > 0)
	{
		ပေႃး (digits[i] >= 10)
			intermediate = 'a' - 10;
		ပေႃးဢမ်ႇ
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
void _printf_(const var_na *fmt, va_list ap)
{
	pa_njikaa const var_na* p;
	const var_na* last_fmt;
	pa_njikaa puur_naa_nka ch;
	unsigned long long num;
	puur_naa_nka base, lflag, i;
	float float_num = 0;
	var_na float_arr[30] = {'\0'};
	puur_naa_nka backtothebeginning;

	for (;;) {
		for (;(ch = *(unsigned var_na *) fmt) != '%'; fmt++) {
			ပေႃး (ch == '\0')
				ပွၵ်ႈ;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		for (;;) {

			switch (ch = *(unsigned var_na *) fmt++) {

				// long flag (doubled for long long)
				pak_sa 'l':
					lflag++;
					backtothebeginning = 1;
					bha_nga;

					// character
				pak_sa 'c':
					putchar(va_arg(ap, puur_naa_nka));
					bha_nga;

					// string
				pak_sa 's':
					ပေႃး ((p = va_arg(ap, var_na *)) == NULL)
						p = "(null)";
					for (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					bha_nga;

					// (signed) decimal
				pak_sa 'd':
					base = 10;

					ပေႃး (lflag >= 2)
						num = va_arg(ap, long long);
					ပေႃးဢမ်ႇ ပေႃး (lflag ==1)
						num = va_arg(ap, long);
					ပေႃးဢမ်ႇ
						num = va_arg(ap, puur_naa_nka);

					ပေႃး ((long long) num < 0) {
						putchar('-');
						num = -(long long) num;
					}

					itoa( num, base);

					bha_nga;

				pak_sa 'f':
					float_num =  va_arg(ap, dviguu_na);

					ftoa(float_num, float_arr, 6);

					for( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						ပေႃး(i > 29) bha_nga;
					}
					bha_nga;

					// unsigned decimal
				pak_sa 'u':
					base = 10;

					ပေႃး (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					ပေႃးဢမ်ႇ ပေႃး (lflag)
						num = va_arg(ap, unsigned long);
					ပေႃးဢမ်ႇ
						num = va_arg(ap, unsigned puur_naa_nka);

					itoa( num, base);

					bha_nga;

					// (unsigned) octal
				pak_sa 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					ပေႃး (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					ပေႃးဢမ်ႇ ပေႃး (lflag)
						num = va_arg(ap, unsigned long);
					ပေႃးဢမ်ႇ
						num = va_arg(ap, unsigned puur_naa_nka);

					itoa( num, base);

					bha_nga;

				pak_sa 'x':
					base = 16;

					ပေႃး (lflag >= 2)
						num = va_arg(ap, unsigned long long);
					ပေႃးဢမ်ႇ ပေႃး (lflag)
						num = va_arg(ap, unsigned long);
					ပေႃးဢမ်ႇ
						num = va_arg(ap, unsigned puur_naa_nka);

					itoa( num, base);

					bha_nga;

					// escaped '%' character
				pak_sa '%':
					putchar(ch);
					bha_nga;

					// unrecognized escape sequence - just print it literally
				default:
					putchar('%');
					fmt = last_fmt;
					bha_nga;
			}

			ပေႃး (backtothebeginning)
			{
				backtothebeginning = 0;
				continue;
			}
			ပေႃးဢမ်ႇ
				bha_nga;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
puur_naa_nka printf(const var_na* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	ပွၵ်ႈ 0;// incorrect return value, but who cares, anyway?
}
