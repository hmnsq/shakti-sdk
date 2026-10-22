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

#ضمن "platform.h"
#ضمن "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#define I2C_SCL GPIO0 
#define I2C_SDA GPIO1
#define GPIOD_IS_IN 0
#define GPIOD_IS_OUT 1
#define I2C_WRITE 0
#define I2C_READ 1

// function prototype 
فراغ I2cInit();
فراغ I2cSendSlaveAddress(unsigned حرف , unsigned حرف , unsigned حرف );
فراغ I2cWriteByte(unsigned حرف , unsigned حرف );
unsigned حرف I2cReadByte(unsigned حرف );
فراغ I2cWriteData(unsigned حرف , unsigned حرف );
unsigned حرف I2cReadDataAck(unsigned حرف );
unsigned حرف I2cReadDataNack(unsigned حرف );
فراغ I2cStart(unsigned حرف );
فراغ I2cStop(unsigned حرف );
فراغ I2c_Write_byte(unsigned حرف, unsigned حرف, unsigned حرف, unsigned حرف);
صحيح I2c_Read_byte(unsigned حرف ,unsigned حرف , unsigned حرف );
صحيح I2c_shakti_readbytes(حرف *, صحيح , صحيح , unsigned حرف );
فراغ ReadAckForWrite(unsigned حرف delay);
فراغ SendNackForRead(unsigned حرف delay);
فراغ SendAckForRead(unsigned حرف delay);

#endif
