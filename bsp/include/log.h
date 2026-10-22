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

#అన్తర్భావ <stdarg.h>

// Log Levels
#నిర్వచించు TRACE 5
#నిర్వచించు DEBUG 4
#నిర్వచించు INFO  3
#నిర్వచించు WARN  2
#నిర్వచించు ERROR 1
#నిర్వచించు FATAL 0

బాహ్య శూన్య vprintfmt(శూన్య (*putch)(పూర్ణాంకం, శూన్య**), శూన్య **putdat, స్థిరరాశి అక్షరం *fmt, va_list ap);

//function prototype
శూన్య log_trace(స్థిరరాశి అక్షరం*fmt, ...);
శూన్య log_info(స్థిరరాశి అక్షరం*fmt, ...);
శూన్య log_debug(స్థిరరాశి అక్షరం*fmt, ...);
శూన్య log_warn(స్థిరరాశి అక్షరం*fmt, ...);
శూన్య log_error(స్థిరరాశి అక్షరం*fmt, ...);
శూన్య log_fatal(స్థిరరాశి అక్షరం*fmt, ...);
