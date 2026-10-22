/****************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: utils.h
 * Brief Description of file    : Header file for utils
 * Name of Author    	        : Sathya Narayanan N
 * Email ID                     : sathya281@gmail.com

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
*******************************************************************************/
/**
 * @file utils.h
 * @brief header file for utils
 * @detail This is the header file for util.c
 */

#ifndef UTIL_H
#define UTIL_H
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdint.h>

/* function prototype */
शून्य waitfor(अचिन्हित पूर्णाङ्क secs);
शून्य delay(अचिन्हित दीर्घ seconds);
भिन्न pow_10(अचिन्हित पूर्णाङ्क y);
शून्य reverse(वर्ण *str, पूर्णाङ्क len);
शून्य ftoa( भिन्न, वर्ण *, अचिन्हित पूर्णाङ्क);
शून्य delay_loop(अचिन्हित दीर्घ cntr1, अचिन्हित दीर्घ cntr2);
अचिन्हित दीर्घ read_word(uint32_t *addr);
शून्य write_word(uint32_t *addr, अचिन्हित दीर्घ val);
पूर्णाङ्क int_to_string(पूर्णाङ्क सङ्ख्या, वर्ण str[], अचिन्हित पूर्णाङ्क afterpoint);
शून्य _printf_(अचर वर्ण *fmt, बहु_सूची ap);
पूर्णाङ्क म_लिखो(अचर वर्ण* fmt, ...);

#endif
