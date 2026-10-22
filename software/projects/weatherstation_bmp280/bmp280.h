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

#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[1]

#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_SLAVE_ವಿಳಾಸ 0xEC       //Defines the Starting address of slave//
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_CTRL_MEANS 0xF4
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_ಸಾಮಾನ್ಯ_ಬಹುಲಕ 0x26
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ 0xF3
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_CONFIG_ರಿಜಿಸ್ಟರ್ 0xF5
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_RESET_ರಿಜಿಸ್ಟರ್ 0xE0

#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_T1 0x88
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_T2 0x8A
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_T3 0x8C

#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P1 0x8E
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P2 0x90
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P3 0x92
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P4 0x94
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P5 0x96
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P6 0x98
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P7 0x9A
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P8 0x9C
#ವ್ಯಾಖ್ಯಾನಿಸು BMP280_REG_DIG_P9 0x9E

