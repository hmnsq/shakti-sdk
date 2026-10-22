/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : pcf8591.c
 * Brief Description of file   : Contains the driver routines to configure
 and read pcf8591.
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
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/
/**
  @file  at24c256.c
  @brief Contains the driver routines to write and read all locations of AT24C256.
  @detail I2C based routines to write and read all locations of AT24C256.
 */

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు AT24_C256_SLAVE_చిరునామా 0xA0 
#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91
#నిర్వచించు I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
పూర్ణాంకం read_eeprom_చిరునామా(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం చిరునామా, uint8_t *read_దత్తాంశం_2, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0, k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;

	//Writes the slave address for write
	i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
	*read_దత్తాంశం_2 = తాత్కాలిక;

	i2c_instance->control = I2C_STOP;
	తిరిగి 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
పూర్ణాంకం read_eeprom_locations(i2c_struct * i2c_instance, uint16_t చిరునామా, uint8_t *write_దత్తాంశం_2, uint16_t నిడివి_2, uint32_t delay)
{
	పూర్ణాంకం i = 0, j = 0, k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		ఒకవేళ (0 == (చిరునామా % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
		}

		i2c_read_దత్తాంశం(i2c_instance, write_దత్తాంశం_2, delay);
		రాయి("\nread Value: %x", *write_దత్తాంశం_2);

		ఒకవేళ( i == (నిడివి_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_దత్తాంశం_2++;
		చిరునామా ++;

		ఒకవేళ(0 == (చిరునామా % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	తిరిగి 0;
}

/** @fn int write_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned int *write_value, unsigned long delay)
 * @brief Writes into AT24C256 Register
 * @details Writes the passed data into passed AT24C256 address over I2C interface.
 * @param i2c_struct*
 * @param address
 * @param write_value
 * @param delay
 * @return Write status (Zero on success)
 */
పూర్ణాంకం write_eeprom_చిరునామా(i2c_struct * i2c_instance, uint16_t చిరునామా, uint8_t write_విలువ, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0, k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
	i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, ( ( చిరునామా >> 0 ) & 0xFF), delay);

	i2c_write_దత్తాంశం(i2c_instance, ( write_విలువ & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	తిరిగి 0;
}

/** @fn int write_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned int *write_value, unsigned long delay)
 * @brief Writes into passed address of AT24C256
 * @details Writes the passed data into passed AT24C256 address over I2C interface.
 * @param i2c_struct*
 * @param address
 * @param write_value
 * @param delay
 * @return Write status (Zero on success)
 */
పూర్ణాంకం write_eeprom_locations(i2c_struct * i2c_instance, uint16_t చిరునామా, uint8_t *write_విలువ, uint16_t నిడివి_2, uint32_t delay)
{
	పూర్ణాంకం i = 0, j = 0, k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;

	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		ఒకవేళ(0 == (చిరునామా % 64) )
		{
			i2c_send_slave_చిరునామా(i2c_instance, AT24_C256_SLAVE_చిరునామా, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_దత్తాంశం(i2c_instance, (( చిరునామా >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_దత్తాంశం(i2c_instance, (( చిరునామా >> 0 ) & 0xFF), delay);
		}
		i2c_write_దత్తాంశం(i2c_instance, (*write_విలువ++ & 0xff), delay);
		చిరునామా ++;

		ఒకవేళ(0 == (చిరునామా % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	తిరిగి 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
పూర్ణాంకం ప్రధాన()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t నిడివి_2 = 0;
	uint16_t చిరునామా = 0;
	uint8_t read_దత్తాంశం_2 = 0;
	uint8_t write_దత్తాంశం_2 = 0;
	uint8_t లెక్క = 0;
	uint8_t write_విలువ[256] = {'\0'};
	uint8_t read_విలువ[256] = {'\0'};
	uint32_t దత్తాంశం_read = 0, దత్తాంశం_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_దత్తాంశం_2 = 0x55;

	ఒకవేళ(read_దత్తాంశం_2 != write_దత్తాంశం_2)
		రాయి("\n Values are not equal. RV: %x; WV: %x", read_దత్తాంశం_2, write_దత్తాంశం_2);
	లేకపోతే
		రాయి("\n Values are equal. RV: %x; WV: %x", read_దత్తాంశం_2, write_దత్తాంశం_2);

	ఒకవేళ(write_దత్తాంశం_2 != read_దత్తాంశం_2)
		రాయి("\n Values are not equal. RV: %x; WV: %x", read_దత్తాంశం_2, write_దత్తాంశం_2);
	లేకపోతే
		రాయి("\n Values are equal. RV: %x; WV: %x", read_దత్తాంశం_2, write_దత్తాంశం_2);

	i2c_init();

	ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క, SCLK_లెక్క))
	{
		log_error("\tSomething Wrong In Initialization\n");
		తిరిగి -1;
	}
	లేకపోతే
		log_info("\tI2C Intilization Success\n");

	నిడివి_2 = 256;
	చిరునామా = 0x00;
	write_దత్తాంశం_2 = 0x55;
	read_దత్తాంశం_2 = 0x0;

	write_eeprom_చిరునామా(I2C, చిరునామా , write_దత్తాంశం_2, delay);
	log_debug("\n Write complete");

	read_eeprom_చిరునామా(I2C, చిరునామా, &read_దత్తాంశం_2, delay);
	log_debug("\n Read Complete");
	read_దత్తాంశం_2 = 0x0;

	ఒకవేళ(write_దత్తాంశం_2 == read_దత్తాంశం_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	లేకపోతే
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_దత్తాంశం_2, write_దత్తాంశం_2);
	}

	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		write_విలువ[i] = i;
		దత్తాంశం_write = write_విలువ[i];
		log_error("\n Write Value: %x", దత్తాంశం_write);
	}

	write_eeprom_locations(I2C, చిరునామా, &write_విలువ, నిడివి_2, delay);
	చిరునామా = 0;
	read_eeprom_locations(I2C, చిరునామా, &read_విలువ, నిడివి_2, delay);

	కొరకు (i = 0; i < నిడివి_2; i++)
	{
		దత్తాంశం_write = write_విలువ[i];
		దత్తాంశం_read = read_విలువ[i];

		log_info("\n wv: %x; rv: %x", దత్తాంశం_write, దత్తాంశం_read );

		ఒకవేళ(write_విలువ[i] != read_విలువ[i])
			లెక్క++;
	}

	ఒకవేళ(0 != లెక్క )
		రాయి("\n Write failed");
	లేకపోతే
		రాయి("\n I2C test passed");

	తిరిగి 0;
}
