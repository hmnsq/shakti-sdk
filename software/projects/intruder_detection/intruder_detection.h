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


#جيڪڏهن_وصف_نه_ٿيل INTRUDER_DETECTION_H
#وصف_ڪريو INTRUDER_DETECTION_H

#وصف_ڪريو ROWNUM              4
#وصف_ڪريو COLNUM              4
#وصف_ڪريو OUTPINS_وٿي      0
#وصف_ڪريو INPINS_وٿي       4
#وصف_ڪريو OUTPINS             (0xF << OUTPINS_وٿي)
#وصف_ڪريو INPINS              (0xF << INPINS_وٿي)

//Peripheral Pins
#وصف_ڪريو BUZZER              GPIO11
#وصف_ڪريو LED_P1              GPIO16
#وصف_ڪريو LED_P2              GPIO18
#وصف_ڪريو LED_P3              GPIO19
#وصف_ڪريو LED_P4              GPIO21
#وصف_ڪريو POWER_SWITCH        GPIO24
#وصف_ڪريو DEACTIVATE_SWITCH   GPIO25
#وصف_ڪريو PANIC_BUTTON        GPIO28          //داخلا
#وصف_ڪريو GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#وصف_ڪريو PIR_اندريون	            GPIO8
#وصف_ڪريو PANIC_BUTTON_وٿي 28
#وصف_ڪريو PIR_وٿي          8
#وصف_ڪريو ALARM_TIMER         5
#وصف_ڪريو مٿاهون                1
#وصف_ڪريو هيٺيون                 0

//Keypad 
#وصف_ڪريو PASS_انگ            4               //Number of Digits Password

//function prototype
فراغ سيٽ_ڪنجي_pins_map(بنانشان صحيح* صف, بنانشان صحيح* کانو, صحيح جدول[COLNUM][ROWNUM]);
صحيح get_ڪنجي();
صحيح get_کانو_صف(فراغ);
بنانشان صحيح صف_pins[ROWNUM];
بنانشان صحيح کانو_pins[COLNUM];
صحيح ڪنجي_map[COLNUM][ROWNUM];

#جيڪڏهن_پورو
