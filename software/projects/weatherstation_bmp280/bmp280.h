/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  weatherstation.c
* Brief Description of file     :  A sample project to demonstrate
                                           integration of temperature sensor
                                           and transmission of data to a website
* Name of Author                :  Anand Kumar S
* Email ID                      :  007334@imail.iitm.ac.in

    Copyright (C) 2019  IIT Madras. All rights reserved.

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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[1]

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_SLAVE_ਪਤਾ 0xEC       //Defines the Starting address of slave//
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_CTRL_MEANS 0xF4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_ਸਾਧਾਰਨ_ਬਹੁਲਕ 0x26
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_ਸਥਿਤੀ_ਰਜਿਸਟਰ 0xF3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_CONFIG_ਰਜਿਸਟਰ 0xF5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_RESET_ਰਜਿਸਟਰ 0xE0

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_T1 0x88
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_T2 0x8A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_T3 0x8C

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P1 0x8E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P2 0x90
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P3 0x92
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P4 0x94
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P5 0x96
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P6 0x98
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P7 0x9A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P8 0x9C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BMP280_REG_DIG_P9 0x9E

