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

#تعریف_کرو PERIOD_رجسٹر_MAX     0x0000FFFF 
#تعریف_کرو DUTY_رجسٹر_MAX       0x0000FFFF 
#تعریف_کرو CLOCK_رجسٹر_MAX      0x0000FFFF
#تعریف_کرو CONTROL_رجسٹر_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سیٹ_pwm_period_رجسٹر(صحيح module_نمبر, صحيح قدر)
{
	إذا (قدر > PERIOD_رجسٹر_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_رجسٹر_MAX);	
		أرجع 0;
	}

	متطاير چھوٹا* period_قدر;
	period_قدر = (صحيح*) (PWM_ادھار_پتہ + module_نمبر*PWM_MODULE_وتھ + PERIOD_رجسٹر);
	*period_قدر = قدر;

	log_info("\n Period Register of module number %d set to %x", module_نمبر, قدر);

	أرجع 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سیٹ_pwm_duty_رجسٹر(صحيح module_نمبر, صحيح قدر)
{
	متطاير چھوٹا* duty_قدر;

	إذا (قدر > DUTY_رجسٹر_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_رجسٹر_MAX);
		أرجع 0;
	}

	duty_قدر = PWM_ادھار_پتہ + module_نمبر*PWM_MODULE_وتھ + DUTY_رجسٹر;
	*duty_قدر = قدر;

	log_info("\n Duty Register of module number %d set to %x", module_نمبر, قدر);

	أرجع 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح سیٹ_pwm_control_رجسٹر(صحيح module_نمبر, صحيح قدر)
{
	متطاير حرف* control_قدر;

	إذا (قدر > CONTROL_رجسٹر_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_رجسٹر_MAX);	
		أرجع 0;
	}

	control_قدر = PWM_ادھار_پتہ + module_نمبر*PWM_MODULE_وتھ + CONTROL_رجسٹر;
	*control_قدر = قدر;

	log_info("\n Control Register of module number %d set to %x", module_نمبر, قدر);

	أرجع 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
صحيح pwm_check_continuous_منوال(صحيح module_نمبر)
{
	متطاير حرف* control_قدر;
	control_قدر = PWM_ادھار_پتہ + module_نمبر*PWM_MODULE_وتھ + CONTROL_رجسٹر;
	صحيح قدر = *control_قدر & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (قدر>>3));
	إذا( (قدر>>3) == 1)
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
صحيح سیٹ_pwm_clock_رجسٹر(صحيح module_نمبر, صحيح قدر)
{
	متطاير چھوٹا* clock_قدر;

	إذا (قدر > CLOCK_رجسٹر_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_رجسٹر_MAX);
		أرجع 0;
	}

	clock_قدر = PWM_ادھار_پتہ + module_نمبر*PWM_MODULE_وتھ + CLOCK_رجسٹر;
	*clock_قدر = قدر;

	أرجع 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
فراغ pwm_clear_registers(صحيح module_نمبر)
{
	سیٹ_pwm_period_رجسٹر(module_نمبر, 0);
	سیٹ_pwm_duty_رجسٹر(module_نمبر, 0);
	سیٹ_pwm_control_رجسٹر(module_نمبر, 0);
	سیٹ_pwm_clock_رجسٹر(module_نمبر, 0);

	log_info("\n All registers of module number %d cleared", module_نمبر);
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
صحيح configure_control_رجسٹر_منوال(صحيح منوال)
{
	صحيح قدر = 0x0;

	إذا (منوال == 0) {
		log_info("\n Current Module is set to PWM mode");

		قدر += PWM_ENABLE;
		قدر += PWM_شروع;
		قدر += PWM_OUTPUT_ENABLE;
	}
	وإلا إذا (منوال == 1) {
		log_info("\n Current Module is set to timer once only mode");

		قدر += PWM_شروع;
	}
	وإلا إذا(منوال == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		قدر += PWM_شروع;
		قدر += CONTINUOUS_ONCE;
	}

	أرجع قدر;
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
فراغ pwm_شروع(صحيح module_نمبر, صحيح منوال)
{
	صحيح control = configure_control_رجسٹر_منوال(منوال);

	إذا(سیٹ_pwm_control_رجسٹر(module_نمبر, control))
	{
		log_info("\n PWM module number %d has been entered", module_نمبر);
	}

	إذا(!سیٹ_pwm_control_رجسٹر(module_نمبر, control))
	{
		log_error("\n PWM module number %d not entered",module_نمبر);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
فراغ pwm_use_external_clock(صحيح module_نمبر, bool قدر)
{
	بنانشانی حرف* control_قدر;
	control_قدر = PWM_ادھار_پتہ + module_نمبر * PWM_MODULE_وتھ + CONTROL_رجسٹر;
	إذا(قدر == 1)
	control_قدر += CLOCK_SELECTOR;
	وإلا إذا(control_قدر && CLOCK_SELECTOR)
	control_قدر -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
فراغ pwm_سیٹ_clock(صحيح module_نمبر, صحيح clock_مقسوم_علیہ)
{
	إذا (سیٹ_pwm_clock_رجسٹر(module_نمبر, clock_مقسوم_علیہ) == 0)
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
فراغ pwm_سیٹ_duty_چکر(صحيح module_نمبر, صحيح duty)
{
	إذا (سیٹ_pwm_duty_رجسٹر(module_نمبر, duty) == 0) {
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
فراغ pwm_سیٹ_periodic_چکر(صحيح module_نمبر, صحيح period)
{
	إذا(سیٹ_pwm_period_رجسٹر(module_نمبر, period) == 0) {
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
فراغ pwm_configure(صحيح module_نمبر,صحيح clock_مقسوم_علیہ, صحيح period, صحيح duty, bool external_clock)
{
	pwm_سیٹ_periodic_چکر(module_نمبر, period);
	pwm_سیٹ_duty_چکر(module_نمبر, duty);
	pwm_سیٹ_clock(module_نمبر, clock_مقسوم_علیہ);
	pwm_use_external_clock(module_نمبر, external_clock);
	log_info("\nPWM %d succesfully configured",module_نمبر);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ pwm_stop(صحيح module_نمبر)
{
	سیٹ_pwm_control_رجسٹر(module_نمبر, 0x0);
	log_info("\n PWM module number %d has been stopped", module_نمبر);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ show_رجسٹر_اقدار(صحيح module_نمبر)
{
	متطاير بنانشانی چھوٹا* period_قدر;
	متطاير بنانشانی چھوٹا* duty_قدر;
	متطاير بنانشانی حرف*  control_قدر;
	متطاير بنانشانی چھوٹا* clock_قدر;

	period_قدر = PWM_ادھار_پتہ + module_نمبر * PWM_MODULE_وتھ + PERIOD_رجسٹر;
	duty_قدر = PWM_ادھار_پتہ + module_نمبر * PWM_MODULE_وتھ + DUTY_رجسٹر;
	control_قدر = PWM_ادھار_پتہ + module_نمبر * PWM_MODULE_وتھ + CONTROL_رجسٹر;
	clock_قدر = PWM_ادھار_پتہ + module_نمبر * PWM_MODULE_وتھ + CLOCK_رجسٹر;

	log_info("\nThe value of period register is %x",  *period_قدر);
	log_info("\nThe value of duty register is %x",    *duty_قدر);
	log_info("\nThe value of control register is %x", *control_قدر);
	log_info("\nThe value of clock register is %x",   *clock_قدر);
}

