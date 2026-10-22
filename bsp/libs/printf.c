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

स्थिर अन्तःस्थ शून्य itoa (अचिह्नित दीर्घ दीर्घ पूर्णाङ्क सङ्ख्या, अचिह्नित आधारः)
{
	पूर्णाङ्क i = 0;
	अचिह्नित पूर्णाङ्क intermediate = 0;
	अचिह्नित पूर्णाङ्क digits[परिमाण(सङ्ख्या)*8];

	यावत् (1) {
		digits[i] = सङ्ख्या % आधारः;

		यदि (सङ्ख्या < आधारः)
			भङ्ग;

		सङ्ख्या /= आधारः;
		i++;
	}
	i++;
	यावत् (i-- > 0)
	{
		यदि (digits[i] >= 10)
			intermediate = 'a' - 10;
		अन्यथा
			intermediate = '0';

		अक्षरं_लिख(digits[i] + intermediate);
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
	ध्रुव वर्ण* चरमः_fmt;
	पञ्जिका पूर्णाङ्क ch;
	अचिह्नित दीर्घ दीर्घ अङ्कः;
	पूर्णाङ्क आधारः, lflag, i;
	भिन्न float_अङ्कः = 0;
	वर्ण float_arr[30] = {'\0'};
	पूर्णाङ्क backtothebeginning;

	प्रति (;;) {
		प्रति (;(ch = *(अचिह्नित वर्ण *) fmt) != '%'; fmt++) {
			यदि (ch == '\0')
				प्रत्यागम;
			अक्षरं_लिख(ch);
		}
		fmt++;

		// Process a %-escape sequence
		चरमः_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		प्रति (;;) {

			विकल्प (ch = *(अचिह्नित वर्ण *) fmt++) {

				// long flag (doubled for long long)
				पक्ष 'l':
					lflag++;
					backtothebeginning = 1;
					भङ्ग;

					// character
				पक्ष 'c':
					अक्षरं_लिख(va_arg(ap, पूर्णाङ्क));
					भङ्ग;

					// string
				पक्ष 's':
					यदि ((p = va_arg(ap, वर्ण *)) == रिक्त)
						p = "(null)";
					प्रति (; (ch = *p) != '\0' ;) {
						अक्षरं_लिख(ch);
						p++;
					}
					भङ्ग;

					// (signed) decimal
				पक्ष 'd':
					आधारः = 10;

					यदि (lflag >= 2)
						अङ्कः = va_arg(ap, दीर्घ दीर्घ);
					अन्यथा यदि (lflag ==1)
						अङ्कः = va_arg(ap, दीर्घ);
					अन्यथा
						अङ्कः = va_arg(ap, पूर्णाङ्क);

					यदि ((दीर्घ दीर्घ) अङ्कः < 0) {
						अक्षरं_लिख('-');
						अङ्कः = -(दीर्घ दीर्घ) अङ्कः;
					}

					itoa( अङ्कः, आधारः);

					भङ्ग;

				पक्ष 'f':
					float_अङ्कः =  va_arg(ap, द्विगुण);

					ftoa(float_अङ्कः, float_arr, 6);

					प्रति( i = 0; float_arr[i] != '\0'; i++)
					{
						अक्षरं_लिख(float_arr[i]);
						यदि(i > 29) भङ्ग;
					}
					भङ्ग;

					// unsigned decimal
				पक्ष 'u':
					आधारः = 10;

					यदि (lflag >= 2)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ);
					अन्यथा
						अङ्कः = va_arg(ap, अचिह्नित पूर्णाङ्क);

					itoa( अङ्कः, आधारः);

					भङ्ग;

					// (unsigned) octal
				पक्ष 'o':
					// should do something with padding so it's always 3 octits
					आधारः = 8;

					यदि (lflag >= 2)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ);
					अन्यथा
						अङ्कः = va_arg(ap, अचिह्नित पूर्णाङ्क);

					itoa( अङ्कः, आधारः);

					भङ्ग;

				पक्ष 'x':
					आधारः = 16;

					यदि (lflag >= 2)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्कः = va_arg(ap, अचिह्नित दीर्घ);
					अन्यथा
						अङ्कः = va_arg(ap, अचिह्नित पूर्णाङ्क);

					itoa( अङ्कः, आधारः);

					भङ्ग;

					// escaped '%' character
				पक्ष '%':
					अक्षरं_लिख(ch);
					भङ्ग;

					// unrecognized escape sequence - just print it literally
				स्वभाव:
					अक्षरं_लिख('%');
					fmt = चरमः_fmt;
					भङ्ग;
			}

			यदि (backtothebeginning)
			{
				backtothebeginning = 0;
				अनुवर्त;
			}
			अन्यथा
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
पूर्णाङ्क प्रारूप_लिख(ध्रुव वर्ण* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	प्रत्यागम 0;// incorrect return value, but who cares, anyway?
}
