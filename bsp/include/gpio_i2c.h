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
 
#اگر_غیر_تعریف_شدہ GPIO_I2C_H
#تعریف_کرو GPIO_I2C_H

#شامل "platform.h"
#شامل "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#تعریف_کرو I2C_SCL GPIO0 
#تعریف_کرو I2C_SDA GPIO1
#تعریف_کرو GPIOD_IS_اندر 0
#تعریف_کرو GPIOD_IS_برآمد 1
#تعریف_کرو I2C_WRITE 0
#تعریف_کرو I2C_READ 1

// function prototype 
خالی I2cInit();
خالی I2c_Send_Slave_پتہ(غیرعلامتی حرف , غیرعلامتی حرف , غیرعلامتی حرف );
خالی I2cWriteByte(غیرعلامتی حرف , غیرعلامتی حرف );
غیرعلامتی حرف I2cReadByte(غیرعلامتی حرف );
خالی I2c_Write_ڈیٹا(غیرعلامتی حرف , غیرعلامتی حرف );
غیرعلامتی حرف I2c_Read_ڈیٹا_Ack(غیرعلامتی حرف );
غیرعلامتی حرف I2c_Read_ڈیٹا_Nack(غیرعلامتی حرف );
خالی I2c_آغاز(غیرعلامتی حرف );
خالی I2cStop(غیرعلامتی حرف );
خالی I2c_Write_byte(غیرعلامتی حرف, غیرعلامتی حرف, غیرعلامتی حرف, غیرعلامتی حرف);
صحیح I2c_Read_byte(غیرعلامتی حرف ,غیرعلامتی حرف , غیرعلامتی حرف );
صحیح I2c_shakti_readbytes(حرف *, صحیح , صحیح , غیرعلامتی حرف );
خالی ReadAckForWrite(غیرعلامتی حرف delay);
خالی SendNackForRead(غیرعلامتی حرف delay);
خالی SendAckForRead(غیرعلامتی حرف delay);

#اگر_ختم
