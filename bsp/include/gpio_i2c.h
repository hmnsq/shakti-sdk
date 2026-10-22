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
 
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GPIO_I2C_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_I2C_H

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_SCL GPIO0 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_SDA GPIO1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIOD_IS_ਵਿੱਚ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIOD_IS_ਬਾਹਰਲਾ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_WRITE 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_READ 1

// function prototype 
ਖਾਲੀ I2cInit();
ਖਾਲੀ I2c_Send_Slave_ਪਤਾ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ I2cWriteByte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2cReadByte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ I2c_Write_ਅੰਕੜੇ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2c_Read_ਅੰਕੜੇ_Ack(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2c_Read_ਅੰਕੜੇ_Nack(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ I2c_ਸ਼ੁਰੂ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ I2cStop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ I2c_Write_byte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ);
ਪੂਰਨ I2c_Read_byte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਪੂਰਨ I2c_shakti_readbytes(ਅੱਖਰ *, ਪੂਰਨ , ਪੂਰਨ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ );
ਖਾਲੀ ReadAckForWrite(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);
ਖਾਲੀ SendNackForRead(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);
ਖਾਲੀ SendAckForRead(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);

#ਜੇ_ਅੰਤ
