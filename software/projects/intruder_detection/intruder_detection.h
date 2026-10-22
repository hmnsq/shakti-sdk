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


#جے_بنا_تعریف INTRUDER_DETECTION_H
#تعریف_کرو INTRUDER_DETECTION_H

#تعریف_کرو ROWNUM              4
#تعریف_کرو COLNUM              4
#تعریف_کرو OUTPINS_وتھ      0
#تعریف_کرو INPINS_وتھ       4
#تعریف_کرو OUTPINS             (0xF << OUTPINS_وتھ)
#تعریف_کرو INPINS              (0xF << INPINS_وتھ)

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
#تعریف_کرو PIR_وچ	            GPIO8
#تعریف_کرو PANIC_BUTTON_وتھ 28
#تعریف_کرو PIR_وتھ          8
#تعریف_کرو ALARM_TIMER         5
#تعریف_کرو بلند                1
#تعریف_کرو کم                 0

//Keypad 
#تعریف_کرو PASS_عدد            4               //Number of Digits Password

//function prototype
فراغ سیٹ_کلید_pins_map(بنانشانی صحيح* صف, بنانشانی صحيح* خانہ, صحيح جدول[COLNUM][ROWNUM]);
صحيح get_کلید();
صحيح get_خانہ_صف(فراغ);
بنانشانی صحيح صف_pins[ROWNUM];
بنانشانی صحيح خانہ_pins[COLNUM];
صحيح کلید_map[COLNUM][ROWNUM];

#جے_انت
