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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ "utils.h"
#అన్తర్భావ "uart.h"

/** @fn  static inline void itoa (unsigned long long int number, unsigned base)
 * @brief integer to string conversion
 * @param unsigned long long int
 * @param unsigned
 */

స్థిర అంతఃవరుస శూన్య itoa (గుర్తులేని దీర్ఘ దీర్ఘ పూర్ణాంకం సంఖ్య, గుర్తులేని పునాది)
{
	పూర్ణాంకం i = 0;
	గుర్తులేని పూర్ణాంకం intermediate = 0;
	గుర్తులేని పూర్ణాంకం digits[పరిమాణం(సంఖ్య)*8];

	అయితే (1) {
		digits[i] = సంఖ్య % పునాది;

		ఒకవేళ (సంఖ్య < పునాది)
			ఆపు;

		సంఖ్య /= పునాది;
		i++;
	}
	i++;
	అయితే (i-- > 0)
	{
		ఒకవేళ (digits[i] >= 10)
			intermediate = 'a' - 10;
		లేకపోతే
			intermediate = '0';

		అక్షరం_రాయి(digits[i] + intermediate);
	}
}

/** @fn void _printf_(const char *fmt, va_list ap)
 * @brief Handles the input stream of characters to print on screen
 * @details Identifies the type of format string, number of arguments and prints the right characer on screen
 * @param const char * fmt - formatting strings
 * @param const va_list ap - arg list
 */
శూన్య _printf_(స్థిరరాశి అక్షరం *fmt, va_list ap)
{
	నమోదు స్థిరరాశి అక్షరం* p;
	స్థిరరాశి అక్షరం* చివరి_fmt;
	నమోదు పూర్ణాంకం ch;
	గుర్తులేని దీర్ఘ దీర్ఘ అంకె;
	పూర్ణాంకం పునాది, lflag, i;
	దశాంశం float_అంకె = 0;
	అక్షరం float_arr[30] = {'\0'};
	పూర్ణాంకం backtothebeginning;

	కొరకు (;;) {
		కొరకు (;(ch = *(గుర్తులేని అక్షరం *) fmt) != '%'; fmt++) {
			ఒకవేళ (ch == '\0')
				తిరిగి;
			అక్షరం_రాయి(ch);
		}
		fmt++;

		// Process a %-escape sequence
		చివరి_fmt = fmt;
		lflag = 0;

		backtothebeginning = 0;
		కొరకు (;;) {

			ఎంపిక (ch = *(గుర్తులేని అక్షరం *) fmt++) {

				// long flag (doubled for long long)
				స్థితి 'l':
					lflag++;
					backtothebeginning = 1;
					ఆపు;

					// character
				స్థితి 'c':
					అక్షరం_రాయి(va_arg(ap, పూర్ణాంకం));
					ఆపు;

					// string
				స్థితి 's':
					ఒకవేళ ((p = va_arg(ap, అక్షరం *)) == ఖాళీ)
						p = "(null)";
					కొరకు (; (ch = *p) != '\0' ;) {
						అక్షరం_రాయి(ch);
						p++;
					}
					ఆపు;

					// (signed) decimal
				స్థితి 'd':
					పునాది = 10;

					ఒకవేళ (lflag >= 2)
						అంకె = va_arg(ap, దీర్ఘ దీర్ఘ);
					లేకపోతే ఒకవేళ (lflag ==1)
						అంకె = va_arg(ap, దీర్ఘ);
					లేకపోతే
						అంకె = va_arg(ap, పూర్ణాంకం);

					ఒకవేళ ((దీర్ఘ దీర్ఘ) అంకె < 0) {
						అక్షరం_రాయి('-');
						అంకె = -(దీర్ఘ దీర్ఘ) అంకె;
					}

					itoa( అంకె, పునాది);

					ఆపు;

				స్థితి 'f':
					float_అంకె =  va_arg(ap, ద్విగుణ);

					ftoa(float_అంకె, float_arr, 6);

					కొరకు( i = 0; float_arr[i] != '\0'; i++)
					{
						అక్షరం_రాయి(float_arr[i]);
						ఒకవేళ(i > 29) ఆపు;
					}
					ఆపు;

					// unsigned decimal
				స్థితి 'u':
					పునాది = 10;

					ఒకవేళ (lflag >= 2)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ దీర్ఘ);
					లేకపోతే ఒకవేళ (lflag)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ);
					లేకపోతే
						అంకె = va_arg(ap, గుర్తులేని పూర్ణాంకం);

					itoa( అంకె, పునాది);

					ఆపు;

					// (unsigned) octal
				స్థితి 'o':
					// should do something with padding so it's always 3 octits
					పునాది = 8;

					ఒకవేళ (lflag >= 2)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ దీర్ఘ);
					లేకపోతే ఒకవేళ (lflag)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ);
					లేకపోతే
						అంకె = va_arg(ap, గుర్తులేని పూర్ణాంకం);

					itoa( అంకె, పునాది);

					ఆపు;

				స్థితి 'x':
					పునాది = 16;

					ఒకవేళ (lflag >= 2)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ దీర్ఘ);
					లేకపోతే ఒకవేళ (lflag)
						అంకె = va_arg(ap, గుర్తులేని దీర్ఘ);
					లేకపోతే
						అంకె = va_arg(ap, గుర్తులేని పూర్ణాంకం);

					itoa( అంకె, పునాది);

					ఆపు;

					// escaped '%' character
				స్థితి '%':
					అక్షరం_రాయి(ch);
					ఆపు;

					// unrecognized escape sequence - just print it literally
				అప్రమేయ:
					అక్షరం_రాయి('%');
					fmt = చివరి_fmt;
					ఆపు;
			}

			ఒకవేళ (backtothebeginning)
			{
				backtothebeginning = 0;
				కొనసాగు;
			}
			లేకపోతే
				ఆపు;
		}
	}
}

/** @fn int printf(const char* fmt, ...)
 * @brief function to print characters on file
 * @details prints the characters on terminal
 * @param const char*
 * @return int
 */
పూర్ణాంకం రాయి(స్థిరరాశి అక్షరం* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	_printf_(fmt, ap);

	va_end(ap);
	తిరిగి 0;// incorrect return value, but who cares, anyway?
}
