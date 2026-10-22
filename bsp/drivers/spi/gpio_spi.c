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

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "gpio_spi.h"

/** @fn static void writebyte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte
 * @details This function writes a byte into SPI Slave device using GPIO lines.
 * @param unsigned char writeData
 * @param unsigned char delay
 */
// at starting  edge sending
ಸ್ಥಿರ ಶೂನ್ಯ writebyte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ j = 0, k;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	//readData = read_word(GPIO_DATA_REG);

    // Before initiating communication SS -> low
       write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(SPI_SS)) );
	ಆಗ (j < 8) {
		k = write_ದತ್ತಾಂಶ;
		k = ( k << j ) & 0x80;

        // lowering sck --> FALLING EDGE 
        //write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(SPI_SCLK)) );
        // increasing sck --> Rising EDGE
        write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | SPI_SCLK) );

        ಆದರೆ (k == 0) {
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(SPI_MOSI)) );
			delay_loop(delay, delay);
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | SPI_MOSI) );
			delay_loop(delay, delay);
		}

        //delay_loop(delay,delay);
        // making sck up 
		//write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | SPI_SCLK));
        // sck down
        write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(SPI_SCLK)) );
        //delay_loop(delay, delay);
		++j;
	}
        // MAKE SS PIN high after transfer of a byte
        write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) |SPI_SS ));
}

/** @fn unsigned char readbyte(unsigned char delay)
 * @brief Reads a byte 
 * @details Reads a byte from slave SPI device using GPIO lines as SPI lines.
 * @param unsigned char delay
 * @return Read value
 */
//reading at rising edge reading 
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ readbyte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ j = 0, i = 0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಬಿಟ್_ಮೌಲ್ಯ;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_ದತ್ತಾಂಶ = 0;
        ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_Gpio_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
	ಆಗ (j < 8) {
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | SPI_SCLK) );
		delay_loop(delay, delay);

		read_Gpio_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG)  & SPI_MISO;

        ಆದರೆ (read_Gpio_ದತ್ತಾಂಶ != 0)
			ಬಿಟ್_ಮೌಲ್ಯ = 1;
		ಇಲ್ಲದಿದ್ದರೆ
			ಬಿಟ್_ಮೌಲ್ಯ = 0;
	    
        read_ದತ್ತಾಂಶ = read_ದತ್ತಾಂಶ << 1;
		read_ದತ್ತಾಂಶ = read_ದತ್ತಾಂಶ | ಬಿಟ್_ಮೌಲ್ಯ;
		
        delay_loop(delay, delay);

		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(SPI_SCLK)));
		delay_loop(delay, delay);
		++j;
	}
	ಹಿಂತಿರುಗಿ read_ದತ್ತಾಂಶ;
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
ಪೂರ್ಣಾಂಕ config()
{
    write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG) & ~(SPI_MISO)));
    write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG) | SPI_MOSI));
    write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG) | SPI_SS));
    write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG) | SPI_SCLK));
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ = (ಪೂರ್ಣಾಂಕ) 'a';
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay = 10;
    ಗಾಗಿ (;;)
    {
    writebyte(write_ದತ್ತಾಂಶ,delay);
    ಬರೆ("%d\n",write_ದತ್ತಾಂಶ);
    delay_loop(100,120);
    }
}



