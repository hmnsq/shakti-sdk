/***********************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	      : lm75.c
 * Brief Description of file  : reads current room temperature over i2c interface
 * Name of Author             : Kotteeswaran
 * Email ID                   : kottee.1@gmail.com

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

***********************************************************************************/
/**
@file lm75.c
@brief Contains the driver routines to configure and read lm75.
@detail I2C based routines to configures and read the temperature from LM75.
*/
#ಅನ್ತರ್ಭಾವ <stdint.h>//Includes the definitions of standard input/output functions//
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[1]

#ವ್ಯಾಖ್ಯಾನಿಸು LM75_SLAVE_ವಿಳಾಸ 0x90//Defines the Starting address of slave//
#ವ್ಯಾಖ್ಯಾನಿಸು LM75_ತಾತ್ಕಾಲಿಕ_REG_ಸ್ಥಾನಾಂತರ 0x00
#ವ್ಯಾಖ್ಯಾನಿಸು LM75_CONF_REG_ಸ್ಥಾನಾಂತರ 0x01
#ವ್ಯಾಖ್ಯಾನಿಸು LM75_HYST_REG_ಸ್ಥಾನಾಂತರ 0x02
#ವ್ಯಾಖ್ಯಾನಿಸು LM75_ಸ್ಥಾನಾಂತರ_REG_ಸ್ಥಾನಾಂತರ 0x03

#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
ಪೂರ್ಣಾಂಕ read_lm75_ರಿಜಿಸ್ಟರ್(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *read_ತಾತ್ಕಾಲಿಕ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;
//Writes the slave address for write
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, LM75_SLAVE_ವಿಳಾಸ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;


//Writes the slave address for read
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, LM75_SLAVE_ವಿಳಾಸ, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*read_ತಾತ್ಕಾಲಿಕ = (read_buf[1] << 1) | (read_buf[0] >> 7);

	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int write_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief Writes the value into passed lm75 register 
 * @details Writes the passed value into the passed lm75 register address over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param delay
 * @return Write Status (Zero on Success)
 */
ಪೂರ್ಣಾಂಕ write_lm75_ರಿಜಿಸ್ಟರ್(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, LM75_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( (write_ಮೌಲ್ಯ >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	ಬರೆ("\n Write Value[0]: %02x", (write_ಮೌಲ್ಯ >> 1) & 0xff);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( ( (write_ಮೌಲ್ಯ & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	ಬರೆ("\n Write Value[1]: %02x", ( ( (write_ಮೌಲ್ಯ & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
ಪೂರ್ಣಾಂಕ temperature_ಮೌಲ್ಯ()
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 1000;
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ,SCLK_ಎಣಿಕೆ))
		{
				log_error("\tSomething Wrong In Initialization\n");
				ಹಿಂತಿರುಗಿ -1;
		}
	ಇಲ್ಲದಿದ್ದರೆ
				log_info("\tIntilization Happened Fine\n");
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ LM75_HYST_CHECK
	write_lm75_ರಿಜಿಸ್ಟರ್(I2C, LM75_HYST_REG_ಸ್ಥಾನಾಂತರ, 0x30, delay);
		ಆದರೆ(0 == read_lm75_ರಿಜಿಸ್ಟರ್(I2C, LM75_HYST_REG_ಸ್ಥಾನಾಂತರ, &ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ);
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ LM75_ಸ್ಥಾನಾಂತರ_CHECK
	write_lm75_ರಿಜಿಸ್ಟರ್(I2C, LM75_ಸ್ಥಾನಾಂತರ_REG_ಸ್ಥಾನಾಂತರ, 0x35, delay);
	ಆದರೆ(0 == read_lm75_ರಿಜಿಸ್ಟರ್(I2C, LM75_ಸ್ಥಾನಾಂತರ_REG_ಸ್ಥಾನಾಂತರ, &ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ);
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#ಆದರೆ_ಅಂತ್ಯ

		ಆದರೆ(0 == read_lm75_ರಿಜಿಸ್ಟರ್(I2C, LM75_ತಾತ್ಕಾಲಿಕ_REG_ಸ್ಥಾನಾಂತರ, &ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			ಆದರೆ(ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ & 0x100) {
				ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = ( (~ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ);
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ >> 1;
				log_info("\n\t Current Temperature:=+%u°C",ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ);
			 }
			 ಹಿಂತಿರುಗಿ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ;
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
	//Display the error
			log_error("\nTemperature read failed.");
			 ಹಿಂತಿರುಗಿ 999;
		}
		delay_loop(1000, 1000);


	ಹಿಂತಿರುಗಿ 0;
}
