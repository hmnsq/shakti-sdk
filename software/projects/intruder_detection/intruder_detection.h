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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ INTRUDER_DETECTION_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INTRUDER_DETECTION_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROWNUM              4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COLNUM              4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OUTPINS_ਵਿੱਥ      0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INPINS_ਵਿੱਥ       4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OUTPINS             (0xF << OUTPINS_ਵਿੱਥ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INPINS              (0xF << INPINS_ਵਿੱਥ)

//Peripheral Pins
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUZZER              GPIO11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED_P1              GPIO16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED_P2              GPIO18
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED_P3              GPIO19
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED_P4              GPIO21
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POWER_SWITCH        GPIO24
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEACTIVATE_SWITCH   GPIO25
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PANIC_BUTTON        GPIO28          //ਨਿਵੇਸ਼
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIR_ਵਿੱਚ	            GPIO8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PANIC_BUTTON_ਵਿੱਥ 28
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PIR_ਵਿੱਥ          8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALARM_TIMER         5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਉੱਚਾ                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨੀਵਾਂ                 0

//Keypad 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PASS_ਅੰਕ            4               //Number of Digits Password

//function prototype
ਖਾਲੀ ਸੈੱਟ_ਕੁੰਜੀ_pins_map(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਪੰਕਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਖਾਨਾ, ਪੂਰਨ ਸਾਰਣੀ[COLNUM][ROWNUM]);
ਪੂਰਨ get_ਕੁੰਜੀ();
ਪੂਰਨ get_ਖਾਨਾ_ਪੰਕਤੀ(ਖਾਲੀ);
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ_pins[ROWNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ_pins[COLNUM];
ਪੂਰਨ ਕੁੰਜੀ_map[COLNUM][ROWNUM];

#ਜੇ_ਅੰਤ
