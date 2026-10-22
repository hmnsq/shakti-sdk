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
 
#నిర్వచితం_కాకపోతే GPIO_I2C_H
#నిర్వచించు GPIO_I2C_H

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#నిర్వచించు I2C_SCL GPIO0 
#నిర్వచించు I2C_SDA GPIO1
#నిర్వచించు GPIOD_IS_లోపల 0
#నిర్వచించు GPIOD_IS_బహిర్గతం 1
#నిర్వచించు I2C_WRITE 0
#నిర్వచించు I2C_READ 1

// function prototype 
శూన్య I2cInit();
శూన్య I2c_Send_Slave_చిరునామా(గుర్తులేని అక్షరం , గుర్తులేని అక్షరం , గుర్తులేని అక్షరం );
శూన్య I2cWriteByte(గుర్తులేని అక్షరం , గుర్తులేని అక్షరం );
గుర్తులేని అక్షరం I2cReadByte(గుర్తులేని అక్షరం );
శూన్య I2c_Write_దత్తాంశం(గుర్తులేని అక్షరం , గుర్తులేని అక్షరం );
గుర్తులేని అక్షరం I2c_Read_దత్తాంశం_Ack(గుర్తులేని అక్షరం );
గుర్తులేని అక్షరం I2c_Read_దత్తాంశం_Nack(గుర్తులేని అక్షరం );
శూన్య I2c_ప్రారంభం(గుర్తులేని అక్షరం );
శూన్య I2cStop(గుర్తులేని అక్షరం );
శూన్య I2c_Write_byte(గుర్తులేని అక్షరం, గుర్తులేని అక్షరం, గుర్తులేని అక్షరం, గుర్తులేని అక్షరం);
పూర్ణాంకం I2c_Read_byte(గుర్తులేని అక్షరం ,గుర్తులేని అక్షరం , గుర్తులేని అక్షరం );
పూర్ణాంకం I2c_shakti_readbytes(అక్షరం *, పూర్ణాంకం , పూర్ణాంకం , గుర్తులేని అక్షరం );
శూన్య ReadAckForWrite(గుర్తులేని అక్షరం delay);
శూన్య SendNackForRead(గుర్తులేని అక్షరం delay);
శూన్య SendAckForRead(గుర్తులేని అక్షరం delay);

#అయితే_ముగింపు
