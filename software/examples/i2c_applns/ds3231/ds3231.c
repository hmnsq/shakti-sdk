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
#ਅਨ੍ਤਰ੍ਭਾਵ "i2c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UPDATE_ਸਮਾਂ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C i2c_instance[1]
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DS3231_SLAVE_ਪਤਾ 0XD0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DS3231_REG_ਵਿੱਥ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY_ਮੁੱਲ 900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRESCALER_ਗਿਣਤੀ 0x1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCLK_ਗਿਣਤੀ 0x91


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
ਪੂਰਨ read_ds3231_registers(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *read_ਆਰਜ਼ੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_buf[4] = {'\0'};
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਰਜ਼ੀ = 0;

//Writes the slave address for write
		i2c_send_slave_ਪਤਾ(i2c_instance, DS3231_SLAVE_ਪਤਾ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_ਪਤਾ(i2c_instance, DS3231_SLAVE_ਪਤਾ, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
		{
			i2c_read_ਅੰਕੜੇ(i2c_instance, &ਆਰਜ਼ੀ, delay);
			*read_ਆਰਜ਼ੀ = ਆਰਜ਼ੀ;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			ਜੇ( i == (ਲੰਮਾਈ_2 - 2) )
				i2c_instance->control = I2C_NACK;
			*read_ਆਰਜ਼ੀ++;
		}
		i2c_instance->control = I2C_STOP;
		ਵਾਪਸ 0;
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
ਪੂਰਨ write_ds3231_registers(i2c_struct * i2c_instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ reg_ਵਿੱਥ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *write_ਮੁੱਲ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay)
{
	ਪੂਰਨ i = 0, j = 0,  k = 0, ਸਥਿਤੀ_2=0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ = 0;
		i2c_send_slave_ਪਤਾ(i2c_instance, DS3231_SLAVE_ਪਤਾ, I2C_WRITE, delay);
		i2c_write_ਅੰਕੜੇ(i2c_instance, reg_ਵਿੱਥ, delay);
		ਲਈ(i = 0; i < ਲੰਮਾਈ_2; i++)
	{
		i2c_write_ਅੰਕੜੇ(i2c_instance,  ( *write_ਮੁੱਲ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			ਵਾਪਸ 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
ਪੂਰਨ dayofweek(ਪੂਰਨ d, ਪੂਰਨ m, ਪੂਰਨ y)
{
    ਸਥਿਰ ਪੂਰਨ t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    ਵਾਪਸ ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ds3231_decimal_ਮੰਜ਼ਿਲ_hex(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ decimal)
{
	ਵਾਪਸ( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
ਖਾਲੀ ਮੁੱਖ()
{
		ਪੂਰਨ timeout;
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਆਰਜ਼ੀ_Read_ਮੁੱਲ = 0;
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay = 1000;
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ write_buf[7] = {0x00}, read_buf[7] = {0x00};
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਲੰਮਾਈ_2;
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ hour, minute, ਦੂਜਾ, date, month, year;
	
		hour = 11;
		minute = 46;
		ਦੂਜਾ = 30;
	
		date = 25;
		month = 01;
		year = 2020;
	
		write_buf[0] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(ਦੂਜਾ); //Seconds
		write_buf[1] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(minute); //Minutes
		write_buf[2] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(hour); //Hours
	
		write_buf[4] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(date); //Seconds
		write_buf[5] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX(month); //Minutes
		write_buf[6] = DS3231_DEC_ਮੰਜ਼ਿਲ_HEX( (year % 100) ); //Hours
	
		write_buf[3] = dayofweek(date, month, year) + 1;
		ਲੰਮਾਈ_2 = 7;
	
//	set_baud_rate(uart_instance[0], 115200);
	ਲਿਖੋ("\nHello Welcome to Shakti");

	i2c_init();

	ਜੇ(config_i2c(I2C, PRESCALER_ਗਿਣਤੀ, SCLK_ਗਿਣਤੀ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ
		log_info("\tIntilization Happened Fine\n");
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ UPDATE_ਸਮਾਂ
	write_ds3231_registers(I2C, 0x00, &write_buf[0], ਲੰਮਾਈ_2, delay);
			ਲਿਖੋ("\n Write complete");
#ਜੇ_ਅੰਤ
	ਜਦੋਂ(1)
	{
			read_ds3231_registers(I2C, DS3231_REG_ਵਿੱਥ, &read_buf[0], 7, 800);
			
			log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
			
			ਚੋਣ(read_buf[3])
			{
				ਹਾਲਤ 1:
						log_info( "   Sunday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 2:
						log_info( "   Monday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 3:
						log_info( "  Tuesday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 4:
						log_info( "Wednesday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 5:
						log_info( " Thursday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 6:
						log_info( "   Friday; ");
						ਰੋਕੋ;

				ਹਾਲਤ 7:
						log_info( " Saturday; ");
						ਰੋਕੋ;
			}
			log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
			delay_loop(1000, 1000);

	}
}

