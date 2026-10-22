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

#ضمن <stdint.h>
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"

#تعریف_کن AT24_C256_SLAVE_آدرس 0xA0 
#تعریف_کن DELAY_مقدار 900
#تعریف_کن PRESCALER_شمار 0x1F
#تعریف_کن SCLK_شمار 0x91
#تعریف_کن I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
صحيح read_eeprom_آدرس(i2c_struct * i2c_instance, بیعلامت صحيح آدرس, uint8_t *read_داده_2, بیعلامت دراز delay)
{
	بیعلامت حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0, k = 0, وضعیت_2=0;
	بیعلامت حرف موقت = 0;

	//Writes the slave address for write
	i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_داده(i2c_instance, ( ( آدرس >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_داده(i2c_instance, ( ( آدرس >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_داده(i2c_instance, &موقت, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_داده(i2c_instance, &موقت, delay);
	*read_داده_2 = موقت;

	i2c_instance->control = I2C_STOP;
	أرجع 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
صحيح read_eeprom_locations(i2c_struct * i2c_instance, uint16_t آدرس, uint8_t *write_داده_2, uint16_t درازی_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, وضعیت_2=0;
	بیعلامت حرف موقت = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < درازی_2; i++)
	{
		إذا (0 == (آدرس % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_داده(i2c_instance, ( ( آدرس >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_داده(i2c_instance, ( ( آدرس >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_داده(i2c_instance, &موقت, delay);
		}

		i2c_read_داده(i2c_instance, write_داده_2, delay);
		چاپ_کن("\nread Value: %x", *write_داده_2);

		إذا( i == (درازی_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_داده_2++;
		آدرس ++;

		إذا(0 == (آدرس % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	أرجع 0;
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
صحيح write_eeprom_آدرس(i2c_struct * i2c_instance, uint16_t آدرس, uint8_t write_مقدار, بیعلامت دراز delay)
{
	صحيح i = 0, j = 0, k = 0, وضعیت_2=0;
	بیعلامت صحيح موقت = 0;
	i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_داده(i2c_instance, ( ( آدرس >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_داده(i2c_instance, ( ( آدرس >> 0 ) & 0xFF), delay);

	i2c_write_داده(i2c_instance, ( write_مقدار & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	أرجع 0;
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
صحيح write_eeprom_locations(i2c_struct * i2c_instance, uint16_t آدرس, uint8_t *write_مقدار, uint16_t درازی_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, وضعیت_2=0;
	بیعلامت صحيح موقت = 0;

	لكل(i = 0; i < درازی_2; i++)
	{
		إذا(0 == (آدرس % 64) )
		{
			i2c_send_slave_آدرس(i2c_instance, AT24_C256_SLAVE_آدرس, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_داده(i2c_instance, (( آدرس >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_داده(i2c_instance, (( آدرس >> 0 ) & 0xFF), delay);
		}
		i2c_write_داده(i2c_instance, (*write_مقدار++ & 0xff), delay);
		آدرس ++;

		إذا(0 == (آدرس % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	أرجع 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
صحيح اصلی()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t درازی_2 = 0;
	uint16_t آدرس = 0;
	uint8_t read_داده_2 = 0;
	uint8_t write_داده_2 = 0;
	uint8_t شمار = 0;
	uint8_t write_مقدار[256] = {'\0'};
	uint8_t read_مقدار[256] = {'\0'};
	uint32_t داده_read = 0, داده_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_داده_2 = 0x55;

	إذا(read_داده_2 != write_داده_2)
		چاپ_کن("\n Values are not equal. RV: %x; WV: %x", read_داده_2, write_داده_2);
	وإلا
		چاپ_کن("\n Values are equal. RV: %x; WV: %x", read_داده_2, write_داده_2);

	إذا(write_داده_2 != read_داده_2)
		چاپ_کن("\n Values are not equal. RV: %x; WV: %x", read_داده_2, write_داده_2);
	وإلا
		چاپ_کن("\n Values are equal. RV: %x; WV: %x", read_داده_2, write_داده_2);

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_شمار, SCLK_شمار))
	{
		log_error("\tSomething Wrong In Initialization\n");
		أرجع -1;
	}
	وإلا
		log_info("\tI2C Intilization Success\n");

	درازی_2 = 256;
	آدرس = 0x00;
	write_داده_2 = 0x55;
	read_داده_2 = 0x0;

	write_eeprom_آدرس(I2C, آدرس , write_داده_2, delay);
	log_debug("\n Write complete");

	read_eeprom_آدرس(I2C, آدرس, &read_داده_2, delay);
	log_debug("\n Read Complete");
	read_داده_2 = 0x0;

	إذا(write_داده_2 == read_داده_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	وإلا
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_داده_2, write_داده_2);
	}

	لكل(i = 0; i < درازی_2; i++)
	{
		write_مقدار[i] = i;
		داده_write = write_مقدار[i];
		log_error("\n Write Value: %x", داده_write);
	}

	write_eeprom_locations(I2C, آدرس, &write_مقدار, درازی_2, delay);
	آدرس = 0;
	read_eeprom_locations(I2C, آدرس, &read_مقدار, درازی_2, delay);

	لكل (i = 0; i < درازی_2; i++)
	{
		داده_write = write_مقدار[i];
		داده_read = read_مقدار[i];

		log_info("\n wv: %x; rv: %x", داده_write, داده_read );

		إذا(write_مقدار[i] != read_مقدار[i])
			شمار++;
	}

	إذا(0 != شمار )
		چاپ_کن("\n Write failed");
	وإلا
		چاپ_کن("\n I2C test passed");

	أرجع 0;
}
