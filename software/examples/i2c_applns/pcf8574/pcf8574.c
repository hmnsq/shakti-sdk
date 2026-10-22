/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : pcf8574.c
 * Brief Description of file   : Contains the driver routines to configure pcf8574.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file   pcf8574.c
@brief  Contains the driver routines to configure pcf8574.
@detail I2C based routines to configure pcf8574.
*/

#अन्तर्भाव <stdint.h>//Includes the definitions of standard input/output functions//
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#परिभाषय PCF8574_SLAVE_स्थानाङ्कः 0x4E
#परिभाषय I2C i2c_instance[0]
#परिभाषय PRESCALER_गणनम् 0x1F
#परिभाषय SCLK_गणनम् 0x91
#परिभाषय PCF8574_DEC_गन्तव्यम्_HEX(decimal)  ( ( (decimal / 10 ) << 4) | (decimal % 10) )
#परिभाषय DELAY_मानम् 900
#परिभाषय PCF8574_REG_विस्थापनम् 0

/** @fn int write_pcf8574_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int write_value, unsigned long delay)
 * @brief  configures and write the pcf8574 
 * @param i2c instance
 * @param reg_offset
 * @param *write_value
 * @param delay
 * @return write status (Zero on SUCCESS.)
 */
पूर्णाङ्क write_pcf8574_registers(i2c_struct * i2c_instance,अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क write_मानम्, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
	i2c_send_slave_स्थानाङ्कः(i2c_instance, PCF8574_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
	i2c_write_दत्त(i2c_instance,  ( write_मानम् & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	// delay_loop(800, 800);
	प्रत्यागम 0;
}

/** @fn void main()
 * @brief configures and write the pcf8574 IO expander.
 * @details 
 */
शून्य मुख्यम्()
{
	पूर्णाङ्क timeout;
	अचिह्नित पूर्णाङ्क अस्थायी_Read_मानम् = 0;
	अचिह्नित दीर्घ delay = 1000;

	प्रारूप_लिख("\nPCF8574 IO Expander Test");

	i2c_init();

	यदि(config_i2c(I2C, PRESCALER_गणनम्, SCLK_गणनम्))
	{
		log_error("\tSomething Wrong In Initialization\n");
		प्रत्यागम -1;
	}
		अन्यथा
		log_info("\tIntilization Happened Fine\n");
		प्रारूप_लिख("\n Write he scomplete");
	यावत्(1)
	{
		प्रारूप_लिख("\n Writing 0");
		write_pcf8574_registers(I2C, 0x00, 0x00, delay);
		delay_loop(2000, 5000);
		प्रारूप_लिख("\n Writing 1");
		write_pcf8574_registers(I2C, 0x00, 0xFF, delay);
		delay_loop(2000, 5000);
	}
}




