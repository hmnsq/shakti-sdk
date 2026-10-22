/*******************************************************************************
 * Project                     : shakti devt board
 * Name of the file	       : util.c
 * Brief Description of file   : src file for util
 * Name of Author    	       : Sathya Narayanan N
 * Email ID                    : sathya281@gmail.com

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
 *********************************************************************************/
/**
@file util.c
@brief source file for util
@detail Commonly used utility fuctions are implemented here. These functions are
used to achieve higher level objectives.
*/

#شامل "log.h"
#شامل "utils.h"
#شامل "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
خالی waitfor(غیرعلامتی صحیح secs)
{
	غیرعلامتی صحیح وقت = 0;
	جب (وقت++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
خالی delay(غیرعلامتی طویل گنتی)
{
	غیرعلامتی طویل cntr1 = گنتی *1000;
	غیرعلامتی طویل tmpCntr;

	جب (cntr1--){
		tmpCntr = 1000;
		جب (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
اعشاری pow_10(غیرعلامتی صحیح y)
{
	غیرعلامتی صحیح x=1;

	برائے (غیرعلامتی صحیح i=0; i <y; i++)
	{
		x *= 10;
	}

	واپس ((اعشاری) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
خالی الٹ(حرف *str, صحیح لمبائی_2)
{
	صحیح i = 0;
	صحیح j = لمبائی_2 - 1;
	حرف tmp;

	جب (i<j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;

		i++;
		j--;
	}
}

/** @fn int int_to_string(int number, char str[], int afterpoint)
 * @brief convert decimal numbers to string
 * @details Takes num as input and converts it to string.
 *	    The converted string is stored in str. The
 *          position of last character in the str is returned.
 *          This function is tailored to support ftoa.
 * @param int number
 * @param char str[]
 * @param int afterpoint
 * @return int
 */
صحیح int_مقصد_string(صحیح نمبر, حرف str[], غیرعلامتی صحیح afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	جب (نمبر != 0)
	{
		str[i] = ((نمبر%10) + '0');
		i++;
		نمبر = نمبر/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	جب (i < afterpoint)
	{
		str[i] = '0';
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	الٹ(str, i);
	str[i] = '\0';

	واپس i;
}
/** @fn void ftoa(float n, char *res, int afterpoint)
 * @brief converts float to string
 * @details Split floating number into fpart and ipart
 *          Finally merge it into one float number.
 *          Return a string, which has the float value.
 * @param float (floating point number - n)
 * @param char* (float in string - res)
 * @param int (precision - afterpoint)
 */
خالی ftoa(اعشاری n, حرف *res, غیرعلامتی صحیح afterpoint)
{
	صحیح i=0;
	حرف عارضی[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	صحیح ipart = (صحیح)n;

	// Extract floating part
	اعشاری fpart = (اعشاری) (n - (اعشاری)ipart);
	صحیح j=0;

	اگر(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	اگر (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	ورنہ{
		اگر (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_مقصد_string(ipart, عارضی, 0);

		strcpy(res+j,عارضی);
	}

	i = i+j;

	// check for display option after point
	اگر (afterpoint != 0)
	{
		res[i] = '.';// add dot

		اگر (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		ورنہ اگر (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_مقصد_string((صحیح)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
خالی delay_loop(غیرعلامتی طویل cntr1, غیرعلامتی طویل cntr2)
{
	غیرعلامتی طویل tmpCntr = cntr2;

	جب (cntr1--)
	{
		tmpCntr = cntr2;

		جب (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
غیرعلامتی طویل read_لفظ(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	واپس *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
خالی write_لفظ(uint32_t *addr, غیرعلامتی طویل val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
