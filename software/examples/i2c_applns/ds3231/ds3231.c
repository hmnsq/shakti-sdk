/****************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	      : ds3231.c
 * Brief Description of file  : reads real time calendar (date & time) over i2c interface.
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

*******************************************************************************/
/**
@file ds3231.c
@brief Contains the driver routines to configure and read DS3231.
@detail I2C based routines to configures and read the RTC information from DS3231.
*/

//#include <stdint.h>//Includes the definitions of standard input/output functions//
#ଅନ୍ତର୍ଭାଵ "i2c.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "uart.h"

#define UPDATE_TIME 1
#define I2C i2c_instance[1]
#define DS3231_SLAVE_ADDRESS 0XD0
#define DS3231_REG_OFFSET 0
#define DS3231_DEC_TO_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#define DELAY_ମୂଲ୍ୟ 900
#define PRESCALER_ଗଣନା 0x1F
#define SCLK_ଗଣନା 0x91


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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_ds3231_registers(i2c_struct * i2c_instance, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା reg_offset, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *readTemp, unsigned ଅକ୍ଷର length, unsigned long delay)
{
	unsigned ଅକ୍ଷର read_buf[4] = {'\0'};
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0, j = 0,  k = 0, status=0;
	unsigned ଅକ୍ଷର temp = 0;

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
		ପାଇଁ(i = 0; i < length; i++)
		{
			i2c_read_data(i2c_instance, &temp, delay);
			*readTemp = temp;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			ଯଦି( i == (length - 2) )
				i2c_instance->control = I2C_NACK;
			*readTemp++;
		}
		i2c_instance->control = I2C_STOP;
		ଫେରନ୍ତୁ 0;
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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା write_ds3231_registers(i2c_struct * i2c_instance, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା reg_offset, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *write_ମୂଲ୍ୟ, unsigned ଅକ୍ଷର length, unsigned long delay)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0, j = 0,  k = 0, status=0;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp = 0;
		i2c_send_slave_address(i2c_instance, DS3231_SLAVE_ADDRESS, I2C_WRITE, delay);
		i2c_write_data(i2c_instance, reg_offset, delay);
		ପାଇଁ(i = 0; i < length; i++)
	{
		i2c_write_data(i2c_instance,  ( *write_ମୂଲ୍ୟ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			ଫେରନ୍ତୁ 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା dayofweek(ପୂର୍ଣ୍ଣସଂଖ୍ୟା d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା m, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    ଫେରନ୍ତୁ ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ds3231_decimal_to_hex(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା decimal)
{
	ଫେରନ୍ତୁ( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
ଶୂନ୍ୟ ମୁଖ୍ୟ()
{
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା timeout;
		unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp_Read_ମୂଲ୍ୟ = 0;
		unsigned long delay = 1000;
		unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା write_buf[7] = {0x00}, read_buf[7] = {0x00};
		unsigned ଅକ୍ଷର length;
		unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା hour, minute, second, date, month, year;
	
		hour = 11;
		minute = 46;
		second = 30;
	
		date = 25;
		month = 01;
		year = 2020;
	
		write_buf[0] = DS3231_DEC_TO_HEX(second); //Seconds
		write_buf[1] = DS3231_DEC_TO_HEX(minute); //Minutes
		write_buf[2] = DS3231_DEC_TO_HEX(hour); //Hours
	
		write_buf[4] = DS3231_DEC_TO_HEX(date); //Seconds
		write_buf[5] = DS3231_DEC_TO_HEX(month); //Minutes
		write_buf[6] = DS3231_DEC_TO_HEX( (year % 100) ); //Hours
	
		write_buf[3] = dayofweek(date, month, year) + 1;
		length = 7;
	
//	set_baud_rate(uart_instance[0], 115200);
	printf("\nHello Welcome to Shakti");

	i2c_init();

	ଯଦି(config_i2c(I2C, PRESCALER_ଗଣନା, SCLK_ଗଣନା))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ଫେରନ୍ତୁ -1;
	}
	ଅନ୍ୟଥା
		log_info("\tIntilization Happened Fine\n");
#ifdef UPDATE_TIME
	write_ds3231_registers(I2C, 0x00, &write_buf[0], length, delay);
			printf("\n Write complete");
#endif
	ଯେତେବେଳେ(1)
	{
			read_ds3231_registers(I2C, DS3231_REG_OFFSET, &read_buf[0], 7, 800);
			
			log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
			
			ବାଛ(read_buf[3])
			{
				ସ୍ଥିତି 1:
						log_info( "   Sunday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 2:
						log_info( "   Monday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 3:
						log_info( "  Tuesday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 4:
						log_info( "Wednesday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 5:
						log_info( " Thursday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 6:
						log_info( "   Friday; ");
						ଭାଙ୍ଗ;

				ସ୍ଥିତି 7:
						log_info( " Saturday; ");
						ଭାଙ୍ଗ;
			}
			log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
			delay_loop(1000, 1000);

	}
}

