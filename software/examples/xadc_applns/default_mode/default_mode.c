/***************************************************************************
* Project                               : shakti devt board
* Name of the file                      : xadc_default.c
* Brief Description of file             : Demonstrates the usage of onchip xadc.
* Name of Author                        : Sathya Narayanan
* Email ID                              : sathya281@gmail.com

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
@file xadc_default.c
@brief  write data to flash by xadc
@detail Contains driver codes to read and write flash using SPI interface.
*/

#समावेश <stdint.h>
#समावेश "xadc_driver.h"
#समावेश "uart.h"

/** 
 * @fn int main()
 * @brief Calls the xadc apis to read temperature and onchip voltage.
 * @return none
 */
व्योम मुख्य()
{
	जबतक(1)
	{
		uint32_t मूल्य = xadc_read_तथ्य(0x41200);

		म_लिखो("value = %f\n", xadc_onchip_अस्थायी(मूल्य));

		मूल्य = xadc_read_तथ्य(0x41204);
		म_लिखो("value = %f\n", xadc_onchip_voltage(मूल्य));
	}
}
