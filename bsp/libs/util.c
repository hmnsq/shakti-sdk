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

#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "utils.h"
#അന്തര്ഭാവ "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
ശൂന്യം waitfor(unsigned പൂർണ്ണസംഖ്യ secs)
{
	unsigned പൂർണ്ണസംഖ്യ time = 0;
	ആകുമ്പോൾ (time++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
ശൂന്യം delay(unsigned long എണ്ണം)
{
	unsigned long cntr1 = എണ്ണം *1000;
	unsigned long tmpCntr;

	ആകുമ്പോൾ (cntr1--){
		tmpCntr = 1000;
		ആകുമ്പോൾ (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
ദശാംശം pow_10(unsigned പൂർണ്ണസംഖ്യ y)
{
	unsigned പൂർണ്ണസംഖ്യ x=1;

	വേണ്ടി (unsigned പൂർണ്ണസംഖ്യ i=0; i <y; i++)
	{
		x *= 10;
	}

	തിരികെ ((ദശാംശം) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
ശൂന്യം reverse(അക്ഷരം *str, പൂർണ്ണസംഖ്യ length)
{
	പൂർണ്ണസംഖ്യ i = 0;
	പൂർണ്ണസംഖ്യ j = length - 1;
	അക്ഷരം tmp;

	ആകുമ്പോൾ (i<j)
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
പൂർണ്ണസംഖ്യ int_to_string(പൂർണ്ണസംഖ്യ സംഖ്യ, അക്ഷരം str[], unsigned പൂർണ്ണസംഖ്യ afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	ആകുമ്പോൾ (സംഖ്യ != 0)
	{
		str[i] = ((സംഖ്യ%10) + '0');
		i++;
		സംഖ്യ = സംഖ്യ/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	ആകുമ്പോൾ (i < afterpoint)
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

	തിരികെ i;
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
ശൂന്യം ftoa(ദശാംശം n, അക്ഷരം *res, unsigned പൂർണ്ണസംഖ്യ afterpoint)
{
	പൂർണ്ണസംഖ്യ i=0;
	അക്ഷരം temp[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	പൂർണ്ണസംഖ്യ ipart = (പൂർണ്ണസംഖ്യ)n;

	// Extract floating part
	ദശാംശം fpart = (ദശാംശം) (n - (ദശാംശം)ipart);
	പൂർണ്ണസംഖ്യ j=0;

	എങ്കിൽ(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	എങ്കിൽ (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	അല്ലെങ്കിൽ{
		എങ്കിൽ (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, temp, 0);

		strcpy(res+j,temp);
	}

	i = i+j;

	// check for display option after point
	എങ്കിൽ (afterpoint != 0)
	{
		res[i] = '.';// add dot

		എങ്കിൽ (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		അല്ലെങ്കിൽ എങ്കിൽ (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((പൂർണ്ണസംഖ്യ)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
ശൂന്യം delay_loop(unsigned long cntr1, unsigned long cntr2)
{
	unsigned long tmpCntr = cntr2;

	ആകുമ്പോൾ (cntr1--)
	{
		tmpCntr = cntr2;

		ആകുമ്പോൾ (tmpCntr--);
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
	തിരികെ *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
ശൂന്യം write_word(uint32_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
