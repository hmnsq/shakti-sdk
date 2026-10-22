/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : pcf8591.c
 * Brief Description of file   : Contains the driver routines to configure and read pcf8591.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
/**
@file   pcf8591.c
@brief  Contains the driver routines to configure and read pcf8591.
@detail I2C based routines to configures and read the adc value from pcf8591.
*/

#ಅನ್ತರ್ಭಾವ <stdint.h>//Includes the definitions of standard input/output functions//
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು PCF8591_SLAVE_ವಿಳಾಸ 0x90 // I2C bus address //doubt
#ವ್ಯಾಖ್ಯಾನಿಸು PCF8591_CONTROL_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯ 0x04
#ವ್ಯಾಖ್ಯಾನಿಸು PCF8591_REG_ಸ್ಥಾನಾಂತರ 0

#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91

#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[0]

/** @fn int read_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
 * @brief Reads the ADC value from PCF8591
 * @details Reads 4 ADC values from PCF8591 over I2C interface
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param length
 * @param delay
 * @return read status (zero on success)
 */
ಪೂರ್ಣಾಂಕ read_pcf8591_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *read_ತಾತ್ಕಾಲಿಕ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;
//Writes the slave address for write
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, PCF8591_SLAVE_ವಿಳಾಸ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, PCF8591_SLAVE_ವಿಳಾಸ, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
		*read_ತಾತ್ಕಾಲಿಕ = ತಾತ್ಕಾಲಿಕ;
		ಆದರೆ( i == (ಉದ್ದಳತೆ_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_ತಾತ್ಕಾಲಿಕ++;
	}
	
	i2c_instance->control = I2C_STOP;
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief WRites into PCF8591 Register
 * @details WRites the passed value into passed PCF8591 Register (address) over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param length
 * @param delay
 * @return Write status (Zero on success)
 */
ಪೂರ್ಣಾಂಕ write_pcf8591_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, PCF8591_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( *write_ಮೌಲ್ಯ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;;
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ i = 0;
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 1000;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf[7] = {0x00}, read_buf[7] = {0x00};
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ, SCLK_ಎಣಿಕೆ))
	{
			log_error("\tSomething Wrong In Initialization\n");
			ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		log_info("\tIntilization Happened Fine\n");
		ಉದ್ದಳತೆ_2 = 1;
		write_buf[0] = PCF8591_CONTROL_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯ;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], ಉದ್ದಳತೆ_2, delay);
		log_debug("\n Write complete");
		ಉದ್ದಳತೆ_2 = 5;
	ಆಗ(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯ, &read_buf[0], ಉದ್ದಳತೆ_2, 800);
			log_info("\n");
			ಗಾಗಿ( i = 1; i < ಉದ್ದಳತೆ_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	ಹಿಂತಿರುಗಿ 0;
}

