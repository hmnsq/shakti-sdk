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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>//Includes the definitions of standard input/output functions//
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[0]

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_SLAVE_ਪਤਾ 0x90//Defines the Starting address of slave//
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_ਆਰਜ਼ੀ_REG_ਵਿੱਥ 0x00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_CONF_REG_ਵਿੱਥ 0x01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_HYST_REG_ਵਿੱਥ 0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_ਵਿੱਥ_REG_ਵਿੱਥ 0x03

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
ਪੂਰਨ read_lm75_ਰਜਿਸਟਰ(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *read_ਆਰਜ਼ੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_buf[4] = {'\0'};
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਰਜ਼ੀ = 0;
//Writes the slave address for write
	i2c_send_slave_ਪਤਾ(i2c_instance, LM75_SLAVE_ਪਤਾ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;


//Writes the slave address for read
	i2c_send_slave_ਪਤਾ(i2c_instance, LM75_SLAVE_ਪਤਾ, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ਅੰਕੜੇ(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_ਅੰਕੜੇ(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*read_ਆਰਜ਼ੀ = (read_buf[1] << 1) | (read_buf[0] >> 7);

	ਵਾਪਸ 0;
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
ਪੂਰਨ write_lm75_ਰਜਿਸਟਰ(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_ਮੁੱਲ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;
	i2c_send_slave_ਪਤਾ(i2c_instance, LM75_SLAVE_ਪਤਾ, I2C_WRITE, delay);
	i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_ਅੰਕੜੇ(i2c_instance,  ( (write_ਮੁੱਲ >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	ਲਿਖੋ("\n Write Value[0]: %02x", (write_ਮੁੱਲ >> 1) & 0xff);
	i2c_write_ਅੰਕੜੇ(i2c_instance,  ( ( (write_ਮੁੱਲ & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	ਲਿਖੋ("\n Write Value[1]: %02x", ( ( (write_ਮੁੱਲ & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	ਵਾਪਸ 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
ਪੂਰਨ ਮੁੱਖ()
{
	ਪੂਰਨ timeout;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ_Read_ਮੁੱਲ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay = 1000;
//	set_baud_rate(uart_instance[0], 115200);
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		ਜੇ(config_i2c(I2C, PRESCALER_ਗਿਣਤੀ,SCLK_ਗਿਣਤੀ))
		{
				log_error("\tSomething Wrong In Initialization\n");
				ਵਾਪਸ -1;
		}
	ਨਹੀਂਤਾਂ
				log_info("\tIntilization Happened Fine\n");
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ LM75_HYST_CHECK
	write_lm75_ਰਜਿਸਟਰ(I2C, LM75_HYST_REG_ਵਿੱਥ, 0x30, delay);
		ਜੇ(0 == read_lm75_ਰਜਿਸਟਰ(I2C, LM75_HYST_REG_ਵਿੱਥ, &ਆਰਜ਼ੀ_Read_ਮੁੱਲ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",ਆਰਜ਼ੀ_Read_ਮੁੱਲ);
		}
		ਨਹੀਂਤਾਂ
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ LM75_ਵਿੱਥ_CHECK
	write_lm75_ਰਜਿਸਟਰ(I2C, LM75_ਵਿੱਥ_REG_ਵਿੱਥ, 0x35, delay);
	ਜੇ(0 == read_lm75_ਰਜਿਸਟਰ(I2C, LM75_ਵਿੱਥ_REG_ਵਿੱਥ, &ਆਰਜ਼ੀ_Read_ਮੁੱਲ, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",ਆਰਜ਼ੀ_Read_ਮੁੱਲ);
	}
	ਨਹੀਂਤਾਂ
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#ਜੇ_ਅੰਤ
	ਜਦੋਂ(1)
	{

		ਜੇ(0 == read_lm75_ਰਜਿਸਟਰ(I2C, LM75_ਆਰਜ਼ੀ_REG_ਵਿੱਥ, &ਆਰਜ਼ੀ_Read_ਮੁੱਲ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			ਜੇ(ਆਰਜ਼ੀ_Read_ਮੁੱਲ & 0x100) {
				ਆਰਜ਼ੀ_Read_ਮੁੱਲ = ( (~ਆਰਜ਼ੀ_Read_ਮੁੱਲ) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",ਆਰਜ਼ੀ_Read_ਮੁੱਲ);
			}
			ਨਹੀਂਤਾਂ {
				ਆਰਜ਼ੀ_Read_ਮੁੱਲ = ਆਰਜ਼ੀ_Read_ਮੁੱਲ >> 1;
				log_info("\n\t Current Temperature:=+%u°C",ਆਰਜ਼ੀ_Read_ਮੁੱਲ);
			 }
		}
		ਨਹੀਂਤਾਂ
		{
	//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}


	ਵਾਪਸ 0;
}
