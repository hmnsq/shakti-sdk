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

स्थिर ओळीत शून्य itoa (अचिन्हित दीर्घ दीर्घ पूर्णांक संख्या, अचिन्हित base)
{
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक intermediate = 0;
	अचिन्हित पूर्णांक digits[आकार(संख्या)*8];

	पर्यंत (1) {
		digits[i] = संख्या % base;

		जर (संख्या < base)
			थांबा;

		संख्या /= base;
		i++;
	}
	i++;
	पर्यंत (i-- > 0)
	{
		जर (digits[i] >= 10)
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
शून्य _printf_(स्थिरांक अक्षर *fmt, बहु_सूची ap)
{
	नोंदणी स्थिरांक अक्षर* p;
	स्थिरांक अक्षर* last_fmt;
	नोंदणी पूर्णांक ch;
	अचिन्हित दीर्घ दीर्घ अंक;
	पूर्णांक base, lflag, i;
	दशांश float_अंक = 0;
	अक्षर float_arr[30] = {'\0'};
	पूर्णांक backtothebeginning;

	साठी (;;) {
		साठी (;(ch = *(अचिन्हित अक्षर *) fmt) != '%'; fmt++) {
			जर (ch == '\0')
				परत;
			अक्षर_दो(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		साठी (;;) {

			निवड (ch = *(अचिन्हित अक्षर *) fmt++) {

				// long flag (doubled for long long)
				स्थिती 'l':
					lflag++;
					backtothebeginning = 1;
					थांबा;

					// character
				स्थिती 'c':
					अक्षर_दो(बहु_तर्क(ap, पूर्णांक));
					थांबा;

					// string
				स्थिती 's':
					जर ((p = बहु_तर्क(ap, अक्षर *)) == रिक्त)
						p = "(null)";
					साठी (; (ch = *p) != '\0' ;) {
						अक्षर_दो(ch);
						p++;
					}
					थांबा;

					// (signed) decimal
				स्थिती 'd':
					base = 10;

					जर (lflag >= 2)
						अंक = बहु_तर्क(ap, दीर्घ दीर्घ);
					अन्यथा जर (lflag ==1)
						अंक = बहु_तर्क(ap, दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, पूर्णांक);

					जर ((दीर्घ दीर्घ) अंक < 0) {
						अक्षर_दो('-');
						अंक = -(दीर्घ दीर्घ) अंक;
					}

					itoa( अंक, base);

					थांबा;

				स्थिती 'f':
					float_अंक =  बहु_तर्क(ap, द्विगुण);

					ftoa(float_अंक, float_arr, 6);

					साठी( i = 0; float_arr[i] != '\0'; i++)
					{
						अक्षर_दो(float_arr[i]);
						जर(i > 29) थांबा;
					}
					थांबा;

					// unsigned decimal
				स्थिती 'u':
					base = 10;

					जर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा जर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					थांबा;

					// (unsigned) octal
				स्थिती 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					जर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा जर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					थांबा;

				स्थिती 'x':
					base = 16;

					जर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा जर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					थांबा;

					// escaped '%' character
				स्थिती '%':
					अक्षर_दो(ch);
					थांबा;

					// unrecognized escape sequence - just print it literally
				पूर्वनिर्धारित:
					अक्षर_दो('%');
					fmt = last_fmt;
					थांबा;
			}

			जर (backtothebeginning)
			{
				backtothebeginning = 0;
				सुरूठेवा;
			}
			अन्यथा
				थांबा;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
पूर्णांक म_लिखो(स्थिरांक अक्षर* fmt, ...)
{
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);

	_printf_(fmt, ap);

	बहु_पूर्ण(ap);
	परत 0;// incorrect return value, but who cares, anyway?
}
