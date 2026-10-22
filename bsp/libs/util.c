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

#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "string.h"

/** @fn  void waitfor(unsigned int secs)
 * @brief stall the process for given time
 * @param unsigned int secs
 */
ಶೂನ್ಯ waitfor(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ secs)
{
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಸಮಯ = 0;
	ಆಗ (ಸಮಯ++ < secs);
}

/** @fn void delay(unsigned long count)
 * @brief  sleeps for number of "count"
 * @param unsigned long (number of count)
 */
ಶೂನ್ಯ delay(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಎಣಿಕೆ_2)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ cntr1 = ಎಣಿಕೆ_2 *1000;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ tmpCntr;

	ಆಗ (cntr1--){
		tmpCntr = 1000;
		ಆಗ (tmpCntr--);
	}
}

/** @fn float pow_10(unsigned int y)
 * @brief generate different powers of 10
 * @param unsigned int y
 * @return return result in float 
 */
ದಶಮಾಂಶ pow_10(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ y)
{
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x=1;

	ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i=0; i <y; i++)
	{
		x *= 10;
	}

	ಹಿಂತಿರುಗಿ ((ದಶಮಾಂಶ) x);
}
/** @fn void reverse(char *str, int length)
 * @brief reverse a string and store in the same string
 * @param char *str
 * @param int length
 */
ಶೂನ್ಯ ಹಿಮ್ಮುಖ(ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ_2)
{
	ಪೂರ್ಣಾಂಕ i = 0;
	ಪೂರ್ಣಾಂಕ j = ಉದ್ದಳತೆ_2 - 1;
	ಅಕ್ಷರ tmp;

	ಆಗ (i<j)
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
ಪೂರ್ಣಾಂಕ int_ಗಮ್ಯ_string(ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ, ಅಕ್ಷರ str[], ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ afterpoint)
{
	uint32_t i = 0;

	/*extract each digit and put into str[i]*/

	ಆಗ (ಸಂಖ್ಯೆ != 0)
	{
		str[i] = ((ಸಂಖ್ಯೆ%10) + '0');
		i++;
		ಸಂಖ್ಯೆ = ಸಂಖ್ಯೆ/10;
	}

	/*insert 0 after the numbers, if count of digits less than afterpoint*/

	ಆಗ (i < afterpoint)
	{
		str[i] = '0';
		i++;
	}

	/*
	   zeroth digit is in oth position in array,
	   To read digits properly, reverse array
	 */
	ಹಿಮ್ಮುಖ(str, i);
	str[i] = '\0';

	ಹಿಂತಿರುಗಿ i;
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
ಶೂನ್ಯ ftoa(ದಶಮಾಂಶ n, ಅಕ್ಷರ *res, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ afterpoint)
{
	ಪೂರ್ಣಾಂಕ i=0;
	ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ[30]={'\0'};
	n += 0.0000001;

	// Extract integer part
	ಪೂರ್ಣಾಂಕ ipart = (ಪೂರ್ಣಾಂಕ)n;

	// Extract floating part
	ದಶಮಾಂಶ fpart = (ದಶಮಾಂಶ) (n - (ದಶಮಾಂಶ)ipart);
	ಪೂರ್ಣಾಂಕ j=0;

	ಆದರೆ(n < (0/1))
	{
		res[j]='-';
		j=1;
	}

	ಆದರೆ (ipart == 0)
	{
		res[j]='0';
		j=j+1;
	}
	ಇಲ್ಲದಿದ್ದರೆ{
		ಆದರೆ (ipart <0)
		{
			ipart =(-1)*ipart;
		}

		i = int_ಗಮ್ಯ_string(ipart, ತಾತ್ಕಾಲಿಕ, 0);

		strcpy(res+j,ತಾತ್ಕಾಲಿಕ);
	}

	i = i+j;

	// check for display option after point
	ಆದರೆ (afterpoint != 0)
	{
		res[i] = '.';// add dot

		ಆದರೆ (fpart < 0/1)
		{

			fpart = (-1)*fpart;

		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fpart == 0/1)
		{
			fpart = fpart;
		}

		fpart = fpart * pow_10( afterpoint);

		int_ಗಮ್ಯ_string((ಪೂರ್ಣಾಂಕ)fpart, res + i + 1, afterpoint);
	}
}

/** @fn void delay_loop(unsigned long cntr1, unsigned long cntr2)
 * @brief Delay calculated interms of iterative operation
 * @param unsigned long cntr1 - one counter value
 * @param unsigned long cntr2 - another counter value
 */
ಶೂನ್ಯ delay_loop(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ cntr1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ cntr2)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ tmpCntr = cntr2;

	ಆಗ (cntr1--)
	{
		tmpCntr = cntr2;

		ಆಗ (tmpCntr--);
	}
}

/** @fn long int read_word(int *addr)
 * @brief returns the value stored at a given address
 * Here we assume the word size to be 32 bits for gpio
 * @param int* addr
 * @return long int
 */
ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ಶಬ್ದ(uint32_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	ಹಿಂತಿರುಗಿ *addr;
}

/** @fn void write_word(int *addr, unsigned long val)
 * @brief  writes a value to an address
 * @param int*
 * @param unsigned long
 */
ಶೂನ್ಯ write_ಶಬ್ದ(uint32_t *addr, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
