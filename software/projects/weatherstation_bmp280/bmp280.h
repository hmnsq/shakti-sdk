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

#وصف_ڪريو I2C i2c_instance[1]

#وصف_ڪريو BMP280_SLAVE_پتو 0xEC       //Defines the Starting address of slave//
#وصف_ڪريو DELAY_قدر 900
#وصف_ڪريو PRESCALER_ڳڻپ 0x1F
#وصف_ڪريو SCLK_ڳڻپ 0x91
#وصف_ڪريو BMP280_CTRL_MEANS 0xF4
#وصف_ڪريو BMP280_عام_گهڻائي 0x26
#وصف_ڪريو BMP280_حالت_رجسٽر 0xF3
#وصف_ڪريو BMP280_CONFIG_رجسٽر 0xF5
#وصف_ڪريو BMP280_RESET_رجسٽر 0xE0

#وصف_ڪريو BMP280_REG_DIG_T1 0x88
#وصف_ڪريو BMP280_REG_DIG_T2 0x8A
#وصف_ڪريو BMP280_REG_DIG_T3 0x8C

#وصف_ڪريو BMP280_REG_DIG_P1 0x8E
#وصف_ڪريو BMP280_REG_DIG_P2 0x90
#وصف_ڪريو BMP280_REG_DIG_P3 0x92
#وصف_ڪريو BMP280_REG_DIG_P4 0x94
#وصف_ڪريو BMP280_REG_DIG_P5 0x96
#وصف_ڪريو BMP280_REG_DIG_P6 0x98
#وصف_ڪريو BMP280_REG_DIG_P7 0x9A
#وصف_ڪريو BMP280_REG_DIG_P8 0x9C
#وصف_ڪريو BMP280_REG_DIG_P9 0x9E

