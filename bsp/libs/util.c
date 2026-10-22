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

#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
ਖਾਲੀ waitfor(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ secs)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸਮਾਂ = 0;
	ਜਦੋਂ (ਸਮਾਂ++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
ਖਾਲੀ delay(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਗਿਣਤੀ_2)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ cntr1 = ਗਿਣਤੀ_2 *1000;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ tmpCntr;

	ਜਦੋਂ (cntr1--){
		tmpCntr = 1000;
		ਜਦੋਂ (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
ਦਸ਼ਮਲਵ pow_10(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ y)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x=1;

	ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i=0; i <y; i++)
	{
		x *= 10;
	}

	ਵਾਪਸ ((ਦਸ਼ਮਲਵ) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
ਖਾਲੀ ਉਲਟ(ਅੱਖਰ *str, ਪੂਰਨ ਲੰਮਾਈ_2)
{
	ਪੂਰਨ i = 0;
	ਪੂਰਨ j = ਲੰਮਾਈ_2 - 1;
	ਅੱਖਰ tmp;

	ਜਦੋਂ (i<j)
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
ਪੂਰਨ int_ਮੰਜ਼ਿਲ_string(ਪੂਰਨ ਸੰਖਿਆ, ਅੱਖਰ str[], ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	ਜਦੋਂ (ਸੰਖਿਆ != 0)
	{
		str[i] = ((ਸੰਖਿਆ%10) + '0');
		i++;
		ਸੰਖਿਆ = ਸੰਖਿਆ/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	ਜਦੋਂ (i < afterpoint)
	{
		str[i] = '0';
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	ਉਲਟ(str, i);
	str[i] = '\0';

	ਵਾਪਸ i;
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
ਖਾਲੀ ftoa(ਦਸ਼ਮਲਵ n, ਅੱਖਰ *res, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ afterpoint)
{
	ਪੂਰਨ i=0;
	ਅੱਖਰ ਆਰਜ਼ੀ[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	ਪੂਰਨ ipart = (ਪੂਰਨ)n;

	// Extract floating part
	ਦਸ਼ਮਲਵ fpart = (ਦਸ਼ਮਲਵ) (n - (ਦਸ਼ਮਲਵ)ipart);
	ਪੂਰਨ j=0;

	ਜੇ(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	ਜੇ (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	ਨਹੀਂਤਾਂ{
		ਜੇ (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_ਮੰਜ਼ਿਲ_string(ipart, ਆਰਜ਼ੀ, 0);

		strcpy(res+j,ਆਰਜ਼ੀ);
	}

	i = i+j;

	// check for display option after point
	ਜੇ (afterpoint != 0)
	{
		res[i] = '.';// add dot

		ਜੇ (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		ਨਹੀਂਤਾਂ ਜੇ (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_ਮੰਜ਼ਿਲ_string((ਪੂਰਨ)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
ਖਾਲੀ delay_loop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ cntr1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ cntr2)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ tmpCntr = cntr2;

	ਜਦੋਂ (cntr1--)
	{
		tmpCntr = cntr2;

		ਜਦੋਂ (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਸ਼ਬਦ(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	ਵਾਪਸ *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
ਖਾਲੀ write_ਸ਼ਬਦ(uint32_t *addr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
