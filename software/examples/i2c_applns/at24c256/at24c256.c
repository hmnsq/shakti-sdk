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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT24_C256_SLAVE_ਪਤਾ 0xA0 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
ਪੂਰਨ read_eeprom_ਪਤਾ(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪਤਾ, uint8_t *read_ਅੰਕੜੇ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_buf[4] = {'\0'};
	ਪੂਰਨ i = 0, j = 0, k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਰਜ਼ੀ = 0;

	//Writes the slave address for write
	i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);
	*read_ਅੰਕੜੇ_2 = ਆਰਜ਼ੀ;

	i2c_instance->control = I2C_STOP;
	ਵਾਪਸ 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
ਪੂਰਨ read_eeprom_locations(i2c_struct * i2c_instance, uint16_t ਪਤਾ, uint8_t *write_ਅੰਕੜੇ_2, uint16_t ਲੰਮਾਈ_2, uint32_t delay)
{
	ਪੂਰਨ i = 0, j = 0, k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਰਜ਼ੀ = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		ਜੇ (0 == (ਪਤਾ % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);
		}

		i2c_read_ਅੰਕੜੇ(i2c_instance, write_ਅੰਕੜੇ_2, delay);
		ਲਿਖੋ("\nread Value: %x", *write_ਅੰਕੜੇ_2);

		ਜੇ( i == (ਲੰਮਾਈ_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_ਅੰਕੜੇ_2++;
		ਪਤਾ ++;

		ਜੇ(0 == (ਪਤਾ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	ਵਾਪਸ 0;
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
ਪੂਰਨ write_eeprom_ਪਤਾ(i2c_struct * i2c_instance, uint16_t ਪਤਾ, uint8_t write_ਮੁੱਲ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਪੂਰਨ i = 0, j = 0, k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;
	i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, ( ( ਪਤਾ >> 0 ) & 0xFF), delay);

	i2c_write_ਅੰਕੜੇ(i2c_instance, ( write_ਮੁੱਲ & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	ਵਾਪਸ 0;
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
ਪੂਰਨ write_eeprom_locations(i2c_struct * i2c_instance, uint16_t ਪਤਾ, uint8_t *write_ਮੁੱਲ, uint16_t ਲੰਮਾਈ_2, uint32_t delay)
{
	ਪੂਰਨ i = 0, j = 0, k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;

	ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		ਜੇ(0 == (ਪਤਾ % 64) )
		{
			i2c_send_slave_ਪਤਾ(i2c_instance, AT24_C256_SLAVE_ਪਤਾ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ਅੰਕੜੇ(i2c_instance, (( ਪਤਾ >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_ਅੰਕੜੇ(i2c_instance, (( ਪਤਾ >> 0 ) & 0xFF), delay);
		}
		i2c_write_ਅੰਕੜੇ(i2c_instance, (*write_ਮੁੱਲ++ & 0xff), delay);
		ਪਤਾ ++;

		ਜੇ(0 == (ਪਤਾ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	ਵਾਪਸ 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
ਪੂਰਨ ਮੁੱਖ()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t ਲੰਮਾਈ_2 = 0;
	uint16_t ਪਤਾ = 0;
	uint8_t read_ਅੰਕੜੇ_2 = 0;
	uint8_t write_ਅੰਕੜੇ_2 = 0;
	uint8_t ਗਿਣਤੀ_2 = 0;
	uint8_t write_ਮੁੱਲ[256] = {'\0'};
	uint8_t read_ਮੁੱਲ[256] = {'\0'};
	uint32_t ਅੰਕੜੇ_read = 0, ਅੰਕੜੇ_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_ਅੰਕੜੇ_2 = 0x55;

	ਜੇ(read_ਅੰਕੜੇ_2 != write_ਅੰਕੜੇ_2)
		ਲਿਖੋ("\n Values are not equal. RV: %x; WV: %x", read_ਅੰਕੜੇ_2, write_ਅੰਕੜੇ_2);
	ਨਹੀਂਤਾਂ
		ਲਿਖੋ("\n Values are equal. RV: %x; WV: %x", read_ਅੰਕੜੇ_2, write_ਅੰਕੜੇ_2);

	ਜੇ(write_ਅੰਕੜੇ_2 != read_ਅੰਕੜੇ_2)
		ਲਿਖੋ("\n Values are not equal. RV: %x; WV: %x", read_ਅੰਕੜੇ_2, write_ਅੰਕੜੇ_2);
	ਨਹੀਂਤਾਂ
		ਲਿਖੋ("\n Values are equal. RV: %x; WV: %x", read_ਅੰਕੜੇ_2, write_ਅੰਕੜੇ_2);

	i2c_init();

	ਜੇ(config_i2c(I2C, PRESCALER_ਗਿਣਤੀ, SCLK_ਗਿਣਤੀ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ
		log_info("\tI2C Intilization Success\n");

	ਲੰਮਾਈ_2 = 256;
	ਪਤਾ = 0x00;
	write_ਅੰਕੜੇ_2 = 0x55;
	read_ਅੰਕੜੇ_2 = 0x0;

	write_eeprom_ਪਤਾ(I2C, ਪਤਾ , write_ਅੰਕੜੇ_2, delay);
	log_debug("\n Write complete");

	read_eeprom_ਪਤਾ(I2C, ਪਤਾ, &read_ਅੰਕੜੇ_2, delay);
	log_debug("\n Read Complete");
	read_ਅੰਕੜੇ_2 = 0x0;

	ਜੇ(write_ਅੰਕੜੇ_2 == read_ਅੰਕੜੇ_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	ਨਹੀਂਤਾਂ
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_ਅੰਕੜੇ_2, write_ਅੰਕੜੇ_2);
	}

	ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		write_ਮੁੱਲ[i] = i;
		ਅੰਕੜੇ_write = write_ਮੁੱਲ[i];
		log_error("\n Write Value: %x", ਅੰਕੜੇ_write);
	}

	write_eeprom_locations(I2C, ਪਤਾ, &write_ਮੁੱਲ, ਲੰਮਾਈ_2, delay);
	ਪਤਾ = 0;
	read_eeprom_locations(I2C, ਪਤਾ, &read_ਮੁੱਲ, ਲੰਮਾਈ_2, delay);

	ਲਈ (i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		ਅੰਕੜੇ_write = write_ਮੁੱਲ[i];
		ਅੰਕੜੇ_read = read_ਮੁੱਲ[i];

		log_info("\n wv: %x; rv: %x", ਅੰਕੜੇ_write, ਅੰਕੜੇ_read );

		ਜੇ(write_ਮੁੱਲ[i] != read_ਮੁੱਲ[i])
			ਗਿਣਤੀ_2++;
	}

	ਜੇ(0 != ਗਿਣਤੀ_2 )
		ਲਿਖੋ("\n Write failed");
	ਨਹੀਂਤਾਂ
		ਲਿਖੋ("\n I2C test passed");

	ਵਾਪਸ 0;
}
