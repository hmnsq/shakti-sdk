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


#اگر_تعریف_نشده INTRUDER_DETECTION_H
#تعریف_کن INTRUDER_DETECTION_H

#تعریف_کن ROWNUM              4
#تعریف_کن COLNUM              4
#تعریف_کن OUTPINS_جابه_جایی      0
#تعریف_کن INPINS_جابه_جایی       4
#تعریف_کن OUTPINS             (0xF << OUTPINS_جابه_جایی)
#تعریف_کن INPINS              (0xF << INPINS_جابه_جایی)

//Peripheral Pins
#تعریف_کن BUZZER              GPIO11
#تعریف_کن LED_P1              GPIO16
#تعریف_کن LED_P2              GPIO18
#تعریف_کن LED_P3              GPIO19
#تعریف_کن LED_P4              GPIO21
#تعریف_کن POWER_SWITCH        GPIO24
#تعریف_کن DEACTIVATE_SWITCH   GPIO25
#تعریف_کن PANIC_BUTTON        GPIO28          //درون داد
#تعریف_کن GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#تعریف_کن PIR_درون	            GPIO8
#تعریف_کن PANIC_BUTTON_جابه_جایی 28
#تعریف_کن PIR_جابه_جایی          8
#تعریف_کن ALARM_TIMER         5
#تعریف_کن بالا                1
#تعریف_کن کم                 0

//Keypad 
#تعریف_کن PASS_رقم            4               //Number of Digits Password

//function prototype
فراغ مجموعه_کلید_pins_map(بیعلامت صحيح* ردیف, بیعلامت صحيح* ستون, صحيح جدول[COLNUM][ROWNUM]);
صحيح get_کلید();
صحيح get_ستون_ردیف(فراغ);
بیعلامت صحيح ردیف_pins[ROWNUM];
بیعلامت صحيح ستون_pins[COLNUM];
صحيح کلید_map[COLNUM][ROWNUM];

#پایان_اگر
