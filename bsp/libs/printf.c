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

#समावेश <stdint.h>
#समावेश <stdarg.h>
#समावेश "utils.h"
#समावेश "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

अटल अंतरभूत व्योम itoa (अचिन्हित दीर्घ दीर्घ पूर्णांक संख्या, अचिन्हित base)
{
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक intermediate = 0;
	अचिन्हित पूर्णांक digits[माप(संख्या)*8];

	जबतक (1) {
		digits[i] = संख्या % base;

		अगर (संख्या < base)
			अवरोध;

		संख्या /= base;
		i++;
	}
	i++;
	जबतक (i-- > 0)
	{
		अगर (digits[i] >= 10)
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
व्योम _printf_(स्थिर अक्षर *fmt, बहु_सूची ap)
{
	रेजिस्टर स्थिर अक्षर* p;
	स्थिर अक्षर* last_fmt;
	रेजिस्टर पूर्णांक ch;
	अचिन्हित दीर्घ दीर्घ अंक;
	पूर्णांक base, lflag, i;
	भग्न float_अंक = 0;
	अक्षर float_arr[30] = {'\0'};
	पूर्णांक backtothebeginning;

	क्रम (;;) {
		क्रम (;(ch = *(अचिन्हित अक्षर *) fmt) != '%'; fmt++) {
			अगर (ch == '\0')
				वापस;
			अक्षर_दो(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		क्रम (;;) {

			चयन (ch = *(अचिन्हित अक्षर *) fmt++) {

				// long flag (doubled for long long)
				हाल 'l':
					lflag++;
					backtothebeginning = 1;
					अवरोध;

					// character
				हाल 'c':
					अक्षर_दो(बहु_तर्क(ap, पूर्णांक));
					अवरोध;

					// string
				हाल 's':
					अगर ((p = बहु_तर्क(ap, अक्षर *)) == शून्य)
						p = "(null)";
					क्रम (; (ch = *p) != '\0' ;) {
						अक्षर_दो(ch);
						p++;
					}
					अवरोध;

					// (signed) decimal
				हाल 'd':
					base = 10;

					अगर (lflag >= 2)
						अंक = बहु_तर्क(ap, दीर्घ दीर्घ);
					अन्यथा अगर (lflag ==1)
						अंक = बहु_तर्क(ap, दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, पूर्णांक);

					अगर ((दीर्घ दीर्घ) अंक < 0) {
						अक्षर_दो('-');
						अंक = -(दीर्घ दीर्घ) अंक;
					}

					itoa( अंक, base);

					अवरोध;

				हाल 'f':
					float_अंक =  बहु_तर्क(ap, द्विगुन);

					ftoa(float_अंक, float_arr, 6);

					क्रम( i = 0; float_arr[i] != '\0'; i++)
					{
						अक्षर_दो(float_arr[i]);
						अगर(i > 29) अवरोध;
					}
					अवरोध;

					// unsigned decimal
				हाल 'u':
					base = 10;

					अगर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा अगर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					अवरोध;

					// (unsigned) octal
				हाल 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					अगर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा अगर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					अवरोध;

				हाल 'x':
					base = 16;

					अगर (lflag >= 2)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ दीर्घ);
					अन्यथा अगर (lflag)
						अंक = बहु_तर्क(ap, अचिन्हित दीर्घ);
					अन्यथा
						अंक = बहु_तर्क(ap, अचिन्हित पूर्णांक);

					itoa( अंक, base);

					अवरोध;

					// escaped '%' character
				हाल '%':
					अक्षर_दो(ch);
					अवरोध;

					// unrecognized escape sequence - just print it literally
				शेष:
					अक्षर_दो('%');
					fmt = last_fmt;
					अवरोध;
			}

			अगर (backtothebeginning)
			{
				backtothebeginning = 0;
				जारी;
			}
			अन्यथा
				अवरोध;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
पूर्णांक म_लिखो(स्थिर अक्षर* fmt, ...)
{
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);

	_printf_(fmt, ap);

	बहु_पूर्ण(ap);
	वापस 0;// incorrect return value, but who cares, anyway?
}
