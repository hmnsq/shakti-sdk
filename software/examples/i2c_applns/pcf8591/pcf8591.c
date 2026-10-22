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

#अन्तर्भाव <stdint.h>//Includes the definitions of standard input/output functions//
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#परिभाषय PCF8591_SLAVE_स्थानाङ्कः 0x90 // I2C bus address //doubt
#परिभाषय PCF8591_CONTROL_पञ्जिकाकोशः_मानम् 0x04
#परिभाषय PCF8591_REG_विस्थापनम् 0

#परिभाषय DELAY_मानम् 900
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91

#परिभाषय I2C i2c_instance[0]

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
पूर्णाङ्क read_pcf8591_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *read_अस्थायी, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;
//Writes the slave address for write
	i2c_send_slave_स्थानाङ्कः(i2c_instance, PCF8591_SLAVE_स्थानाङ्कः, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_स्थानाङ्कः(i2c_instance, PCF8591_SLAVE_स्थानाङ्कः, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);


//Reads the MSB Byte of temperature [D9 - D1]
	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
		*read_अस्थायी = अस्थायी;
		यदि( i == (दीर्घता_2 - 2) )
		i2c_instance->control = I2C_NACK;
		*read_अस्थायी++;
	}
	
	i2c_instance->control = I2C_STOP;
	प्रत्यागम 0;
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
पूर्णाङ्क write_pcf8591_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *write_मानम्, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
	i2c_send_slave_स्थानाङ्कः(i2c_instance, PCF8591_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		i2c_write_दत्त(i2c_instance,  ( *write_मानम्++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;;
	प्रत्यागम 0;
}

/** @fn int main()
 * @brief Configures and reads the ADC values.
 * @details Configures the PCF8591 to read 4 ADC values, reads the same 
 * prints the read values
 * @return Zero
 */
पूर्णाङ्क मुख्यम्()
{
	अचिह्नित वर्ण i = 0;
	पूर्णाङ्क timeout;
	अचिह्नित पूर्णाङ्क अस्थायी_Read_मानम् = 0;
	अचिह्नित दीर्घ delay = 1000;
	अचिह्नित पूर्णाङ्क write_buf[7] = {0x00}, read_buf[7] = {0x00};
	अचिह्नित वर्ण दीर्घता_2 = 0;
	
	log_debug("\tI2C: PCF8591 - ADC test\n");

	i2c_init();

	यदि(config_i2c(I2C, PRESCALER_गणनम्, SCLK_गणनम्))
	{
			log_error("\tSomething Wrong In Initialization\n");
			प्रत्यागम -1;
	}
	अन्यथा
		log_info("\tIntilization Happened Fine\n");
		दीर्घता_2 = 1;
		write_buf[0] = PCF8591_CONTROL_पञ्जिकाकोशः_मानम्;
		write_pcf8591_registers(I2C, 0x00, &write_buf[0], दीर्घता_2, delay);
		log_debug("\n Write complete");
		दीर्घता_2 = 5;
	यावत्(1)
	{
			read_pcf8591_registers(I2C, PCF8591_CONTROL_पञ्जिकाकोशः_मानम्, &read_buf[0], दीर्घता_2, 800);
			log_info("\n");
			प्रति( i = 1; i < दीर्घता_2; i++)
			log_info("\nADC Input[%d]: %x", i, read_buf[i]);
			delay_loop(3000, 2000);
	}

	प्रत्यागम 0;
}

