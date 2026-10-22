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
 
#నిర్వచితం_కాకపోతే GPIO_SPI_H
#నిర్వచించు GPIO_SPI_H

#నిర్వచించు IR_1 (1 << 4)
#నిర్వచించు IR_2 (1 << 5)
#నిర్వచించు IR_3 (1 << 6)
#నిర్వచించు IR_4 (1 << 7)
#నిర్వచించు IR_5 (1 << 8)

#నిర్వచించు SPI_MISO 1<<0 //1st bit 
#నిర్వచించు SPI_MOSI 1<<1 //2nd bit
#నిర్వచించు SPI_SCLK 1<<2 //3rd bit
#నిర్వచించు SPI_SS   1<<3 //4th bit
#నిర్వచించు SPI_ADC_లోపల 0xC0

// function prototype
 గుర్తులేని అక్షరం readbyte(గుర్తులేని అక్షరం delay);
 పూర్ణాంకం config();

#అయితే_ముగింపు/* GPIO_SPI_H*/

