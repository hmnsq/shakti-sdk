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

#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "utils.h"
#અન્તર્ભાવ "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
શૂન્ય waitfor(unsigned પૂર્ણાંક secs)
{
	unsigned પૂર્ણાંક time = 0;
	જ્યારે (time++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
શૂન્ય delay(unsigned long ગણતરી)
{
	unsigned long cntr1 = ગણતરી *1000;
	unsigned long tmpCntr;

	જ્યારે (cntr1--){
		tmpCntr = 1000;
		જ્યારે (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
દશાંશ pow_10(unsigned પૂર્ણાંક y)
{
	unsigned પૂર્ણાંક x=1;

	માટે (unsigned પૂર્ણાંક i=0; i <y; i++)
	{
		x *= 10;
	}

	પાછા ((દશાંશ) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
શૂન્ય reverse(અક્ષર *str, પૂર્ણાંક length)
{
	પૂર્ણાંક i = 0;
	પૂર્ણાંક j = length - 1;
	અક્ષર tmp;

	જ્યારે (i<j)
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
પૂર્ણાંક int_to_string(પૂર્ણાંક સંખ્યા, અક્ષર str[], unsigned પૂર્ણાંક afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	જ્યારે (સંખ્યા != 0)
	{
		str[i] = ((સંખ્યા%10) + '0');
		i++;
		સંખ્યા = સંખ્યા/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	જ્યારે (i < afterpoint)
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

	પાછા i;
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
શૂન્ય ftoa(દશાંશ n, અક્ષર *res, unsigned પૂર્ણાંક afterpoint)
{
	પૂર્ણાંક i=0;
	અક્ષર temp[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	પૂર્ણાંક ipart = (પૂર્ણાંક)n;

	// Extract floating part
	દશાંશ fpart = (દશાંશ) (n - (દશાંશ)ipart);
	પૂર્ણાંક j=0;

	જો(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	જો (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	નહીંતર{
		જો (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0);

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point
	જો (afterpoint != 0)
	{
		res[i] = '.';// add dot

		જો (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		નહીંતર જો (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((પૂર્ણાંક)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
શૂન્ય delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;

	જ્યારે (cntr1--)
	{
		tmpCntr = cntr2;

		જ્યારે (tmpCntr--);
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
	પાછા *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
શૂન્ય write_word(uint32_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
