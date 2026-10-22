/***************************************************************************
 * Project           	         	:  shakti devt board
 * Name of the file	     		:  gpio_spi.c
 * Brief Description of file            :  driver file for using gpio pins as SPI
 * Name of Author    	                :  Kottee @ aditya dubey
 * Email ID                             :  kottee.1@gmail.com

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
 ****************************************************************************/
/**
@file   gpio_spi.c
@brief  Contains the driver routines for GPIO based SPI interface.
@detail The GPIO_SPI module driver supports SPI driver routines using GPIO lines as SPI lines.
*/

#समावेश "platform.h"
#समावेश "gpio.h"
#समावेश "gpio_spi.h"

/** @fn static void writebyte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte
 * @details This function writes a byte into SPI Slave device using GPIO lines.
 * @param unsigned char writeData
 * @param unsigned char delay
 */
// at starting  edge sending
अटल व्योम writebyte(अचिन्हित अक्षर write_तथ्य, अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर j = 0, k;
	अचिन्हित दीर्घ read_तथ्य = 0;
	//readData = read_word(GPIO_DATA_REG);

    // Before initiating communication SS -> low
       write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(SPI_SS)) );
	जबतक (j < 8) {
		k = write_तथ्य;
		k = ( k << j ) & 0x80;

        // lowering sck --> FALLING EDGE 
        //write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(SPI_SCLK)) );
        // increasing sck --> Rising EDGE
        write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | SPI_SCLK) );

        अगर (k == 0) {
			write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(SPI_MOSI)) );
			delay_loop(delay, delay);
		}
		अन्यथा {
			write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | SPI_MOSI) );
			delay_loop(delay, delay);
		}

        //delay_loop(delay,delay);
        // making sck up 
		//write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | SPI_SCLK));
        // sck down
        write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(SPI_SCLK)) );
        //delay_loop(delay, delay);
		++j;
	}
        // MAKE SS PIN high after transfer of a byte
        write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) |SPI_SS ));
}

/** @fn unsigned char readbyte(unsigned char delay)
 * @brief Reads a byte 
 * @details Reads a byte from slave SPI device using GPIO lines as SPI lines.
 * @param unsigned char delay
 * @return Read value
 */
//reading at rising edge reading 
अचिन्हित अक्षर readbyte(अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर j = 0, i = 0;
	अचिन्हित अक्षर bit_मूल्य;
	अचिन्हित अक्षर read_तथ्य = 0;
        अचिन्हित दीर्घ read_Gpio_तथ्य = 0;
	read_तथ्य = read_word(GPIO_तथ्य_REG);
	जबतक (j < 8) {
		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | SPI_SCLK) );
		delay_loop(delay, delay);

		read_Gpio_तथ्य = read_word(GPIO_तथ्य_REG)  & SPI_MISO;

        अगर (read_Gpio_तथ्य != 0)
			bit_मूल्य = 1;
		अन्यथा
			bit_मूल्य = 0;
	    
        read_तथ्य = read_तथ्य << 1;
		read_तथ्य = read_तथ्य | bit_मूल्य;
		
        delay_loop(delay, delay);

		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(SPI_SCLK)));
		delay_loop(delay, delay);
		++j;
	}
	वापस read_तथ्य;
}
/*
  1.) MISO_pin  --> 1st GPIO //0 
  2.) MOSI_pin -->  2nd GPIO // 1
  3.) SCLK_pin -->  3rth GPIO // 1
  4.) SS_Pin   -->  4th GPIO  // 1
*/

/** @fn int config()
 * @brief Configures the GPIO pins for SPI functionality
 * @details Configures the GPIO pins as input or output based on the SPI pin functionlity.
 */
पूर्णांक config()
{
    write_word(GPIO_DIRECTION_CNTRL_REG, (read_word(GPIO_DIRECTION_CNTRL_REG) & ~(SPI_MISO)));
    write_word(GPIO_DIRECTION_CNTRL_REG, (read_word(GPIO_DIRECTION_CNTRL_REG) | SPI_MOSI));
    write_word(GPIO_DIRECTION_CNTRL_REG, (read_word(GPIO_DIRECTION_CNTRL_REG) | SPI_SS));
    write_word(GPIO_DIRECTION_CNTRL_REG, (read_word(GPIO_DIRECTION_CNTRL_REG) | SPI_SCLK));
    अचिन्हित अक्षर write_तथ्य = (पूर्णांक) 'a';
    अचिन्हित अक्षर delay = 10;
    क्रम (;;)
    {
    writebyte(write_तथ्य,delay);
    म_लिखो("%d\n",write_तथ्य);
    delay_loop(100,120);
    }
}



