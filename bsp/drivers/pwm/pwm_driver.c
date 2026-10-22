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

#समावेश "pwm_driver.h"
#समावेश "platform.h"
#समावेश "log.h"

#घोषणा PERIOD_REGISTER_MAX     0x0000FFFF 
#घोषणा DUTY_REGISTER_MAX       0x0000FFFF 
#घोषणा CLOCK_REGISTER_MAX      0x0000FFFF
#घोषणा CONTROL_REGISTER_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
पूर्णांक set_pwm_period_register(पूर्णांक module_संख्या, पूर्णांक मूल्य)
{
	अगर (मूल्य > PERIOD_REGISTER_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_REGISTER_MAX);	
		वापस 0;
	}

	अस्थिर लघु* period_मूल्य;
	period_मूल्य = (पूर्णांक*) (PWM_BASE_ADDRESS + module_संख्या*PWM_MODULE_OFFSET + PERIOD_REGISTER);
	*period_मूल्य = मूल्य;

	log_info("\n Period Register of module number %d set to %x", module_संख्या, मूल्य);

	वापस 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
पूर्णांक set_pwm_duty_register(पूर्णांक module_संख्या, पूर्णांक मूल्य)
{
	अस्थिर लघु* duty_मूल्य;

	अगर (मूल्य > DUTY_REGISTER_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_REGISTER_MAX);
		वापस 0;
	}

	duty_मूल्य = PWM_BASE_ADDRESS + module_संख्या*PWM_MODULE_OFFSET + DUTY_REGISTER;
	*duty_मूल्य = मूल्य;

	log_info("\n Duty Register of module number %d set to %x", module_संख्या, मूल्य);

	वापस 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
पूर्णांक set_pwm_control_register(पूर्णांक module_संख्या, पूर्णांक मूल्य)
{
	अस्थिर अक्षर* control_मूल्य;

	अगर (मूल्य > CONTROL_REGISTER_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_REGISTER_MAX);	
		वापस 0;
	}

	control_मूल्य = PWM_BASE_ADDRESS + module_संख्या*PWM_MODULE_OFFSET + CONTROL_REGISTER;
	*control_मूल्य = मूल्य;

	log_info("\n Control Register of module number %d set to %x", module_संख्या, मूल्य);

	वापस 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
पूर्णांक pwm_check_continuous_mode(पूर्णांक module_संख्या)
{
	अस्थिर अक्षर* control_मूल्य;
	control_मूल्य = PWM_BASE_ADDRESS + module_संख्या*PWM_MODULE_OFFSET + CONTROL_REGISTER;
	पूर्णांक मूल्य = *control_मूल्य & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (मूल्य>>3));
	अगर( (मूल्य>>3) == 1)
		वापस 1;
	अन्यथा
		वापस 0;
}

/** @fn int set_pwm_clock_register(int module_number, int value)
 * @brief Function to set the clock register of the selected pwm module
 * @details This function will be called to set the value of the clock register(clock divisor) for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
पूर्णांक set_pwm_clock_register(पूर्णांक module_संख्या, पूर्णांक मूल्य)
{
	अस्थिर लघु* clock_मूल्य;

	अगर (मूल्य > CLOCK_REGISTER_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_REGISTER_MAX);
		वापस 0;
	}

	clock_मूल्य = PWM_BASE_ADDRESS + module_संख्या*PWM_MODULE_OFFSET + CLOCK_REGISTER;
	*clock_मूल्य = मूल्य;

	वापस 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
व्योम pwm_clear_registers(पूर्णांक module_संख्या)
{
	set_pwm_period_register(module_संख्या, 0);
	set_pwm_duty_register(module_संख्या, 0);
	set_pwm_control_register(module_संख्या, 0);
	set_pwm_clock_register(module_संख्या, 0);

	log_info("\n All registers of module number %d cleared", module_संख्या);
}

/** @fn void pwm_init
 * @brief Function to initialize all pwm modules
 * @details This function will be called to initialize all pwm modules
 */
व्योम pwm_init(व्योम)
{
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) {
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
पूर्णांक configure_control_register_mode(पूर्णांक mode)
{
	पूर्णांक मूल्य = 0x0;

	अगर (mode == 0) {
		log_info("\n Current Module is set to PWM mode");

		मूल्य += PWM_ENABLE;
		मूल्य += PWM_START;
		मूल्य += PWM_OUTPUT_ENABLE;
	}
	अन्यथा अगर (mode == 1) {
		log_info("\n Current Module is set to timer once only mode");

		मूल्य += PWM_START;
	}
	अन्यथा अगर(mode == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		मूल्य += PWM_START;
		मूल्य += CONTINUOUS_ONCE;
	}

	वापस मूल्य;
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
व्योम pwm_start(पूर्णांक module_संख्या, पूर्णांक mode)
{
	पूर्णांक control = configure_control_register_mode(mode);

	अगर(set_pwm_control_register(module_संख्या, control))
	{
		log_info("\n PWM module number %d has been entered", module_संख्या);
	}

	अगर(!set_pwm_control_register(module_संख्या, control))
	{
		log_error("\n PWM module number %d not entered",module_संख्या);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
व्योम pwm_use_external_clock(पूर्णांक module_संख्या, bool मूल्य)
{
	अचिन्हित अक्षर* control_मूल्य;
	control_मूल्य = PWM_BASE_ADDRESS + module_संख्या * PWM_MODULE_OFFSET + CONTROL_REGISTER;
	अगर(मूल्य == 1)
	control_मूल्य += CLOCK_SELECTOR;
	अन्यथा अगर(control_मूल्य && CLOCK_SELECTOR)
	control_मूल्य -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
व्योम pwm_set_clock(पूर्णांक module_संख्या, पूर्णांक clock_भाजक)
{
	अगर (set_pwm_clock_register(module_संख्या, clock_भाजक) == 0)
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
व्योम pwm_set_duty_cycle(पूर्णांक module_संख्या, पूर्णांक duty)
{
	अगर (set_pwm_duty_register(module_संख्या, duty) == 0) {
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
व्योम pwm_set_periodic_cycle(पूर्णांक module_संख्या, पूर्णांक period)
{
	अगर(set_pwm_period_register(module_संख्या, period) == 0) {
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
व्योम pwm_configure(पूर्णांक module_संख्या,पूर्णांक clock_भाजक, पूर्णांक period, पूर्णांक duty, bool external_clock)
{
	pwm_set_periodic_cycle(module_संख्या, period);
	pwm_set_duty_cycle(module_संख्या, duty);
	pwm_set_clock(module_संख्या, clock_भाजक);
	pwm_use_external_clock(module_संख्या, external_clock);
	log_info("\nPWM %d succesfully configured",module_संख्या);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
व्योम pwm_stop(पूर्णांक module_संख्या)
{
	set_pwm_control_register(module_संख्या, 0x0);
	log_info("\n PWM module number %d has been stopped", module_संख्या);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
व्योम show_register_मूल्यावली(पूर्णांक module_संख्या)
{
	अस्थिर अचिन्हित लघु* period_मूल्य;
	अस्थिर अचिन्हित लघु* duty_मूल्य;
	अस्थिर अचिन्हित अक्षर*  control_मूल्य;
	अस्थिर अचिन्हित लघु* clock_मूल्य;

	period_मूल्य = PWM_BASE_ADDRESS + module_संख्या * PWM_MODULE_OFFSET + PERIOD_REGISTER;
	duty_मूल्य = PWM_BASE_ADDRESS + module_संख्या * PWM_MODULE_OFFSET + DUTY_REGISTER;
	control_मूल्य = PWM_BASE_ADDRESS + module_संख्या * PWM_MODULE_OFFSET + CONTROL_REGISTER;
	clock_मूल्य = PWM_BASE_ADDRESS + module_संख्या * PWM_MODULE_OFFSET + CLOCK_REGISTER;

	log_info("\nThe value of period register is %x",  *period_मूल्य);
	log_info("\nThe value of duty register is %x",    *duty_मूल्य);
	log_info("\nThe value of control register is %x", *control_मूल्य);
	log_info("\nThe value of clock register is %x",   *clock_मूल्य);
}

