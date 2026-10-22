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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>

// Log Levels
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRACE 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INFO  3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WARN  2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ERROR 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FATAL 0

ਬਾਹਰੀ ਖਾਲੀ vprintfmt(ਖਾਲੀ (*putch)(ਪੂਰਨ, ਖਾਲੀ**), ਖਾਲੀ **putdat, ਅਚਲ ਅੱਖਰ *fmt, va_list ap);

//function prototype
ਖਾਲੀ log_trace(ਅਚਲ ਅੱਖਰ*fmt, ...);
ਖਾਲੀ log_info(ਅਚਲ ਅੱਖਰ*fmt, ...);
ਖਾਲੀ log_debug(ਅਚਲ ਅੱਖਰ*fmt, ...);
ਖਾਲੀ log_warn(ਅਚਲ ਅੱਖਰ*fmt, ...);
ਖਾਲੀ log_error(ਅਚਲ ਅੱਖਰ*fmt, ...);
ਖਾਲੀ log_fatal(ਅਚਲ ਅੱਖਰ*fmt, ...);
