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

#تعریف_کړه PCF8591_SLAVE_پته 0x90 // I2C bus address //doubt
#تعریف_کړه PCF8591_CONTROL_ثبتوونکی_ارزښت 0x04
#تعریف_کړه PCF8591_REG_دننه_واټن 0

#تعریف_کړه DELAY_ارزښت 900
#تعریف_کړه PRESCALER_شمېر 0x1F
#تعریف_کړه SCLK_شمېر 0x91

#تعریف_کړه I2C i2c_instance[0]

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
صحيح read_pcf8591_registers(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه صحيح *read_لنډمهاله, بینښه حرف اوږدتیا_2, بینښه اوږد delay)
{
	بینښه حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بینښه حرف لنډمهاله = 0;
//Writes the slave address for write
	i2c_send_slave_پته(i2c_instance, PCF8591_SLAVE_پته, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_پته(i2c_instance, PCF8591_SLAVE_پته, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
		*read_لنډمهاله = لنډمهاله;
		إذا( i == (اوږدتیا_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_لنډمهاله++;
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
صحيح write_pcf8591_registers(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه صحيح *write_ارزښت, بینښه حرف اوږدتیا_2, بینښه اوږد delay)
{
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بینښه صحيح لنډمهاله = 0;
	i2c_send_slave_پته(i2c_instance, PCF8591_SLAVE_پته, I2C_WRITE, delay);
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		i2c_write_معلومات(i2c_instance,  ( *write_ارزښت++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
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
صحيح اصلي()
{
	بینښه حرف i = 0;
	صحيح timeout;
	بینښه صحيح لنډمهاله_Read_ارزښت = 0;
	بینښه اوږد delay = 1000;
	بینښه صحيح write_buf[7] = {0x00}, read_buf[7] = {0x00};
	بینښه حرف اوږدتیا_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_شمېر, SCLK_شمېر))
	{
			log_error("\tSomething Wrong In Initialization\n");
			أرجع -1;
	}
	وإلا
		log_info("\tIntilization Happened Fine\n");
		اوږدتیا_2 = 1;
		write_buf[0] = PCF8591_CONTROL_ثبتوونکی_ارزښت;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], اوږدتیا_2, delay);
		log_debug("\n Write complete");
		اوږدتیا_2 = 5;
	طالما(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_ثبتوونکی_ارزښت, &read_buf[0], اوږدتیا_2, 800);
			log_info("\n");
			لكل( i = 1; i < اوږدتیا_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	أرجع 0;
}

