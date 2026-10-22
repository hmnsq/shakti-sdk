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

#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#define I2C_SCL GPIO0 
#define I2C_SDA GPIO1
#define GPIOD_IS_IN 0
#define GPIOD_IS_OUT 1
#define I2C_WRITE 0
#define I2C_READ 1

// function prototype 
শূন্য I2cInit();
শূন্য I2cSendSlaveAddress(unsigned বর্ণ , unsigned বর্ণ , unsigned বর্ণ );
শূন্য I2cWriteByte(unsigned বর্ণ , unsigned বর্ণ );
unsigned বর্ণ I2cReadByte(unsigned বর্ণ );
শূন্য I2cWriteData(unsigned বর্ণ , unsigned বর্ণ );
unsigned বর্ণ I2cReadDataAck(unsigned বর্ণ );
unsigned বর্ণ I2cReadDataNack(unsigned বর্ণ );
শূন্য I2cStart(unsigned বর্ণ );
শূন্য I2cStop(unsigned বর্ণ );
শূন্য I2c_Write_byte(unsigned বর্ণ, unsigned বর্ণ, unsigned বর্ণ, unsigned বর্ণ);
পূর্ণাঙ্ক I2c_Read_byte(unsigned বর্ণ ,unsigned বর্ণ , unsigned বর্ণ );
পূর্ণাঙ্ক I2c_shakti_readbytes(বর্ণ *, পূর্ণাঙ্ক , পূর্ণাঙ্ক , unsigned বর্ণ );
শূন্য ReadAckForWrite(unsigned বর্ণ delay);
শূন্য SendNackForRead(unsigned বর্ণ delay);
শূন্য SendAckForRead(unsigned বর্ণ delay);

#endif
