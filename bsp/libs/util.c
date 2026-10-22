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

#अन्तर्भाव "log.h"
#अन्तर्भाव "utils.h"
#अन्तर्भाव "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
शून्य waitfor(unsigned पूर्णाङ्क secs)
{
	unsigned पूर्णाङ्क time = 0;
	जाव (time++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
शून्य delay(unsigned long गणनम्)
{
	unsigned long cntr1 = गणनम् *1000;
	unsigned long tmpCntr;

	जाव (cntr1--){
		tmpCntr = 1000;
		जाव (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
भिन्न pow_10(unsigned पूर्णाङ्क y)
{
	unsigned पूर्णाङ्क x=1;

	प्रति (unsigned पूर्णाङ्क i=0; i <y; i++)
	{
		x *= 10;
	}

	प्रत्यागम ((भिन्न) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
शून्य reverse(वर्ण *str, पूर्णाङ्क length)
{
	पूर्णाङ्क i = 0;
	पूर्णाङ्क j = length - 1;
	वर्ण tmp;

	जाव (i<j)
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
पूर्णाङ्क int_to_string(पूर्णाङ्क सङ्ख्या, वर्ण str[], unsigned पूर्णाङ्क afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	जाव (सङ्ख्या != 0)
	{
		str[i] = ((सङ्ख्या%10) + '0');
		i++;
		सङ्ख्या = सङ्ख्या/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	जाव (i < afterpoint)
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

	प्रत्यागम i;
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
शून्य ftoa(भिन्न n, वर्ण *res, unsigned पूर्णाङ्क afterpoint)
{
	पूर्णाङ्क i=0;
	वर्ण temp[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	पूर्णाङ्क ipart = (पूर्णाङ्क)n;

	// Extract floating part
	भिन्न fpart = (भिन्न) (n - (भिन्न)ipart);
	पूर्णाङ्क j=0;

	जइ(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	जइ (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	अण्णहा{
		जइ (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0);

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point
	जइ (afterpoint != 0)
	{
		res[i] = '.';// add dot

		जइ (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		अण्णहा जइ (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((पूर्णाङ्क)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
शून्य delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;

	जाव (cntr1--)
	{
		tmpCntr = cntr2;

		जाव (tmpCntr--);
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
	प्रत्यागम *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
शून्य write_word(uint32_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
