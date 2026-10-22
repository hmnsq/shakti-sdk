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

#అన్తర్భావ "log.h"
#అన్తర్భావ "utils.h"
#అన్తర్భావ "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
శూన్య waitfor(గుర్తులేని పూర్ణాంకం secs)
{
	గుర్తులేని పూర్ణాంకం సమయం = 0;
	అయితే (సమయం++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
శూన్య delay(గుర్తులేని దీర్ఘ లెక్క)
{
	గుర్తులేని దీర్ఘ cntr1 = లెక్క *1000;
	గుర్తులేని దీర్ఘ tmpCntr;

	అయితే (cntr1--){
		tmpCntr = 1000;
		అయితే (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
దశాంశం pow_10(గుర్తులేని పూర్ణాంకం y)
{
	గుర్తులేని పూర్ణాంకం x=1;

	కొరకు (గుర్తులేని పూర్ణాంకం i=0; i <y; i++)
	{
		x *= 10;
	}

	తిరిగి ((దశాంశం) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
శూన్య తిరగేయి(అక్షరం *str, పూర్ణాంకం నిడివి_2)
{
	పూర్ణాంకం i = 0;
	పూర్ణాంకం j = నిడివి_2 - 1;
	అక్షరం tmp;

	అయితే (i<j)
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
పూర్ణాంకం int_గమ్యం_string(పూర్ణాంకం సంఖ్య, అక్షరం str[], గుర్తులేని పూర్ణాంకం afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	అయితే (సంఖ్య != 0)
	{
		str[i] = ((సంఖ్య%10) + '0');
		i++;
		సంఖ్య = సంఖ్య/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	అయితే (i < afterpoint)
	{
		str[i] = '0';
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	తిరగేయి(str, i);
	str[i] = '\0';

	తిరిగి i;
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
శూన్య ftoa(దశాంశం n, అక్షరం *res, గుర్తులేని పూర్ణాంకం afterpoint)
{
	పూర్ణాంకం i=0;
	అక్షరం తాత్కాలిక[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	పూర్ణాంకం ipart = (పూర్ణాంకం)n;

	// Extract floating part
	దశాంశం fpart = (దశాంశం) (n - (దశాంశం)ipart);
	పూర్ణాంకం j=0;

	ఒకవేళ(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	ఒకవేళ (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	లేకపోతే{
		ఒకవేళ (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_గమ్యం_string(ipart, తాత్కాలిక, 0);

		strcpy(res+j,తాత్కాలిక);
	}

	i = i+j;

	// check for display option after point
	ఒకవేళ (afterpoint != 0)
	{
		res[i] = '.';// add dot

		ఒకవేళ (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		లేకపోతే ఒకవేళ (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_గమ్యం_string((పూర్ణాంకం)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
శూన్య delay_loop(గుర్తులేని దీర్ఘ cntr1, గుర్తులేని దీర్ఘ cntr2)
{
	గుర్తులేని దీర్ఘ tmpCntr = cntr2;

	అయితే (cntr1--)
	{
		tmpCntr = cntr2;

		అయితే (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
గుర్తులేని దీర్ఘ read_మాట(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	తిరిగి *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
శూన్య write_మాట(uint32_t *addr, గుర్తులేని దీర్ఘ val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
