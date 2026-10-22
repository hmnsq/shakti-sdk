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

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio_spi.h"

/** @fn static void writebyte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte
 * @details This function writes a byte into SPI Slave device using GPIO lines.
 * @param unsigned char writeData
 * @param unsigned char delay
 */
// at starting  edge sending
ਸਥਿਰ ਖਾਲੀ writebyte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ j = 0, k;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	//readData = read_word(GPIO_DATA_REG);

    // Before initiating communication SS -> low
       write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(SPI_SS)) );
	ਜਦੋਂ (j < 8) {
		k = write_ਅੰਕੜੇ;
		k = ( k << j ) & 0x80;

        // lowering sck --> FALLING EDGE 
        //write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(SPI_SCLK)) );
        // increasing sck --> Rising EDGE
        write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | SPI_SCLK) );

        ਜੇ (k == 0) {
			write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(SPI_MOSI)) );
			delay_loop(delay, delay);
		}
		ਨਹੀਂਤਾਂ {
			write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | SPI_MOSI) );
			delay_loop(delay, delay);
		}

        //delay_loop(delay,delay);
        // making sck up 
		//write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | SPI_SCLK));
        // sck down
        write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(SPI_SCLK)) );
        //delay_loop(delay, delay);
		++j;
	}
        // MAKE SS PIN high after transfer of a byte
        write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) |SPI_SS ));
}

/** @fn unsigned char readbyte(unsigned char delay)
 * @brief Reads a byte 
 * @details Reads a byte from slave SPI device using GPIO lines as SPI lines.
 * @param unsigned char delay
 * @return Read value
 */
//reading at rising edge reading 
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ readbyte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ j = 0, i = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_ਅੰਕੜੇ = 0;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_Gpio_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
	ਜਦੋਂ (j < 8) {
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | SPI_SCLK) );
		delay_loop(delay, delay);

		read_Gpio_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG)  & SPI_MISO;

        ਜੇ (read_Gpio_ਅੰਕੜੇ != 0)
			ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ = 1;
		ਨਹੀਂਤਾਂ
			ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ = 0;
	    
        read_ਅੰਕੜੇ = read_ਅੰਕੜੇ << 1;
		read_ਅੰਕੜੇ = read_ਅੰਕੜੇ | ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;
		
        delay_loop(delay, delay);

		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(SPI_SCLK)));
		delay_loop(delay, delay);
		++j;
	}
	ਵਾਪਸ read_ਅੰਕੜੇ;
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
ਪੂਰਨ config()
{
    write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG) & ~(SPI_MISO)));
    write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG) | SPI_MOSI));
    write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG) | SPI_SS));
    write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG) | SPI_SCLK));
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ = (ਪੂਰਨ) 'a';
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay = 10;
    ਲਈ (;;)
    {
    writebyte(write_ਅੰਕੜੇ,delay);
    ਲਿਖੋ("%d\n",write_ਅੰਕੜੇ);
    delay_loop(100,120);
    }
}



