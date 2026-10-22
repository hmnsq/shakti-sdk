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

#परिभाषय I2C i2c_instance[0]

#परिभाषय LM75_SLAVE_स्थानाङ्कः 0x90//Defines the Starting address of slave//
#परिभाषय LM75_अस्थायी_REG_विस्थापनम् 0x00
#परिभाषय LM75_CONF_REG_विस्थापनम् 0x01
#परिभाषय LM75_HYST_REG_विस्थापनम् 0x02
#परिभाषय LM75_विस्थापनम्_REG_विस्थापनम् 0x03

#परिभाषय DELAY_मानम् 900
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
पूर्णाङ्क read_lm75_पञ्जिकाकोशः(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *read_अस्थायी, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;
//Writes the slave address for write
	i2c_send_slave_स्थानाङ्कः(i2c_instance, LM75_SLAVE_स्थानाङ्कः, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम् , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;


//Writes the slave address for read
	i2c_send_slave_स्थानाङ्कः(i2c_instance, LM75_SLAVE_स्थानाङ्कः, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_दत्त(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_दत्त(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*read_अस्थायी = (read_buf[1] << 1) | (read_buf[0] >> 7);

	प्रत्यागम 0;
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
पूर्णाङ्क write_lm75_पञ्जिकाकोशः(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क write_मानम्, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
	i2c_send_slave_स्थानाङ्कः(i2c_instance, LM75_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम् /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_दत्त(i2c_instance,  ( (write_मानम् >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	प्रारूप_लिख("\n Write Value[0]: %02x", (write_मानम् >> 1) & 0xff);
	i2c_write_दत्त(i2c_instance,  ( ( (write_मानम् & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	प्रारूप_लिख("\n Write Value[1]: %02x", ( ( (write_मानम् & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	प्रत्यागम 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
पूर्णाङ्क मुख्यम्()
{
	पूर्णाङ्क timeout;
	अचिह्नित पूर्णाङ्क अस्थायी_Read_मानम् = 0;
	अचिह्नित दीर्घ delay = 1000;
//	set_baud_rate(uart_instance[0], 115200);
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		यदि(config_i2c(I2C, PRESCALER_गणनम्,SCLK_गणनम्))
		{
				log_error("\tSomething Wrong In Initialization\n");
				प्रत्यागम -1;
		}
	अन्यथा
				log_info("\tIntilization Happened Fine\n");
#यदि_परिभाषितम् LM75_HYST_CHECK
	write_lm75_पञ्जिकाकोशः(I2C, LM75_HYST_REG_विस्थापनम्, 0x30, delay);
		यदि(0 == read_lm75_पञ्जिकाकोशः(I2C, LM75_HYST_REG_विस्थापनम्, &अस्थायी_Read_मानम्, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",अस्थायी_Read_मानम्);
		}
		अन्यथा
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#यदि_अन्तः
#यदि_परिभाषितम् LM75_विस्थापनम्_CHECK
	write_lm75_पञ्जिकाकोशः(I2C, LM75_विस्थापनम्_REG_विस्थापनम्, 0x35, delay);
	यदि(0 == read_lm75_पञ्जिकाकोशः(I2C, LM75_विस्थापनम्_REG_विस्थापनम्, &अस्थायी_Read_मानम्, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",अस्थायी_Read_मानम्);
	}
	अन्यथा
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#यदि_अन्तः
	यावत्(1)
	{

		यदि(0 == read_lm75_पञ्जिकाकोशः(I2C, LM75_अस्थायी_REG_विस्थापनम्, &अस्थायी_Read_मानम्, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			यदि(अस्थायी_Read_मानम् & 0x100) {
				अस्थायी_Read_मानम् = ( (~अस्थायी_Read_मानम्) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",अस्थायी_Read_मानम्);
			}
			अन्यथा {
				अस्थायी_Read_मानम् = अस्थायी_Read_मानम् >> 1;
				log_info("\n\t Current Temperature:=+%u°C",अस्थायी_Read_मानम्);
			 }
		}
		अन्यथा
		{
	//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}


	प्रत्यागम 0;
}
