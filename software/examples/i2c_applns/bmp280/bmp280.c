/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: bmp280.c
* Brief Description of file     : It helps to find the temperature and pressure of a surroundings. 
* Name of Author    	        : Soutrick Roy Chowdhury
* Email ID                      : soutrick97@gmail.com

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
@file bmp280.c
@brief Implements i2c functionality.
@detail It helps to find the temperature and pressure of a surroundings.
*/

#অন্তর্ভাব <stdint.h>//Includes the definitions of standard input/output functions//
#অন্তর্ভাব "i2c.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "uart.h"

#define I2C i2c_instance[1]

#define BMP280_SLAVE_ADDRESS 0xEC	//Defines the Starting address of slave//
#define DELAY_মান 900
#define PRESCALER_গুনতি 0x1F
#define SCLK_গুনতি 0x91
#define BMP280_CTRL_MEANS 0xF4
#define BMP280_NORMAL_MODE 0x26
#define BMP280_STATUS_REGISTER 0xF3
#define BMP280_CONFIG_REGISTER 0xF5
#define BMP280_RESET_REGISTER 0xE0

#define BMP280_REG_DIG_T1 0x88
#define BMP280_REG_DIG_T2 0x8A
#define BMP280_REG_DIG_T3 0x8C

#define BMP280_REG_DIG_P1 0x8E
#define BMP280_REG_DIG_P2 0x90
#define BMP280_REG_DIG_P3 0x92
#define BMP280_REG_DIG_P4 0x94
#define BMP280_REG_DIG_P5 0x96
#define BMP280_REG_DIG_P6 0x98
#define BMP280_REG_DIG_P7 0x9A
#define BMP280_REG_DIG_P8 0x9C
#define BMP280_REG_DIG_P9 0x9E

uint16_t bmp280_calib_dig_T1;
int16_t  bmp280_calib_dig_T2;
int16_t  bmp280_calib_dig_T3;

uint16_t bmp280_calib_dig_P1;
int16_t  bmp280_calib_dig_P2;
int16_t  bmp280_calib_dig_P3;
int16_t  bmp280_calib_dig_P4;
int16_t  bmp280_calib_dig_P5;
int16_t  bmp280_calib_dig_P6;
int16_t  bmp280_calib_dig_P7;
int16_t  bmp280_calib_dig_P8;
int16_t  bmp280_calib_dig_P9;

/** @fn int read_bmp280_register(i2c_struct *i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned long delay) 
 * @brief It helps to read the register value of the bmp280.
 * @details It reads the 1byte register value of the chip.
 * @warning The slave should have support for this option.
 * @param i2c_struct *i2c_instance  It uses i2c_instance[0].
 * @param unsigned int reg_offset  Used to store the register offset value.
 * @param unsigned int *readTemp  Reading the temperature value.
 * @param unsigned long delay  Used delay for I2C functionality.
 * @return It returns the value to the main.
 */
পূর্ণাঙ্ক read_bmp280_register(i2c_struct *i2c_instance, unsigned পূর্ণাঙ্ক reg_offset, unsigned পূর্ণাঙ্ক *readTemp, unsigned long delay)
{
	unsigned বর্ণ read_buf[4] = {'\0'};
	পূর্ণাঙ্ক i = 0, j = 0,  k = 0, status=0;
	unsigned বর্ণ temp = 0;
//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_WRITE, 800);

//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, reg_offset , delay);

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);
	i2c_instance->control = I2C_NACK;

//Reads the MSB Byte of temperature [D9 - D1]
	i2c_read_data(i2c_instance, &read_buf[0], delay);

	i2c_instance->control = I2C_STOP;
	*readTemp = read_buf[0] ;
	প্রত্যাগম 0;
}

/** @fn int read_bmp280_values(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned long *pressure, unsigned long *temperature, unsigned long delay) 
 * @brief Functions used to reads the temperature and pressure values.
 * @details It reads 8bits data of temperature and pressure.
 * @warning The slave should have support for this option.
 * @param i2c_struct * i2c_instance  It uses i2c_instance[0].
 * @param unsigned int reg_offset  Used to store the register offset value.
 * @param unsigned long *pressure  Reading the pressure value.
 * @param unsigned long *temperature  Reading the temperature value.
 * @param unsigned long delay  Used delay for I2C functionality.
 */
পূর্ণাঙ্ক read_bmp280_মানসমূহ(i2c_struct * i2c_instance, unsigned পূর্ণাঙ্ক reg_offset, unsigned long *pressure, unsigned long *temperature, unsigned long delay)
{
	unsigned বর্ণ read_buf[6] = {'\0'};
	পূর্ণাঙ্ক i = 0, j = 0,  k = 0, status=0;
	int32_t adc_P, adc_T, var1, var2, var3, var4, t_fine, temp;
	int32_t p;

//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_WRITE, 800);

//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, reg_offset , delay);

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);

//Read Pressure
	i2c_read_data(i2c_instance, &read_buf[0], delay);
	i2c_read_data(i2c_instance, &read_buf[1], delay);
	i2c_read_data(i2c_instance, &read_buf[2], delay);
	
//Read Temperature	
	i2c_read_data(i2c_instance, &read_buf[3], delay);
	i2c_read_data(i2c_instance, &read_buf[4], delay);
	i2c_instance->control = I2C_NACK;
	i2c_read_data(i2c_instance, &read_buf[5], delay);
	
	i2c_instance->control = I2C_STOP;
	adc_P = ((read_buf[0] << 12) | (read_buf[1] << 4) | (read_buf[2] >> 4));
	adc_T = ((read_buf[3] << 12) | (read_buf[4] << 4) | (read_buf[5] >> 4));

// Calculate TEMPERATURE
	var1 = ((((adc_T / 8) - ((int32_t)bmp280_calib_dig_T1 * 2))) * ((int32_t)bmp280_calib_dig_T2)) / 2048;
  	var2 = (((((adc_T / 16) - ((int32_t)bmp280_calib_dig_T1)) * ((adc_T / 16) - ((int32_t)bmp280_calib_dig_T1))) / 4096) * ((int32_t)bmp280_calib_dig_T3)) / 16384;
  	t_fine = var1 + var2;
	temp = (t_fine * 5 + 128) / 256;
	*temperature = temp;
	printf("\nTemperature Value:%u.%u °C", (temp/100),(temp%100));

//Calculate Pressure
	var1 = 0; var2 = 0;
	var1 = (((int32_t)t_fine) / 2) - (int32_t)64000;
	var2 = (((var1/4) * (var1/4)) / 2048 ) * ((int32_t)bmp280_calib_dig_P6);
	var2 = var2 + ((var1 * ((int32_t)bmp280_calib_dig_P5)) * 2);
	var2 = (var2/4) + (((int32_t)bmp280_calib_dig_P4) * 65536);
	var1 = ((((int32_t)bmp280_calib_dig_P3 * (((var1/4) * (var1/4)) / 8192 )) / 8) + ((((int32_t)bmp280_calib_dig_P2) * var1)/2)) / 262144;
	var1 =((((32768 + var1)) * ((int32_t)bmp280_calib_dig_P1)) / 32768);

	যদি (var1 == 0)
		প্রত্যাগম 0; // avoid exception caused by division by zero

	p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2 / 4096))) * 3125;

	যদি (p < 0x80000000)
		p = (p * 2) / ((uint32_t)var1);

	অন্যথা
		p = (p / (uint32_t)var1) * 2;

	var1 = (((int32_t)bmp280_calib_dig_P9) * ((int32_t)(((p/8) * (p/8)) / 8192))) / 4096;
	var2 = (((int32_t)(p/4)) * ((int32_t)bmp280_calib_dig_P8)) / 8192;

	p = (uint32_t)((int32_t)p + ((var1 + var2 + (int32_t)bmp280_calib_dig_P7) / 16));
	*pressure = p;
	printf("\nThe Pressure Value:%u.%u Kpa",(p/1000),(p%1000));
		প্রত্যাগম 0;
}

/** @fn short read_bmp280_values16(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned long delay)
 * @brief Functions is used to read 16bits values.
 * @details It used to read 16bits from the chips.
 * @warning The slave should have support for this option.
 * @param i2c_struct * i2c_instance  It uses i2c_instance[0].
 * @param unsigned int reg_offset  Used to store the register offset value.
 * @param unsigned long delay  Used delay for I2C functionality.
 * @return It returns 16bits value to the main.
 */
short read_bmp280_values16(i2c_struct * i2c_instance, unsigned পূর্ণাঙ্ক reg_offset, unsigned long delay)
{
	unsigned বর্ণ read_buf[2] = {'\0'};
	পূর্ণাঙ্ক i = 0, j = 0,  k = 0, status=0;
	int8_t temp = 0;

//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_WRITE, 800);

//Writes the pointer to address that needs to be read
	i2c_write_data(i2c_instance, reg_offset , delay);

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;

//Writes the slave address for read
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_READ, 800);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_data(i2c_instance, &temp, delay);

	i2c_read_data(i2c_instance, &read_buf[0], delay);
	i2c_instance->control = I2C_NACK;
	i2c_read_data(i2c_instance, &read_buf[1], delay);
	i2c_instance->control = I2C_STOP;

	প্রত্যাগম ( ( read_buf[1] << 8 ) | read_buf[0] );	
}

/** @fn int write_bmp280_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned char write_value, unsigned long delay) 
 * @brief It used to write the desired value to the register.
 * @details To get the result chip have to given the instruction by writing a value to yhe register.
 * @warning The slave should have support for this option.
 * @param i2c_struct * i2c_instance  It uses i2c_instance[0].
 * @param unsigned int reg_offset  Used to store the register offset value.
 * @param unsigned char write_value  Passing the value want write to register.
 * @param unsigned long delay  Used delay for I2C functionality.
 * @return Returns 0 to the main after stopping I2C.
 */
পূর্ণাঙ্ক write_bmp280_register(i2c_struct * i2c_instance, unsigned পূর্ণাঙ্ক reg_offset, unsigned বর্ণ write_মান, unsigned long delay)
{
	পূর্ণাঙ্ক i = 0, j = 0, k = 0, status=0;
	unsigned পূর্ণাঙ্ক temp = 0;
	i2c_send_slave_address(i2c_instance, BMP280_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_data(i2c_instance, reg_offset , delay);
	i2c_write_data(i2c_instance, write_মান , delay);

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	প্রত্যাগম 0;
}

/** @fn int main()
 * @brief Helps to get temperature and pressure as a output.
 * @details By passing the value and calling the functions according to the datasheet we will get the perfect result.
 * @warning All the functions should call accordingly to get the perfect output.
 * @return It returns 0.
 */
পূর্ণাঙ্ক main()
{
	পূর্ণাঙ্ক timeout;
	unsigned পূর্ণাঙ্ক temp_Read_মান = 0;
	unsigned long delay = 1000;
	unsigned long pressure = 0, temperature = 0;
	পূর্ণাঙ্ক len;
	log_debug("\n\tI2C: BMP280 Temperature Sensor I2C read\n");
	i2c_init();

	//Initialises I2C Controller
	যদি(config_i2c(I2C, PRESCALER_গুনতি,SCLK_গুনতি))
	{
		log_error("\tSomething Wrong In Initialization\n");
		প্রত্যাগম -1;
	}
	অন্যথা
		log_info("\tIntilization BMP280_STATUS_REGISTER Happened Fine\n");

	write_bmp280_register(I2C, BMP280_CONFIG_REGISTER, 0xC0, delay);
	write_bmp280_register(I2C, BMP280_CTRL_MEANS, 0x27, delay);

	যদি(0 == read_bmp280_register(I2C, 0xD0, &temp_Read_মান, delay))
	{
		যদি (0x58 != temp_Read_মান)
		{
			printf("\n Device Not detected");
			প্রত্যাগম -1;
		}
	}
		
	write_bmp280_register(I2C, BMP280_RESET_REGISTER, 0xB6, delay);
	read_bmp280_register(I2C, BMP280_RESET_REGISTER, &temp_Read_মান, delay);
	
	bmp280_calib_dig_T1 = read_bmp280_values16(I2C, BMP280_REG_DIG_T1, delay);
	bmp280_calib_dig_T2 = read_bmp280_values16(I2C, BMP280_REG_DIG_T2, delay);
	bmp280_calib_dig_T3 = read_bmp280_values16(I2C, BMP280_REG_DIG_T3, delay);

	bmp280_calib_dig_P1 = read_bmp280_values16(I2C, BMP280_REG_DIG_P1, delay);
	bmp280_calib_dig_P2 = read_bmp280_values16(I2C, BMP280_REG_DIG_P2, delay);
	bmp280_calib_dig_P3 = read_bmp280_values16(I2C, BMP280_REG_DIG_P3, delay);
	bmp280_calib_dig_P4 = read_bmp280_values16(I2C, BMP280_REG_DIG_P4, delay);
	bmp280_calib_dig_P5 = read_bmp280_values16(I2C, BMP280_REG_DIG_P5, delay);
	bmp280_calib_dig_P6 = read_bmp280_values16(I2C, BMP280_REG_DIG_P6, delay);
	bmp280_calib_dig_P7 = read_bmp280_values16(I2C, BMP280_REG_DIG_P7, delay);
	bmp280_calib_dig_P8 = read_bmp280_values16(I2C, BMP280_REG_DIG_P8, delay);
	bmp280_calib_dig_P9 = read_bmp280_values16(I2C, BMP280_REG_DIG_P9, delay);

যাবত্(1)
	{
		write_bmp280_register(I2C, BMP280_CTRL_MEANS, BMP280_NORMAL_MODE, delay );     // Set it to NORMAL MODE
		যদি(0 == read_bmp280_register(I2C, BMP280_STATUS_REGISTER, &temp_Read_মান, delay))
		{
			যদি(!(temp_Read_মান & 0x9))
			{
			//Read pressure and temperature values.
			read_bmp280_মানসমূহ(I2C, 0xF7, &pressure, &temperature, delay);
			}
		}
			অন্যথা
			{
			//Display the error
				log_error("\nTemperature read failed.");
			}
			delay_loop(2000, 2000);
	}
	প্রত্যাগম 0;
}
