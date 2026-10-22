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


#నిర్వచితం_కాకపోతే INTRUDER_DETECTION_H
#నిర్వచించు INTRUDER_DETECTION_H

#నిర్వచించు ROWNUM              4
#నిర్వచించు COLNUM              4
#నిర్వచించు OUTPINS_స్థానభ్రంశం      0
#నిర్వచించు INPINS_స్థానభ్రంశం       4
#నిర్వచించు OUTPINS             (0xF << OUTPINS_స్థానభ్రంశం)
#నిర్వచించు INPINS              (0xF << INPINS_స్థానభ్రంశం)

//Peripheral Pins
#నిర్వచించు BUZZER              GPIO11
#నిర్వచించు LED_P1              GPIO16
#నిర్వచించు LED_P2              GPIO18
#నిర్వచించు LED_P3              GPIO19
#నిర్వచించు LED_P4              GPIO21
#నిర్వచించు POWER_SWITCH        GPIO24
#నిర్వచించు DEACTIVATE_SWITCH   GPIO25
#నిర్వచించు PANIC_BUTTON        GPIO28          //ఆదానం
#నిర్వచించు GPIO_OUTPINS        (LED_P1 | LED_P2 | LED_P3 | LED_P4 | BUZZER)
#నిర్వచించు PIR_లోపల	            GPIO8
#నిర్వచించు PANIC_BUTTON_స్థానభ్రంశం 28
#నిర్వచించు PIR_స్థానభ్రంశం          8
#నిర్వచించు ALARM_TIMER         5
#నిర్వచించు ఎగువ                1
#నిర్వచించు దిగువ                 0

//Keypad 
#నిర్వచించు PASS_అంకె            4               //Number of Digits Password

//function prototype
శూన్య సమితి_కీలకం_pins_map(గుర్తులేని పూర్ణాంకం* అడ్డువరుస, గుర్తులేని పూర్ణాంకం* నిలువు, పూర్ణాంకం పట్టిక[COLNUM][ROWNUM]);
పూర్ణాంకం get_కీలకం();
పూర్ణాంకం get_నిలువు_అడ్డువరుస(శూన్య);
గుర్తులేని పూర్ణాంకం అడ్డువరుస_pins[ROWNUM];
గుర్తులేని పూర్ణాంకం నిలువు_pins[COLNUM];
పూర్ణాంకం కీలకం_map[COLNUM][ROWNUM];

#అయితే_ముగింపు
