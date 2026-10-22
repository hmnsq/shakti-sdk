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

#include "log.h"
#include "utils.h"
#include "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
void waitfor(unsigned 정수 secs)
{
	unsigned 정수 time = 0;
	동안 (time++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
void delay(unsigned long count)
{
	unsigned long cntr1 = count *1000;
	unsigned long tmpCntr;

	동안 (cntr1--){
		tmpCntr = 1000;
		동안 (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
float pow_10(unsigned 정수 y)
{
	unsigned 정수 x=1;

	위해 (unsigned 정수 i=0; i <y; i++)
	{
		x *= 10;
	}

	반환 ((float) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
void reverse(char *str, 정수 length)
{
	정수 i = 0;
	정수 j = length - 1;
	char tmp;

	동안 (i<j)
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
정수 int_to_string(정수 number, char str[], unsigned 정수 afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	동안 (number != 0)
	{
		str[i] = ((number%10) + '0');
		i++;
		number = number/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	동안 (i < afterpoint)
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

	반환 i;
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
void ftoa(float n, char *res, unsigned 정수 afterpoint)
{
	정수 i=0;
	char temp[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	정수 ipart = (정수)n;

	// Extract floating part
	float fpart = (float) (n - (float)ipart);
	정수 j=0;

	만약(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	만약 (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	아니면{
		만약 (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0);

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point
	만약 (afterpoint != 0)
	{
		res[i] = '.';// add dot

		만약 (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		아니면 만약 (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((정수)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
void delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;

	동안 (cntr1--)
	{
		tmpCntr = cntr2;

		동안 (tmpCntr--);
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
	반환 *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
void write_word(uint32_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
