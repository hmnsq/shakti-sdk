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

स्थिर अन्तःस्थ शून्य itoa (अचिन्हित दीर्घ दीर्घ पूर्णाङ्क सङ्ख्या, अचिन्हित base)
{
	पूर्णाङ्क i = 0;
	अचिन्हित पूर्णाङ्क intermediate = 0;
	अचिन्हित पूर्णाङ्क digits[परिमाण(सङ्ख्या)*8];

	जबसम्म (1) {
		digits[i] = सङ्ख्या % base;

		यदि (सङ्ख्या < base)
			रोक;

		सङ्ख्या /= base;
		i++;
	}
	i++;
	जबसम्म (i-- > 0)
	{
		यदि (digits[i] >= 10)
			intermediate = 'a' - 10;
		अन्यथा
			intermediate = '0';

		अक्षर_दो(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
शून्य _printf_(अचर वर्ण *fmt, बहु_सूची ap)
{
	पञ्जिका अचर वर्ण* p;
	अचर वर्ण* last_fmt;
	पञ्जिका पूर्णाङ्क ch;
	अचिन्हित दीर्घ दीर्घ अङ्क;
	पूर्णाङ्क base, lflag, i;
	भिन्न float_अङ्क = 0;
	वर्ण float_arr[30] = {'\0'};
	पूर्णाङ्क backtothebeginning;

	लागि (;;) {
		लागि (;(ch = *(अचिन्हित वर्ण *) fmt) != '%'; fmt++) {
			यदि (ch == '\0')
				फर्काऊ;
			अक्षर_दो(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		लागि (;;) {

			विकल्प (ch = *(अचिन्हित वर्ण *) fmt++) {

				// long flag (doubled for long long)
				पक्ष 'l':
					lflag++;
					backtothebeginning = 1;
					रोक;

					// character
				पक्ष 'c':
					अक्षर_दो(बहु_तर्क(ap, पूर्णाङ्क));
					रोक;

					// string
				पक्ष 's':
					यदि ((p = बहु_तर्क(ap, वर्ण *)) == रिक्त)
						p = "(null)";
					लागि (; (ch = *p) != '\0' ;) {
						अक्षर_दो(ch);
						p++;
					}
					रोक;

					// (signed) decimal
				पक्ष 'd':
					base = 10;

					यदि (lflag >= 2)
						अङ्क = बहु_तर्क(ap, दीर्घ दीर्घ);
					अन्यथा यदि (lflag ==1)
						अङ्क = बहु_तर्क(ap, दीर्घ);
					अन्यथा
						अङ्क = बहु_तर्क(ap, पूर्णाङ्क);

					यदि ((दीर्घ दीर्घ) अङ्क < 0) {
						अक्षर_दो('-');
						अङ्क = -(दीर्घ दीर्घ) अङ्क;
					}

					itoa( अङ्क, base);

					रोक;

				पक्ष 'f':
					float_अङ्क =  बहु_तर्क(ap, द्विगुण);

					ftoa(float_अङ्क, float_arr, 6);

					लागि( i = 0; float_arr[i] != '\0'; i++)
					{
						अक्षर_दो(float_arr[i]);
						यदि(i > 29) रोक;
					}
					रोक;

					// unsigned decimal
				पक्ष 'u':
					base = 10;

					यदि (lflag >= 2)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अङ्क = बहु_तर्क(ap, अचिन्हित पूर्णाङ्क);

					itoa( अङ्क, base);

					रोक;

					// (unsigned) octal
				पक्ष 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					यदि (lflag >= 2)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अङ्क = बहु_तर्क(ap, अचिन्हित पूर्णाङ्क);

					itoa( अङ्क, base);

					रोक;

				पक्ष 'x':
					base = 16;

					यदि (lflag >= 2)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा यदि (lflag)
						अङ्क = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अङ्क = बहु_तर्क(ap, अचिन्हित पूर्णाङ्क);

					itoa( अङ्क, base);

					रोक;

					// escaped '%' character
				पक्ष '%':
					अक्षर_दो(ch);
					रोक;

					// unrecognized escape sequence - just print it literally
				स्वभाव:
					अक्षर_दो('%');
					fmt = last_fmt;
					रोक;
			}

			यदि (backtothebeginning)
			{
				backtothebeginning = 0;
				जारी;
			}
			अन्यथा
				रोक;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
पूर्णाङ्क म_लिखो(अचर वर्ण* fmt, ...)
{
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);

	_printf_(fmt, ap);

	बहु_पूर्ण(ap);
	फर्काऊ 0;// incorrect return value, but who cares, anyway?
}
