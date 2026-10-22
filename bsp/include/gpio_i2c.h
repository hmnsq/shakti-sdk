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
 
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GPIO_I2C_H
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_I2C_H

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"

/* This code uses GPIO pins 0 & 1 and any GPIO pin can be used or
add a method to set the GPIO pins that are to be used  */
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_SCL GPIO0 
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_SDA GPIO1
#ವ್ಯಾಖ್ಯಾನಿಸು GPIOD_IS_ಒಳ 0
#ವ್ಯಾಖ್ಯಾನಿಸು GPIOD_IS_ಹೊರಹೋಗು 1
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_WRITE 0
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_READ 1

// function prototype 
ಶೂನ್ಯ I2cInit();
ಶೂನ್ಯ I2c_Send_Slave_ವಿಳಾಸ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ I2cWriteByte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2cReadByte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ I2c_Write_ದತ್ತಾಂಶ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2c_Read_ದತ್ತಾಂಶ_Ack(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2c_Read_ದತ್ತಾಂಶ_Nack(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ I2c_ಆರಂಭ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ I2cStop(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ I2c_Write_byte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ);
ಪೂರ್ಣಾಂಕ I2c_Read_byte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಪೂರ್ಣಾಂಕ I2c_shakti_readbytes(ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ , ಪೂರ್ಣಾಂಕ , ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ );
ಶೂನ್ಯ ReadAckForWrite(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay);
ಶೂನ್ಯ SendNackForRead(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay);
ಶೂನ್ಯ SendAckForRead(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay);

#ಆದರೆ_ಅಂತ್ಯ
