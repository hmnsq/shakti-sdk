/***********************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	          : tca9548a.c
 * Brief Description of file  : TCA9548A I2C Expander multiplexes DS3231 RTC Sensor
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
@file TCF9548A.c
@brief Contains the driver routines to multiplex ds3231 using TCA9548A.
@detail I2C based routines to read ds3231 date and time sensor over an I2C expander TCF9548A.
*/
#include <stdint.h>//Includes the definitions of standard input/output functions//
#include "i2c.h"
#include "log.h"
#include "uart.h"


#define UPDATE_TIME 1
#define I2C i2c_instance[1]

#define DS3231_SLAVE_ADDRESS 0XD0
#define DS3231_REG_OFFSET 0

#define DS3231_DEC_TO_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )

#define DELAY_VALUE 900
#define PRESCALER_COUNT 0x1F
#define SCLK_COUNT 0x91


#define TCA9548A_SLAVE_ADDRESS 0xE0 //Defines the Starting address of slave//

/** @fn int TCA_select(i2c_struct * i2c_instance, unsigned int tca_channel_select,  unsigned long delay)
 * @brief Selects the TCA9548A multiplexer channel
 * @details selects TCF9548A channel using "tca_channel_select" over I2C Interface. 
 * @param i2c_struct*
 * @param tca_channel_select
 * @param delay
 * @return  Read Status (Zero on Success).
 */
int TCA_select(i2c_struct * i2c_instance, unsigned int tca_channel_select,  unsigned long delay){
	i2c_send_slave_address(i2c_instance, TCA9548A_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_data(i2c_instance, 1 << tca_channel_select /*TCA_Channel_selection*/, delay);
	//log_info("\n\tselected channel %u :", tca_channel_select);
	i2c_instance->control = I2C_STOP;
	return 0;
}




/** @fn int read_ds3231_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
 * @brief Reads the date and time field of DS3231 registers.
 * @details Reads the date value (date, month and year) and time (hour, minutes and seconds) 
 * DS3231 registers.
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param length
 * @param delay
 * @return read status (Zero of success)
 */
int read_ds3231_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
{
	unsigned char read_buf[4] = {'\0'};
	int i = 0, j = 0,  k = 0, status=0;
	unsigned char temp = 0;

//Writes the slave address for write
		i2c_send_slave_address(i2c_instance, DS3231_SLAVE_ADDRESS, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_data(i2c_instance, reg_offset, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_address(i2c_instance, DS3231_SLAVE_ADDRESS, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_data(i2c_instance, &temp, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		for(i = 0; i < length; i++)
		{
			i2c_read_data(i2c_instance, &temp, delay);
			*readTemp = temp;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			if( i == (length - 2) )
				i2c_instance->control = I2C_NACK;
			*readTemp++;
		}
		i2c_instance->control = I2C_STOP;
		return 0;
}

/** @fn int write_ds3231_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief configures the DS3231 date and time format.
 * @details Configures the DS3231 Configuration registers with the required 
 * Date and time format over I2C interface.
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param length
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
int write_ds3231_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
{
	int i = 0, j = 0,  k = 0, status=0;
	unsigned int temp = 0;
		i2c_send_slave_address(i2c_instance, DS3231_SLAVE_ADDRESS, I2C_WRITE, delay);
		i2c_write_data(i2c_instance, reg_offset, delay);
		for(i = 0; i < length; i++)
	{
		i2c_write_data(i2c_instance,  ( *write_value++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


	return 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
unsigned int ds3231_decimal_to_hex(unsigned int decimal)
{
	return( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
void main()
{
		int timeout;
		unsigned int tempReadValue = 0;
		unsigned long delay = 1000;
		unsigned int write_buf0[7] = {0x00}, read_buf[7] = {0x00};
		unsigned int write_buf1[7] = {0x00};
		unsigned char length;
		unsigned int hour[2], minute[2], second[2], date[2], month[2], year[2];


		unsigned int tca_channel_select =0;
		int failed=0;
	
		hour[0] = 11;
		minute[0] = 46;
		second[0] = 30;
	
		date[0] = 25;
		month[0] = 01;
		year[0] = 2020;
	
		write_buf0[0] = DS3231_DEC_TO_HEX(second[0]); //Seconds
		write_buf0[1] = DS3231_DEC_TO_HEX(minute[0]); //Minutes
		write_buf0[2] = DS3231_DEC_TO_HEX(hour[0]); //Hours
	
		write_buf0[4] = DS3231_DEC_TO_HEX(date[0]); //Seconds
		write_buf0[5] = DS3231_DEC_TO_HEX(month[0]); //Minutes
		write_buf0[6] = DS3231_DEC_TO_HEX( (year[0] % 100) ); //Hours
	
		write_buf0[3] = dayofweek(date[0], month[0], year[0]) + 1;


		hour[1] = 11;
		minute[1] = 25;
		second[1] = 20;
	
		date[1] = 9;
		month[1] = 9;
		year[1] = 1998;
	
		write_buf1[0] = DS3231_DEC_TO_HEX(second[1]); //Seconds
		write_buf1[1] = DS3231_DEC_TO_HEX(minute[1]); //Minutes
		write_buf1[2] = DS3231_DEC_TO_HEX(hour[1]); //Hours
	
		write_buf1[4] = DS3231_DEC_TO_HEX(date[1]); //Seconds
		write_buf1[5] = DS3231_DEC_TO_HEX(month[1]); //Minutes
		write_buf1[6] = DS3231_DEC_TO_HEX( (year[1] % 100) ); //Hours
	
		write_buf1[3] = dayofweek(date[1], month[1], year[1]) + 1;




		length = 7;



	//	set_baud_rate(uart_instance[0], 115200);
		printf("\nHello Welcome to Shakti");

		i2c_init();

		if(config_i2c(I2C, PRESCALER_COUNT, SCLK_COUNT))
		{
			log_error("\tSomething Wrong In Initialization\n");
			return -1;
		}
		else
			log_info("\tIntilization Happened Fine\n");


		for(unsigned int index=0;index<2;index++){
			failed = TCA_select(I2C, index , delay);
			if(!failed){
				log_info("\nTCF9548A channel selection success. Selected channel %u", tca_channel_select);
			}
			else{
					log_error("\nTCF9548A channel selection failed for channel %u", tca_channel_select);
			}
			#ifdef UPDATE_TIME
				if(index==1){
				write_ds3231_registers(I2C, 0x00, &write_buf0[0], length, delay);
				printf("\n Write complete for channel: %u ", index);
				log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
				}
				else{
				write_ds3231_registers(I2C, 0x00, &write_buf1[0], length, delay);
				printf("\n Write complete for channel: %u ", index);
				log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
				}
			#endif
		}

	while(1)
	{

		/* Start of TCA9548A channel selection code*/
		
		/*tca_channel_select is used for channel selection. tca_channel_select will always remain in the range 0 to 7 */
		
		tca_channel_select = tca_channel_select % 2;
		failed = TCA_select(I2C, tca_channel_select , delay);
		if(!failed){
			log_info("\nTCF9548A channel selection success. Selected channel %u", tca_channel_select);
		}
		else{
				log_error("\nTCF9548A channel selection failed for channel %u", tca_channel_select);
		}
		/* End of TCA9548A channel selection code*/

		read_ds3231_registers(I2C, DS3231_REG_OFFSET, &read_buf[0], 7, 800);
		
		log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
		
			switch(read_buf[3])
		{
			case 1:
					log_info( "   Sunday; ");
					break;

			case 2:
					log_info( "   Monday; ");
					break;

			case 3:
					log_info( "  Tuesday; ");
					break;

			case 4:
					log_info( "Wednesday; ");
					break;

			case 5:
					log_info( " Thursday; ");
					break;

			case 6:
					log_info( "   Friday; ");
					break;

			case 7:
					log_info( " Saturday; ");
					break;
		}
		log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
		delay_loop(1000, 1000);
		tca_channel_select++;

	}
}

