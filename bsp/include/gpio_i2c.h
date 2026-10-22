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

#include "platform.h"
#include "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#define I2C_SCL GPIO0 
#define I2C_SDA GPIO1
#define GPIOD_IS_IN 0
#define GPIOD_IS_OUT 1
#define I2C_WRITE 0
#define I2C_READ 1

// function prototype 
void I2cInit();
void I2cSendSlaveAddress(unsigned var_na , unsigned var_na , unsigned var_na );
void I2cWriteByte(unsigned var_na , unsigned var_na );
unsigned var_na I2cReadByte(unsigned var_na );
void I2cWriteData(unsigned var_na , unsigned var_na );
unsigned var_na I2cReadDataAck(unsigned var_na );
unsigned var_na I2cReadDataNack(unsigned var_na );
void I2cStart(unsigned var_na );
void I2cStop(unsigned var_na );
void I2c_Write_byte(unsigned var_na, unsigned var_na, unsigned var_na, unsigned var_na);
puur_naa_nka I2c_Read_byte(unsigned var_na ,unsigned var_na , unsigned var_na );
puur_naa_nka I2c_shakti_readbytes(var_na *, puur_naa_nka , puur_naa_nka , unsigned var_na );
void ReadAckForWrite(unsigned var_na delay);
void SendNackForRead(unsigned var_na delay);
void SendAckForRead(unsigned var_na delay);

#endif
