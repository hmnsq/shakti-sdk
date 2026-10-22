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

#অন্তর্ভাব "log.h"
#অন্তর্ভাব "utils.h"
#অন্তর্ভাব "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
শূন্য waitfor(unsigned পূর্ণাঙ্ক secs)
{
	unsigned পূর্ণাঙ্ক time = 0;
	যাবত্ (time++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
শূন্য delay(unsigned long গুনতি)
{
	unsigned long cntr1 = গুনতি *1000;
	unsigned long tmpCntr;

	যাবত্ (cntr1--){
		tmpCntr = 1000;
		যাবত্ (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
ভিন্ন pow_10(unsigned পূর্ণাঙ্ক y)
{
	unsigned পূর্ণাঙ্ক x=1;

	প্রতি (unsigned পূর্ণাঙ্ক i=0; i <y; i++)
	{
		x *= 10;
	}

	প্রত্যাগম ((ভিন্ন) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
শূন্য reverse(বর্ণ *str, পূর্ণাঙ্ক length)
{
	পূর্ণাঙ্ক i = 0;
	পূর্ণাঙ্ক j = length - 1;
	বর্ণ tmp;

	যাবত্ (i<j)
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
পূর্ণাঙ্ক int_to_string(পূর্ণাঙ্ক সংখ্যা, বর্ণ str[], unsigned পূর্ণাঙ্ক afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	যাবত্ (সংখ্যা != 0)
	{
		str[i] = ((সংখ্যা%10) + '0');
		i++;
		সংখ্যা = সংখ্যা/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	যাবত্ (i < afterpoint)
	{
		str[i] = '0';
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	reverse(str, i);
	str[i] = '\0';

	প্রত্যাগম i;
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
শূন্য ftoa(ভিন্ন n, বর্ণ *res, unsigned পূর্ণাঙ্ক afterpoint)
{
	পূর্ণাঙ্ক i=0;
	বর্ণ temp[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	পূর্ণাঙ্ক ipart = (পূর্ণাঙ্ক)n;

	// Extract floating part
	ভিন্ন fpart = (ভিন্ন) (n - (ভিন্ন)ipart);
	পূর্ণাঙ্ক j=0;

	যদি(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	যদি (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	অন্যথা{
		যদি (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0);

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point
	যদি (afterpoint != 0)
	{
		res[i] = '.';// add dot

		যদি (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		অন্যথা যদি (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((পূর্ণাঙ্ক)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
শূন্য delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;

	যাবত্ (cntr1--)
	{
		tmpCntr = cntr2;

		যাবত্ (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
unsigned long read_word(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	প্রত্যাগম *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
শূন্য write_word(uint32_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
