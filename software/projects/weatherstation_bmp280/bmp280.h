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

#परिभाषय I2C i2c_instance[1]

#परिभाषय BMP280_SLAVE_स्थानाङ्कः 0xEC       //Defines the Starting address of slave//
#परिभाषय DELAY_मानम् 900
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91
#परिभाषय BMP280_CTRL_MEANS 0xF4
#परिभाषय BMP280_प्रसामान्यम्_बहुलकम् 0x26
#परिभाषय BMP280_स्थितिः_पञ्जिकाकोशः 0xF3
#परिभाषय BMP280_CONFIG_पञ्जिकाकोशः 0xF5
#परिभाषय BMP280_RESET_पञ्जिकाकोशः 0xE0

#परिभाषय BMP280_REG_DIG_T1 0x88
#परिभाषय BMP280_REG_DIG_T2 0x8A
#परिभाषय BMP280_REG_DIG_T3 0x8C

#परिभाषय BMP280_REG_DIG_P1 0x8E
#परिभाषय BMP280_REG_DIG_P2 0x90
#परिभाषय BMP280_REG_DIG_P3 0x92
#परिभाषय BMP280_REG_DIG_P4 0x94
#परिभाषय BMP280_REG_DIG_P5 0x96
#परिभाषय BMP280_REG_DIG_P6 0x98
#परिभाषय BMP280_REG_DIG_P7 0x9A
#परिभाषय BMP280_REG_DIG_P8 0x9C
#परिभाषय BMP280_REG_DIG_P9 0x9E

