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

#تعریف_کړه AT24_C256_SLAVE_پته 0xA0 
#تعریف_کړه DELAY_ارزښت 900
#تعریف_کړه PRESCALER_شمېر 0x1F
#تعریف_کړه SCLK_شمېر 0x91
#تعریف_کړه I2C i2c_instance[0]

/** @fn int read_eeprom_address(i2c_struct * i2c_instance, unsigned int address, unsigned long delay)
 * @brief Reads the data of the given address
 * @details Reads the data of the given address over I2C interface
 * @param i2c_struct*
 * @param address
 * @param delay
 * @return read status (zero on success)
 */
صحيح read_eeprom_پته(i2c_struct * i2c_instance, بینښه صحيح پته, uint8_t *read_معلومات_2, بینښه اوږد delay)
{
	بینښه حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بینښه حرف لنډمهاله = 0;

	//Writes the slave address for write
	i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_WRITE, 800);

	//Writes the pointer to address that needs to be read
	i2c_write_معلومات(i2c_instance, ( ( پته >> 8 ) & 0xFF), delay);
	//Writes the pointer to address that needs to be read
	i2c_write_معلومات(i2c_instance, ( ( پته >> 0 ) & 0xFF), delay);

	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

	//Writes the slave address for read
	i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_READ, delay);

	/* Make a dummy read as per spec of the I2C controller */
	i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);

	//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
	*read_معلومات_2 = لنډمهاله;

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
صحيح read_eeprom_locations(i2c_struct * i2c_instance, uint16_t پته, uint8_t *write_معلومات_2, uint16_t اوږدتیا_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بینښه حرف لنډمهاله = 0;

	//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		إذا (0 == (پته % 64 ) )
		{
			//Writes the slave address for write
			i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_معلومات(i2c_instance, ( ( پته >> 8 ) & 0xFF), delay);
			//Writes the pointer to lsb address that needs to be read
			i2c_write_معلومات(i2c_instance, ( ( پته >> 0 ) & 0xFF), delay);

			//Stops the I2C transaction to start reading the temperature value.
			i2c_instance->control = I2C_STOP;

			//Writes the slave address for read
			i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_READ, delay);
			/* Make a dummy read as per spec of the I2C controller */
			i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
		}

		i2c_read_معلومات(i2c_instance, write_معلومات_2, delay);
		چاپ_کړه("\nread Value: %x", *write_معلومات_2);

		إذا( i == (اوږدتیا_2 - 2) )
			i2c_instance->control = I2C_NACK;

		*write_معلومات_2++;
		پته ++;

		إذا(0 == (پته % 64) )
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
صحيح write_eeprom_پته(i2c_struct * i2c_instance, uint16_t پته, uint8_t write_ارزښت, بینښه اوږد delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بینښه صحيح لنډمهاله = 0;
	i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_WRITE, delay);

	//Writes the pointer to msb address that needs to be read
	i2c_write_معلومات(i2c_instance, ( ( پته >> 8 ) & 0xFF), delay);
	//Writes the pointer to lsb address that needs to be read
	i2c_write_معلومات(i2c_instance, ( ( پته >> 0 ) & 0xFF), delay);

	i2c_write_معلومات(i2c_instance, ( write_ارزښت & 0xff), delay);

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
صحيح write_eeprom_locations(i2c_struct * i2c_instance, uint16_t پته, uint8_t *write_ارزښت, uint16_t اوږدتیا_2, uint32_t delay)
{
	صحيح i = 0, j = 0, k = 0, حالت_2=0;
	بینښه صحيح لنډمهاله = 0;

	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		إذا(0 == (پته % 64) )
		{
			i2c_send_slave_پته(i2c_instance, AT24_C256_SLAVE_پته, I2C_WRITE, delay);

			//Writes the pointer to msb address that needs to be read
			i2c_write_معلومات(i2c_instance, (( پته >> 8 ) & 0xFF), delay);

			//Writes the pointer to lsb address that needs to be read
			i2c_write_معلومات(i2c_instance, (( پته >> 0 ) & 0xFF), delay);
		}
		i2c_write_معلومات(i2c_instance, (*write_ارزښت++ & 0xff), delay);
		پته ++;

		إذا(0 == (پته % 64) )
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
صحيح اصلي()
{
	uint16_t i = 0;
	uint16_t timeout;
	uint32_t delay = 2000;
	uint16_t اوږدتیا_2 = 0;
	uint16_t پته = 0;
	uint8_t read_معلومات_2 = 0;
	uint8_t write_معلومات_2 = 0;
	uint8_t شمېر = 0;
	uint8_t write_ارزښت[256] = {'\0'};
	uint8_t read_ارزښت[256] = {'\0'};
	uint32_t معلومات_read = 0, معلومات_write = 0;

	log_debug("\tI2C: AT24C256 - EEPROM test\n");
	read_معلومات_2 = 0x55;

	إذا(read_معلومات_2 != write_معلومات_2)
		چاپ_کړه("\n Values are not equal. RV: %x; WV: %x", read_معلومات_2, write_معلومات_2);
	وإلا
		چاپ_کړه("\n Values are equal. RV: %x; WV: %x", read_معلومات_2, write_معلومات_2);

	إذا(write_معلومات_2 != read_معلومات_2)
		چاپ_کړه("\n Values are not equal. RV: %x; WV: %x", read_معلومات_2, write_معلومات_2);
	وإلا
		چاپ_کړه("\n Values are equal. RV: %x; WV: %x", read_معلومات_2, write_معلومات_2);

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_شمېر, SCLK_شمېر))
	{
		log_error("\tSomething Wrong In Initialization\n");
		أرجع -1;
	}
	وإلا
		log_info("\tI2C Intilization Success\n");

	اوږدتیا_2 = 256;
	پته = 0x00;
	write_معلومات_2 = 0x55;
	read_معلومات_2 = 0x0;

	write_eeprom_پته(I2C, پته , write_معلومات_2, delay);
	log_debug("\n Write complete");

	read_eeprom_پته(I2C, پته, &read_معلومات_2, delay);
	log_debug("\n Read Complete");
	read_معلومات_2 = 0x0;

	إذا(write_معلومات_2 == read_معلومات_2)
		log_info("\n AT24C256 EEPROM RW Passed");
	وإلا
	{
		log_error("\n AT24C256 EEPROM RW Failed; RV: %x; WV: %x", read_معلومات_2, write_معلومات_2);
	}

	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		write_ارزښت[i] = i;
		معلومات_write = write_ارزښت[i];
		log_error("\n Write Value: %x", معلومات_write);
	}

	write_eeprom_locations(I2C, پته, &write_ارزښت, اوږدتیا_2, delay);
	پته = 0;
	read_eeprom_locations(I2C, پته, &read_ارزښت, اوږدتیا_2, delay);

	لكل (i = 0; i < اوږدتیا_2; i++)
	{
		معلومات_write = write_ارزښت[i];
		معلومات_read = read_ارزښت[i];

		log_info("\n wv: %x; rv: %x", معلومات_write, معلومات_read );

		إذا(write_ارزښت[i] != read_ارزښت[i])
			شمېر++;
	}

	إذا(0 != شمېر )
		چاپ_کړه("\n Write failed");
	وإلا
		چاپ_کړه("\n I2C test passed");

	أرجع 0;
}
