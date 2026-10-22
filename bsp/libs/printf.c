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

ایستا درونخطی تهی itoa (unsigned long long صحیح عدد, unsigned base)
{
	صحیح i = 0;
	unsigned صحیح intermediate = 0;
	unsigned صحیح digits[اندازه(عدد)*8];

	وقتی (1) {
		digits[i] = عدد % base;

		اگر (عدد < base)
			بشکن;

		عدد /= base;
		i++;
	}
	i++;
	وقتی (i-- > 0)
	{
		اگر (digits[i] >= 10)
			intermediate = 'a' - 10;
		وگرنه
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
تهی _printf_(ثابت نویسه *fmt, va_list ap)
{
	ثبات ثابت نویسه* p;
	ثابت نویسه* last_fmt;
	ثبات صحیح ch;
	unsigned long long رقم;
	صحیح base, lflag, i;
	اعشاری float_رقم = 0;
	نویسه float_arr[30] = {'\0'};
	صحیح backtothebeginning;

	برای (;;) {
		برای (;(ch = *(unsigned نویسه *) fmt) != '%'; fmt++) {
			اگر (ch == '\0')
				بازگشت;
			putchar(ch);
		}
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		برای (;;) {

			انتخاب (ch = *(unsigned نویسه *) fmt++) {

				// long flag (doubled for long long)
				حالت 'l':
					lflag++;
					backtothebeginning = 1;
					بشکن;

					// character
				حالت 'c':
					putchar(va_arg(ap, صحیح));
					بشکن;

					// string
				حالت 's':
					اگر ((p = va_arg(ap, نویسه *)) == پوچ)
						p = "(null)";
					برای (; (ch = *p) != '\0' ;) {
						putchar(ch);
						p++;
					}
					بشکن;

					// (signed) decimal
				حالت 'd':
					base = 10;

					اگر (lflag >= 2)
						رقم = va_arg(ap, long long);
					وگرنه اگر (lflag ==1)
						رقم = va_arg(ap, long);
					وگرنه
						رقم = va_arg(ap, صحیح);

					اگر ((long long) رقم < 0) {
						putchar('-');
						رقم = -(long long) رقم;
					}

					itoa( رقم, base);

					بشکن;

				حالت 'f':
					float_رقم =  va_arg(ap, دوگانه);

					ftoa(float_رقم, float_arr, 6);

					برای( i = 0; float_arr[i] != '\0'; i++)
					{
						putchar(float_arr[i]);
						اگر(i > 29) بشکن;
					}
					بشکن;

					// unsigned decimal
				حالت 'u':
					base = 10;

					اگر (lflag >= 2)
						رقم = va_arg(ap, unsigned long long);
					وگرنه اگر (lflag)
						رقم = va_arg(ap, unsigned long);
					وگرنه
						رقم = va_arg(ap, unsigned صحیح);

					itoa( رقم, base);

					بشکن;

					// (unsigned) octal
				حالت 'o':
					// should do something with padding so it's always 3 octits
					base = 8;

					اگر (lflag >= 2)
						رقم = va_arg(ap, unsigned long long);
					وگرنه اگر (lflag)
						رقم = va_arg(ap, unsigned long);
					وگرنه
						رقم = va_arg(ap, unsigned صحیح);

					itoa( رقم, base);

					بشکن;

				حالت 'x':
					base = 16;

					اگر (lflag >= 2)
						رقم = va_arg(ap, unsigned long long);
					وگرنه اگر (lflag)
						رقم = va_arg(ap, unsigned long);
					وگرنه
						رقم = va_arg(ap, unsigned صحیح);

					itoa( رقم, base);

					بشکن;

					// escaped '%' character
				حالت '%':
					putchar(ch);
					بشکن;

					// unrecognized escape sequence - just print it literally
				پیشفرض:
					putchar('%');
					fmt = last_fmt;
					بشکن;
			}

			اگر (backtothebeginning)
			{
				backtothebeginning = 0;
				ادامه;
			}
			وگرنه
				بشکن;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
صحیح printf(ثابت نویسه* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	بازگشت 0;// incorrect return value, but who cares, anyway?
}
