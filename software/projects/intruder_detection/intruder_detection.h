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


#अगर_अघोषित INTRUDER_DETECTION_H
#घोषणा INTRUDER_DETECTION_H

#घोषणा ROWNUM              4
#घोषणा COLNUM              4
#घोषणा OUTPINS_OFFSET      0
#घोषणा INPINS_OFFSET       4
#घोषणा OUTPINS             (0xF << OUTPINS_OFFSET)
#घोषणा INPINS              (0xF << INPINS_OFFSET)

//Peripheral Pins
#घोषणा BUZZER              GPIO11
#घोषणा LED_P1              GPIO16
#घोषणा LED_P2              GPIO18
#घोषणा LED_P3              GPIO19
#घोषणा LED_P4              GPIO21
#घोषणा POWER_SWITCH        GPIO24
#घोषणा DEACTIVATE_SWITCH   GPIO25
#घोषणा PANIC_BUTTON        GPIO28          //निवेश
#घोषणा GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#घोषणा PIR_IN	            GPIO8
#घोषणा PANIC_BUTTON_OFFSET 28
#घोषणा PIR_OFFSET          8
#घोषणा ALARM_TIMER         5
#घोषणा ऊपरी                1
#घोषणा निचला                 0

//Keypad 
#घोषणा PASS_अंक            4               //Number of Digits Password

//function prototype
व्योम set_कुंजी_pins_map(अचिन्हित पूर्णांक* row, अचिन्हित पूर्णांक* col, पूर्णांक table[COLNUM][ROWNUM]);
पूर्णांक get_कुंजी();
पूर्णांक get_col_row(व्योम);
अचिन्हित पूर्णांक row_pins[ROWNUM];
अचिन्हित पूर्णांक col_pins[COLNUM];
पूर्णांक कुंजी_map[COLNUM][ROWNUM];

#पूर्ण_अगर
