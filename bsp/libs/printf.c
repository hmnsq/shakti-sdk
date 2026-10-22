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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव "utils.h"
#अन्तर्भाव "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

स्थिर अन्तःस्थ शून्य itoa (unsigned long long पूर्णाङ्क सङ्ख्या, unsigned base)
{
	पूर्णाङ्क i = 0;
	unsigned पूर्णाङ्क intermediate = 0;
	unsigned पूर्णाङ्क digits[परिमाण(सङ्ख्या)*8];

	याव (1) {
		digits[i] = सङ्ख्या % base;

		सचे (सङ्ख्या < base)
			भङ्ग;

		सङ्ख्या /= base;
		i++;
	}
	i++;
	याव (i-- > 0)
	{
		सचे (digits[i] >= 10)
			intermediate = 'a' - 10;
		अञ्ञथा
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
शून्य _printf_(ध्रुव वर्ण *fmt, va_list ap)
{
	पञ्जिका ध्रुव वर्ण* p;
	ध्रुव वर्ण* last_fmt;
	पञ्जिका पूर्णाङ्क ch;
	unsigned long long अङ्कः;
	पूर्णाङ्क base, lflag, i;
	भिन्न float_अङ्कः = 0;
	वर्ण float_arr[30] = {'\0'};
	पूर्णाङ्क backtothebeginning;

	अत्थाय (;;) {
		अत्थाय (;(ch = *(unsigned वर्ण *) fmt) != '%'; fmt++) {
			सचे (ch == '\0')
				पटिनिवत्त;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		अत्थाय (;;) {

			विकल्प (ch = *(unsigned वर्ण *) fmt++) {

				// long flag (doubled for long long)
				पक्ष 'l':
					lflag++;
					backtothebeginning = 1;
					भङ्ग;

					// character
				पक्ष 'c':
					putchar(va_arg(ap, पूर्णाङ्क));
					भङ्ग;

					// string
				पक्ष 's':
					सचे ((p = va_arg(ap, वर्ण *)) == रिक्त)
						p = "(null)";
					अत्थाय (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					भङ्ग;

					// (signed) decimal
				पक्ष 'd':
					base = 10;

					सचे (lflag >= 2)
						अङ्कः = va_arg(ap, long long);
					अञ्ञथा सचे (lflag ==1)
						अङ्कः = va_arg(ap, long);
					अञ्ञथा
						अङ्कः = va_arg(ap, पूर्णाङ्क);

					सचे ((long long) अङ्कः < 0) {
						putchar('-');
						अङ्कः = -(long long) अङ्कः;
					}

					itoa( अङ्कः, base);

					भङ्ग;

				पक्ष 'f':
					float_अङ्कः =  va_arg(ap, द्विगुण);

					ftoa(float_अङ्कः, float_arr, 6);

					अत्थाय( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						सचे(i > 29) भङ्ग;
					}
					भङ्ग;

					// unsigned decimal
				पक्ष 'u':
					base = 10;

					सचे (lflag >= 2)
						अङ्कः = va_arg(ap, unsigned long long);
					अञ्ञथा सचे (lflag)
						अङ्कः = va_arg(ap, unsigned long);
					अञ्ञथा
						अङ्कः = va_arg(ap, unsigned पूर्णाङ्क);

					itoa( अङ्कः, base);

					भङ्ग;

					// (unsigned) octal
				पक्ष 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					सचे (lflag >= 2)
						अङ्कः = va_arg(ap, unsigned long long);
					अञ्ञथा सचे (lflag)
						अङ्कः = va_arg(ap, unsigned long);
					अञ्ञथा
						अङ्कः = va_arg(ap, unsigned पूर्णाङ्क);

					itoa( अङ्कः, base);

					भङ्ग;

				पक्ष 'x':
					base = 16;

					सचे (lflag >= 2)
						अङ्कः = va_arg(ap, unsigned long long);
					अञ्ञथा सचे (lflag)
						अङ्कः = va_arg(ap, unsigned long);
					अञ्ञथा
						अङ्कः = va_arg(ap, unsigned पूर्णाङ्क);

					itoa( अङ्कः, base);

					भङ्ग;

					// escaped '%' character
				पक्ष '%':
					putchar(ch);
					भङ्ग;

					// unrecognized escape sequence - just print it literally
				स्वभाव:
					putchar('%');
					fmt = last_fmt;
					भङ्ग;
			}

			सचे (backtothebeginning)
			{
				backtothebeginning = 0;
				अनुवर्त;
			}
			अञ्ञथा
				भङ्ग;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
पूर्णाङ्क printf(ध्रुव वर्ण* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	पटिनिवत्त 0;// incorrect return value, but who cares, anyway?
}
