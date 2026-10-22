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
 
#که_نه_تعریف_شوی GPIO_I2C_H
#تعریف_کړه GPIO_I2C_H

#ضمن "platform.h"
#ضمن "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#تعریف_کړه I2C_SCL GPIO0 
#تعریف_کړه I2C_SDA GPIO1
#تعریف_کړه GPIOD_IS_دننه 0
#تعریف_کړه GPIOD_IS_بهر 1
#تعریف_کړه I2C_WRITE 0
#تعریف_کړه I2C_READ 1

// function prototype 
فراغ I2cInit();
فراغ I2c_Send_Slave_پته(بینښه حرف , بینښه حرف , بینښه حرف );
فراغ I2cWriteByte(بینښه حرف , بینښه حرف );
بینښه حرف I2cReadByte(بینښه حرف );
فراغ I2c_Write_معلومات(بینښه حرف , بینښه حرف );
بینښه حرف I2c_Read_معلومات_Ack(بینښه حرف );
بینښه حرف I2c_Read_معلومات_Nack(بینښه حرف );
فراغ I2c_پیل(بینښه حرف );
فراغ I2cStop(بینښه حرف );
فراغ I2c_Write_byte(بینښه حرف, بینښه حرف, بینښه حرف, بینښه حرف);
صحيح I2c_Read_byte(بینښه حرف ,بینښه حرف , بینښه حرف );
صحيح I2c_shakti_readbytes(حرف *, صحيح , صحيح , بینښه حرف );
فراغ ReadAckForWrite(بینښه حرف delay);
فراغ SendNackForRead(بینښه حرف delay);
فراغ SendAckForRead(بینښه حرف delay);

#د_که_پای
