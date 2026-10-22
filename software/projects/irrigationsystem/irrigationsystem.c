/***************************************************************************
* Project                               :  shakti devt board
* Name of the file                      :  irrigationsystem.c
* Brief Description of file             :  Sample project to demonstrate 
                                           integration of temperature and moiture sensors.
* Name of Author                        :  Anand Kumar S
* Email ID                              :  007334@imail.iitm.ac.in

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
  @file irrigationsystem.c
  @brief Sample project to build a irrigation system.
  @details Mositure sensor checks for the water content in the soil or medium.
  Based on the sensor value, a motor is turned on or off.

  In this sample project Artix7 35t board is used. Shakti E class is programmed
  in Artix7 35t.
  Moisture sensor is connected to GPIO pin 0 and 3.3v source on the board.
  Motor is connected to GPIO pin 7. GPIO provides less than 3.3V on high,
  which is not sufficient to drive a motor, hence a level convertor has
  to be used to convert to 5V and also provide higher amps to the motor
  from a power source independent of the power from the board.
  When there is sufficient moisture in soil or medium, sensor sends high signal.
  Based on the signal state, motor is turned off. When there is no moisture
  in the soil, there is no signal from mositure sensor and motor will be turned
  on.
*/

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"

బాహ్య శూన్య delay_loop(గుర్తులేని దీర్ఘ cntr1, గుర్తులేని దీర్ఘ cntr2);

#నిర్వచించు MOTOR_ON (1 << 7)
#నిర్వచించు MOTOR_OFF 0

/**
 * @fn void main ()
 * @brief Entry point for the program
 */

శూన్య ప్రధాన()
{
    గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
    గుర్తులేని దీర్ఘ moistureDetetected = 0;

/*********************************************************************
   set the read & write bits in GPIO Direction Control Register
   Bit 0 for read, this corresponds to GPIO0 
   Bit 7 for write, this corresponds to GPIO7
*********************************************************************/
    write_మాట(GPIO_DIRECTION_CNTRL_REG, (0x00|MOTOR_ON));
    
    అయితే (1) {
        read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
        రాయి("\n Read Data:=%d", read_దత్తాంశం);
	moistureDetetected = ((read_దత్తాంశం & 1 ) == 1) ? 1 : 0;
        ఒకవేళ (moistureDetetected == 0) {
            write_మాట(GPIO_దత్తాంశం_REG, MOTOR_ON);
            రాయి("\nTurn on Motor");
        }
        లేకపోతే {
            write_మాట(GPIO_దత్తాంశం_REG, MOTOR_OFF);
            రాయి("\nTurn off Motor");
        }
        delay_loop(1000,1000);
    } 
}
