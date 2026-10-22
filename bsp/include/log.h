/***************************************************************************
* Project               	: shakti devt board
* Name of the file	        : log.h
* Brief Description of file     : Header file for logger.
* Name of Author    	        : Abhinav Ramnath
* Email ID                      : abhinavramnath13@gmail.com

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
***************************************************************************/
/**
 * @file log.h
 * @brief Header file for logger.
 * @detail This file is used for logging. There are 6 levels of logging.
 Level 0 is the most critical. Usually system stops after level 0 logging.
 Level 3 is the default level of logging.
 */

#समावेश <stdarg.h>

// Log Levels
#घोषणा TRACE 5
#घोषणा DEBUG 4
#घोषणा INFO  3
#घोषणा WARN  2
#घोषणा ERROR 1
#घोषणा FATAL 0

बाह्य व्योम vprintfmt(व्योम (*putch)(पूर्णांक, व्योम**), व्योम **putdat, स्थिर अक्षर *fmt, बहु_सूची ap);

//function prototype
व्योम log_trace(स्थिर अक्षर*fmt, ...);
व्योम log_info(स्थिर अक्षर*fmt, ...);
व्योम log_debug(स्थिर अक्षर*fmt, ...);
व्योम log_warn(स्थिर अक्षर*fmt, ...);
व्योम log_error(स्थिर अक्षर*fmt, ...);
व्योम log_fatal(स्थिर अक्षर*fmt, ...);
