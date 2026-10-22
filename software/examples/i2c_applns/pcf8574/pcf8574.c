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

#అన్తర్భావ <stdint.h>//Includes the definitions of standard input/output functions//
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు PCF8574_SLAVE_చిరునామా 0x4E
#నిర్వచించు I2C i2c_instance[0]
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91
#నిర్వచించు PCF8574_DEC_గమ్యం_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PCF8574_REG_స్థానభ్రంశం 0

/** @fn int write_pcf8574_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief  configures and write the pcf8574 
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
పూర్ణాంకం write_pcf8574_registers(i2c_struct * i2c_instance,గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం write_విలువ, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
	i2c_send_slave_చిరునామా(i2c_instance, PCF8574_SLAVE_చిరునామా, I2C_WRITE, delay);
	i2c_write_దత్తాంశం(i2c_instance,  ( write_విలువ & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	// delay_loop(800, 800);
	తిరిగి 0;
}

/** @fn void main()
 * @brief configures and write the pcf8574 IO expander.
 * @details 
 */
శూన్య ప్రధాన()
{
	పూర్ణాంకం timeout;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక_Read_విలువ = 0;
	గుర్తులేని దీర్ఘ delay = 1000;

	రాయి("\nPCF8574 IO Expander Test");

	i2c_init();

	ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క, SCLK_లెక్క))
	{
		log_error("\tSomething Wrong In Initialization\n");
		తిరిగి -1;
	}
		లేకపోతే
		log_info("\tIntilization Happened Fine\n");
		రాయి("\n Write he scomplete");
	అయితే(1)
	{
		రాయి("\n Writing 0");
		write_pcf8574_registers(I2C, 0x00, 0x00, delay);
		delay_loop(2000, 5000);
		రాయి("\n Writing 1");
		write_pcf8574_registers(I2C, 0x00, 0xFF, delay);
		delay_loop(2000, 5000);
	}
}




