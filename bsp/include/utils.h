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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ UTIL_H
#ವ್ಯಾಖ್ಯಾನಿಸು UTIL_H
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

/* function prototype */
ಶೂನ್ಯ waitfor(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ secs);
ಶೂನ್ಯ delay(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ seconds);
ದಶಮಾಂಶ pow_10(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ y);
ಶೂನ್ಯ ಹಿಮ್ಮುಖ(ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ftoa( ದಶಮಾಂಶ, ಅಕ್ಷರ *, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);
ಶೂನ್ಯ delay_loop(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ cntr1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ cntr2);
ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ಶಬ್ದ(uint32_t *addr);
ಶೂನ್ಯ write_ಶಬ್ದ(uint32_t *addr, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ val);
ಪೂರ್ಣಾಂಕ int_ಗಮ್ಯ_string(ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ, ಅಕ್ಷರ str[], ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ afterpoint);
ಶೂನ್ಯ _printf_(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ap);
ಪೂರ್ಣಾಂಕ ಬರೆ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* fmt, ...);

#ಆದರೆ_ಅಂತ್ಯ
