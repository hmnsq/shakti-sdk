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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "i2c.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "uart.h"

#define AT24C256_SLAVE_ADDRESS 0xA0 
#define DELAY_மதிப்பு 900
#define PRESCALER_மொத்தம் 0x1F
#define SCLK_மொத்தம் 0x91
#define I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
முழு read_eeprom_address(i2c_struct * i2c_instance, unsigned முழு address, uint8_t *read_data, unsigned long delay)
{
	unsigned எழுத்து read_buf[4] = {'\0'};
	முழு i = 0, j = 0, k = 0, status=0;
	unsigned எழுத்து temp = 0;

	//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &temp, delay);
	*read_data = temp;

	i2c_instance->control = I2C_STOP;
	திரும்பு 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
முழு read_eeprom_locations(i2c_struct * i2c_instance, uint16_t address, uint8_t *write_data, uint16_t length, uint32_t delay)
{
	முழு i = 0, j = 0, k = 0, status=0;
	unsigned எழுத்து temp = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	க்கு(i = 0; i < length; i++)
	{
		எனில் (0 == (address % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_data(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_data(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_data(i2c_instance, &temp, delay);
		}

		i2c_read_data(i2c_instance, write_data, delay);
		printf("\nread Value: %x", *write_data);

		எனில்( i == (length - 2) )
			i2c_instance->control = I2C_NACK;

		*write_data++;
		address ++;

		எனில்(0 == (address % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	திரும்பு 0;
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
முழு write_eeprom_address(i2c_struct * i2c_instance, uint16_t address, uint8_t write_மதிப்பு, unsigned long delay)
{
	முழு i = 0, j = 0, k = 0, status=0;
	unsigned முழு temp = 0;
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_data(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_data(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

	i2c_write_data(i2c_instance, ( write_மதிப்பு & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	திரும்பு 0;
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
முழு write_eeprom_locations(i2c_struct * i2c_instance, uint16_t address, uint8_t *write_மதிப்பு, uint16_t length, uint32_t delay)
{
	முழு i = 0, j = 0, k = 0, status=0;
	unsigned முழு temp = 0;

	க்கு(i = 0; i < length; i++)
	{
		எனில்(0 == (address % 64) )
		{
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_data(i2c_instance, (( address >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_data(i2c_instance, (( address >> 0 ) & 0xFF), delay);
		}
		i2c_write_data(i2c_instance, (*write_மதிப்பு++ & 0xff), delay);
		address ++;

		எனில்(0 == (address % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	திரும்பு 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
முழு முதன்மை()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t length = 0;
	uint16_t address = 0;
	uint8_t read_data = 0;
	uint8_t write_data = 0;
	uint8_t மொத்தம் = 0;
	uint8_t write_மதிப்பு[256] = {'\0'};
	uint8_t read_மதிப்பு[256] = {'\0'};
	uint32_t data_read = 0, data_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_data = 0x55;

	எனில்(read_data != write_data)
		printf("\n Values are not equal. RV: %x; WV: %x", read_data, write_data);
	இல்லையெனில்
		printf("\n Values are equal. RV: %x; WV: %x", read_data, write_data);

	எனில்(write_data != read_data)
		printf("\n Values are not equal. RV: %x; WV: %x", read_data, write_data);
	இல்லையெனில்
		printf("\n Values are equal. RV: %x; WV: %x", read_data, write_data);

	i2c_init();

	எனில்(config_i2c(I2C, PRESCALER_மொத்தம், SCLK_மொத்தம்))
	{
		log_error("\tSomething Wrong In Initialization\n");
		திரும்பு -1;
	}
	இல்லையெனில்
		log_info("\tI2C Intilization Success\n");

	length = 256;
	address = 0x00;
	write_data = 0x55;
	read_data = 0x0;

	write_eeprom_address(I2C, address , write_data, delay);
	log_debug("\n Write complete");

	read_eeprom_address(I2C, address, &read_data, delay);
	log_debug("\n Read Complete");
	read_data = 0x0;

	எனில்(write_data == read_data)
		log_info("\n AT24C256 EEPROM RW Passed");
	இல்லையெனில்
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_data, write_data);
	}

	க்கு(i = 0; i < length; i++)
	{
		write_மதிப்பு[i] = i;
		data_write = write_மதிப்பு[i];
		log_error("\n Write Value: %x", data_write);
	}

	write_eeprom_locations(I2C, address, &write_மதிப்பு, length, delay);
	address = 0;
	read_eeprom_locations(I2C, address, &read_மதிப்பு, length, delay);

	க்கு (i = 0; i < length; i++)
	{
		data_write = write_மதிப்பு[i];
		data_read = read_மதிப்பு[i];

		log_info("\n wv: %x; rv: %x", data_write, data_read );

		எனில்(write_மதிப்பு[i] != read_மதிப்பு[i])
			மொத்தம்++;
	}

	எனில்(0 != மொத்தம் )
		printf("\n Write failed");
	இல்லையெனில்
		printf("\n I2C test passed");

	திரும்பு 0;
}
