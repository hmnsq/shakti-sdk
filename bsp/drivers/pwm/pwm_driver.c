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

#అన్తర్భావ "pwm_driver.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "log.h"

#నిర్వచించు PERIOD_రిజిస్టరు_MAX     0x0000FFFF 
#నిర్వచించు DUTY_రిజిస్టరు_MAX       0x0000FFFF 
#నిర్వచించు CLOCK_రిజిస్టరు_MAX      0x0000FFFF
#నిర్వచించు CONTROL_రిజిస్టరు_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
పూర్ణాంకం సమితి_pwm_period_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ)
{
	ఒకవేళ (విలువ > PERIOD_రిజిస్టరు_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_రిజిస్టరు_MAX);	
		తిరిగి 0;
	}

	అస్థిర పొట్టి* period_విలువ;
	period_విలువ = (పూర్ణాంకం*) (PWM_పునాది_చిరునామా + module_సంఖ్య*PWM_MODULE_స్థానభ్రంశం + PERIOD_రిజిస్టరు);
	*period_విలువ = విలువ;

	log_info("\n Period Register of module number %d set to %x", module_సంఖ్య, విలువ);

	తిరిగి 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
పూర్ణాంకం సమితి_pwm_duty_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ)
{
	అస్థిర పొట్టి* duty_విలువ;

	ఒకవేళ (విలువ > DUTY_రిజిస్టరు_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_రిజిస్టరు_MAX);
		తిరిగి 0;
	}

	duty_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య*PWM_MODULE_స్థానభ్రంశం + DUTY_రిజిస్టరు;
	*duty_విలువ = విలువ;

	log_info("\n Duty Register of module number %d set to %x", module_సంఖ్య, విలువ);

	తిరిగి 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
పూర్ణాంకం సమితి_pwm_control_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ)
{
	అస్థిర అక్షరం* control_విలువ;

	ఒకవేళ (విలువ > CONTROL_రిజిస్టరు_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_రిజిస్టరు_MAX);	
		తిరిగి 0;
	}

	control_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య*PWM_MODULE_స్థానభ్రంశం + CONTROL_రిజిస్టరు;
	*control_విలువ = విలువ;

	log_info("\n Control Register of module number %d set to %x", module_సంఖ్య, విలువ);

	తిరిగి 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
పూర్ణాంకం pwm_check_continuous_బహుళకం(పూర్ణాంకం module_సంఖ్య)
{
	అస్థిర అక్షరం* control_విలువ;
	control_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య*PWM_MODULE_స్థానభ్రంశం + CONTROL_రిజిస్టరు;
	పూర్ణాంకం విలువ = *control_విలువ & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (విలువ>>3));
	ఒకవేళ( (విలువ>>3) == 1)
		తిరిగి 1;
	లేకపోతే
		తిరిగి 0;
}

/** @fn int set_pwm_clock_register(int module_number, int value)
 * @brief Function to set the clock register of the selected pwm module
 * @details This function will be called to set the value of the clock register(clock divisor) for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
పూర్ణాంకం సమితి_pwm_clock_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ)
{
	అస్థిర పొట్టి* clock_విలువ;

	ఒకవేళ (విలువ > CLOCK_రిజిస్టరు_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_రిజిస్టరు_MAX);
		తిరిగి 0;
	}

	clock_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య*PWM_MODULE_స్థానభ్రంశం + CLOCK_రిజిస్టరు;
	*clock_విలువ = విలువ;

	తిరిగి 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
శూన్య pwm_clear_registers(పూర్ణాంకం module_సంఖ్య)
{
	సమితి_pwm_period_రిజిస్టరు(module_సంఖ్య, 0);
	సమితి_pwm_duty_రిజిస్టరు(module_సంఖ్య, 0);
	సమితి_pwm_control_రిజిస్టరు(module_సంఖ్య, 0);
	సమితి_pwm_clock_రిజిస్టరు(module_సంఖ్య, 0);

	log_info("\n All registers of module number %d cleared", module_సంఖ్య);
}

/** @fn void pwm_init
 * @brief Function to initialize all pwm modules
 * @details This function will be called to initialize all pwm modules
 */
శూన్య pwm_init(శూన్య)
{
	పూర్ణాంకం i;

	కొరకు (i = 0; i < 5; i++) {
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
పూర్ణాంకం configure_control_రిజిస్టరు_బహుళకం(పూర్ణాంకం బహుళకం)
{
	పూర్ణాంకం విలువ = 0x0;

	ఒకవేళ (బహుళకం == 0) {
		log_info("\n Current Module is set to PWM mode");

		విలువ += PWM_ENABLE;
		విలువ += PWM_ప్రారంభం;
		విలువ += PWM_OUTPUT_ENABLE;
	}
	లేకపోతే ఒకవేళ (బహుళకం == 1) {
		log_info("\n Current Module is set to timer once only mode");

		విలువ += PWM_ప్రారంభం;
	}
	లేకపోతే ఒకవేళ(బహుళకం == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		విలువ += PWM_ప్రారంభం;
		విలువ += CONTINUOUS_ONCE;
	}

	తిరిగి విలువ;
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
శూన్య pwm_ప్రారంభం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం బహుళకం)
{
	పూర్ణాంకం control = configure_control_రిజిస్టరు_బహుళకం(బహుళకం);

	ఒకవేళ(సమితి_pwm_control_రిజిస్టరు(module_సంఖ్య, control))
	{
		log_info("\n PWM module number %d has been entered", module_సంఖ్య);
	}

	ఒకవేళ(!సమితి_pwm_control_రిజిస్టరు(module_సంఖ్య, control))
	{
		log_error("\n PWM module number %d not entered",module_సంఖ్య);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
శూన్య pwm_use_external_clock(పూర్ణాంకం module_సంఖ్య, bool విలువ)
{
	గుర్తులేని అక్షరం* control_విలువ;
	control_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య * PWM_MODULE_స్థానభ్రంశం + CONTROL_రిజిస్టరు;
	ఒకవేళ(విలువ == 1)
	control_విలువ += CLOCK_SELECTOR;
	లేకపోతే ఒకవేళ(control_విలువ && CLOCK_SELECTOR)
	control_విలువ -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
శూన్య pwm_సమితి_clock(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం clock_భాజకం)
{
	ఒకవేళ (సమితి_pwm_clock_రిజిస్టరు(module_సంఖ్య, clock_భాజకం) == 0)
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
శూన్య pwm_సమితి_duty_చక్రం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం duty)
{
	ఒకవేళ (సమితి_pwm_duty_రిజిస్టరు(module_సంఖ్య, duty) == 0) {
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
శూన్య pwm_సమితి_periodic_చక్రం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం period)
{
	ఒకవేళ(సమితి_pwm_period_రిజిస్టరు(module_సంఖ్య, period) == 0) {
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
శూన్య pwm_configure(పూర్ణాంకం module_సంఖ్య,పూర్ణాంకం clock_భాజకం, పూర్ణాంకం period, పూర్ణాంకం duty, bool external_clock)
{
	pwm_సమితి_periodic_చక్రం(module_సంఖ్య, period);
	pwm_సమితి_duty_చక్రం(module_సంఖ్య, duty);
	pwm_సమితి_clock(module_సంఖ్య, clock_భాజకం);
	pwm_use_external_clock(module_సంఖ్య, external_clock);
	log_info("\nPWM %d succesfully configured",module_సంఖ్య);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
శూన్య pwm_stop(పూర్ణాంకం module_సంఖ్య)
{
	సమితి_pwm_control_రిజిస్టరు(module_సంఖ్య, 0x0);
	log_info("\n PWM module number %d has been stopped", module_సంఖ్య);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
శూన్య show_రిజిస్టరు_విలువలు(పూర్ణాంకం module_సంఖ్య)
{
	అస్థిర గుర్తులేని పొట్టి* period_విలువ;
	అస్థిర గుర్తులేని పొట్టి* duty_విలువ;
	అస్థిర గుర్తులేని అక్షరం*  control_విలువ;
	అస్థిర గుర్తులేని పొట్టి* clock_విలువ;

	period_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య * PWM_MODULE_స్థానభ్రంశం + PERIOD_రిజిస్టరు;
	duty_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య * PWM_MODULE_స్థానభ్రంశం + DUTY_రిజిస్టరు;
	control_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య * PWM_MODULE_స్థానభ్రంశం + CONTROL_రిజిస్టరు;
	clock_విలువ = PWM_పునాది_చిరునామా + module_సంఖ్య * PWM_MODULE_స్థానభ్రంశం + CLOCK_రిజిస్టరు;

	log_info("\nThe value of period register is %x",  *period_విలువ);
	log_info("\nThe value of duty register is %x",    *duty_విలువ);
	log_info("\nThe value of control register is %x", *control_విలువ);
	log_info("\nThe value of clock register is %x",   *clock_విలువ);
}

