/***************************************************************************
 * Project           	        : shakti devt board
 * Name of the file	     	: gpio_spi.h
 * Brief Description of file    : header file for spi gpio
 * Name of Author    	        : Kottee & Aditya dubey
 * Email ID                     : kottee.1@gmail.com

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
 ****************************************************************************/
/**
@file gpio_spi.h
@brief headear file for spi gpio
@detail this is header file for gpio_spi.c
*/ 
 
#यदि_अपरिभाषितम् GPIO_SPI_H
#परिभाषय GPIO_SPI_H

#परिभाषय IR_1 (1 << 4)
#परिभाषय IR_2 (1 << 5)
#परिभाषय IR_3 (1 << 6)
#परिभाषय IR_4 (1 << 7)
#परिभाषय IR_5 (1 << 8)

#परिभाषय SPI_MISO 1<<0 //1st bit 
#परिभाषय SPI_MOSI 1<<1 //2nd bit
#परिभाषय SPI_SCLK 1<<2 //3rd bit
#परिभाषय SPI_SS   1<<3 //4th bit
#परिभाषय SPI_ADC_अन्तर् 0xC0

// function prototype
 अचिह्नित वर्ण readbyte(अचिह्नित वर्ण delay);
 पूर्णाङ्क config();

#यदि_अन्तः/* GPIO_SPI_H*/

