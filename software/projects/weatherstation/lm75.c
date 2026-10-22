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
#अन्तर्भाव <stdint.h>//Includes the definitions of standard input/output functions//
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#define I2C i2c_instance[1]

#define LM75_SLAVE_ADDRESS 0x90//Defines the Starting address of slave//
#define LM75_TEMP_REG_OFFSET 0x00
#define LM75_CONF_REG_OFFSET 0x01
#define LM75_HYST_REG_OFFSET 0x02
#define LM75_OFFSET_REG_OFFSET 0x03

#define DELAY_मान 900
#define PRESCALER_गन्ती 0x1F
#define SCLK_गन्ती 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
पूर्णाङ्क read_lm75_register(i2c_struct * i2c_instance, अचिन्हित पूर्णाङ्क reg_offset, अचिन्हित पूर्णाङ्क *readTemp, अचिन्हित दीर्घ delay)
{
	अचिन्हित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, status=0;
	अचिन्हित वर्ण temp = 0;
//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, LM75_SLAVE_ADDRESS, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, reg_offset , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;


//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, LM75_SLAVE_ADDRESS, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*readTemp = (read_buf[1] << 1) | (read_buf[0] >> 7);

	फर्काऊ 0;
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
पूर्णाङ्क write_lm75_register(i2c_struct * i2c_instance, अचिन्हित पूर्णाङ्क reg_offset, अचिन्हित पूर्णाङ्क write_मान, अचिन्हित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, status=0;
	अचिन्हित पूर्णाङ्क temp = 0;
	i2c_send_slave_address(i2c_instance, LM75_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_data(i2c_instance, reg_offset /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_data(i2c_instance,  ( (write_मान >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	म_लिखो("\n Write Value[0]: %02x", (write_मान >> 1) & 0xff);
	i2c_write_data(i2c_instance,  ( ( (write_मान & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	म_लिखो("\n Write Value[1]: %02x", ( ( (write_मान & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	फर्काऊ 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
पूर्णाङ्क temperature_मान()
{
	पूर्णाङ्क timeout;
	अचिन्हित पूर्णाङ्क temp_Read_मान = 0;
	अचिन्हित दीर्घ delay = 1000;
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		यदि(config_i2c(I2C, PRESCALER_गन्ती,SCLK_गन्ती))
		{
				log_error("\tSomething Wrong In Initialization\n");
				फर्काऊ -1;
		}
	अन्यथा
				log_info("\tIntilization Happened Fine\n");
#ifdef LM75_HYST_CHECK
	write_lm75_register(I2C, LM75_HYST_REG_OFFSET, 0x30, delay);
		यदि(0 == read_lm75_register(I2C, LM75_HYST_REG_OFFSET, &temp_Read_मान, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",temp_Read_मान);
		}
		अन्यथा
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#endif
#ifdef LM75_OFFSET_CHECK
	write_lm75_register(I2C, LM75_OFFSET_REG_OFFSET, 0x35, delay);
	यदि(0 == read_lm75_register(I2C, LM75_OFFSET_REG_OFFSET, &temp_Read_मान, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",temp_Read_मान);
	}
	अन्यथा
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#endif

		यदि(0 == read_lm75_register(I2C, LM75_TEMP_REG_OFFSET, &temp_Read_मान, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			यदि(temp_Read_मान & 0x100) {
				temp_Read_मान = ( (~temp_Read_मान) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",temp_Read_मान);
			}
			अन्यथा {
				temp_Read_मान = temp_Read_मान >> 1;
				log_info("\n\t Current Temperature:=+%u°C",temp_Read_मान);
			 }
			 फर्काऊ temp_Read_मान;
		}
		अन्यथा
		{
	//Display the error
			log_error("\nTemperature read failed.");
			 फर्काऊ 999;
		}
		delay_loop(1000, 1000);


	फर्काऊ 0;
}
