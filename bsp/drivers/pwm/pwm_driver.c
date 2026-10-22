/***************************************************************************
* Project               	  : shakti devt board
* Name of the file	          : pwm_driver.c
* Brief Description of file       : PWM Driver Code.
* Name of Author    	          : Abhinav Ramnath
* Email ID                        : abhinavramnath13@gmail.com

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
@file pwm_driver.c
@brief source file for pwm
@detail the device driver for the pwm module which is used to change the frequency, period and duty registers 
*/

#ضمن "pwm_driver.h"
#ضمن "platform.h"
#ضمن "log.h"

#تعریف_کړه PERIOD_ثبتوونکی_MAX     0x0000FFFF 
#تعریف_کړه DUTY_ثبتوونکی_MAX       0x0000FFFF 
#تعریف_کړه CLOCK_ثبتوونکی_MAX      0x0000FFFF
#تعریف_کړه CONTROL_ثبتوونکی_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سېټ_pwm_period_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت)
{
	إذا (ارزښت > PERIOD_ثبتوونکی_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_ثبتوونکی_MAX);	
		أرجع 0;
	}

	متطاير لنډ* period_ارزښت;
	period_ارزښت = (صحيح*) (PWM_بنسټ_پته + module_شمېره*PWM_MODULE_دننه_واټن + PERIOD_ثبتوونکی);
	*period_ارزښت = ارزښت;

	log_info("\n Period Register of module number %d set to %x", module_شمېره, ارزښت);

	أرجع 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سېټ_pwm_duty_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت)
{
	متطاير لنډ* duty_ارزښت;

	إذا (ارزښت > DUTY_ثبتوونکی_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_ثبتوونکی_MAX);
		أرجع 0;
	}

	duty_ارزښت = PWM_بنسټ_پته + module_شمېره*PWM_MODULE_دننه_واټن + DUTY_ثبتوونکی;
	*duty_ارزښت = ارزښت;

	log_info("\n Duty Register of module number %d set to %x", module_شمېره, ارزښت);

	أرجع 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سېټ_pwm_control_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت)
{
	متطاير حرف* control_ارزښت;

	إذا (ارزښت > CONTROL_ثبتوونکی_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_ثبتوونکی_MAX);	
		أرجع 0;
	}

	control_ارزښت = PWM_بنسټ_پته + module_شمېره*PWM_MODULE_دننه_واټن + CONTROL_ثبتوونکی;
	*control_ارزښت = ارزښت;

	log_info("\n Control Register of module number %d set to %x", module_شمېره, ارزښت);

	أرجع 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
صحيح pwm_check_continuous_ډېرپېښ(صحيح module_شمېره)
{
	متطاير حرف* control_ارزښت;
	control_ارزښت = PWM_بنسټ_پته + module_شمېره*PWM_MODULE_دننه_واټن + CONTROL_ثبتوونکی;
	صحيح ارزښت = *control_ارزښت & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (ارزښت>>3));
	إذا( (ارزښت>>3) == 1)
		أرجع 1;
	وإلا
		أرجع 0;
}

/** @fn int set_pwm_clock_register(int module_number, int value)
 * @brief Function to set the clock register of the selected pwm module
 * @details This function will be called to set the value of the clock register(clock divisor) for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سېټ_pwm_clock_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت)
{
	متطاير لنډ* clock_ارزښت;

	إذا (ارزښت > CLOCK_ثبتوونکی_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_ثبتوونکی_MAX);
		أرجع 0;
	}

	clock_ارزښت = PWM_بنسټ_پته + module_شمېره*PWM_MODULE_دننه_واټن + CLOCK_ثبتوونکی;
	*clock_ارزښت = ارزښت;

	أرجع 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
فراغ pwm_clear_registers(صحيح module_شمېره)
{
	سېټ_pwm_period_ثبتوونکی(module_شمېره, 0);
	سېټ_pwm_duty_ثبتوونکی(module_شمېره, 0);
	سېټ_pwm_control_ثبتوونکی(module_شمېره, 0);
	سېټ_pwm_clock_ثبتوونکی(module_شمېره, 0);

	log_info("\n All registers of module number %d cleared", module_شمېره);
}

/** @fn void pwm_init
 * @brief Function to initialize all pwm modules
 * @details This function will be called to initialize all pwm modules
 */
فراغ pwm_init(فراغ)
{
	صحيح i;

	لكل (i = 0; i < 5; i++) {
		pwm_clear_registers(i);
	}

	log_info("\n All Register values of all modules cleared");
}

/** @fn int configure_control_register_mode(int mode)
 * @brief Function to set value of control register based on mode selected 
 * @details This function will set value of control register based on mode selected
 * @param  int ( mode- 
 *                0-PWM Mode.
 *                1-Timer Mode run once.
 *                2-Timer Mode run continuously.)
 * @return int (returns value to be set in the control register.)
 */
صحيح configure_control_ثبتوونکی_ډېرپېښ(صحيح ډېرپېښ)
{
	صحيح ارزښت = 0x0;

	إذا (ډېرپېښ == 0) {
		log_info("\n Current Module is set to PWM mode");

		ارزښت += PWM_ENABLE;
		ارزښت += PWM_پیل;
		ارزښت += PWM_OUTPUT_ENABLE;
	}
	وإلا إذا (ډېرپېښ == 1) {
		log_info("\n Current Module is set to timer once only mode");

		ارزښت += PWM_پیل;
	}
	وإلا إذا(ډېرپېښ == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		ارزښت += PWM_پیل;
		ارزښت += CONTINUOUS_ONCE;
	}

	أرجع ارزښت;
}

/** @fn void pwm_start(int module_number, int mode) 
 * @brief Function to start a pwm module with a specific mode
 * @details This function will start a pwm module with a specific mode
 * @param int module_number-  the pwm module to be selected
 * @param int (mode - mode to be selected
 *                  0-PWM Mode
 *                  1-Timer Mode run once
 *                  2-Timer Mode run contin )
 */
فراغ pwm_پیل(صحيح module_شمېره, صحيح ډېرپېښ)
{
	صحيح control = configure_control_ثبتوونکی_ډېرپېښ(ډېرپېښ);

	إذا(سېټ_pwm_control_ثبتوونکی(module_شمېره, control))
	{
		log_info("\n PWM module number %d has been entered", module_شمېره);
	}

	إذا(!سېټ_pwm_control_ثبتوونکی(module_شمېره, control))
	{
		log_error("\n PWM module number %d not entered",module_شمېره);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
فراغ pwm_use_external_clock(صحيح module_شمېره, bool ارزښت)
{
	بینښه حرف* control_ارزښت;
	control_ارزښت = PWM_بنسټ_پته + module_شمېره * PWM_MODULE_دننه_واټن + CONTROL_ثبتوونکی;
	إذا(ارزښت == 1)
	control_ارزښت += CLOCK_SELECTOR;
	وإلا إذا(control_ارزښت && CLOCK_SELECTOR)
	control_ارزښت -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
فراغ pwm_سېټ_clock(صحيح module_شمېره, صحيح clock_وېشونکی)
{
	إذا (سېټ_pwm_clock_ثبتوونکی(module_شمېره, clock_وېشونکی) == 0)
	{
		log_error("\n Error in setting clock register");
	}
}

/** @fn void pwm_set_duty_cycle(int module_number, int duty) 
 * @brief Function to set the duty cycle value of a specific pwm module 
 * @details This function will set the duty cycles value of a specific pwm module
 * @param int module_number-  the pwm module to be selected 
 * @param int duty - value of duty cycles to be used to decide how many period cycles the pwm signal is set to 1.
 */
فراغ pwm_سېټ_duty_دوره(صحيح module_شمېره, صحيح duty)
{
	إذا (سېټ_pwm_duty_ثبتوونکی(module_شمېره, duty) == 0) {
		log_error("\n Error in setting duty register");
	}
}

/** @fn  void pwm_set_periodic_cycle(int module_number, int period)
 * @brief Function to set the period cycles value of a specific pwm module
 * @details This function will set the period cycles value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 * @param int clock_divisor-  value of period cycles which is used to further divide the                                                      
 *         frequency into fixed period cycles.
 */
فراغ pwm_سېټ_periodic_دوره(صحيح module_شمېره, صحيح period)
{
	إذا(سېټ_pwm_period_ثبتوونکی(module_شمېره, period) == 0) {
		log_error("\n Error in setting period register");
	}
}

/** @fn void pwm_configure(int module_number,int clock_divisor, int period, int duty, bool external_clock)
 * @brief Function to configure the pwm module with all the values required like clock divisor, period, duty cycle, and the use of external clock
 * @details This function configure the pwm module
 * @param int module_number - the pwm module to be selected
 * @param int clock_divisor - value of clock divisor to be used it divides the base clock frequency by the given value
 * @param int period - value of periodic cycle to be used. the signal resets after every count of the periodic cycle
 * @param int duty_cycle - value of duty cycle. It specifies how many cycles the signal is active out of the periodic cycle
 * @param bool external_clock - value of external clock selector. It specifies if external clock is to be used.
  */
فراغ pwm_configure(صحيح module_شمېره,صحيح clock_وېشونکی, صحيح period, صحيح duty, bool external_clock)
{
	pwm_سېټ_periodic_دوره(module_شمېره, period);
	pwm_سېټ_duty_دوره(module_شمېره, duty);
	pwm_سېټ_clock(module_شمېره, clock_وېشونکی);
	pwm_use_external_clock(module_شمېره, external_clock);
	log_info("\nPWM %d succesfully configured",module_شمېره);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ pwm_stop(صحيح module_شمېره)
{
	سېټ_pwm_control_ثبتوونکی(module_شمېره, 0x0);
	log_info("\n PWM module number %d has been stopped", module_شمېره);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ show_ثبتوونکی_ارزښتونه(صحيح module_شمېره)
{
	متطاير بینښه لنډ* period_ارزښت;
	متطاير بینښه لنډ* duty_ارزښت;
	متطاير بینښه حرف*  control_ارزښت;
	متطاير بینښه لنډ* clock_ارزښت;

	period_ارزښت = PWM_بنسټ_پته + module_شمېره * PWM_MODULE_دننه_واټن + PERIOD_ثبتوونکی;
	duty_ارزښت = PWM_بنسټ_پته + module_شمېره * PWM_MODULE_دننه_واټن + DUTY_ثبتوونکی;
	control_ارزښت = PWM_بنسټ_پته + module_شمېره * PWM_MODULE_دننه_واټن + CONTROL_ثبتوونکی;
	clock_ارزښت = PWM_بنسټ_پته + module_شمېره * PWM_MODULE_دننه_واټن + CLOCK_ثبتوونکی;

	log_info("\nThe value of period register is %x",  *period_ارزښت);
	log_info("\nThe value of duty register is %x",    *duty_ارزښت);
	log_info("\nThe value of control register is %x", *control_ارزښت);
	log_info("\nThe value of clock register is %x",   *clock_ارزښت);
}

