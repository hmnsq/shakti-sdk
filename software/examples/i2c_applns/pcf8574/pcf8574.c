/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : pcf8574.c
 * Brief Description of file   : Contains the driver routines to configure pcf8574.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file   pcf8574.c
@brief  Contains the driver routines to configure pcf8574.
@detail I2C based routines to configure pcf8574.
*/

#ಅನ್ತರ್ಭಾವ <stdint.h>//Includes the definitions of standard input/output functions//
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು PCF8574_SLAVE_ವಿಳಾಸ 0x4E
#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[0]
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91
#ವ್ಯಾಖ್ಯಾನಿಸು PCF8574_DEC_ಗಮ್ಯ_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PCF8574_REG_ಸ್ಥಾನಾಂತರ 0

/** @fn int write_pcf8574_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief  configures and write the pcf8574 
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
ಪೂರ್ಣಾಂಕ write_pcf8574_registers(i2c_struct * i2c_instance,ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, PCF8574_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( write_ಮೌಲ್ಯ & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	// delay_loop(800, 800);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn void main()
 * @brief configures and write the pcf8574 IO expander.
 * @details 
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 1000;

	ಬರೆ("\nPCF8574 IO Expander Test");

	i2c_init();

	ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ, SCLK_ಎಣಿಕೆ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ಹಿಂತಿರುಗಿ -1;
	}
		ಇಲ್ಲದಿದ್ದರೆ
		log_info("\tIntilization Happened Fine\n");
		ಬರೆ("\n Write he scomplete");
	ಆಗ(1)
	{
		ಬರೆ("\n Writing 0");
		write_pcf8574_registers(I2C, 0x00, 0x00, delay);
		delay_loop(2000, 5000);
		ಬರೆ("\n Writing 1");
		write_pcf8574_registers(I2C, 0x00, 0xFF, delay);
		delay_loop(2000, 5000);
	}
}




