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

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "gpio_spi.h"

/** @fn static void writebyte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte
 * @details This function writes a byte into SPI Slave device using GPIO lines.
 * @param unsigned char writeData
 * @param unsigned char delay
 */
// at starting  edge sending
స్థిర శూన్య writebyte(గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay)
{
	గుర్తులేని అక్షరం j = 0, k;
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	//readData = read_word(GPIO_DATA_REG);

    // Before initiating communication SS -> low
       write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(SPI_SS)) );
	అయితే (j < 8) {
		k = write_దత్తాంశం;
		k = ( k << j ) & 0x80;

        // lowering sck --> FALLING EDGE 
        //write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(SPI_SCLK)) );
        // increasing sck --> Rising EDGE
        write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | SPI_SCLK) );

        ఒకవేళ (k == 0) {
			write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(SPI_MOSI)) );
			delay_loop(delay, delay);
		}
		లేకపోతే {
			write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | SPI_MOSI) );
			delay_loop(delay, delay);
		}

        //delay_loop(delay,delay);
        // making sck up 
		//write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | SPI_SCLK));
        // sck down
        write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(SPI_SCLK)) );
        //delay_loop(delay, delay);
		++j;
	}
        // MAKE SS PIN high after transfer of a byte
        write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) |SPI_SS ));
}

/** @fn unsigned char readbyte(unsigned char delay)
 * @brief Reads a byte 
 * @details Reads a byte from slave SPI device using GPIO lines as SPI lines.
 * @param unsigned char delay
 * @return Read value
 */
//reading at rising edge reading 
గుర్తులేని అక్షరం readbyte(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని అక్షరం j = 0, i = 0;
	గుర్తులేని అక్షరం బిట్టు_విలువ;
	గుర్తులేని అక్షరం read_దత్తాంశం = 0;
        గుర్తులేని దీర్ఘ read_Gpio_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
	అయితే (j < 8) {
		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | SPI_SCLK) );
		delay_loop(delay, delay);

		read_Gpio_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG)  & SPI_MISO;

        ఒకవేళ (read_Gpio_దత్తాంశం != 0)
			బిట్టు_విలువ = 1;
		లేకపోతే
			బిట్టు_విలువ = 0;
	    
        read_దత్తాంశం = read_దత్తాంశం << 1;
		read_దత్తాంశం = read_దత్తాంశం | బిట్టు_విలువ;
		
        delay_loop(delay, delay);

		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(SPI_SCLK)));
		delay_loop(delay, delay);
		++j;
	}
	తిరిగి read_దత్తాంశం;
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
పూర్ణాంకం config()
{
    write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_మాట(GPIO_DIRECTION_CNTRL_REG) & ~(SPI_MISO)));
    write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_మాట(GPIO_DIRECTION_CNTRL_REG) | SPI_MOSI));
    write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_మాట(GPIO_DIRECTION_CNTRL_REG) | SPI_SS));
    write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_మాట(GPIO_DIRECTION_CNTRL_REG) | SPI_SCLK));
    గుర్తులేని అక్షరం write_దత్తాంశం = (పూర్ణాంకం) 'a';
    గుర్తులేని అక్షరం delay = 10;
    కొరకు (;;)
    {
    writebyte(write_దత్తాంశం,delay);
    రాయి("%d\n",write_దత్తాంశం);
    delay_loop(100,120);
    }
}



