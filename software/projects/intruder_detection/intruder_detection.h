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


#اگر_غیر_تعریف_شدہ INTRUDER_DETECTION_H
#تعریف_کرو INTRUDER_DETECTION_H

#تعریف_کرو ROWNUM              4
#تعریف_کرو COLNUM              4
#تعریف_کرو OUTPINS_انحراف      0
#تعریف_کرو INPINS_انحراف       4
#تعریف_کرو OUTPINS             (0xF << OUTPINS_انحراف)
#تعریف_کرو INPINS              (0xF << INPINS_انحراف)

//Peripheral Pins
#تعریف_کرو BUZZER              GPIO11
#تعریف_کرو LED_P1              GPIO16
#تعریف_کرو LED_P2              GPIO18
#تعریف_کرو LED_P3              GPIO19
#تعریف_کرو LED_P4              GPIO21
#تعریف_کرو POWER_SWITCH        GPIO24
#تعریف_کرو DEACTIVATE_SWITCH   GPIO25
#تعریف_کرو PANIC_BUTTON        GPIO28          //داخلہ
#تعریف_کرو GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#تعریف_کرو PIR_اندر	            GPIO8
#تعریف_کرو PANIC_BUTTON_انحراف 28
#تعریف_کرو PIR_انحراف          8
#تعریف_کرو ALARM_TIMER         5
#تعریف_کرو بلند                1
#تعریف_کرو کم                 0

//Keypad 
#تعریف_کرو PASS_عدد            4               //Number of Digits Password

//function prototype
خالی سیٹ_کلید_pins_map(غیرعلامتی صحیح* صف, غیرعلامتی صحیح* ستون, صحیح جدول[COLNUM][ROWNUM]);
صحیح get_کلید();
صحیح get_ستون_صف(خالی);
غیرعلامتی صحیح صف_pins[ROWNUM];
غیرعلامتی صحیح ستون_pins[COLNUM];
صحیح کلید_map[COLNUM][ROWNUM];

#اگر_ختم
