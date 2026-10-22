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
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"

#تعریف_کرو UPDATE_ویلا 1
#تعریف_کرو I2C i2c_instance[1]
#تعریف_کرو DS3231_SLAVE_پتہ 0XD0
#تعریف_کرو DS3231_REG_وتھ 0
#تعریف_کرو DS3231_DEC_منزل_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#تعریف_کرو DELAY_قدر 900
#تعریف_کرو PRESCALER_گنتی 0x1F
#تعریف_کرو SCLK_گنتی 0x91


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
صحيح read_ds3231_registers(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی صحيح *read_عارضی, بنانشانی حرف لمائی_2, بنانشانی لما delay)
{
	بنانشانی حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی حرف عارضی = 0;

//Writes the slave address for write
		i2c_send_slave_پتہ(i2c_instance, DS3231_SLAVE_پتہ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_پتہ(i2c_instance, DS3231_SLAVE_پتہ, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_انکڑے(i2c_instance, &عارضی, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		لكل(i = 0; i < لمائی_2; i++)
		{
			i2c_read_انکڑے(i2c_instance, &عارضی, delay);
			*read_عارضی = عارضی;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			إذا( i == (لمائی_2 - 2) )
				i2c_instance->control = I2C_NACK;
			*read_عارضی++;
		}
		i2c_instance->control = I2C_STOP;
		أرجع 0;
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
صحيح write_ds3231_registers(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی صحيح *write_قدر, بنانشانی حرف لمائی_2, بنانشانی لما delay)
{
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی صحيح عارضی = 0;
		i2c_send_slave_پتہ(i2c_instance, DS3231_SLAVE_پتہ, I2C_WRITE, delay);
		i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
		لكل(i = 0; i < لمائی_2; i++)
	{
		i2c_write_انکڑے(i2c_instance,  ( *write_قدر++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			أرجع 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
صحيح dayofweek(صحيح d, صحيح m, صحيح y)
{
    ساكن صحيح t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    أرجع ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
بنانشانی صحيح ds3231_decimal_منزل_hex(بنانشانی صحيح decimal)
{
	أرجع( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
فراغ مکھ()
{
		صحيح timeout;
		بنانشانی صحيح عارضی_Read_قدر = 0;
		بنانشانی لما delay = 1000;
		بنانشانی صحيح write_buf[7] = {0x00}, read_buf[7] = {0x00};
		بنانشانی حرف لمائی_2;
		بنانشانی صحيح hour, minute, دوجا, date, month, year;
	
		hour = 11;
		minute = 46;
		دوجا = 30;
	
		date = 25;
		month = 01;
		year = 2020;
	
		write_buf[0] = DS3231_DEC_منزل_HEX(دوجا); //Seconds
		write_buf[1] = DS3231_DEC_منزل_HEX(minute); //Minutes
		write_buf[2] = DS3231_DEC_منزل_HEX(hour); //Hours
	
		write_buf[4] = DS3231_DEC_منزل_HEX(date); //Seconds
		write_buf[5] = DS3231_DEC_منزل_HEX(month); //Minutes
		write_buf[6] = DS3231_DEC_منزل_HEX( (year % 100) ); //Hours
	
		write_buf[3] = dayofweek(date, month, year) + 1;
		لمائی_2 = 7;
	
//	set_baud_rate(uart_instance[0], 115200);
	لکھو("\nHello Welcome to Shakti");

	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_گنتی, SCLK_گنتی))
	{
		log_error("\tSomething Wrong In Initialization\n");
		أرجع -1;
	}
	وإلا
		log_info("\tIntilization Happened Fine\n");
#جے_تعریف_شدہ UPDATE_ویلا
	write_ds3231_registers(I2C, 0x00, &write_buf[0], لمائی_2, delay);
			لکھو("\n Write complete");
#جے_انت
	طالما(1)
	{
			read_ds3231_registers(I2C, DS3231_REG_وتھ, &read_buf[0], 7, 800);
			
			log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
			
			بدل(read_buf[3])
			{
				حالة 1:
						log_info( "   Sunday; ");
						اكسر;

				حالة 2:
						log_info( "   Monday; ");
						اكسر;

				حالة 3:
						log_info( "  Tuesday; ");
						اكسر;

				حالة 4:
						log_info( "Wednesday; ");
						اكسر;

				حالة 5:
						log_info( " Thursday; ");
						اكسر;

				حالة 6:
						log_info( "   Friday; ");
						اكسر;

				حالة 7:
						log_info( " Saturday; ");
						اكسر;
			}
			log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
			delay_loop(1000, 1000);

	}
}

