/****************************************************************************
* Project           		:  shakti devt board
* Name of the file	     	:  adc_dac_test.c
* Brief Description of file     :  Does the printing of hello with the help of uart communication protocol.
* Name of Author    	        :  Kotteeswaran Ekambaram
* Email ID                      :  kottee.1@gmail.com

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

***************************************************************************/
/**
@file adc_dac.c
@brief Sends sine wave through DAC and feeds the same to ADC and read the samples.
*/

#include "uart.h"
#include "pinmux.h"
#include "adc_dac.h"
#include "gpiov2.h"
#include "sspi.h"
#include "utils.h"

#define LDAC GPIO4
#define SHUT GPIO6
#define SSPI_SIZE 2
#define DATA_SIZE 8

#define SSPI_INSTANCE1  1
// #define SSPI_INSTANCE3  3

#define GPIO_OUTPUTS ( GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15 ) 
uint32_t gpio_cntrl = 0;

/** @fn sspi_configure(sspi_struct *sspi_instance, uint32_t clk_rate, uint8_t clk_pol, uint8_t clk_phase, uint8_t pins_master, uint8_t mas_slv, uint8_t lsb_first, uint8_t setup_time, uint8_t hold_time) 
 * @brief sspi configuration function which configures the SSPI registers
 * @details Configures the SSPI registers like control register, clock register, etc. 
 * @warning No warning
 * @param[in] sspi_struct *sspi_instance ---> instance of SSPI that needs to be configured
 * 			  clk_rate --> SSPI clock frequency.
 * 			  clk_pol --> Polarity of the clock
 * 			  clk_phase --> Phase of the clock, 
 * 			  pins_master --> SPI pin functionality (master or slave)
 * 			  mas_slv --> SSPI Master / SSPI Slave, 
 * 			  lsb_first --> Bit transfer (MSB first / LSB first),
 *  		  setup_time --> Delay in data transfer after CS is low and before the data transmit starts,
 * 			  hold_time ---> Delay after data transfer completes and before CS becomes high.
 * @param[Out] No output parameter
 */
void sspi_configure(sspi_struct *sspi_instance, uint32_t clk_rate, uint8_t clk_pol, uint8_t clk_phase, uint8_t pins_master, uint8_t mas_slv, uint8_t lsb_first, uint8_t setup_time, uint8_t hold_time)
{
 	sspi_enable_txrx(sspi_instance, DISABLE);
	sspi_configure_clock(sspi_instance, clk_rate, clk_pol, clk_phase);
	sspi_configure_clock_in_hz(sspi_instance, clk_rate); /* Currently configuring for 100kHz, as the maximum clock is 20MHz */
	sspi_configure_clock_pol(sspi_instance, clk_pol);
	sspi_configure_clock_phase(sspi_instance, clk_phase);	
	if(pins_master)
	{
		sspi_configure_pins(sspi_instance, 1, 0 ,  1 , 1);}
	else
	{
		sspi_configure_pins(sspi_instance, 0, 1 ,  0 , 0);
		//  printf("\n 3333");
	}
	if(mas_slv)
		sspi_configure_mas_slv(sspi_instance, SPI_MASTER);
	else//added by sugnathi
		sspi_configure_mas_slv(sspi_instance, ~SPI_MASTER);
	if(!lsb_first)
		sspi_configure_lsb_first(sspi_instance, MSB_FIRST);
	sspi_configure_tx_setup_time(sspi_instance, setup_time);
	sspi_configure_tx_hold_time(sspi_instance, hold_time);
}


/// @brief 
/// @param data 
/// @param dac_channel_select 
/// @param single_differential 
void adc_read_digital_value(unsigned int *data, unsigned char dac_channel_select, unsigned char single_differential,sspi_struct *sspi_instance)
{
	unsigned char upper_byte = 0, lower_byte = 0;
	uint32_t temp = 0;
	unsigned char temp_data[3] = {'\0'};
	//printf("the upper byte is %x", upper_byte);
	sspi_instance->data_tx = 0x01; //Start bit
	sspi_instance->data_tx = (CHANNEL_SELECT(dac_channel_select) | SINGLE_DIFFERENTIAL_CHANNEL(single_differential) );
	sspi_instance->data_tx = 0xff;
	sspi_configure_tx_rx_length(sspi_instance, (SSPI_SIZE +1) * DATA_SIZE, (SSPI_SIZE+1) * DATA_SIZE);
	sspi_configure_comm_mode(sspi_instance, FULL_DUPLEX );
	sspi_enable_txrx(sspi_instance, ENABLE);
	temp = sspi_notbusy(sspi_instance);
	temp_data[2] = sspi_instance->data_rx;
	temp_data[1] = sspi_instance->data_rx;
	temp_data[0] = sspi_instance->data_rx;
	// printf("\n temp2 %x :temp1 %x : temp0 %x ", temp_data[2],temp_data[1],temp_data[0]);
	*data = ( (temp_data[1] << 8) & 0x300) | temp_data[0];
	
}




void dac_send_digital_value(unsigned short data, unsigned char dac_select, unsigned char buf_contrl, unsigned char gain_value, unsigned char shutdwn_cntrl)
{
	unsigned char upper_byte = 0, lower_byte = 0;
	uint32_t temp = 0;
	if(dac_select)
		upper_byte |= SELECT_DAC1;
	else
		upper_byte &= SELECT_DAC0;

	if(buf_contrl)
		upper_byte |= BUFFERED;
	else
		upper_byte &= NON_BUFFERED;

	if(gain_value)
		upper_byte |= GAIN_1X;
	else
		upper_byte &= GAIN_2X;
	if(shutdwn_cntrl)
		upper_byte |= DO_NOT_SHUT_DOWN;
	else
		upper_byte = CHANNEL_SELECT(CHANNEL_0), SINGLE_DIFFERENTIAL_CHANNEL(SINGLE_CHANNEL);

	printf("the upper byte is %x", upper_byte);

	// sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 8 & 0xf) | (upper_byte & 0xf0);
	// sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 0) & 0xff;
	sspi_instance[SSPI_INSTANCE1]->data_tx = (0x8f);
	sspi_instance[SSPI_INSTANCE1]->data_tx = 0xff;
	printf("\n sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 8 & 0xf) | (upper_byte & 0xf0) :  %x ",sspi_instance[SSPI_INSTANCE1]->data_tx = (data >> 8 & 0xf) | (upper_byte & 0xf0));
	printf("\n sspi_instance[SSPI_INSTANCE]->data_tx = (data >> 0) & 0xff : %x ",sspi_instance[SSPI_INSTANCE1]->data_tx = (data >> 0) & 0xff);
	sspi_configure_tx_rx_length(sspi_instance[SSPI_INSTANCE1], SSPI_SIZE * DATA_SIZE, SSPI_SIZE * DATA_SIZE);
	sspi_configure_comm_mode(sspi_instance[SSPI_INSTANCE1], FULL_DUPLEX );
	gpiov2_instance->set = LDAC;
	sspi_enable_txrx(sspi_instance[SSPI_INSTANCE1], ENABLE);
	// temp = sspi_notbusy(sspi_instance[SSPI_INSTANCE1]);
	gpiov2_instance->clear = LDAC;
	delay_loop(10, 10);
	gpiov2_instance->set = LDAC;
	// gpiov2_instance->clear1 = SHUT;
	// delay_loop(10, 10);
	// gpiov2_instance->set = SHUT;


}

/** @fn void main()
 * @brief prints hello world
 */
void main()
{
	uint32_t temp = 0, retval = 0;
	uint8_t i = 0, j = 0;
	uint8_t temp_data = 0;
	uint8_t clk_rate = SSPI_CLOCK_FREQUENCY;
	uint8_t setup_time = SETUP_TIME_CYCLES, hold_time = HOLD_TIME_CYCLES;
	uint32_t read_value0 = 0 ,read_value1 = 0, read_value2 = 0, read_value3 = 0 , read_value4 = 0, read_value5 = 0, read_value6 = 0, read_value7 = 0;
	uint32_t vref = 3.3, div = 1024, result;
	uint32_t gpio_cntrl = 0, gpio_rd_data  = 0, test_rst[4] = {0};
	unsigned long temp_ctrl = 0;
	// gpiov2_instance->direction1 = LDAC | SHUT;
	*(pinmux_config_reg) = 0x154000;
	sspi_init();
	gpiov2_init();
	sspi_clear_fifo(sspi_instance[SSPI_INSTANCE1]);
	temp = sspi_notbusy(sspi_instance[SSPI_INSTANCE1]);
	printf("SSPI1 status: %x \n", temp);
	sspi_configure(sspi_instance[SSPI_INSTANCE1],  clk_rate, CLK_POLARITY_HIGH, CLK_PHASE_HIGH, MASTER, SPI_MASTER, MSB_FIRST, setup_time, hold_time);
	// sspi_instance[SSPI_INSTANCE1]->qual=0x00;
	// temp = sspi_notbusy(sspi_instance[SSPI_INSTANCE0]);
	// printf("SSPI1 status: %x \n", temp);

	// sspi_clear_fifo(sspi_instance[SSPI_INSTANCE0]);
	// temp = sspi_notbusy(sspi_instance[SSPI_INSTANCE0]);
	// printf("SSPI1 status: %x \n", temp);

	sspi_configure(sspi_instance[SSPI_INSTANCE1],  clk_rate, CLK_POLARITY_HIGH, CLK_PHASE_HIGH, MASTER, SPI_MASTER, MSB_FIRST, setup_time, hold_time);

	// sspi_instance[SSPI_INSTANCE1]->qual=0x00;
	temp = sspi_notbusy(sspi_instance[SSPI_INSTANCE1]);
	printf("SSPI1 status: %x \n", temp);
	printf("GPIO outputs %x ; GPIO8: %x", (uint16_t) GPIO_OUTPUTS, (uint16_t) GPIO8);
    printf("\n before Direction reg: %x", gpiov2_instance->direction);
	printf("Gpio_cntl before : %x ",gpio_cntrl);
	gpio_cntrl = GPIO_OUTPUTS;
	printf("Gpio_cntl AFTER : %x ",gpio_cntrl);
	gpiov2_instance->direction = GPIO_OUTPUTS;
	delay_loop(1000,1000);
 	printf("\n after Direction reg: %x", gpiov2_instance->direction);
	// while(1);
    gpiov2_instance->clear = gpio_cntrl; //Make gpio1 (output) as low
 	printf("\n Data reg: %x", (gpiov2_instance->data)>>7);
	printf("\n Data reg: %x", gpiov2_instance->data);
	//while(1);
	while(1)
	{
//Read ADC value 
	adc_read_digital_value(&read_value0, CHANNEL_0, SINGLE_CHANNEL, sspi_instance[SSPI_INSTANCE1]);	
	//printf("\n The read value0 is %x", read_value0);
	printf("\n The read value0 is %x", read_value0/64);
	gpio_cntrl = read_value0 / 64;

    gpiov2_instance->set = (gpio_cntrl & 0xf) << 20; //Make gpio1 (output) as high

	gpiov2_instance->clear = (~gpio_cntrl & 0xf) << 20;
	delay_loop(1000, 2000);

	// adc_read_digital_value(&read_value0, CHANNEL_0, SINGLE_CHANNEL, sspi_instance[SSPI_INSTANCE1]);	
	// //printf("\n The read value0 is %x", read_value0);
	// printf("\n The read value1 is %x", read_value0/64);
	// gpio_cntrl = read_value0 / 64;

    // gpiov2_instance->set = (gpio_cntrl & 0xf) << 24; //Make gpio1 (output) as high

	// gpiov2_instance->clear = (~gpio_cntrl & 0xf) << 24;
	// delay_loop(1000, 2000);


	// adc_read_digital_value(&read_value1, CHANNEL_1, SINGLE_CHANNEL);	
	// printf("\n The read value1 is %x", read_value1);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value2, CHANNEL_2, SINGLE_CHANNEL);	
	// printf("\n The read value2 is %x", read_value2);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value3, CHANNEL_3, SINGLE_CHANNEL);	
	// printf("\n The read value3 is %x", read_value3);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value4, CHANNEL_4, SINGLE_CHANNEL);	
	// printf("\n The read value4 is %x", read_value4);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value5, CHANNEL_5, SINGLE_CHANNEL);	
	// printf("\n The read value5 is %x", read_value5);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value6, CHANNEL_6, SINGLE_CHANNEL);	
	// printf("\n The read value6 is %x", read_value6);
	// delay_loop(1000, 2000);
	// adc_read_digital_value(&read_value7, CHANNEL_7, SINGLE_CHANNEL);	
	// printf("\n The read value7 is %x", read_value7);
	// delay_loop(1000, 2000);

//Write to DAC A
		// dac_send_digital_value(0x000, 0, 1, 1, 1);
		// printf("\n DATA SENT");
		// delay_loop(2000, 2000);
		// dac_send_digital_value(0x8F, 0, 0, 0, 0);
		// printf("\n DATA1 SENT");
		// delay_loop(2000, 2000);

//Write to DAC B
		// dac_send_digital_value(0x000, 1, 1, 1, 1);
		// delay_loop(2000, 2000);
		// dac_send_digital_value(0xFFF, 1, 1, 1, 1);
		// delay_loop(2000, 2000);
	};
}