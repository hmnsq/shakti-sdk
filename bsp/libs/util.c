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

#समावेश "log.h"
#समावेश "utils.h"
#समावेश "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
व्योम waitfor(अचिन्हित पूर्णांक secs)
{
	अचिन्हित पूर्णांक समय = 0;
	जबतक (समय++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
व्योम delay(अचिन्हित दीर्घ गिनती)
{
	अचिन्हित दीर्घ cntr1 = गिनती *1000;
	अचिन्हित दीर्घ tmpCntr;

	जबतक (cntr1--){
		tmpCntr = 1000;
		जबतक (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
भग्न pow_10(अचिन्हित पूर्णांक y)
{
	अचिन्हित पूर्णांक x=1;

	क्रम (अचिन्हित पूर्णांक i=0; i <y; i++)
	{
		x *= 10;
	}

	वापस ((भग्न) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
व्योम reverse(अक्षर *str, पूर्णांक लंबाई_2)
{
	पूर्णांक i = 0;
	पूर्णांक j = लंबाई_2 - 1;
	अक्षर tmp;

	जबतक (i<j)
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
पूर्णांक int_to_string(पूर्णांक संख्या, अक्षर str[], अचिन्हित पूर्णांक afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	जबतक (संख्या != 0)
	{
		str[i] = ((संख्या%10) + '0');
		i++;
		संख्या = संख्या/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	जबतक (i < afterpoint)
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

	वापस i;
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
व्योम ftoa(भग्न n, अक्षर *res, अचिन्हित पूर्णांक afterpoint)
{
	पूर्णांक i=0;
	अक्षर अस्थायी[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	पूर्णांक ipart = (पूर्णांक)n;

	// Extract floating part
	भग्न fpart = (भग्न) (n - (भग्न)ipart);
	पूर्णांक j=0;

	अगर(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	अगर (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	अन्यथा{
		अगर (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_to_string(ipart, अस्थायी, 0);

		म_नकल(res+j,अस्थायी);
	}

	i = i+j;

	// check for display option after point
	अगर (afterpoint != 0)
	{
		res[i] = '.';// add dot

		अगर (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		अन्यथा अगर (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_to_string((पूर्णांक)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
व्योम delay_loop(अचिन्हित दीर्घ cntr1, अचिन्हित दीर्घ cntr2)
{
	अचिन्हित दीर्घ tmpCntr = cntr2;

	जबतक (cntr1--)
	{
		tmpCntr = cntr2;

		जबतक (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
अचिन्हित दीर्घ read_word(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	वापस *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
व्योम write_word(uint32_t *addr, अचिन्हित दीर्घ val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
