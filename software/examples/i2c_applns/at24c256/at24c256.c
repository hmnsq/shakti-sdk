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

#شامل <stdint.h>
#شامل "i2c.h"
#شامل "log.h"
#شامل "uart.h"

#تعریف_کرو AT24_C256_SLAVE_پتہ 0xA0 
#تعریف_کرو DELAY_قدر 900
#تعریف_کرو PRESCALER_گنتی 0x1F
#تعریف_کرو SCLK_گنتی 0x91
#تعریف_کرو I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
صحیح read_eeprom_پتہ(i2c_struct * i2c_instance, غیرعلامتی صحیح پتہ, uint8_t *read_ڈیٹا_2, غیرعلامتی طویل delay)
{
	غیرعلامتی حرف read_buf[4] = {'\0'};
	صحیح i = 0, j = 0, k = 0, حالت_3=0;
	غیرعلامتی حرف عارضی = 0;

	//Writes the slave address for write
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ڈیٹا(i2c_instance, &عارضی, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ڈیٹا(i2c_instance, &عارضی, delay);
	*read_ڈیٹا_2 = عارضی;

	i2c_instance->control = I2C_STOP;
	واپس 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
صحیح read_eeprom_locations(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t *write_ڈیٹا_2, uint16_t لمبائی_2, uint32_t delay)
{
	صحیح i = 0, j = 0, k = 0, حالت_3=0;
	غیرعلامتی حرف عارضی = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	برائے(i = 0; i < لمبائی_2; i++)
	{
		اگر (0 == (پتہ % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_ڈیٹا(i2c_instance, &عارضی, delay);
		}

		i2c_read_ڈیٹا(i2c_instance, write_ڈیٹا_2, delay);
		لکھو("\nread Value: %x", *write_ڈیٹا_2);

		اگر( i == (لمبائی_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_ڈیٹا_2++;
		پتہ ++;

		اگر(0 == (پتہ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	واپس 0;
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
صحیح write_eeprom_پتہ(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t write_قدر, غیرعلامتی طویل delay)
{
	صحیح i = 0, j = 0, k = 0, حالت_3=0;
	غیرعلامتی صحیح عارضی = 0;
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_ڈیٹا(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

	i2c_write_ڈیٹا(i2c_instance, ( write_قدر & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	واپس 0;
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
صحیح write_eeprom_locations(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t *write_قدر, uint16_t لمبائی_2, uint32_t delay)
{
	صحیح i = 0, j = 0, k = 0, حالت_3=0;
	غیرعلامتی صحیح عارضی = 0;

	برائے(i = 0; i < لمبائی_2; i++)
	{
		اگر(0 == (پتہ % 64) )
		{
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ڈیٹا(i2c_instance, (( پتہ >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_ڈیٹا(i2c_instance, (( پتہ >> 0 ) & 0xFF), delay);
		}
		i2c_write_ڈیٹا(i2c_instance, (*write_قدر++ & 0xff), delay);
		پتہ ++;

		اگر(0 == (پتہ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	واپس 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
صحیح مین()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t لمبائی_2 = 0;
	uint16_t پتہ = 0;
	uint8_t read_ڈیٹا_2 = 0;
	uint8_t write_ڈیٹا_2 = 0;
	uint8_t گنتی = 0;
	uint8_t write_قدر[256] = {'\0'};
	uint8_t read_قدر[256] = {'\0'};
	uint32_t ڈیٹا_read = 0, ڈیٹا_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_ڈیٹا_2 = 0x55;

	اگر(read_ڈیٹا_2 != write_ڈیٹا_2)
		لکھو("\n Values are not equal. RV: %x; WV: %x", read_ڈیٹا_2, write_ڈیٹا_2);
	ورنہ
		لکھو("\n Values are equal. RV: %x; WV: %x", read_ڈیٹا_2, write_ڈیٹا_2);

	اگر(write_ڈیٹا_2 != read_ڈیٹا_2)
		لکھو("\n Values are not equal. RV: %x; WV: %x", read_ڈیٹا_2, write_ڈیٹا_2);
	ورنہ
		لکھو("\n Values are equal. RV: %x; WV: %x", read_ڈیٹا_2, write_ڈیٹا_2);

	i2c_init();

	اگر(config_i2c(I2C, PRESCALER_گنتی, SCLK_گنتی))
	{
		log_error("\tSomething Wrong In Initialization\n");
		واپس -1;
	}
	ورنہ
		log_info("\tI2C Intilization Success\n");

	لمبائی_2 = 256;
	پتہ = 0x00;
	write_ڈیٹا_2 = 0x55;
	read_ڈیٹا_2 = 0x0;

	write_eeprom_پتہ(I2C, پتہ , write_ڈیٹا_2, delay);
	log_debug("\n Write complete");

	read_eeprom_پتہ(I2C, پتہ, &read_ڈیٹا_2, delay);
	log_debug("\n Read Complete");
	read_ڈیٹا_2 = 0x0;

	اگر(write_ڈیٹا_2 == read_ڈیٹا_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	ورنہ
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_ڈیٹا_2, write_ڈیٹا_2);
	}

	برائے(i = 0; i < لمبائی_2; i++)
	{
		write_قدر[i] = i;
		ڈیٹا_write = write_قدر[i];
		log_error("\n Write Value: %x", ڈیٹا_write);
	}

	write_eeprom_locations(I2C, پتہ, &write_قدر, لمبائی_2, delay);
	پتہ = 0;
	read_eeprom_locations(I2C, پتہ, &read_قدر, لمبائی_2, delay);

	برائے (i = 0; i < لمبائی_2; i++)
	{
		ڈیٹا_write = write_قدر[i];
		ڈیٹا_read = read_قدر[i];

		log_info("\n wv: %x; rv: %x", ڈیٹا_write, ڈیٹا_read );

		اگر(write_قدر[i] != read_قدر[i])
			گنتی++;
	}

	اگر(0 != گنتی )
		لکھو("\n Write failed");
	ورنہ
		لکھو("\n I2C test passed");

	واپس 0;
}
