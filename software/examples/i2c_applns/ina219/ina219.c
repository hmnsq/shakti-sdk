/***********************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	          : ina219.c
 * Brief Description of file  : monitor current/power i2c interface
 * Student Name               : Kolan Nikshith Reddy
 * Student email              : cs20m030@smail.iitm.ac.in
 * Mentor Name                : Kotteeswaran
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
@file ina219.c
@brief Contains the driver routines to configure and read current/power.
@detail I2C based routines to configures and read current/power using ina219 sensor.
*/
#include <stdint.h>//Includes the definitions of standard input/output functions//
#include "i2c.h"
#include "log.h"
#include "uart.h"

#define I2C i2c_instance[0]

#define DELAY_VALUE 900
#define PRESCALER_COUNT 0x1F
#define SCLK_COUNT 0x91

#define INA219_SLAVE_ADDRESS 0x80//Defines the Starting address of slave//
#define INA219_CONFIG			    0x00
#define INA219_SHUNT_VOLTAGE		0x01 /* readonly */
#define INA219_BUS_VOLTAGE	    	0x02 /* readonly */
#define INA219_POWER			    0x03 /* readonly */
#define INA219_CURRENT			    0x04 /* readonly */
#define INA219_CALIBRATION		    0x05
#define INA219_CURRENT_LSB          50 /*  50 micro-A per bit */

/* Below Two values - depend on use case */
#define INA219_CALIBRATION_VALUE    4096	/* default value  */
#define INA219_CONFIG_VALUE		    0x399F	    /* PGA=8 */


/** @fn int read_ina219_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readValue, unsigned long delay)
 * @brief Read the ina219 register.
 * @details Reads the value of the passed register of ina219 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readValue
 * @param delay
 * @return  Read Status (Zero on Success).
 */
int read_ina219_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readValue, unsigned long delay)
{
	unsigned char read_buf[4] = {'\0'};
	int i = 0, j = 0,  k = 0, status=0;
	unsigned char temp = 0;
//Writes the slave address for write
	
	i2c_send_slave_address(i2c_instance, INA219_SLAVE_ADDRESS, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, reg_offset , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, INA219_SLAVE_ADDRESS, I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);
//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &read_buf[1], delay);
	//i2c_instance->control = I2C_NACK;
//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*readValue = (read_buf[1] << 8) | (read_buf[0]);
	return 0;
}



/** @fn int write_ina219_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief Writes the value into passed ina219 register 
 * @details Writes the passed value into the passed ina219 register address over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param delay
 * @return Write Status (Zero on Success)
 */
int write_ina219_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value,  unsigned long delay)
{
	i2c_send_slave_address(i2c_instance, INA219_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_data(i2c_instance, reg_offset /*INA219 */, delay);
	i2c_write_data(i2c_instance,  ( (write_value >> 8) & 0xff )/*MSB byte*/, delay);
	//printf("\n Write Value[0]: %02x", (write_value >> 8) & 0xff);
	i2c_write_data(i2c_instance,   write_value  & 0xff /* LSB */, delay);
	//printf("\n Write Value[1]: %02x", write_value & 0xff);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	return 0;
}



/** @fn int main()
 * @brief reads power, current, shunt voltage, Bus voltage value from ina219 and prints the same.
 * @details Configures the ina219, Reads the encoded  value, 
 * calculates the actual value and prints the same.
 * @return Zero
 */
int main()
{
	int timeout;
	unsigned int tempReadValue = 0;
	unsigned long delay = 1000;
	log_debug("\n\tI2C: INA219 CURRENT/POWER MONITOR Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
	if(config_i2c(I2C, PRESCALER_COUNT,SCLK_COUNT))
	{
			log_error("\tSomething Wrong In Initialization\n");
			return -1;
	}
	else
			log_info("\tIntilization Happened Fine\n");
	
	int failed = 1;
	failed = write_ina219_register(I2C, INA219_CONFIG,INA219_CONFIG_VALUE,  delay);
	if( !failed  ){
		log_info("\tConfiguration Happened Fine\n");

	}else{
		log_error("\t Configuration failed!\n");
		return -1;
	}

	failed = 1;
	failed = write_ina219_register(I2C, INA219_CALIBRATION,(INA219_CALIBRATION_VALUE << 1), delay);
	if(!failed ){
		log_info("\tCalibration Happened Fine\n");

	}else{
		log_error("\t Configuration failed! Current and Power Values cant be measured. Bus voltage and shunt can be measured.\n");
			//return -1;
	}


	log_info("\n\t***..started reading into ina219..***\n");
	while(1)
		{
			int shuntValue = 0;
			int currentValue =0 ;
			int powerValue = 0;
			int busValue = 0;
			int shuntSign=0;

			failed = 1;
			failed = read_ina219_register(I2C, INA219_SHUNT_VOLTAGE, &tempReadValue, delay);
			if(!failed )
			{	
				//log_info("shunt:  %d", tempReadValue);
				if(tempReadValue & 0x8000) {
					tempReadValue = ( (~tempReadValue) + 1 );
					shuntSign = 1;

				}
				shuntValue = tempReadValue/100; //multiplying pow(10,-2) shunt_lsb value;
				if(shuntSign)
					log_info("\n\t shunt voltage:=-%u mV",shuntValue);
				else
					log_info("\n\t shunt voltage :=%u mV",shuntValue);
			}
			else
			{
				log_error("\nc=shunt read failed.");
			}
			delay_loop(1000, 1000);


			failed = 1;
			failed = read_ina219_register(I2C, INA219_BUS_VOLTAGE, &tempReadValue, delay); 
			if( !failed)
			{
				//log_info("bus:  %d", tempReadValue);
				

				int k = tempReadValue & 1;
				if(k)
					log_error("\nc=Bus voltage read failed.");
				else{

					tempReadValue = tempReadValue >> 3;
					busValue = tempReadValue *4;
					log_info("\n\t Bus voltage  :=%u mV",busValue);
				}

			}
			else
			{
				log_error("\nc=Bus voltage read failed.");
			}
			delay_loop(1000, 1000);

			// currentValue = ((float)(shuntValue * INA219_CALIBRATION_VALUE ) / 4096) * INA219_CURRENT_LSB;
			// log_info("\n\t Current calculated using formula:=%u mA\n", currentValue);

			// powerValue = ((float)( (float)currentValue * (float)busValue/1000 ) / 5000) * 20 * INA219_CURRENT_LSB;
			// log_info("\n\t Power calculated using formula :=%u mW\n", powerValue);
		
			failed = 1;
			failed = read_ina219_register(I2C, INA219_CURRENT, &tempReadValue, delay); 
			if(!failed )
			{
				//log_info("\n\t Current reg value: %u", tempReadValue);
						
				log_info("\n\t Current :=%u mA",(tempReadValue *  INA219_CURRENT_LSB)/1000 );
				
			}
			else
			{
				log_error("\nCurrent read failed.");
			}
			delay_loop(1000, 1000);


			failed = 1;
			failed = read_ina219_register(I2C, INA219_POWER, &tempReadValue, delay); 
			if( !failed)
			{
					//log_info("\n\t Power reg value: %u", tempReadValue);
					log_info("\n\t Power :=%d mW\n",(tempReadValue * 20 * INA219_CURRENT_LSB)/1000);
			}
			else
			{
				log_error("\nc=Power read failed.");
			}
			delay_loop(1000, 1000);
		}


	return 0;
}
