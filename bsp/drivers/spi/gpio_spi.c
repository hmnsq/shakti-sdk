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

#ضمن "platform.h"
#ضمن "gpio.h"
#ضمن "gpio_spi.h"

/** @fn static void writebyte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte
 * @details This function writes a byte into SPI Slave device using GPIO lines.
 * @param unsigned char writeData
 * @param unsigned char delay
 */
// at starting  edge sending
ساكن فراغ writebyte(بیعلامت حرف write_داده, بیعلامت حرف delay)
{
	بیعلامت حرف j = 0, k;
	بیعلامت دراز read_داده = 0;
	//readData = read_word(GPIO_DATA_REG);

    // Before initiating communication SS -> low
       write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) & ~(SPI_SS)) );
	طالما (j < 8) {
		k = write_داده;
		k = ( k << j ) & 0x80;

        // lowering sck --> FALLING EDGE 
        //write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(SPI_SCLK)) );
        // increasing sck --> Rising EDGE
        write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) | SPI_SCLK) );

        إذا (k == 0) {
			write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) & ~(SPI_MOSI)) );
			delay_loop(delay, delay);
		}
		وإلا {
			write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) | SPI_MOSI) );
			delay_loop(delay, delay);
		}

        //delay_loop(delay,delay);
        // making sck up 
		//write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | SPI_SCLK));
        // sck down
        write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) & ~(SPI_SCLK)) );
        //delay_loop(delay, delay);
		++j;
	}
        // MAKE SS PIN high after transfer of a byte
        write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) |SPI_SS ));
}

/** @fn unsigned char readbyte(unsigned char delay)
 * @brief Reads a byte 
 * @details Reads a byte from slave SPI device using GPIO lines as SPI lines.
 * @param unsigned char delay
 * @return Read value
 */
//reading at rising edge reading 
بیعلامت حرف readbyte(بیعلامت حرف delay)
{
	بیعلامت حرف j = 0, i = 0;
	بیعلامت حرف بیت_مقدار;
	بیعلامت حرف read_داده = 0;
        بیعلامت دراز read_Gpio_داده = 0;
	read_داده = read_کلمه(GPIO_داده_REG);
	طالما (j < 8) {
		write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) | SPI_SCLK) );
		delay_loop(delay, delay);

		read_Gpio_داده = read_کلمه(GPIO_داده_REG)  & SPI_MISO;

        إذا (read_Gpio_داده != 0)
			بیت_مقدار = 1;
		وإلا
			بیت_مقدار = 0;
	    
        read_داده = read_داده << 1;
		read_داده = read_داده | بیت_مقدار;
		
        delay_loop(delay, delay);

		write_کلمه(GPIO_داده_REG, (read_کلمه(GPIO_داده_REG) & ~(SPI_SCLK)));
		delay_loop(delay, delay);
		++j;
	}
	أرجع read_داده;
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
صحيح config()
{
    write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_کلمه(GPIO_DIRECTION_CNTRL_REG) & ~(SPI_MISO)));
    write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_کلمه(GPIO_DIRECTION_CNTRL_REG) | SPI_MOSI));
    write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_کلمه(GPIO_DIRECTION_CNTRL_REG) | SPI_SS));
    write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_کلمه(GPIO_DIRECTION_CNTRL_REG) | SPI_SCLK));
    بیعلامت حرف write_داده = (صحيح) 'a';
    بیعلامت حرف delay = 10;
    لكل (;;)
    {
    writebyte(write_داده,delay);
    چاپ_کن("%d\n",write_داده);
    delay_loop(100,120);
    }
}



