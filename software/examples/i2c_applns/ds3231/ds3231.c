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
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು UPDATE_ಸಮಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[1]
#ವ್ಯಾಖ್ಯಾನಿಸು DS3231_SLAVE_ವಿಳಾಸ 0XD0
#ವ್ಯಾಖ್ಯಾನಿಸು DS3231_REG_ಸ್ಥಾನಾಂತರ 0
#ವ್ಯಾಖ್ಯಾನಿಸು DS3231_DEC_ಗಮ್ಯ_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 0x1F
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 0x91


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
ಪೂರ್ಣಾಂಕ read_ds3231_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *read_ತಾತ್ಕಾಲಿಕ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;

//Writes the slave address for write
		i2c_send_slave_ವಿಳಾಸ(i2c_instance, DS3231_SLAVE_ವಿಳಾಸ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_ವಿಳಾಸ(i2c_instance, DS3231_SLAVE_ವಿಳಾಸ, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
		{
			i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
			*read_ತಾತ್ಕಾಲಿಕ = ತಾತ್ಕಾಲಿಕ;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			ಆದರೆ( i == (ಉದ್ದಳತೆ_2 - 2) )
				i2c_instance->control = I2C_NACK;
			*read_ತಾತ್ಕಾಲಿಕ++;
		}
		i2c_instance->control = I2C_STOP;
		ಹಿಂತಿರುಗಿ 0;
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
ಪೂರ್ಣಾಂಕ write_ds3231_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
		i2c_send_slave_ವಿಳಾಸ(i2c_instance, DS3231_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
		i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
		ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( *write_ಮೌಲ್ಯ++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			ಹಿಂತಿರುಗಿ 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
ಪೂರ್ಣಾಂಕ dayofweek(ಪೂರ್ಣಾಂಕ d, ಪೂರ್ಣಾಂಕ m, ಪೂರ್ಣಾಂಕ y)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    ಹಿಂತಿರುಗಿ ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ds3231_decimal_ಗಮ್ಯ_hex(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ decimal)
{
	ಹಿಂತಿರುಗಿ( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void main()
 * @brief Reads and prints the Date and Time information.
 * @details Configures the DS3231 and reads Date and time information and prints the 
 * in decimal
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
		ಪೂರ್ಣಾಂಕ timeout;
		ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = 0;
		ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 1000;
		ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf[7] = {0x00}, read_buf[7] = {0x00};
		ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2;
		ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ hour, minute, ಎರಡನೇ, date, month, year;
	
		hour = 11;
		minute = 46;
		ಎರಡನೇ = 30;
	
		date = 25;
		month = 01;
		year = 2020;
	
		write_buf[0] = DS3231_DEC_ಗಮ್ಯ_HEX(ಎರಡನೇ); //Seconds
		write_buf[1] = DS3231_DEC_ಗಮ್ಯ_HEX(minute); //Minutes
		write_buf[2] = DS3231_DEC_ಗಮ್ಯ_HEX(hour); //Hours
	
		write_buf[4] = DS3231_DEC_ಗಮ್ಯ_HEX(date); //Seconds
		write_buf[5] = DS3231_DEC_ಗಮ್ಯ_HEX(month); //Minutes
		write_buf[6] = DS3231_DEC_ಗಮ್ಯ_HEX( (year % 100) ); //Hours
	
		write_buf[3] = dayofweek(date, month, year) + 1;
		ಉದ್ದಳತೆ_2 = 7;
	
//	set_baud_rate(uart_instance[0], 115200);
	ಬರೆ("\nHello Welcome to Shakti");

	i2c_init();

	ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ, SCLK_ಎಣಿಕೆ))
	{
		log_error("\tSomething Wrong In Initialization\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		log_info("\tIntilization Happened Fine\n");
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ UPDATE_ಸಮಯ
	write_ds3231_registers(I2C, 0x00, &write_buf[0], ಉದ್ದಳತೆ_2, delay);
			ಬರೆ("\n Write complete");
#ಆದರೆ_ಅಂತ್ಯ
	ಆಗ(1)
	{
			read_ds3231_registers(I2C, DS3231_REG_ಸ್ಥಾನಾಂತರ, &read_buf[0], 7, 800);
			
			log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
			
			ಆಯ್ಕೆ(read_buf[3])
			{
				ಸ್ಥಿತಿ 1:
						log_info( "   Sunday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 2:
						log_info( "   Monday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 3:
						log_info( "  Tuesday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 4:
						log_info( "Wednesday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 5:
						log_info( " Thursday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 6:
						log_info( "   Friday; ");
						ನಿಲ್ಲಿಸು;

				ಸ್ಥಿತಿ 7:
						log_info( " Saturday; ");
						ನಿಲ್ಲಿಸು;
			}
			log_info("Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);
			delay_loop(1000, 1000);

	}
}

