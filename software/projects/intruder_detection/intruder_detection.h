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


#यदि_अपरिभाषितम् INTRUDER_DETECTION_H
#परिभाषय INTRUDER_DETECTION_H

#परिभाषय ROWNUM              4
#परिभाषय COLNUM              4
#परिभाषय OUTPINS_विस्थापनम्      0
#परिभाषय INPINS_विस्थापनम्       4
#परिभाषय OUTPINS             (0xF << OUTPINS_विस्थापनम्)
#परिभाषय INPINS              (0xF << INPINS_विस्थापनम्)

//Peripheral Pins
#परिभाषय BUZZER              GPIO11
#परिभाषय LED_P1              GPIO16
#परिभाषय LED_P2              GPIO18
#परिभाषय LED_P3              GPIO19
#परिभाषय LED_P4              GPIO21
#परिभाषय POWER_SWITCH        GPIO24
#परिभाषय DEACTIVATE_SWITCH   GPIO25
#परिभाषय PANIC_BUTTON        GPIO28          //निवेशः
#परिभाषय GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#परिभाषय PIR_अन्तर्	            GPIO8
#परिभाषय PANIC_BUTTON_विस्थापनम् 28
#परिभाषय PIR_विस्थापनम्          8
#परिभाषय ALARM_TIMER         5
#परिभाषय उच्चः                1
#परिभाषय नीचः                 0

//Keypad 
#परिभाषय PASS_अङ्कः            4               //Number of Digits Password

//function prototype
शून्य समुच्चयः_कुञ्चिका_pins_map(अचिह्नित पूर्णाङ्क* row, अचिह्नित पूर्णाङ्क* col, पूर्णाङ्क सारणी[COLNUM][ROWNUM]);
पूर्णाङ्क get_कुञ्चिका();
पूर्णाङ्क get_col_row(शून्य);
अचिह्नित पूर्णाङ्क row_pins[ROWNUM];
अचिह्नित पूर्णाङ्क col_pins[COLNUM];
पूर्णाङ्क कुञ्चिका_map[COLNUM][ROWNUM];

#यदि_अन्तः
