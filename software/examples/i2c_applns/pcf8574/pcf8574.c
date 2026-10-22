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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>//Includes the definitions of standard input/output functions//
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8574_SLAVE_ਪਤਾ 0x4E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[0]
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8574_DEC_ਮੰਜ਼ਿਲ_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8574_REG_ਵਿੱਥ 0

/** @fn int write_pcf8574_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief  configures and write the pcf8574 
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
ਪੂਰਨ write_pcf8574_registers(i2c_struct * i2c_instance,ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_ਮੁੱਲ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;
	i2c_send_slave_ਪਤਾ(i2c_instance, PCF8574_SLAVE_ਪਤਾ, I2C_WRITE, delay);
	i2c_write_ਅੰਕੜੇ(i2c_instance,  ( write_ਮੁੱਲ & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	// delay_loop(800, 800);
	ਵਾਪਸ 0;
}

/** @fn void main()
 * @brief configures and write the pcf8574 IO expander.
 * @details 
 */
ਖਾਲੀ ਮੁੱਖ()
{
	ਪੂਰਨ timeout;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ_Read_ਮੁੱਲ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay = 1000;

	ਲਿਖੋ("\nPCF8574 IO Expander Test");

	i2c_init();

	ਜੇ(config_i2c(I2C, PRESCALER_ਗਿਣਤੀ, SCLK_ਗਿਣਤੀ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ਵਾਪਸ -1;
	}
		ਨਹੀਂਤਾਂ
		log_info("\tIntilization Happened Fine\n");
		ਲਿਖੋ("\n Write he scomplete");
	ਜਦੋਂ(1)
	{
		ਲਿਖੋ("\n Writing 0");
		write_pcf8574_registers(I2C, 0x00, 0x00, delay);
		delay_loop(2000, 5000);
		ਲਿਖੋ("\n Writing 1");
		write_pcf8574_registers(I2C, 0x00, 0xFF, delay);
		delay_loop(2000, 5000);
	}
}




