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

#ضمن <stdarg.h>

// Log Levels
#تعریف_کرو TRACE 5
#تعریف_کرو DEBUG 4
#تعریف_کرو INFO  3
#تعریف_کرو WARN  2
#تعریف_کرو ERROR 1
#تعریف_کرو FATAL 0

خارجي فراغ vprintfmt(فراغ (*putch)(صحيح, فراغ**), فراغ **putdat, ثابت حرف *fmt, va_list ap);

//function prototype
فراغ log_trace(ثابت حرف*fmt, ...);
فراغ log_info(ثابت حرف*fmt, ...);
فراغ log_debug(ثابت حرف*fmt, ...);
فراغ log_warn(ثابت حرف*fmt, ...);
فراغ log_error(ثابت حرف*fmt, ...);
فراغ log_fatal(ثابت حرف*fmt, ...);
