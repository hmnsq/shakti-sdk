/************************************************************************
 * Project           		:  Shakti development board
 * Name of the file	     	:  Intruder detection.c
 * Brief Description of file    :  This is a program for Intruder Detection System which uses PIR Sensor to detect any intrusion
 * Name of the author           :  Sambhav Jain 
 * Email ID                     :  sambhav.jv@gmail.com
    Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file intruder_detection.h
@brief Intruder detection using PIR Sensors and Keypad 
@detail Intruder detection using PIR Sensors for detection of intruder and Keypad for interfacing, locking and unlocking the device.
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ INTRUDER_DETECTION_H
#ವ್ಯಾಖ್ಯಾನಿಸು INTRUDER_DETECTION_H

#ವ್ಯಾಖ್ಯಾನಿಸು ROWNUM              4
#ವ್ಯಾಖ್ಯಾನಿಸು COLNUM              4
#ವ್ಯಾಖ್ಯಾನಿಸು OUTPINS_ಸ್ಥಾನಾಂತರ      0
#ವ್ಯಾಖ್ಯಾನಿಸು INPINS_ಸ್ಥಾನಾಂತರ       4
#ವ್ಯಾಖ್ಯಾನಿಸು OUTPINS             (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ)
#ವ್ಯಾಖ್ಯಾನಿಸು INPINS              (0xF << INPINS_ಸ್ಥಾನಾಂತರ)

//Peripheral Pins
#ವ್ಯಾಖ್ಯಾನಿಸು BUZZER              GPIO11
#ವ್ಯಾಖ್ಯಾನಿಸು LED_P1              GPIO16
#ವ್ಯಾಖ್ಯಾನಿಸು LED_P2              GPIO18
#ವ್ಯಾಖ್ಯಾನಿಸು LED_P3              GPIO19
#ವ್ಯಾಖ್ಯಾನಿಸು LED_P4              GPIO21
#ವ್ಯಾಖ್ಯಾನಿಸು POWER_SWITCH        GPIO24
#ವ್ಯಾಖ್ಯಾನಿಸು DEACTIVATE_SWITCH   GPIO25
#ವ್ಯಾಖ್ಯಾನಿಸು PANIC_BUTTON        GPIO28          //ಒಳಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#ವ್ಯಾಖ್ಯಾನಿಸು PIR_ಒಳ	            GPIO8
#ವ್ಯಾಖ್ಯಾನಿಸು PANIC_BUTTON_ಸ್ಥಾನಾಂತರ 28
#ವ್ಯಾಖ್ಯಾನಿಸು PIR_ಸ್ಥಾನಾಂತರ          8
#ವ್ಯಾಖ್ಯಾನಿಸು ALARM_TIMER         5
#ವ್ಯಾಖ್ಯಾನಿಸು ಮೇಲಿನ                1
#ವ್ಯಾಖ್ಯಾನಿಸು ಕೆಳಗಿನ                 0

//Keypad 
#ವ್ಯಾಖ್ಯಾನಿಸು PASS_ಅಂಕೆ            4               //Number of Digits Password

//function prototype
ಶೂನ್ಯ ಗಣ_ಕೀಲಿ_pins_map(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಅಡ್ಡಸಾಲು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಲಂಬಸಾಲು, ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ[COLNUM][ROWNUM]);
ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ();
ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು(ಶೂನ್ಯ);
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_pins[ROWNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_pins[COLNUM];
ಪೂರ್ಣಾಂಕ ಕೀಲಿ_map[COLNUM][ROWNUM];

#ಆದರೆ_ಅಂತ್ಯ
