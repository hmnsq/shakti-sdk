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
 
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GPIO_SPI_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_SPI_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IR_1 (1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IR_2 (1 << 5)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IR_3 (1 << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IR_4 (1 << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IR_5 (1 << 8)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_MISO 1<<0 //1st bit 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_MOSI 1<<1 //2nd bit
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SCLK 1<<2 //3rd bit
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SS   1<<3 //4th bit
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_ADC_ਵਿੱਚ 0xC0

// function prototype
 ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ readbyte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);
 ਪੂਰਨ config();

#ਜੇ_ਅੰਤ/* GPIO_SPI_H*/

