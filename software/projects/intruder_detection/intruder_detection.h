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


#که_نه_تعریف_شوی INTRUDER_DETECTION_H
#تعریف_کړه INTRUDER_DETECTION_H

#تعریف_کړه ROWNUM              4
#تعریف_کړه COLNUM              4
#تعریف_کړه OUTPINS_دننه_واټن      0
#تعریف_کړه INPINS_دننه_واټن       4
#تعریف_کړه OUTPINS             (0xF << OUTPINS_دننه_واټن)
#تعریف_کړه INPINS              (0xF << INPINS_دننه_واټن)

//Peripheral Pins
#تعریف_کړه BUZZER              GPIO11
#تعریف_کړه LED_P1              GPIO16
#تعریف_کړه LED_P2              GPIO18
#تعریف_کړه LED_P3              GPIO19
#تعریف_کړه LED_P4              GPIO21
#تعریف_کړه POWER_SWITCH        GPIO24
#تعریف_کړه DEACTIVATE_SWITCH   GPIO25
#تعریف_کړه PANIC_BUTTON        GPIO28          //ننوت
#تعریف_کړه GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#تعریف_کړه PIR_دننه	            GPIO8
#تعریف_کړه PANIC_BUTTON_دننه_واټن 28
#تعریف_کړه PIR_دننه_واټن          8
#تعریف_کړه ALARM_TIMER         5
#تعریف_کړه لوړ                1
#تعریف_کړه ټیټ                 0

//Keypad 
#تعریف_کړه PASS_عدد            4               //Number of Digits Password

//function prototype
فراغ سېټ_کلی_pins_map(بینښه صحيح* لیکه, بینښه صحيح* ستون, صحيح جدول[COLNUM][ROWNUM]);
صحيح get_کلی();
صحيح get_ستون_لیکه(فراغ);
بینښه صحيح لیکه_pins[ROWNUM];
بینښه صحيح ستون_pins[COLNUM];
صحيح کلی_map[COLNUM][ROWNUM];

#د_که_پای
