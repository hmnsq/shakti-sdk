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

#घोषणा I2C i2c_instance[1]

#घोषणा BMP280_SLAVE_ADDRESS 0xEC       //Defines the Starting address of slave//
#घोषणा DELAY_मूल्य 900
#घोषणा PRESCALER_गिनती 0x1F
#घोषणा SCLK_गिनती 0x91
#घोषणा BMP280_CTRL_MEANS 0xF4
#घोषणा BMP280_NORMAL_MODE 0x26
#घोषणा BMP280_STATUS_REGISTER 0xF3
#घोषणा BMP280_CONFIG_REGISTER 0xF5
#घोषणा BMP280_RESET_REGISTER 0xE0

#घोषणा BMP280_REG_DIG_T1 0x88
#घोषणा BMP280_REG_DIG_T2 0x8A
#घोषणा BMP280_REG_DIG_T3 0x8C

#घोषणा BMP280_REG_DIG_P1 0x8E
#घोषणा BMP280_REG_DIG_P2 0x90
#घोषणा BMP280_REG_DIG_P3 0x92
#घोषणा BMP280_REG_DIG_P4 0x94
#घोषणा BMP280_REG_DIG_P5 0x96
#घोषणा BMP280_REG_DIG_P6 0x98
#घोषणा BMP280_REG_DIG_P7 0x9A
#घोषणा BMP280_REG_DIG_P8 0x9C
#घोषणा BMP280_REG_DIG_P9 0x9E

