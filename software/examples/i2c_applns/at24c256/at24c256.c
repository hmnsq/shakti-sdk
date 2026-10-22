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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು AT24_C256_SLAVE_ವಿಳಾಸ 0xA0 
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91
#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
ಪೂರ್ಣಾಂಕ read_eeprom_ವಿಳಾಸ(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ವಿಳಾಸ, uint8_t *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0, k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;

	//Writes the slave address for write
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
	*read_ದತ್ತಾಂಶ_2 = ತಾತ್ಕಾಲಿಕ;

	i2c_instance->control = I2C_STOP;
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
ಪೂರ್ಣಾಂಕ read_eeprom_locations(i2c_struct * i2c_instance, uint16_t ವಿಳಾಸ, uint8_t *write_ದತ್ತಾಂಶ_2, uint16_t ಉದ್ದಳತೆ_2, uint32_t delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0, k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		ಆದರೆ (0 == (ವಿಳಾಸ % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
		}

		i2c_read_ದತ್ತಾಂಶ(i2c_instance, write_ದತ್ತಾಂಶ_2, delay);
		ಬರೆ("\nread Value: %x", *write_ದತ್ತಾಂಶ_2);

		ಆದರೆ( i == (ಉದ್ದಳತೆ_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_ದತ್ತಾಂಶ_2++;
		ವಿಳಾಸ ++;

		ಆದರೆ(0 == (ವಿಳಾಸ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	ಹಿಂತಿರುಗಿ 0;
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
ಪೂರ್ಣಾಂಕ write_eeprom_ವಿಳಾಸ(i2c_struct * i2c_instance, uint16_t ವಿಳಾಸ, uint8_t write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0, k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( ( ವಿಳಾಸ >> 0 ) & 0xFF), delay);

	i2c_write_ದತ್ತಾಂಶ(i2c_instance, ( write_ಮೌಲ್ಯ & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	ಹಿಂತಿರುಗಿ 0;
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
ಪೂರ್ಣಾಂಕ write_eeprom_locations(i2c_struct * i2c_instance, uint16_t ವಿಳಾಸ, uint8_t *write_ಮೌಲ್ಯ, uint16_t ಉದ್ದಳತೆ_2, uint32_t delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0, k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;

	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		ಆದರೆ(0 == (ವಿಳಾಸ % 64) )
		{
			i2c_send_slave_ವಿಳಾಸ(i2c_instance, AT24_C256_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_ದತ್ತಾಂಶ(i2c_instance, (( ವಿಳಾಸ >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_ದತ್ತಾಂಶ(i2c_instance, (( ವಿಳಾಸ >> 0 ) & 0xFF), delay);
		}
		i2c_write_ದತ್ತಾಂಶ(i2c_instance, (*write_ಮೌಲ್ಯ++ & 0xff), delay);
		ವಿಳಾಸ ++;

		ಆದರೆ(0 == (ವಿಳಾಸ % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t ಉದ್ದಳತೆ_2 = 0;
	uint16_t ವಿಳಾಸ = 0;
	uint8_t read_ದತ್ತಾಂಶ_2 = 0;
	uint8_t write_ದತ್ತಾಂಶ_2 = 0;
	uint8_t ಎಣಿಕೆ_2 = 0;
	uint8_t write_ಮೌಲ್ಯ[256] = {'\0'};
	uint8_t read_ಮೌಲ್ಯ[256] = {'\0'};
	uint32_t ದತ್ತಾಂಶ_read = 0, ದತ್ತಾಂಶ_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_ದತ್ತಾಂಶ_2 = 0x55;

	ಆದರೆ(read_ದತ್ತಾಂಶ_2 != write_ದತ್ತಾಂಶ_2)
		ಬರೆ("\n Values are not equal. RV: %x; WV: %x", read_ದತ್ತಾಂಶ_2, write_ದತ್ತಾಂಶ_2);
	ಇಲ್ಲದಿದ್ದರೆ
		ಬರೆ("\n Values are equal. RV: %x; WV: %x", read_ದತ್ತಾಂಶ_2, write_ದತ್ತಾಂಶ_2);

	ಆದರೆ(write_ದತ್ತಾಂಶ_2 != read_ದತ್ತಾಂಶ_2)
		ಬರೆ("\n Values are not equal. RV: %x; WV: %x", read_ದತ್ತಾಂಶ_2, write_ದತ್ತಾಂಶ_2);
	ಇಲ್ಲದಿದ್ದರೆ
		ಬರೆ("\n Values are equal. RV: %x; WV: %x", read_ದತ್ತಾಂಶ_2, write_ದತ್ತಾಂಶ_2);

	i2c_init();

	ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ, SCLK_ಎಣಿಕೆ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		log_info("\tI2C Intilization Success\n");

	ಉದ್ದಳತೆ_2 = 256;
	ವಿಳಾಸ = 0x00;
	write_ದತ್ತಾಂಶ_2 = 0x55;
	read_ದತ್ತಾಂಶ_2 = 0x0;

	write_eeprom_ವಿಳಾಸ(I2C, ವಿಳಾಸ , write_ದತ್ತಾಂಶ_2, delay);
	log_debug("\n Write complete");

	read_eeprom_ವಿಳಾಸ(I2C, ವಿಳಾಸ, &read_ದತ್ತಾಂಶ_2, delay);
	log_debug("\n Read Complete");
	read_ದತ್ತಾಂಶ_2 = 0x0;

	ಆದರೆ(write_ದತ್ತಾಂಶ_2 == read_ದತ್ತಾಂಶ_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	ಇಲ್ಲದಿದ್ದರೆ
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_ದತ್ತಾಂಶ_2, write_ದತ್ತಾಂಶ_2);
	}

	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		write_ಮೌಲ್ಯ[i] = i;
		ದತ್ತಾಂಶ_write = write_ಮೌಲ್ಯ[i];
		log_error("\n Write Value: %x", ದತ್ತಾಂಶ_write);
	}

	write_eeprom_locations(I2C, ವಿಳಾಸ, &write_ಮೌಲ್ಯ, ಉದ್ದಳತೆ_2, delay);
	ವಿಳಾಸ = 0;
	read_eeprom_locations(I2C, ವಿಳಾಸ, &read_ಮೌಲ್ಯ, ಉದ್ದಳತೆ_2, delay);

	ಗಾಗಿ (i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		ದತ್ತಾಂಶ_write = write_ಮೌಲ್ಯ[i];
		ದತ್ತಾಂಶ_read = read_ಮೌಲ್ಯ[i];

		log_info("\n wv: %x; rv: %x", ದತ್ತಾಂಶ_write, ದತ್ತಾಂಶ_read );

		ಆದರೆ(write_ಮೌಲ್ಯ[i] != read_ಮೌಲ್ಯ[i])
			ಎಣಿಕೆ_2++;
	}

	ಆದರೆ(0 != ಎಣಿಕೆ_2 )
		ಬರೆ("\n Write failed");
	ಇಲ್ಲದಿದ್ದರೆ
		ಬರೆ("\n I2C test passed");

	ಹಿಂತಿರುಗಿ 0;
}
