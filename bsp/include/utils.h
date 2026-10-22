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
शून्य waitfor(अचिन्हित पूर्णांक secs);
शून्य delay(अचिन्हित दीर्घ seconds);
दशांश pow_10(अचिन्हित पूर्णांक y);
शून्य reverse(अक्षर *str, पूर्णांक len);
शून्य ftoa( दशांश, अक्षर *, अचिन्हित पूर्णांक);
शून्य delay_loop(अचिन्हित दीर्घ cntr1, अचिन्हित दीर्घ cntr2);
अचिन्हित दीर्घ read_word(uint32_t *addr);
शून्य write_word(uint32_t *addr, अचिन्हित दीर्घ val);
पूर्णांक int_to_string(पूर्णांक संख्या, अक्षर str[], अचिन्हित पूर्णांक afterpoint);
शून्य _printf_(स्थिरांक अक्षर *fmt, बहु_सूची ap);
पूर्णांक म_लिखो(स्थिरांक अक्षर* fmt, ...);

#endif
