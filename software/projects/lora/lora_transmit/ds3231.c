/****************************************************************************
 * Project           	      : shakti devt board
 * Name of the file	      : ds3231.c
 * Brief Description of file  : reads real time calendar (date & time) over i2c interface.
 * Name of Author             : Kotteeswaran, Soutrick Roy Chowdhury
 * Email ID                   : kottee.1@gmail.com, soutrickofficial@gmail.com

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
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdint.h>//Includes the definitions of standard input/output functions//
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#परिभाषय UPDATE_TIME 1
#परिभाषय I2C i2c_instance[1]
#परिभाषय DS3231_SLAVE_स्थानाङ्कः 0XD0
#परिभाषय DS3231_REG_विस्थापनम् 0
#परिभाषय DS3231_DEC_गन्तव्यम्_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#परिभाषय DELAY_मानम् 900
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91

वर्ण sending_दत्त[50];

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
पूर्णाङ्क read_ds3231_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *read_अस्थायी, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;

//Writes the slave address for write
		i2c_send_slave_स्थानाङ्कः(i2c_instance, DS3231_SLAVE_स्थानाङ्कः, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
		i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;


//Writes the slave address for read
		i2c_send_slave_स्थानाङ्कः(i2c_instance, DS3231_SLAVE_स्थानाङ्कः, I2C_READ, 800);


/* Make a dummy read as per spec of the I2C controller */
		i2c_read_दत्त(i2c_instance, &अस्थायी, delay);

//Reads the MSB Byte of temperature [D9 - D1]
		प्रति(i = 0; i < दीर्घता_2; i++)
		{
			i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
			*read_अस्थायी = अस्थायी;
//			printf("\n Read Value[%02d]: %02x", i, *readTemp);
			यदि( i == (दीर्घता_2 - 2) )
				i2c_instance->control = I2C_NACK;
			*read_अस्थायी++;
		}
		i2c_instance->control = I2C_STOP;
		प्रत्यागम 0;
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
पूर्णाङ्क write_ds3231_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *write_मानम्, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
		i2c_send_slave_स्थानाङ्कः(i2c_instance, DS3231_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
		i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
		प्रति(i = 0; i < दीर्घता_2; i++)
	{
		i2c_write_दत्त(i2c_instance,  ( *write_मानम्++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
	}
//Stops the I2C transaction to start reading the temperature value.
		i2c_instance->control = I2C_STOP;
//		delay_loop(800, 800);


			प्रत्यागम 0;
}

/** @fn int dayofweek(int d, int m, int y)
 * @brief Calculates day of the week.
 * @details Calculates the week day based on the passed date.
 * @param d
 * @param m
 * @param y
 * @return Day of the week (0 - 6)
 */
पूर्णाङ्क dayofweek(पूर्णाङ्क d, पूर्णाङ्क m, पूर्णाङ्क y)
{
    स्थिर पूर्णाङ्क t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    प्रत्यागम ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
}

/** @fn unsigned int ds3231_decimal_to_hex(unsigned int decimal)
 * @brief Decimal to hex conversion.
 * @details The configuration value is convertd to hex. which is converted from decimal.
 * @param decimal
 * @return Calculated hex value. 
 */
अचिह्नित पूर्णाङ्क ds3231_decimal_गन्तव्यम्_hex(अचिह्नित पूर्णाङ्क decimal)
{
	प्रत्यागम( ((decimal / 10 ) << 4) | (decimal % 10) );
}

/** @fn void intermediate()
 * @brief Do setup for DS3231
 * @details Configures the DS3231 
 */
शून्य intermediate(शून्य)
{
	पूर्णाङ्क timeout;
	अचिह्नित पूर्णाङ्क अस्थायी_Read_मानम् = 0;
	अचिह्नित दीर्घ delay = 1000;
	अचिह्नित पूर्णाङ्क write_buf[7] = {0x00}, read_buf[7] = {0x00};
	अचिह्नित वर्ण दीर्घता_2;
	अचिह्नित पूर्णाङ्क hour, minute, second, date, month, year;

	hour = 11;
	minute = 46;
	second = 30;

	date = 25;
	month = 01;
	year = 2020;

	write_buf[0] = DS3231_DEC_गन्तव्यम्_HEX(second); //Seconds
	write_buf[1] = DS3231_DEC_गन्तव्यम्_HEX(minute); //Minutes
	write_buf[2] = DS3231_DEC_गन्तव्यम्_HEX(hour); //Hours

	write_buf[4] = DS3231_DEC_गन्तव्यम्_HEX(date); //Seconds
	write_buf[5] = DS3231_DEC_गन्तव्यम्_HEX(month); //Minutes
	write_buf[6] = DS3231_DEC_गन्तव्यम्_HEX( (year % 100) ); //Hours

	write_buf[3] = dayofweek(date, month, year) + 1;
	दीर्घता_2 = 7;


	i2c_init();

	यदि(config_i2c(I2C, PRESCALER_गणनम्, SCLK_गणनम्))
	{
		log_error("\tSomething Wrong In Initialization\n");
		प्रत्यागम -1;
	}
	अन्यथा

#यदि_परिभाषितम् UPDATE_TIME
	write_ds3231_registers(I2C, 0x00, &write_buf[0], दीर्घता_2, delay);
#यदि_अन्तः
}


/** @fn const char* values()
 * @brief Configures the DS3231
 * @details Reads Date and time information and returns the in string
 */
ध्रुव वर्ण* मानानि()
{
	अचिह्नित पूर्णाङ्क read_buf[7] = {0x00};

	read_ds3231_registers(I2C, DS3231_REG_विस्थापनम्, &read_buf[0], 7, 800);
	
	// log_info("\n Date: %x-%x-20%x Day: ", read_buf[4], read_buf[5], read_buf[6]);
	// log_info("\n Time: %x:%x:%x", read_buf[2], read_buf[1], read_buf[0]);

	sprintf(sending_दत्त, "AT+SEND=0,50, Date: %x-%x-20%x  Time: %x:%x:%x", read_buf[4], read_buf[5], read_buf[6], read_buf[2], read_buf[1], read_buf[0]);
	// delay_loop(1500, 1500);		

	प्रत्यागम sending_दत्त;

}

