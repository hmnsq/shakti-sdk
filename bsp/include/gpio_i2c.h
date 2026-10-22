/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: gpio_i2c.h
* Brief Description of file     : Header file of the I2C operations using gpio pins.
* Name of Author    	        : Kotteeswaran
* Email ID                      : kottee.1@gmail.com

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
/**
@file gpio_i2c.h
@brief header file of the I2C operations using gpio pins.
@detail this is the header file for gpio_i2c.c
*/ 
 
#ifndef GPIO_I2C_H
#define GPIO_I2C_H

#അന്തര്ഭാവ "platform.h"
#അന്തര്ഭാവ "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#define I2C_SCL GPIO0 
#define I2C_SDA GPIO1
#define GPIOD_IS_IN 0
#define GPIOD_IS_OUT 1
#define I2C_WRITE 0
#define I2C_READ 1

// function prototype 
ശൂന്യം I2cInit();
ശൂന്യം I2cSendSlaveAddress(unsigned അക്ഷരം , unsigned അക്ഷരം , unsigned അക്ഷരം );
ശൂന്യം I2cWriteByte(unsigned അക്ഷരം , unsigned അക്ഷരം );
unsigned അക്ഷരം I2cReadByte(unsigned അക്ഷരം );
ശൂന്യം I2cWriteData(unsigned അക്ഷരം , unsigned അക്ഷരം );
unsigned അക്ഷരം I2cReadDataAck(unsigned അക്ഷരം );
unsigned അക്ഷരം I2cReadDataNack(unsigned അക്ഷരം );
ശൂന്യം I2cStart(unsigned അക്ഷരം );
ശൂന്യം I2cStop(unsigned അക്ഷരം );
ശൂന്യം I2c_Write_byte(unsigned അക്ഷരം, unsigned അക്ഷരം, unsigned അക്ഷരം, unsigned അക്ഷരം);
പൂർണ്ണസംഖ്യ I2c_Read_byte(unsigned അക്ഷരം ,unsigned അക്ഷരം , unsigned അക്ഷരം );
പൂർണ്ണസംഖ്യ I2c_shakti_readbytes(അക്ഷരം *, പൂർണ്ണസംഖ്യ , പൂർണ്ണസംഖ്യ , unsigned അക്ഷരം );
ശൂന്യം ReadAckForWrite(unsigned അക്ഷരം delay);
ശൂന്യം SendNackForRead(unsigned അക്ഷരം delay);
ശൂന്യം SendAckForRead(unsigned അക്ഷരം delay);

#endif
