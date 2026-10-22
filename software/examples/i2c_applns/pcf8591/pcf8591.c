/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : pcf8591.c
 * Brief Description of file   : Contains the driver routines to configure and read pcf8591.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

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
@file   pcf8591.c
@brief  Contains the driver routines to configure and read pcf8591.
@detail I2C based routines to configures and read the adc value from pcf8591.
*/

#అన్తర్భావ <stdint.h>//Includes the definitions of standard input/output functions//
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు PCF8591_SLAVE_చిరునామా 0x90 // I2C bus address //doubt
#నిర్వచించు PCF8591_CONTROL_రిజిస్టరు_విలువ 0x04
#నిర్వచించు PCF8591_REG_స్థానభ్రంశం 0

#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91

#నిర్వచించు I2C i2c_instance[0]

/** @fn int read_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
 * @brief Reads the ADC value from PCF8591
 * @details Reads 4 ADC values from PCF8591 over I2C interface
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param length
 * @param delay
 * @return read status (zero on success)
 */
పూర్ణాంకం read_pcf8591_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *read_తాత్కాలిక, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;
//Writes the slave address for write
	i2c_send_slave_చిరునామా(i2c_instance, PCF8591_SLAVE_చిరునామా, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_చిరునామా(i2c_instance, PCF8591_SLAVE_చిరునామా, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
		*read_తాత్కాలిక = తాత్కాలిక;
		ఒకవేళ( i == (నిడివి_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_తాత్కాలిక++;
	}
	
	i2c_instance->control = I2C_STOP;
	తిరిగి 0;
}

/** @fn int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief WRites into PCF8591 Register
 * @details WRites the passed value into passed PCF8591 Register (address) over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param length
 * @param delay
 * @return Write status (Zero on success)
 */
పూర్ణాంకం write_pcf8591_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *write_విలువ, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
	i2c_send_slave_చిరునామా(i2c_instance, PCF8591_SLAVE_చిరునామా, I2C_WRITE, delay);
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		i2c_write_దత్తాంశం(i2c_instance,  ( *write_విలువ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;;
	తిరిగి 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
పూర్ణాంకం ప్రధాన()
{
	గుర్తులేని అక్షరం i = 0;
	పూర్ణాంకం timeout;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక_Read_విలువ = 0;
	గుర్తులేని దీర్ఘ delay = 1000;
	గుర్తులేని పూర్ణాంకం write_buf[7] = {0x00}, read_buf[7] = {0x00};
	గుర్తులేని అక్షరం నిడివి_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క, SCLK_లెక్క))
	{
			log_error("\tSomething Wrong In Initialization\n");
			తిరిగి -1;
	}
	లేకపోతే
		log_info("\tIntilization Happened Fine\n");
		నిడివి_2 = 1;
		write_buf[0] = PCF8591_CONTROL_రిజిస్టరు_విలువ;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], నిడివి_2, delay);
		log_debug("\n Write complete");
		నిడివి_2 = 5;
	అయితే(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_రిజిస్టరు_విలువ, &read_buf[0], నిడివి_2, 800);
			log_info("\n");
			కొరకు( i = 1; i < నిడివి_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	తిరిగి 0;
}

