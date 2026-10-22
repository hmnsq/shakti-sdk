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
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు UPDATE_సమయం 1
#నిర్వచించు I2C i2c_instance[1]
#నిర్వచించు DS3231_SLAVE_చిరునామా 0XD0
#నిర్వచించు DS3231_REG_స్థానభ్రంశం 0
#నిర్వచించు DS3231_DEC_గమ్యం_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#నిర్వచించు DELAY_విలువ 900
#నిర్వచించు PRESCALER_లెక్క 0x1F
#నిర్వచించు SCLK_లెక్క 0x91


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
పూర్ణాంకం read_ds3231_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *read_తాత్కాలిక, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;

//Writes the slave address for write
		i2c_send_slave_చిరునామా(i2c_instance, DS3231_SLAVE_చిరునామా, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_చిరునామా(i2c_instance, DS3231_SLAVE_చిరునామా, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		కొరకు(i = 0; i < నిడివి_2; i++)
		{
			i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
			*read_తాత్కాలిక = తాత్కాలిక;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			ఒకవేళ( i == (నిడివి_2 - 2) )
				i2c_instance->control = I2C_NACK;
			*read_తాత్కాలిక++;
		}
		i2c_instance->control = I2C_STOP;
		తిరిగి 0;
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
పూర్ణాంకం write_ds3231_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *write_విలువ, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
		i2c_send_slave_చిరునామా(i2c_instance, DS3231_SLAVE_చిరునామా, I2C_WRITE, delay);
		i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
		కొరకు(i = 0; i < నిడివి_2; i++)
	{
		i2c_write_దత్తాంశం(i2c_instance,  ( *write_విలువ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			తిరిగి 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
పూర్ణాంకం dayofweek(పూర్ణాంకం d, పూర్ణాంకం m, పూర్ణాంకం y)
{
    స్థిర పూర్ణాంకం t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    తిరిగి ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
గుర్తులేని పూర్ణాంకం ds3231_decimal_గమ్యం_hex(గుర్తులేని పూర్ణాంకం decimal)
{
	తిరిగి( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
శూన్య ప్రధాన()
{
		పూర్ణాంకం timeout;
		గుర్తులేని పూర్ణాంకం తాత్కాలిక_Read_విలువ = 0;
		గుర్తులేని దీర్ఘ delay = 1000;
		గుర్తులేని పూర్ణాంకం write_buf[7] = {0x00}, read_buf[7] = {0x00};
		గుర్తులేని అక్షరం నిడివి_2;
		గుర్తులేని పూర్ణాంకం hour, minute, రెండవ, date, month, year;
	
		hour = 11;
		minute = 46;
		రెండవ = 30;
	
		date = 25;
		month = 01;
		year = 2020;
	
		write_buf[0] = DS3231_DEC_గమ్యం_HEX(రెండవ); //Seconds
		write_buf[1] = DS3231_DEC_గమ్యం_HEX(minute); //Minutes
		write_buf[2] = DS3231_DEC_గమ్యం_HEX(hour); //Hours
	
		write_buf[4] = DS3231_DEC_గమ్యం_HEX(date); //Seconds
		write_buf[5] = DS3231_DEC_గమ్యం_HEX(month); //Minutes
		write_buf[6] = DS3231_DEC_గమ్యం_HEX( (year % 100) ); //Hours
	
		write_buf[3] = dayofweek(date, month, year) + 1;
		నిడివి_2 = 7;
	
//	set_baud_rate(uart_instance[0], 115200);
	రాయి("\nHello Welcome to Shakti");

	i2c_init();

	ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క, SCLK_లెక్క))
	{
		log_error("\tSomething Wrong In Initialization\n");
		తిరిగి -1;
	}
	లేకపోతే
		log_info("\tIntilization Happened Fine\n");
#నిర్వచితమైతే UPDATE_సమయం
	write_ds3231_registers(I2C, 0x00, &write_buf[0], నిడివి_2, delay);
			రాయి("\n Write complete");
#అయితే_ముగింపు
	అయితే(1)
	{
			read_ds3231_registers(I2C, DS3231_REG_స్థానభ్రంశం, &read_buf[0], 7, 800);
			
			log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
			
			ఎంపిక(read_buf[3])
			{
				స్థితి 1:
						log_info( "   Sunday; ");
						ఆపు;

				స్థితి 2:
						log_info( "   Monday; ");
						ఆపు;

				స్థితి 3:
						log_info( "  Tuesday; ");
						ఆపు;

				స్థితి 4:
						log_info( "Wednesday; ");
						ఆపు;

				స్థితి 5:
						log_info( " Thursday; ");
						ఆపు;

				స్థితి 6:
						log_info( "   Friday; ");
						ఆపు;

				స్థితి 7:
						log_info( " Saturday; ");
						ఆపు;
			}
			log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
			delay_loop(1000, 1000);

	}
}

