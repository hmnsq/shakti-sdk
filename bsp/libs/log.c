/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: log.c
 * Brief Description of file    : print control for all operation
 * Name of Author    	        : Abhinav ramnath & Sathya Narayanan N
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
***************************************************************************/
/**
@file log.c
@brief logger application for debugging and normal uart display.
@detail This file contains implementation of different log levels.
*/ 

#ضمن "log.h"
#ضمن "utils.h"

/*Use -D compiler flag to set the LOG_LEVEL; default value is 1*/
#اگر_تعریف_نشده LOG_LEVEL
#تعریف_کن LOG_LEVEL 3 
#پایان_اگر

/** @fn void log_trace(const char*fmt, ...)
 * @brief Function to print trace logs
 * @details This function print trace logs if the LOG_LEVEL allows trace logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_trace(ثابت حرف* fmt, ...)
{
	إذا (TRACE <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_(fmt, ap);

		va_end(ap);
	}
}

/** @fn void log_info(const char*fmt, ...)
 * @brief Function to print info logs
 * @details This function print info logs if the LOG_LEVEL allows info logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_info(ثابت حرف* fmt, ...)
{
	إذا (INFO <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_( fmt, ap);

		va_end(ap);
	}
}

/** @fn void log_debug(const char*fmt, ...)
 * @brief Function to print debug logs
 * @details This function print debug logs if the LOG_LEVEL allows debug logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_debug(ثابت حرف* fmt, ...)
{
	إذا (DEBUG <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_(fmt, ap);

		va_end(ap);
	}
}

/** @fn void log_warn(const char*fmt, ...)
 * @brief Function to print warn logs
 * @details This function print trace warn if the LOG_LEVEL allows warn logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_warn(ثابت حرف* fmt, ...)
{
	إذا (WARN <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_( fmt, ap);

		va_end(ap);
	}
}

/** @fn void log_error(const char*fmt, ...)
 * @brief Function to print error logs
 * @details This function print error logs if the LOG_LEVEL allows error logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_error(ثابت حرف* fmt, ...)
{
	إذا (ERROR <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_( fmt, ap);

		va_end(ap);
	}
}

/** @fn void log_fatal(const char*fmt, ...)
 * @brief Function to print fatal logs
 * @details This function print fatal logs if the LOG_LEVEL allows fatal logs
 * @param const char* (printf formatted arguments with format specifiers)
 */
فراغ log_fatal(ثابت حرف* fmt, ...)
{
	إذا (FATAL <= LOG_LEVEL) {
		va_list ap;
		va_start(ap, fmt);

		_printf_( fmt, ap);

		va_end(ap);
	}

	log_info("\n panic \n");
	طالما (1);
}
