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

#నిర్వచించు I2C i2c_instance[1]

#నిర్వచించు BMP280_SLAVE_చిరునామా 0xEC       //Defines the Starting address of slave//
#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91
#నిర్వచించు BMP280_CTRL_MEANS 0xF4
#నిర్వచించు BMP280_సాధారణ_బహుళకం 0x26
#నిర్వచించు BMP280_స్థితి_రిజిస్టరు 0xF3
#నిర్వచించు BMP280_CONFIG_రిజిస్టరు 0xF5
#నిర్వచించు BMP280_RESET_రిజిస్టరు 0xE0

#నిర్వచించు BMP280_REG_DIG_T1 0x88
#నిర్వచించు BMP280_REG_DIG_T2 0x8A
#నిర్వచించు BMP280_REG_DIG_T3 0x8C

#నిర్వచించు BMP280_REG_DIG_P1 0x8E
#నిర్వచించు BMP280_REG_DIG_P2 0x90
#నిర్వచించు BMP280_REG_DIG_P3 0x92
#నిర్వచించు BMP280_REG_DIG_P4 0x94
#నిర్వచించు BMP280_REG_DIG_P5 0x96
#నిర్వచించు BMP280_REG_DIG_P6 0x98
#నిర్వచించు BMP280_REG_DIG_P7 0x9A
#నిర్వచించు BMP280_REG_DIG_P8 0x9C
#నిర్వచించు BMP280_REG_DIG_P9 0x9E

