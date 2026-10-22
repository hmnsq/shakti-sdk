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
 
#यदि_अपरिभाषितम् GPIO_I2C_H
#परिभाषय GPIO_I2C_H

#अन्तर्भाव "platform.h"
#अन्तर्भाव "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#परिभाषय I2C_SCL GPIO0 
#परिभाषय I2C_SDA GPIO1
#परिभाषय GPIOD_IS_अन्तर् 0
#परिभाषय GPIOD_IS_बहिर्गमनम् 1
#परिभाषय I2C_WRITE 0
#परिभाषय I2C_READ 1

// function prototype 
शून्य I2cInit();
शून्य I2c_Send_Slave_स्थानाङ्कः(अचिह्नित वर्ण , अचिह्नित वर्ण , अचिह्नित वर्ण );
शून्य I2cWriteByte(अचिह्नित वर्ण , अचिह्नित वर्ण );
अचिह्नित वर्ण I2cReadByte(अचिह्नित वर्ण );
शून्य I2c_Write_दत्त(अचिह्नित वर्ण , अचिह्नित वर्ण );
अचिह्नित वर्ण I2c_Read_दत्त_Ack(अचिह्नित वर्ण );
अचिह्नित वर्ण I2c_Read_दत्त_Nack(अचिह्नित वर्ण );
शून्य I2cStart(अचिह्नित वर्ण );
शून्य I2cStop(अचिह्नित वर्ण );
शून्य I2c_Write_byte(अचिह्नित वर्ण, अचिह्नित वर्ण, अचिह्नित वर्ण, अचिह्नित वर्ण);
पूर्णाङ्क I2c_Read_byte(अचिह्नित वर्ण ,अचिह्नित वर्ण , अचिह्नित वर्ण );
पूर्णाङ्क I2c_shakti_readbytes(वर्ण *, पूर्णाङ्क , पूर्णाङ्क , अचिह्नित वर्ण );
शून्य ReadAckForWrite(अचिह्नित वर्ण delay);
शून्य SendNackForRead(अचिह्नित वर्ण delay);
शून्य SendAckForRead(अचिह्नित वर्ण delay);

#यदि_अन्तः
