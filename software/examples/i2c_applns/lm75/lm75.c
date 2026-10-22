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
#અન્તર્ભાવ <stdint.h>//Includes the definitions of standard input/output functions//
#અન્તર્ભાવ "i2c.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "uart.h"

#define I2C i2c_instance[0]

#define LM75_SLAVE_ADDRESS 0x90//Defines the Starting address of slave//
#define LM75_TEMP_REG_OFFSET 0x00
#define LM75_CONF_REG_OFFSET 0x01
#define LM75_HYST_REG_OFFSET 0x02
#define LM75_OFFSET_REG_OFFSET 0x03

#define DELAY_કિંમત 900
#define PRESCALER_ગણતરી 0x1F
#define SCLK_ગણતરી 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
પૂર્ણાંક read_lm75_register(i2c_struct * i2c_instance, unsigned પૂર્ણાંક reg_offset, unsigned પૂર્ણાંક *readTemp, unsigned long delay)
{
	unsigned અક્ષર read_buf[4] = {'\0'};
	પૂર્ણાંક i = 0, j = 0,  k = 0, status=0;
	unsigned અક્ષર temp = 0;
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

	પાછા 0;
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
પૂર્ણાંક write_lm75_register(i2c_struct * i2c_instance, unsigned પૂર્ણાંક reg_offset, unsigned પૂર્ણાંક write_કિંમત, unsigned long delay)
{
	પૂર્ણાંક i = 0, j = 0,  k = 0, status=0;
	unsigned પૂર્ણાંક temp = 0;
	i2c_send_slave_address(i2c_instance, LM75_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_data(i2c_instance, reg_offset /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_data(i2c_instance,  ( (write_કિંમત >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	printf("\n Write Value[0]: %02x", (write_કિંમત >> 1) & 0xff);
	i2c_write_data(i2c_instance,  ( ( (write_કિંમત & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	printf("\n Write Value[1]: %02x", ( ( (write_કિંમત & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	પાછા 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
પૂર્ણાંક મુખ્ય()
{
	પૂર્ણાંક timeout;
	unsigned પૂર્ણાંક temp_Read_કિંમત = 0;
	unsigned long delay = 1000;
//	set_baud_rate(uart_instance[0], 115200);
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		જો(config_i2c(I2C, PRESCALER_ગણતરી,SCLK_ગણતરી))
		{
				log_error("\tSomething Wrong In Initialization\n");
				પાછા -1;
		}
	નહીંતર
				log_info("\tIntilization Happened Fine\n");
#ifdef LM75_HYST_CHECK
	write_lm75_register(I2C, LM75_HYST_REG_OFFSET, 0x30, delay);
		જો(0 == read_lm75_register(I2C, LM75_HYST_REG_OFFSET, &temp_Read_કિંમત, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",temp_Read_કિંમત);
		}
		નહીંતર
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#endif
#ifdef LM75_OFFSET_CHECK
	write_lm75_register(I2C, LM75_OFFSET_REG_OFFSET, 0x35, delay);
	જો(0 == read_lm75_register(I2C, LM75_OFFSET_REG_OFFSET, &temp_Read_કિંમત, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",temp_Read_કિંમત);
	}
	નહીંતર
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#endif
	જ્યારે(1)
	{

		જો(0 == read_lm75_register(I2C, LM75_TEMP_REG_OFFSET, &temp_Read_કિંમત, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			જો(temp_Read_કિંમત & 0x100) {
				temp_Read_કિંમત = ( (~temp_Read_કિંમત) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",temp_Read_કિંમત);
			}
			નહીંતર {
				temp_Read_કિંમત = temp_Read_કિંમત >> 1;
				log_info("\n\t Current Temperature:=+%u°C",temp_Read_કિંમત);
			 }
		}
		નહીંતર
		{
	//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}


	પાછા 0;
}
