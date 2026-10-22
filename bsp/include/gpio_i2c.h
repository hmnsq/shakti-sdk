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
 
#अगर_अघोषित GPIO_I2C_H
#घोषणा GPIO_I2C_H

#समावेश "platform.h"
#समावेश "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#घोषणा I2C_SCL GPIO0 
#घोषणा I2C_SDA GPIO1
#घोषणा GPIOD_IS_IN 0
#घोषणा GPIOD_IS_OUT 1
#घोषणा I2C_WRITE 0
#घोषणा I2C_READ 1

// function prototype 
व्योम I2cInit();
व्योम I2cSendSlaveAddress(अचिन्हित अक्षर , अचिन्हित अक्षर , अचिन्हित अक्षर );
व्योम I2cWriteByte(अचिन्हित अक्षर , अचिन्हित अक्षर );
अचिन्हित अक्षर I2cReadByte(अचिन्हित अक्षर );
व्योम I2c_Write_तथ्य(अचिन्हित अक्षर , अचिन्हित अक्षर );
अचिन्हित अक्षर I2c_Read_तथ्य_Ack(अचिन्हित अक्षर );
अचिन्हित अक्षर I2c_Read_तथ्य_Nack(अचिन्हित अक्षर );
व्योम I2cStart(अचिन्हित अक्षर );
व्योम I2cStop(अचिन्हित अक्षर );
व्योम I2c_Write_byte(अचिन्हित अक्षर, अचिन्हित अक्षर, अचिन्हित अक्षर, अचिन्हित अक्षर);
पूर्णांक I2c_Read_byte(अचिन्हित अक्षर ,अचिन्हित अक्षर , अचिन्हित अक्षर );
पूर्णांक I2c_shakti_readbytes(अक्षर *, पूर्णांक , पूर्णांक , अचिन्हित अक्षर );
व्योम ReadAckForWrite(अचिन्हित अक्षर delay);
व्योम SendNackForRead(अचिन्हित अक्षर delay);
व्योम SendAckForRead(अचिन्हित अक्षर delay);

#पूर्ण_अगर
