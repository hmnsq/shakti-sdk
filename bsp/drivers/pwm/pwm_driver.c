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

#تعریف_کن PERIOD_ثبات_MAX     0x0000FFFF 
#تعریف_کن DUTY_ثبات_MAX       0x0000FFFF 
#تعریف_کن CLOCK_ثبات_MAX      0x0000FFFF
#تعریف_کن CONTROL_ثبات_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح مجموعه_pwm_period_ثبات(صحيح module_عدد, صحيح مقدار)
{
	إذا (مقدار > PERIOD_ثبات_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_ثبات_MAX);	
		أرجع 0;
	}

	متطاير کوتاه* period_مقدار;
	period_مقدار = (صحيح*) (PWM_پایه_آدرس + module_عدد*PWM_MODULE_جابه_جایی + PERIOD_ثبات);
	*period_مقدار = مقدار;

	log_info("\n Period Register of module number %d set to %x", module_عدد, مقدار);

	أرجع 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح مجموعه_pwm_duty_ثبات(صحيح module_عدد, صحيح مقدار)
{
	متطاير کوتاه* duty_مقدار;

	إذا (مقدار > DUTY_ثبات_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_ثبات_MAX);
		أرجع 0;
	}

	duty_مقدار = PWM_پایه_آدرس + module_عدد*PWM_MODULE_جابه_جایی + DUTY_ثبات;
	*duty_مقدار = مقدار;

	log_info("\n Duty Register of module number %d set to %x", module_عدد, مقدار);

	أرجع 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
صحيح مجموعه_pwm_control_ثبات(صحيح module_عدد, صحيح مقدار)
{
	متطاير حرف* control_مقدار;

	إذا (مقدار > CONTROL_ثبات_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_ثبات_MAX);	
		أرجع 0;
	}

	control_مقدار = PWM_پایه_آدرس + module_عدد*PWM_MODULE_جابه_جایی + CONTROL_ثبات;
	*control_مقدار = مقدار;

	log_info("\n Control Register of module number %d set to %x", module_عدد, مقدار);

	أرجع 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
صحيح pwm_check_continuous_نما(صحيح module_عدد)
{
	متطاير حرف* control_مقدار;
	control_مقدار = PWM_پایه_آدرس + module_عدد*PWM_MODULE_جابه_جایی + CONTROL_ثبات;
	صحيح مقدار = *control_مقدار & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (مقدار>>3));
	إذا( (مقدار>>3) == 1)
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
صحيح مجموعه_pwm_clock_ثبات(صحيح module_عدد, صحيح مقدار)
{
	متطاير کوتاه* clock_مقدار;

	إذا (مقدار > CLOCK_ثبات_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_ثبات_MAX);
		أرجع 0;
	}

	clock_مقدار = PWM_پایه_آدرس + module_عدد*PWM_MODULE_جابه_جایی + CLOCK_ثبات;
	*clock_مقدار = مقدار;

	أرجع 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
فراغ pwm_clear_registers(صحيح module_عدد)
{
	مجموعه_pwm_period_ثبات(module_عدد, 0);
	مجموعه_pwm_duty_ثبات(module_عدد, 0);
	مجموعه_pwm_control_ثبات(module_عدد, 0);
	مجموعه_pwm_clock_ثبات(module_عدد, 0);

	log_info("\n All registers of module number %d cleared", module_عدد);
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
صحيح configure_control_ثبات_نما(صحيح نما)
{
	صحيح مقدار = 0x0;

	إذا (نما == 0) {
		log_info("\n Current Module is set to PWM mode");

		مقدار += PWM_ENABLE;
		مقدار += PWM_شروع;
		مقدار += PWM_OUTPUT_ENABLE;
	}
	وإلا إذا (نما == 1) {
		log_info("\n Current Module is set to timer once only mode");

		مقدار += PWM_شروع;
	}
	وإلا إذا(نما == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		مقدار += PWM_شروع;
		مقدار += CONTINUOUS_ONCE;
	}

	أرجع مقدار;
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
فراغ pwm_شروع(صحيح module_عدد, صحيح نما)
{
	صحيح control = configure_control_ثبات_نما(نما);

	إذا(مجموعه_pwm_control_ثبات(module_عدد, control))
	{
		log_info("\n PWM module number %d has been entered", module_عدد);
	}

	إذا(!مجموعه_pwm_control_ثبات(module_عدد, control))
	{
		log_error("\n PWM module number %d not entered",module_عدد);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
فراغ pwm_use_external_clock(صحيح module_عدد, bool مقدار)
{
	بیعلامت حرف* control_مقدار;
	control_مقدار = PWM_پایه_آدرس + module_عدد * PWM_MODULE_جابه_جایی + CONTROL_ثبات;
	إذا(مقدار == 1)
	control_مقدار += CLOCK_SELECTOR;
	وإلا إذا(control_مقدار && CLOCK_SELECTOR)
	control_مقدار -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
فراغ pwm_مجموعه_clock(صحيح module_عدد, صحيح clock_مقسوم_علیه)
{
	إذا (مجموعه_pwm_clock_ثبات(module_عدد, clock_مقسوم_علیه) == 0)
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
فراغ pwm_مجموعه_duty_چرخه(صحيح module_عدد, صحيح duty)
{
	إذا (مجموعه_pwm_duty_ثبات(module_عدد, duty) == 0) {
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
فراغ pwm_مجموعه_periodic_چرخه(صحيح module_عدد, صحيح period)
{
	إذا(مجموعه_pwm_period_ثبات(module_عدد, period) == 0) {
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
فراغ pwm_configure(صحيح module_عدد,صحيح clock_مقسوم_علیه, صحيح period, صحيح duty, bool external_clock)
{
	pwm_مجموعه_periodic_چرخه(module_عدد, period);
	pwm_مجموعه_duty_چرخه(module_عدد, duty);
	pwm_مجموعه_clock(module_عدد, clock_مقسوم_علیه);
	pwm_use_external_clock(module_عدد, external_clock);
	log_info("\nPWM %d succesfully configured",module_عدد);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ pwm_stop(صحيح module_عدد)
{
	مجموعه_pwm_control_ثبات(module_عدد, 0x0);
	log_info("\n PWM module number %d has been stopped", module_عدد);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
فراغ show_ثبات_مقادیر(صحيح module_عدد)
{
	متطاير بیعلامت کوتاه* period_مقدار;
	متطاير بیعلامت کوتاه* duty_مقدار;
	متطاير بیعلامت حرف*  control_مقدار;
	متطاير بیعلامت کوتاه* clock_مقدار;

	period_مقدار = PWM_پایه_آدرس + module_عدد * PWM_MODULE_جابه_جایی + PERIOD_ثبات;
	duty_مقدار = PWM_پایه_آدرس + module_عدد * PWM_MODULE_جابه_جایی + DUTY_ثبات;
	control_مقدار = PWM_پایه_آدرس + module_عدد * PWM_MODULE_جابه_جایی + CONTROL_ثبات;
	clock_مقدار = PWM_پایه_آدرس + module_عدد * PWM_MODULE_جابه_جایی + CLOCK_ثبات;

	log_info("\nThe value of period register is %x",  *period_مقدار);
	log_info("\nThe value of duty register is %x",    *duty_مقدار);
	log_info("\nThe value of control register is %x", *control_مقدار);
	log_info("\nThe value of clock register is %x",   *clock_مقدار);
}

