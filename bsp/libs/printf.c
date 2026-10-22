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

#شامل <stdint.h>
#شامل <stdarg.h>
#شامل "utils.h"
#شامل "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ساکن اندرونی خالی itoa (غیرعلامتی طویل طویل صحیح نمبر, غیرعلامتی بنیاد)
{
	صحیح i = 0;
	غیرعلامتی صحیح intermediate = 0;
	غیرعلامتی صحیح digits[حجم(نمبر)*8];

	جب (1) {
		digits[i] = نمبر % بنیاد;

		اگر (نمبر < بنیاد)
			توڑو;

		نمبر /= بنیاد;
		i++;
	}
	i++;
	جب (i-- > 0)
	{
		اگر (digits[i] >= 10)
			intermediate = 'a' - 10;
		ورنہ
			intermediate = '0';

		حرف_لکھو(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
خالی _printf_(ثابت حرف *fmt, va_list ap)
{
	اندراج ثابت حرف* p;
	ثابت حرف* آخری_fmt;
	اندراج صحیح ch;
	غیرعلامتی طویل طویل عدد;
	صحیح بنیاد, lflag, i;
	اعشاری float_عدد = 0;
	حرف float_arr[30] = {'\0'};
	صحیح backtothebeginning;

	برائے (;;) {
		برائے (;(ch = *(غیرعلامتی حرف *) fmt) != '%'; fmt++) {
			اگر (ch == '\0')
				واپس;
			حرف_لکھو(ch);
		}
		fmt++;

		// Process a %-escape sequence
		آخری_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		برائے (;;) {

			انتخاب (ch = *(غیرعلامتی حرف *) fmt++) {

				// long flag (doubled for long long)
				حالت 'l':
					lflag++;
					backtothebeginning = 1;
					توڑو;

					// character
				حالت 'c':
					حرف_لکھو(va_arg(ap, صحیح));
					توڑو;

					// string
				حالت 's':
					اگر ((p = va_arg(ap, حرف *)) == تہی)
						p = "(null)";
					برائے (; (ch = *p) != '\0' ;) {
						حرف_لکھو(ch);
						p++;
					}
					توڑو;

					// (signed) decimal
				حالت 'd':
					بنیاد = 10;

					اگر (lflag >= 2)
						عدد = va_arg(ap, طویل طویل);
					ورنہ اگر (lflag ==1)
						عدد = va_arg(ap, طویل);
					ورنہ
						عدد = va_arg(ap, صحیح);

					اگر ((طویل طویل) عدد < 0) {
						حرف_لکھو('-');
						عدد = -(طویل طویل) عدد;
					}

					itoa( عدد, بنیاد);

					توڑو;

				حالت 'f':
					float_عدد =  va_arg(ap, دوہرا);

					ftoa(float_عدد, float_arr, 6);

					برائے( i = 0; float_arr[i] != '\0'; i++)
					{
						حرف_لکھو(float_arr[i]);
						اگر(i > 29) توڑو;
					}
					توڑو;

					// unsigned decimal
				حالت 'u':
					بنیاد = 10;

					اگر (lflag >= 2)
						عدد = va_arg(ap, غیرعلامتی طویل طویل);
					ورنہ اگر (lflag)
						عدد = va_arg(ap, غیرعلامتی طویل);
					ورنہ
						عدد = va_arg(ap, غیرعلامتی صحیح);

					itoa( عدد, بنیاد);

					توڑو;

					// (unsigned) octal
				حالت 'o':
					// should do something with padding so it's always 3 octits
					بنیاد = 8;

					اگر (lflag >= 2)
						عدد = va_arg(ap, غیرعلامتی طویل طویل);
					ورنہ اگر (lflag)
						عدد = va_arg(ap, غیرعلامتی طویل);
					ورنہ
						عدد = va_arg(ap, غیرعلامتی صحیح);

					itoa( عدد, بنیاد);

					توڑو;

				حالت 'x':
					بنیاد = 16;

					اگر (lflag >= 2)
						عدد = va_arg(ap, غیرعلامتی طویل طویل);
					ورنہ اگر (lflag)
						عدد = va_arg(ap, غیرعلامتی طویل);
					ورنہ
						عدد = va_arg(ap, غیرعلامتی صحیح);

					itoa( عدد, بنیاد);

					توڑو;

					// escaped '%' character
				حالت '%':
					حرف_لکھو(ch);
					توڑو;

					// unrecognized escape sequence - just print it literally
				طےشدہ:
					حرف_لکھو('%');
					fmt = آخری_fmt;
					توڑو;
			}

			اگر (backtothebeginning)
			{
				backtothebeginning = 0;
				جاری;
			}
			ورنہ
				توڑو;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
صحیح لکھو(ثابت حرف* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	واپس 0;// incorrect return value, but who cares, anyway?
}
