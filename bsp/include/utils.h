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

#अगर_अघोषित UTIL_H
#घोषणा UTIL_H
#समावेश <stdio.h>
#समावेश <stdint.h>

/* function prototype */
व्योम waitfor(अचिन्हित पूर्णांक secs);
व्योम delay(अचिन्हित दीर्घ seconds);
भग्न pow_10(अचिन्हित पूर्णांक y);
व्योम reverse(अक्षर *str, पूर्णांक len);
व्योम ftoa( भग्न, अक्षर *, अचिन्हित पूर्णांक);
व्योम delay_loop(अचिन्हित दीर्घ cntr1, अचिन्हित दीर्घ cntr2);
अचिन्हित दीर्घ read_word(uint32_t *addr);
व्योम write_word(uint32_t *addr, अचिन्हित दीर्घ val);
पूर्णांक int_to_string(पूर्णांक संख्या, अक्षर str[], अचिन्हित पूर्णांक afterpoint);
व्योम _printf_(स्थिर अक्षर *fmt, बहु_सूची ap);
पूर्णांक म_लिखो(स्थिर अक्षर* fmt, ...);

#पूर्ण_अगर
