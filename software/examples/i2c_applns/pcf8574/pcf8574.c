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

#ضمن <stdint.h>//Includes the definitions of standard input/output functions//
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"

#تعریف_کرو PCF8574_SLAVE_پتہ 0x4E
#تعریف_کرو I2C i2c_instance[0]
#تعریف_کرو PRESCALER_گنتی 0x1F
#تعریف_کرو SCLK_گنتی 0x91
#تعریف_کرو PCF8574_DEC_منزل_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#تعریف_کرو DELAY_قدر 900
#تعریف_کرو PCF8574_REG_وتھ 0

/** @fn int write_pcf8574_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief  configures and write the pcf8574 
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
صحيح write_pcf8574_registers(i2c_struct * i2c_instance,بنانشانی صحيح reg_وتھ, بنانشانی صحيح write_قدر, بنانشانی لما delay)
{
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی صحيح عارضی = 0;
	i2c_send_slave_پتہ(i2c_instance, PCF8574_SLAVE_پتہ, I2C_WRITE, delay);
	i2c_write_انکڑے(i2c_instance,  ( write_قدر & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	// delay_loop(800, 800);
	أرجع 0;
}

/** @fn void main()
 * @brief configures and write the pcf8574 IO expander.
 * @details 
 */
فراغ مکھ()
{
	صحيح timeout;
	بنانشانی صحيح عارضی_Read_قدر = 0;
	بنانشانی لما delay = 1000;

	لکھو("\nPCF8574 IO Expander Test");

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_گنتی, SCLK_گنتی))
	{
		log_error("\tSomething Wrong In Initialization\n");
		أرجع -1;
	}
		وإلا
		log_info("\tIntilization Happened Fine\n");
		لکھو("\n Write he scomplete");
	طالما(1)
	{
		لکھو("\n Writing 0");
		write_pcf8574_registers(I2C, 0x00, 0x00, delay);
		delay_loop(2000, 5000);
		لکھو("\n Writing 1");
		write_pcf8574_registers(I2C, 0x00, 0xFF, delay);
		delay_loop(2000, 5000);
	}
}




