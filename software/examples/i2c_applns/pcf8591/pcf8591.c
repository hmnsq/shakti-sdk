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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>//Includes the definitions of standard input/output functions//
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8591_SLAVE_ਪਤਾ 0x90 // I2C bus address //doubt
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8591_CONTROL_ਰਜਿਸਟਰ_ਮੁੱਲ 0x04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCF8591_REG_ਵਿੱਥ 0

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[0]

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
ਪੂਰਨ read_pcf8591_registers(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *read_ਆਰਜ਼ੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_buf[4] = {'\0'};
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਰਜ਼ੀ = 0;
//Writes the slave address for write
	i2c_send_slave_ਪਤਾ(i2c_instance, PCF8591_SLAVE_ਪਤਾ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_ਪਤਾ(i2c_instance, PCF8591_SLAVE_ਪਤਾ, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);
		*read_ਆਰਜ਼ੀ = ਆਰਜ਼ੀ;
		ਜੇ( i == (ਲੰਮਾਈ_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_ਆਰਜ਼ੀ++;
	}
	
	i2c_instance->control = I2C_STOP;
	ਵਾਪਸ 0;
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
ਪੂਰਨ write_pcf8591_registers(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *write_ਮੁੱਲ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;
	i2c_send_slave_ਪਤਾ(i2c_instance, PCF8591_SLAVE_ਪਤਾ, I2C_WRITE, delay);
	i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ, delay);
	ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		i2c_write_ਅੰਕੜੇ(i2c_instance,  ( *write_ਮੁੱਲ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;;
	ਵਾਪਸ 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
ਪੂਰਨ ਮੁੱਖ()
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ i = 0;
	ਪੂਰਨ timeout;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ_Read_ਮੁੱਲ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay = 1000;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf[7] = {0x00}, read_buf[7] = {0x00};
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	ਜੇ(config_i2c(I2C, PRESCALER_ਗਿਣਤੀ, SCLK_ਗਿਣਤੀ))
	{
			log_error("\tSomething Wrong In Initialization\n");
			ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ
		log_info("\tIntilization Happened Fine\n");
		ਲੰਮਾਈ_2 = 1;
		write_buf[0] = PCF8591_CONTROL_ਰਜਿਸਟਰ_ਮੁੱਲ;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], ਲੰਮਾਈ_2, delay);
		log_debug("\n Write complete");
		ਲੰਮਾਈ_2 = 5;
	ਜਦੋਂ(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_ਰਜਿਸਟਰ_ਮੁੱਲ, &read_buf[0], ਲੰਮਾਈ_2, 800);
			log_info("\n");
			ਲਈ( i = 1; i < ਲੰਮਾਈ_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	ਵਾਪਸ 0;
}

