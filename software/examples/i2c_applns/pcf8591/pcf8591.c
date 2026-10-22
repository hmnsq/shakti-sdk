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

#ضمن <stdint.h>//Includes the definitions of standard input/output functions//
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"

#تعریف_کن PCF8591_SLAVE_آدرس 0x90 // I2C bus address //doubt
#تعریف_کن PCF8591_CONTROL_ثبات_مقدار 0x04
#تعریف_کن PCF8591_REG_جابه_جایی 0

#تعریف_کن DELAY_مقدار 900
#تعریف_کن PRESCALER_شمار 0x1F
#تعریف_کن SCLK_شمار 0x91

#تعریف_کن I2C i2c_instance[0]

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
صحيح read_pcf8591_registers(i2c_struct * i2c_instance, بیعلامت صحيح reg_جابه_جایی, بیعلامت صحيح *read_موقت, بیعلامت حرف درازی_2, بیعلامت دراز delay)
{
	بیعلامت حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, وضعیت_2=0;
	بیعلامت حرف موقت = 0;
//Writes the slave address for write
	i2c_send_slave_آدرس(i2c_instance, PCF8591_SLAVE_آدرس, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_داده(i2c_instance, reg_جابه_جایی, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_آدرس(i2c_instance, PCF8591_SLAVE_آدرس, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_داده(i2c_instance, &موقت, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < درازی_2; i++)
	{
		i2c_read_داده(i2c_instance, &موقت, delay);
		*read_موقت = موقت;
		إذا( i == (درازی_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_موقت++;
	}
	
	i2c_instance->control = I2C_STOP;
	أرجع 0;
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
صحيح write_pcf8591_registers(i2c_struct * i2c_instance, بیعلامت صحيح reg_جابه_جایی, بیعلامت صحيح *write_مقدار, بیعلامت حرف درازی_2, بیعلامت دراز delay)
{
	صحيح i = 0, j = 0,  k = 0, وضعیت_2=0;
	بیعلامت صحيح موقت = 0;
	i2c_send_slave_آدرس(i2c_instance, PCF8591_SLAVE_آدرس, I2C_WRITE, delay);
	i2c_write_داده(i2c_instance, reg_جابه_جایی, delay);
	لكل(i = 0; i < درازی_2; i++)
	{
		i2c_write_داده(i2c_instance,  ( *write_مقدار++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;;
	أرجع 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
صحيح اصلی()
{
	بیعلامت حرف i = 0;
	صحيح timeout;
	بیعلامت صحيح موقت_Read_مقدار = 0;
	بیعلامت دراز delay = 1000;
	بیعلامت صحيح write_buf[7] = {0x00}, read_buf[7] = {0x00};
	بیعلامت حرف درازی_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_شمار, SCLK_شمار))
	{
			log_error("\tSomething Wrong In Initialization\n");
			أرجع -1;
	}
	وإلا
		log_info("\tIntilization Happened Fine\n");
		درازی_2 = 1;
		write_buf[0] = PCF8591_CONTROL_ثبات_مقدار;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], درازی_2, delay);
		log_debug("\n Write complete");
		درازی_2 = 5;
	طالما(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_ثبات_مقدار, &read_buf[0], درازی_2, 800);
			log_info("\n");
			لكل( i = 1; i < درازی_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	أرجع 0;
}

