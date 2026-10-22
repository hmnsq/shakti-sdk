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

#ಅನ್ತರ್ಭಾವ <stdarg.h>

// Log Levels
#ವ್ಯಾಖ್ಯಾನಿಸು TRACE 5
#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG 4
#ವ್ಯಾಖ್ಯಾನಿಸು INFO  3
#ವ್ಯಾಖ್ಯಾನಿಸು WARN  2
#ವ್ಯಾಖ್ಯಾನಿಸು ERROR 1
#ವ್ಯಾಖ್ಯಾನಿಸು FATAL 0

ಬಾಹ್ಯ ಶೂನ್ಯ vprintfmt(ಶೂನ್ಯ (*putch)(ಪೂರ್ಣಾಂಕ, ಶೂನ್ಯ**), ಶೂನ್ಯ **putdat, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ap);

//function prototype
ಶೂನ್ಯ log_trace(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
ಶೂನ್ಯ log_info(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
ಶೂನ್ಯ log_debug(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
ಶೂನ್ಯ log_warn(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
ಶೂನ್ಯ log_error(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
ಶೂನ್ಯ log_fatal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*fmt, ...);
