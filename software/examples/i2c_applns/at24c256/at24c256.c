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
صحيح read_eeprom_پتہ(i2c_struct * i2c_instance, بنانشانی صحيح پتہ, uint8_t *read_انکڑے_2, بنانشانی لما delay)
{
	بنانشانی حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بنانشانی حرف عارضی = 0;

	//Writes the slave address for write
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_انکڑے(i2c_instance, &عارضی, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_انکڑے(i2c_instance, &عارضی, delay);
	*read_انکڑے_2 = عارضی;

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
صحيح read_eeprom_locations(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t *write_انکڑے_2, uint16_t لمائی_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بنانشانی حرف عارضی = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < لمائی_2; i++)
	{
		إذا (0 == (پتہ % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_انکڑے(i2c_instance, &عارضی, delay);
		}

		i2c_read_انکڑے(i2c_instance, write_انکڑے_2, delay);
		لکھو("\nread Value: %x", *write_انکڑے_2);

		إذا( i == (لمائی_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_انکڑے_2++;
		پتہ ++;

		إذا(0 == (پتہ % 64) )
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
صحيح write_eeprom_پتہ(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t write_قدر, بنانشانی لما delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بنانشانی صحيح عارضی = 0;
	i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_انکڑے(i2c_instance, ( ( پتہ >> 0 ) & 0xFF), delay);

	i2c_write_انکڑے(i2c_instance, ( write_قدر & 0xff), delay);

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
صحيح write_eeprom_locations(i2c_struct * i2c_instance, uint16_t پتہ, uint8_t *write_قدر, uint16_t لمائی_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بنانشانی صحيح عارضی = 0;

	لكل(i = 0; i < لمائی_2; i++)
	{
		إذا(0 == (پتہ % 64) )
		{
			i2c_send_slave_پتہ(i2c_instance, AT24_C256_SLAVE_پتہ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_انکڑے(i2c_instance, (( پتہ >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_انکڑے(i2c_instance, (( پتہ >> 0 ) & 0xFF), delay);
		}
		i2c_write_انکڑے(i2c_instance, (*write_قدر++ & 0xff), delay);
		پتہ ++;

		إذا(0 == (پتہ % 64) )
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
صحيح مکھ()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t لمائی_2 = 0;
	uint16_t پتہ = 0;
	uint8_t read_انکڑے_2 = 0;
	uint8_t write_انکڑے_2 = 0;
	uint8_t گنتی = 0;
	uint8_t write_قدر[256] = {'\0'};
	uint8_t read_قدر[256] = {'\0'};
	uint32_t انکڑے_read = 0, انکڑے_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_انکڑے_2 = 0x55;

	إذا(read_انکڑے_2 != write_انکڑے_2)
		لکھو("\n Values are not equal. RV: %x; WV: %x", read_انکڑے_2, write_انکڑے_2);
	وإلا
		لکھو("\n Values are equal. RV: %x; WV: %x", read_انکڑے_2, write_انکڑے_2);

	إذا(write_انکڑے_2 != read_انکڑے_2)
		لکھو("\n Values are not equal. RV: %x; WV: %x", read_انکڑے_2, write_انکڑے_2);
	وإلا
		لکھو("\n Values are equal. RV: %x; WV: %x", read_انکڑے_2, write_انکڑے_2);

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_گنتی, SCLK_گنتی))
	{
		log_error("\tSomething Wrong In Initialization\n");
		أرجع -1;
	}
	وإلا
		log_info("\tI2C Intilization Success\n");

	لمائی_2 = 256;
	پتہ = 0x00;
	write_انکڑے_2 = 0x55;
	read_انکڑے_2 = 0x0;

	write_eeprom_پتہ(I2C, پتہ , write_انکڑے_2, delay);
	log_debug("\n Write complete");

	read_eeprom_پتہ(I2C, پتہ, &read_انکڑے_2, delay);
	log_debug("\n Read Complete");
	read_انکڑے_2 = 0x0;

	إذا(write_انکڑے_2 == read_انکڑے_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	وإلا
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_انکڑے_2, write_انکڑے_2);
	}

	لكل(i = 0; i < لمائی_2; i++)
	{
		write_قدر[i] = i;
		انکڑے_write = write_قدر[i];
		log_error("\n Write Value: %x", انکڑے_write);
	}

	write_eeprom_locations(I2C, پتہ, &write_قدر, لمائی_2, delay);
	پتہ = 0;
	read_eeprom_locations(I2C, پتہ, &read_قدر, لمائی_2, delay);

	لكل (i = 0; i < لمائی_2; i++)
	{
		انکڑے_write = write_قدر[i];
		انکڑے_read = read_قدر[i];

		log_info("\n wv: %x; rv: %x", انکڑے_write, انکڑے_read );

		إذا(write_قدر[i] != read_قدر[i])
			گنتی++;
	}

	إذا(0 != گنتی )
		لکھو("\n Write failed");
	وإلا
		لکھو("\n I2C test passed");

	أرجع 0;
}
