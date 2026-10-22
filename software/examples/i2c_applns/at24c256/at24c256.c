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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#परिभाषय AT24_C256_SLAVE_स्थानाङ्कः 0xA0 
#परिभाषय DELAY_मानम् 900
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91
#परिभाषय I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
पूर्णाङ्क read_eeprom_स्थानाङ्कः(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क स्थानाङ्कः, uint8_t *read_दत्त_2, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0, k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;

	//Writes the slave address for write
	i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
	*read_दत्त_2 = अस्थायी;

	i2c_instance->control = I2C_STOP;
	प्रत्यागम 0;
}

/** @fn int read_eeprom_locations(i2c_struct * i2c_instance, unsigned int address, unsigned char *read_data, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
पूर्णाङ्क read_eeprom_locations(i2c_struct * i2c_instance, uint16_t स्थानाङ्कः, uint8_t *write_दत्त_2, uint16_t दीर्घता_2, uint32_t delay)
{
	पूर्णाङ्क i = 0, j = 0, k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		यदि (0 == (स्थानाङ्कः % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
		}

		i2c_read_दत्त(i2c_instance, write_दत्त_2, delay);
		प्रारूप_लिख("\nread Value: %x", *write_दत्त_2);

		यदि( i == (दीर्घता_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_दत्त_2++;
		स्थानाङ्कः ++;

		यदि(0 == (स्थानाङ्कः % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}
	}

	प्रत्यागम 0;
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
पूर्णाङ्क write_eeprom_स्थानाङ्कः(i2c_struct * i2c_instance, uint16_t स्थानाङ्कः, uint8_t write_मानम्, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0, k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
	i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_दत्त(i2c_instance, ( ( स्थानाङ्कः >> 0 ) & 0xFF), delay);

	i2c_write_दत्त(i2c_instance, ( write_मानम् & 0xff), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	प्रत्यागम 0;
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
पूर्णाङ्क write_eeprom_locations(i2c_struct * i2c_instance, uint16_t स्थानाङ्कः, uint8_t *write_मानम्, uint16_t दीर्घता_2, uint32_t delay)
{
	पूर्णाङ्क i = 0, j = 0, k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;

	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		यदि(0 == (स्थानाङ्कः % 64) )
		{
			i2c_send_slave_स्थानाङ्कः(i2c_instance, AT24_C256_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_दत्त(i2c_instance, (( स्थानाङ्कः >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_दत्त(i2c_instance, (( स्थानाङ्कः >> 0 ) & 0xFF), delay);
		}
		i2c_write_दत्त(i2c_instance, (*write_मानम्++ & 0xff), delay);
		स्थानाङ्कः ++;

		यदि(0 == (स्थानाङ्कः % 64) )
		{
			i2c_instance->control = I2C_STOP;
		}

	}

	प्रत्यागम 0;
}

/** @fn int main()
 * @brief Writes the desired frquency value to the chip
 * @details Configures the sensor and writes the desired frequency value to chip
 * prints the read values
 * @return Zero
 */
पूर्णाङ्क मुख्यम्()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t दीर्घता_2 = 0;
	uint16_t स्थानाङ्कः = 0;
	uint8_t read_दत्त_2 = 0;
	uint8_t write_दत्त_2 = 0;
	uint8_t गणनम् = 0;
	uint8_t write_मानम्[256] = {'\0'};
	uint8_t read_मानम्[256] = {'\0'};
	uint32_t दत्त_read = 0, दत्त_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_दत्त_2 = 0x55;

	यदि(read_दत्त_2 != write_दत्त_2)
		प्रारूप_लिख("\n Values are not equal. RV: %x; WV: %x", read_दत्त_2, write_दत्त_2);
	अन्यथा
		प्रारूप_लिख("\n Values are equal. RV: %x; WV: %x", read_दत्त_2, write_दत्त_2);

	यदि(write_दत्त_2 != read_दत्त_2)
		प्रारूप_लिख("\n Values are not equal. RV: %x; WV: %x", read_दत्त_2, write_दत्त_2);
	अन्यथा
		प्रारूप_लिख("\n Values are equal. RV: %x; WV: %x", read_दत्त_2, write_दत्त_2);

	i2c_init();

	यदि(config_i2c(I2C, PRESCALER_गणनम्, SCLK_गणनम्))
	{
		log_error("\tSomething Wrong In Initialization\n");
		प्रत्यागम -1;
	}
	अन्यथा
		log_info("\tI2C Intilization Success\n");

	दीर्घता_2 = 256;
	स्थानाङ्कः = 0x00;
	write_दत्त_2 = 0x55;
	read_दत्त_2 = 0x0;

	write_eeprom_स्थानाङ्कः(I2C, स्थानाङ्कः , write_दत्त_2, delay);
	log_debug("\n Write complete");

	read_eeprom_स्थानाङ्कः(I2C, स्थानाङ्कः, &read_दत्त_2, delay);
	log_debug("\n Read Complete");
	read_दत्त_2 = 0x0;

	यदि(write_दत्त_2 == read_दत्त_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	अन्यथा
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_दत्त_2, write_दत्त_2);
	}

	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		write_मानम्[i] = i;
		दत्त_write = write_मानम्[i];
		log_error("\n Write Value: %x", दत्त_write);
	}

	write_eeprom_locations(I2C, स्थानाङ्कः, &write_मानम्, दीर्घता_2, delay);
	स्थानाङ्कः = 0;
	read_eeprom_locations(I2C, स्थानाङ्कः, &read_मानम्, दीर्घता_2, delay);

	प्रति (i = 0; i < दीर्घता_2; i++)
	{
		दत्त_write = write_मानम्[i];
		दत्त_read = read_मानम्[i];

		log_info("\n wv: %x; rv: %x", दत्त_write, दत्त_read );

		यदि(write_मानम्[i] != read_मानम्[i])
			गणनम्++;
	}

	यदि(0 != गणनम् )
		प्रारूप_लिख("\n Write failed");
	अन्यथा
		प्रारूप_लिख("\n I2C test passed");

	प्रत्यागम 0;
}
