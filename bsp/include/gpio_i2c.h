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
 
#جيڪڏهن_وصف_نه_ٿيل GPIO_I2C_H
#وصف_ڪريو GPIO_I2C_H

#ضمن "platform.h"
#ضمن "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#وصف_ڪريو I2C_SCL GPIO0 
#وصف_ڪريو I2C_SDA GPIO1
#وصف_ڪريو GPIOD_IS_اندريون 0
#وصف_ڪريو GPIOD_IS_ٻاهريون 1
#وصف_ڪريو I2C_WRITE 0
#وصف_ڪريو I2C_READ 1

// function prototype 
فراغ I2cInit();
فراغ I2c_Send_Slave_پتو(بنانشان حرف , بنانشان حرف , بنانشان حرف );
فراغ I2cWriteByte(بنانشان حرف , بنانشان حرف );
بنانشان حرف I2cReadByte(بنانشان حرف );
فراغ I2c_Write_معلومات(بنانشان حرف , بنانشان حرف );
بنانشان حرف I2c_Read_معلومات_Ack(بنانشان حرف );
بنانشان حرف I2c_Read_معلومات_Nack(بنانشان حرف );
فراغ I2c_شروعات(بنانشان حرف );
فراغ I2cStop(بنانشان حرف );
فراغ I2c_Write_byte(بنانشان حرف, بنانشان حرف, بنانشان حرف, بنانشان حرف);
صحيح I2c_Read_byte(بنانشان حرف ,بنانشان حرف , بنانشان حرف );
صحيح I2c_shakti_readbytes(حرف *, صحيح , صحيح , بنانشان حرف );
فراغ ReadAckForWrite(بنانشان حرف delay);
فراغ SendNackForRead(بنانشان حرف delay);
فراغ SendAckForRead(بنانشان حرف delay);

#جيڪڏهن_پورو
