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

#నిర్వచితం_కాకపోతే UTIL_H
#నిర్వచించు UTIL_H
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdint.h>

/* function prototype */
శూన్య waitfor(గుర్తులేని పూర్ణాంకం secs);
శూన్య delay(గుర్తులేని దీర్ఘ seconds);
దశాంశం pow_10(గుర్తులేని పూర్ణాంకం y);
శూన్య తిరగేయి(అక్షరం *str, పూర్ణాంకం len);
శూన్య ftoa( దశాంశం, అక్షరం *, గుర్తులేని పూర్ణాంకం);
శూన్య delay_loop(గుర్తులేని దీర్ఘ cntr1, గుర్తులేని దీర్ఘ cntr2);
గుర్తులేని దీర్ఘ read_మాట(uint32_t *addr);
శూన్య write_మాట(uint32_t *addr, గుర్తులేని దీర్ఘ val);
పూర్ణాంకం int_గమ్యం_string(పూర్ణాంకం సంఖ్య, అక్షరం str[], గుర్తులేని పూర్ణాంకం afterpoint);
శూన్య _printf_(స్థిరరాశి అక్షరం *fmt, va_list ap);
పూర్ణాంకం రాయి(స్థిరరాశి అక్షరం* fmt, ...);

#అయితే_ముగింపు
