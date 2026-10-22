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
#అన్తర్భావ <stdint.h>//Includes the definitions of standard input/output functions//
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు I2C i2c_instance[1]

#నిర్వచించు LM75_SLAVE_చిరునామా 0x90//Defines the Starting address of slave//
#నిర్వచించు LM75_తాత్కాలిక_REG_స్థానభ్రంశం 0x00
#నిర్వచించు LM75_CONF_REG_స్థానభ్రంశం 0x01
#నిర్వచించు LM75_HYST_REG_స్థానభ్రంశం 0x02
#నిర్వచించు LM75_స్థానభ్రంశం_REG_స్థానభ్రంశం 0x03

#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91

/** @fn int read_lm75_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay)
 * @brief Read the lm75 register.
 * @details Reads the value of the passed register of LM75 over I2C Interface. 
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param delay
 * @return  Read Status (Zero on Success).
 */
పూర్ణాంకం read_lm75_రిజిస్టరు(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *read_తాత్కాలిక, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;
//Writes the slave address for write
	i2c_send_slave_చిరునామా(i2c_instance, LM75_SLAVE_చిరునామా, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం , delay);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;


//Writes the slave address for read
	i2c_send_slave_చిరునామా(i2c_instance, LM75_SLAVE_చిరునామా, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_దత్తాంశం(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_దత్తాంశం(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_STOP;
	*read_తాత్కాలిక = (read_buf[1] << 1) | (read_buf[0] >> 7);

	తిరిగి 0;
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
పూర్ణాంకం write_lm75_రిజిస్టరు(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం write_విలువ, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
	i2c_send_slave_చిరునామా(i2c_instance, LM75_SLAVE_చిరునామా, I2C_WRITE, delay);
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం /*LM75_TEMP_REG_OFFSET */, delay);
	i2c_write_దత్తాంశం(i2c_instance,  ( (write_విలువ >> 1) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	రాయి("\n Write Value[0]: %02x", (write_విలువ >> 1) & 0xff);
	i2c_write_దత్తాంశం(i2c_instance,  ( ( (write_విలువ & 0x01) << 7) & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	రాయి("\n Write Value[1]: %02x", ( ( (write_విలువ & 0x01) << 7) & 0xff));
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	తిరిగి 0;
}

/** @fn int main()
 * @brief reads temperature value from lm75 and prints the same.
 * @details Configures the LM75, Reads the encoded temperature value, 
 * calculates the actual temperature value and prints the same.
 * @return Zero
 */
పూర్ణాంకం temperature_విలువ()
{
	పూర్ణాంకం timeout;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక_Read_విలువ = 0;
	గుర్తులేని దీర్ఘ delay = 1000;
    
	log_debug("\n\tI2C: LM75 Temperature Sensor I2C read\n");
    i2c_init();
	//Initialises I2C Controller
		ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క,SCLK_లెక్క))
		{
				log_error("\tSomething Wrong In Initialization\n");
				తిరిగి -1;
		}
	లేకపోతే
				log_info("\tIntilization Happened Fine\n");
#నిర్వచితమైతే LM75_HYST_CHECK
	write_lm75_రిజిస్టరు(I2C, LM75_HYST_REG_స్థానభ్రంశం, 0x30, delay);
		ఒకవేళ(0 == read_lm75_రిజిస్టరు(I2C, LM75_HYST_REG_స్థానభ్రంశం, &తాత్కాలిక_Read_విలువ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
//				tempReadValue = ( (~tempReadValue) + 1 );
				log_info("\n\t Hyst Reg Value:=%u",తాత్కాలిక_Read_విలువ);
		}
		లేకపోతే
		{
	//Display the error
			log_error("\nHyst Reg Value failed.");
		}
#అయితే_ముగింపు
#నిర్వచితమైతే LM75_స్థానభ్రంశం_CHECK
	write_lm75_రిజిస్టరు(I2C, LM75_స్థానభ్రంశం_REG_స్థానభ్రంశం, 0x35, delay);
	ఒకవేళ(0 == read_lm75_రిజిస్టరు(I2C, LM75_స్థానభ్రంశం_REG_స్థానభ్రంశం, &తాత్కాలిక_Read_విలువ, delay))
	{
		//Display Temperature value
			log_info("\n\t Offset Reg Value:=%u",తాత్కాలిక_Read_విలువ);
	}
	లేకపోతే
	{
//Display the error
		log_error("\nOffset Reg Value failed.");
	}
#అయితే_ముగింపు

		ఒకవేళ(0 == read_lm75_రిజిస్టరు(I2C, LM75_తాత్కాలిక_REG_స్థానభ్రంశం, &తాత్కాలిక_Read_విలువ, delay))
		{
			//Display Temperature value
//			printf("\nTemperature read value is %x", tempReadValue);
			ఒకవేళ(తాత్కాలిక_Read_విలువ & 0x100) {
				తాత్కాలిక_Read_విలువ = ( (~తాత్కాలిక_Read_విలువ) + 1 ) >> 1;
				log_info("\n\t Current Temperature:=-%u°C",తాత్కాలిక_Read_విలువ);
			}
			లేకపోతే {
				తాత్కాలిక_Read_విలువ = తాత్కాలిక_Read_విలువ >> 1;
				log_info("\n\t Current Temperature:=+%u°C",తాత్కాలిక_Read_విలువ);
			 }
			 తిరిగి తాత్కాలిక_Read_విలువ;
		}
		లేకపోతే
		{
	//Display the error
			log_error("\nTemperature read failed.");
			 తిరిగి 999;
		}
		delay_loop(1000, 1000);


	తిరిగి 0;
}
