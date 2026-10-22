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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "i2c.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "uart.h"

#define AT24C256_SLAVE_ADDRESS 0xA0 
#define DELAY_মান 900
#define PRESCALER_গুনতি 0x1F
#define SCLK_গুনতি 0x91
#define I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
পূর্ণসংখ্যা read_eeprom_address(i2c_struct * i2c_instance, unsigned পূর্ণসংখ্যা address, uint8_t *read_তথ্য_2, unsigned long delay)
{
	unsigned অক্ষর read_buf[4] = {'\0'};
	পূর্ণসংখ্যা i = 0, j = 0, k = 0, status=0;
	unsigned অক্ষর অস্থায়ী = 0;

	//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_তথ্য(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_তথ্য(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_তথ্য(i2c_instance, &অস্থায়ী, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_তথ্য(i2c_instance, &অস্থায়ী, delay);
	*read_তথ্য_2 = অস্থায়ী;

	i2c_instance->control = I2C_STOP;
	ফেরত 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
পূর্ণসংখ্যা read_eeprom_locations(i2c_struct * i2c_instance, uint16_t address, uint8_t *write_তথ্য_2, uint16_t দৈর্ঘ্য_2, uint32_t delay)
{
	পূর্ণসংখ্যা i = 0, j = 0, k = 0, status=0;
	unsigned অক্ষর অস্থায়ী = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	জন্য(i = 0; i < দৈর্ঘ্য_2; i++)
	{
		যদি (0 == (address % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_তথ্য(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_তথ্য(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_তথ্য(i2c_instance, &অস্থায়ী, delay);
		}

		i2c_read_তথ্য(i2c_instance, write_তথ্য_2, delay);
		printf("\nread Value: %x", *write_তথ্য_2);

		যদি( i == (দৈর্ঘ্য_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_তথ্য_2++;
		address ++;

		যদি(0 == (address % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	ফেরত 0;
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
পূর্ণসংখ্যা write_eeprom_address(i2c_struct * i2c_instance, uint16_t address, uint8_t write_মান, unsigned long delay)
{
	পূর্ণসংখ্যা i = 0, j = 0, k = 0, status=0;
	unsigned পূর্ণসংখ্যা অস্থায়ী = 0;
	i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_তথ্য(i2c_instance, ( ( address >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_তথ্য(i2c_instance, ( ( address >> 0 ) & 0xFF), delay);

	i2c_write_তথ্য(i2c_instance, ( write_মান & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	ফেরত 0;
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
পূর্ণসংখ্যা write_eeprom_locations(i2c_struct * i2c_instance, uint16_t address, uint8_t *write_মান, uint16_t দৈর্ঘ্য_2, uint32_t delay)
{
	পূর্ণসংখ্যা i = 0, j = 0, k = 0, status=0;
	unsigned পূর্ণসংখ্যা অস্থায়ী = 0;

	জন্য(i = 0; i < দৈর্ঘ্য_2; i++)
	{
		যদি(0 == (address % 64) )
		{
			i2c_send_slave_address(i2c_instance, AT24C256_SLAVE_ADDRESS, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_তথ্য(i2c_instance, (( address >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_তথ্য(i2c_instance, (( address >> 0 ) & 0xFF), delay);
		}
		i2c_write_তথ্য(i2c_instance, (*write_মান++ & 0xff), delay);
		address ++;

		যদি(0 == (address % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	ফেরত 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
পূর্ণসংখ্যা প্রধান()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t দৈর্ঘ্য_2 = 0;
	uint16_t address = 0;
	uint8_t read_তথ্য_2 = 0;
	uint8_t write_তথ্য_2 = 0;
	uint8_t গুনতি = 0;
	uint8_t write_মান[256] = {'\0'};
	uint8_t read_মান[256] = {'\0'};
	uint32_t তথ্য_read = 0, তথ্য_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_তথ্য_2 = 0x55;

	যদি(read_তথ্য_2 != write_তথ্য_2)
		printf("\n Values are not equal. RV: %x; WV: %x", read_তথ্য_2, write_তথ্য_2);
	অন্যথা
		printf("\n Values are equal. RV: %x; WV: %x", read_তথ্য_2, write_তথ্য_2);

	যদি(write_তথ্য_2 != read_তথ্য_2)
		printf("\n Values are not equal. RV: %x; WV: %x", read_তথ্য_2, write_তথ্য_2);
	অন্যথা
		printf("\n Values are equal. RV: %x; WV: %x", read_তথ্য_2, write_তথ্য_2);

	i2c_init();

	যদি(config_i2c(I2C, PRESCALER_গুনতি, SCLK_গুনতি))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ফেরত -1;
	}
	অন্যথা
		log_info("\tI2C Intilization Success\n");

	দৈর্ঘ্য_2 = 256;
	address = 0x00;
	write_তথ্য_2 = 0x55;
	read_তথ্য_2 = 0x0;

	write_eeprom_address(I2C, address , write_তথ্য_2, delay);
	log_debug("\n Write complete");

	read_eeprom_address(I2C, address, &read_তথ্য_2, delay);
	log_debug("\n Read Complete");
	read_তথ্য_2 = 0x0;

	যদি(write_তথ্য_2 == read_তথ্য_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	অন্যথা
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_তথ্য_2, write_তথ্য_2);
	}

	জন্য(i = 0; i < দৈর্ঘ্য_2; i++)
	{
		write_মান[i] = i;
		তথ্য_write = write_মান[i];
		log_error("\n Write Value: %x", তথ্য_write);
	}

	write_eeprom_locations(I2C, address, &write_মান, দৈর্ঘ্য_2, delay);
	address = 0;
	read_eeprom_locations(I2C, address, &read_মান, দৈর্ঘ্য_2, delay);

	জন্য (i = 0; i < দৈর্ঘ্য_2; i++)
	{
		তথ্য_write = write_মান[i];
		তথ্য_read = read_মান[i];

		log_info("\n wv: %x; rv: %x", তথ্য_write, তথ্য_read );

		যদি(write_মান[i] != read_মান[i])
			গুনতি++;
	}

	যদি(0 != গুনতি )
		printf("\n Write failed");
	অন্যথা
		printf("\n I2C test passed");

	ফেরত 0;
}
