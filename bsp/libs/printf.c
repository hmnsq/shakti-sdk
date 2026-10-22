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

#ضمن <stdint.h>
#ضمن <stdarg.h>
#ضمن "utils.h"
#ضمن "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

ساكن مضمن فراغ itoa (بینښه اوږد اوږد صحيح شمېره, بینښه بنسټ)
{
	صحيح i = 0;
	بینښه صحيح intermediate = 0;
	بینښه صحيح digits[حجم(شمېره)*8];

	طالما (1) {
		digits[i] = شمېره % بنسټ;

		إذا (شمېره < بنسټ)
			اكسر;

		شمېره /= بنسټ;
		i++;
	}
	i++;
	طالما (i-- > 0)
	{
		إذا (digits[i] >= 10)
			intermediate = 'a' - 10;
		وإلا
			intermediate = '0';

		توری_چاپ_کړه(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
فراغ _printf_(ثابت حرف *fmt, va_list ap)
{
	سجل ثابت حرف* p;
	ثابت حرف* وروستی_fmt;
	سجل صحيح ch;
	بینښه اوږد اوږد عدد;
	صحيح بنسټ, lflag, i;
	عائم float_عدد = 0;
	حرف float_arr[30] = {'\0'};
	صحيح backtothebeginning;

	لكل (;;) {
		لكل (;(ch = *(بینښه حرف *) fmt) != '%'; fmt++) {
			إذا (ch == '\0')
				أرجع;
			توری_چاپ_کړه(ch);
		}
		fmt++;

		// Process a %-escape sequence
		وروستی_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		لكل (;;) {

			بدل (ch = *(بینښه حرف *) fmt++) {

				// long flag (doubled for long long)
				حالة 'l':
					lflag++;
					backtothebeginning = 1;
					اكسر;

					// character
				حالة 'c':
					توری_چاپ_کړه(va_arg(ap, صحيح));
					اكسر;

					// string
				حالة 's':
					إذا ((p = va_arg(ap, حرف *)) == عدم)
						p = "(null)";
					لكل (; (ch = *p) != '\0' ;) {
						توری_چاپ_کړه(ch);
						p++;
					}
					اكسر;

					// (signed) decimal
				حالة 'd':
					بنسټ = 10;

					إذا (lflag >= 2)
						عدد = va_arg(ap, اوږد اوږد);
					وإلا إذا (lflag ==1)
						عدد = va_arg(ap, اوږد);
					وإلا
						عدد = va_arg(ap, صحيح);

					إذا ((اوږد اوږد) عدد < 0) {
						توری_چاپ_کړه('-');
						عدد = -(اوږد اوږد) عدد;
					}

					itoa( عدد, بنسټ);

					اكسر;

				حالة 'f':
					float_عدد =  va_arg(ap, مزدوج);

					ftoa(float_عدد, float_arr, 6);

					لكل( i = 0; float_arr[i] != '\0'; i++)
					{
						توری_چاپ_کړه(float_arr[i]);
						إذا(i > 29) اكسر;
					}
					اكسر;

					// unsigned decimal
				حالة 'u':
					بنسټ = 10;

					إذا (lflag >= 2)
						عدد = va_arg(ap, بینښه اوږد اوږد);
					وإلا إذا (lflag)
						عدد = va_arg(ap, بینښه اوږد);
					وإلا
						عدد = va_arg(ap, بینښه صحيح);

					itoa( عدد, بنسټ);

					اكسر;

					// (unsigned) octal
				حالة 'o':
					// should do something with padding so it's always 3 octits
					بنسټ = 8;

					إذا (lflag >= 2)
						عدد = va_arg(ap, بینښه اوږد اوږد);
					وإلا إذا (lflag)
						عدد = va_arg(ap, بینښه اوږد);
					وإلا
						عدد = va_arg(ap, بینښه صحيح);

					itoa( عدد, بنسټ);

					اكسر;

				حالة 'x':
					بنسټ = 16;

					إذا (lflag >= 2)
						عدد = va_arg(ap, بینښه اوږد اوږد);
					وإلا إذا (lflag)
						عدد = va_arg(ap, بینښه اوږد);
					وإلا
						عدد = va_arg(ap, بینښه صحيح);

					itoa( عدد, بنسټ);

					اكسر;

					// escaped '%' character
				حالة '%':
					توری_چاپ_کړه(ch);
					اكسر;

					// unrecognized escape sequence - just print it literally
				افتراضي:
					توری_چاپ_کړه('%');
					fmt = وروستی_fmt;
					اكسر;
			}

			إذا (backtothebeginning)
			{
				backtothebeginning = 0;
				استمر;
			}
			وإلا
				اكسر;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
صحيح چاپ_کړه(ثابت حرف* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	أرجع 0;// incorrect return value, but who cares, anyway?
}
