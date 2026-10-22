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

#ಅನ್ತರ್ಭಾವ "pwm_driver.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "log.h"

#ವ್ಯಾಖ್ಯಾನಿಸು PERIOD_ರಿಜಿಸ್ಟರ್_MAX     0x0000FFFF 
#ವ್ಯಾಖ್ಯಾನಿಸು DUTY_ರಿಜಿಸ್ಟರ್_MAX       0x0000FFFF 
#ವ್ಯಾಖ್ಯಾನಿಸು CLOCK_ರಿಜಿಸ್ಟರ್_MAX      0x0000FFFF
#ವ್ಯಾಖ್ಯಾನಿಸು CONTROL_ರಿಜಿಸ್ಟರ್_MAX    0x000000FF

/** @fn int set_pwm_period_register(int module_number, int value)
 * @brief Function to set the period register of the selected pwm module
 * @details This function will be called to set the value of the period register for the selected module 
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_period_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	ಆದರೆ (ಮೌಲ್ಯ > PERIOD_ರಿಜಿಸ್ಟರ್_MAX) {
		log_error("\nPeriod Register Value higher than max value (%x)", PERIOD_ರಿಜಿಸ್ಟರ್_MAX);	
		ಹಿಂತಿರುಗಿ 0;
	}

	ಅಸ್ಥಿರ ಗಿಡ್ಡ* period_ಮೌಲ್ಯ;
	period_ಮೌಲ್ಯ = (ಪೂರ್ಣಾಂಕ*) (PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ*PWM_MODULE_ಸ್ಥಾನಾಂತರ + PERIOD_ರಿಜಿಸ್ಟರ್);
	*period_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

	log_info("\n Period Register of module number %d set to %x", module_ಸಂಖ್ಯೆ, ಮೌಲ್ಯ);

	ಹಿಂತಿರುಗಿ 1;
}

/** @fn int set_pwm_duty_register(int module_number, int value)
 * @brief Function to set the duty register of the selected pwm module
 * @details This function will be called to set the value of the duty register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_duty_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	ಅಸ್ಥಿರ ಗಿಡ್ಡ* duty_ಮೌಲ್ಯ;

	ಆದರೆ (ಮೌಲ್ಯ > DUTY_ರಿಜಿಸ್ಟರ್_MAX) {
		log_error("\nDuty Register Value higher than max value (%x)", DUTY_ರಿಜಿಸ್ಟರ್_MAX);
		ಹಿಂತಿರುಗಿ 0;
	}

	duty_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ*PWM_MODULE_ಸ್ಥಾನಾಂತರ + DUTY_ರಿಜಿಸ್ಟರ್;
	*duty_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

	log_info("\n Duty Register of module number %d set to %x", module_ಸಂಖ್ಯೆ, ಮೌಲ್ಯ);

	ಹಿಂತಿರುಗಿ 1;
}

/** @fn int set_pwm_control_register(int module_number, int value)
 * @brief Function to set the control register of the selected pwm module
 * @details This function will be called to set the value of the control register for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xff.
 * @return int returns 1 on success, 0 on failure.
 */
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	ಅಸ್ಥಿರ ಅಕ್ಷರ* control_ಮೌಲ್ಯ;

	ಆದರೆ (ಮೌಲ್ಯ > CONTROL_ರಿಜಿಸ್ಟರ್_MAX) {
		log_error("\nControl Register Value higher than max value (%x)", CONTROL_ರಿಜಿಸ್ಟರ್_MAX);	
		ಹಿಂತಿರುಗಿ 0;
	}

	control_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ*PWM_MODULE_ಸ್ಥಾನಾಂತರ + CONTROL_ರಿಜಿಸ್ಟರ್;
	*control_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

	log_info("\n Control Register of module number %d set to %x", module_ಸಂಖ್ಯೆ, ಮೌಲ್ಯ);

	ಹಿಂತಿರುಗಿ 1;
}

/** @fn int pwm_check_continuous_mode(int module_number)
 * @brief Function to check if continuous mode is set for current pwm module. (This function helps in handling interrupts using plic).
 * @details This function will be called to check if continuous mode is set for current pwm module
 * @param int module_number- specifies the pwm module to be selected 
 * @return int returns 1 if running in continuous mode, 0 if not.
 */
ಪೂರ್ಣಾಂಕ pwm_check_continuous_ಬಹುಲಕ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ)
{
	ಅಸ್ಥಿರ ಅಕ್ಷರ* control_ಮೌಲ್ಯ;
	control_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ*PWM_MODULE_ಸ್ಥಾನಾಂತರ + CONTROL_ರಿಜಿಸ್ಟರ್;
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = *control_ಮೌಲ್ಯ & CONTINUOUS_ONCE;
	log_info("\n Running in continuous mode(1/0): %d", (ಮೌಲ್ಯ>>3));
	ಆದರೆ( (ಮೌಲ್ಯ>>3) == 1)
		ಹಿಂತಿರುಗಿ 1;
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ 0;
}

/** @fn int set_pwm_clock_register(int module_number, int value)
 * @brief Function to set the clock register of the selected pwm module
 * @details This function will be called to set the value of the clock register(clock divisor) for the selected module
 * @param int module_number- specifies the pwm module to be selected
 * @param int value - value to be set between 0x0000 to 0xffff.
 * @return int returns 1 on success, 0 on failure.
 */
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_clock_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	ಅಸ್ಥಿರ ಗಿಡ್ಡ* clock_ಮೌಲ್ಯ;

	ಆದರೆ (ಮೌಲ್ಯ > CLOCK_ರಿಜಿಸ್ಟರ್_MAX) {
		log_error("\nClock Register Value higher than max value (%x)", CLOCK_ರಿಜಿಸ್ಟರ್_MAX);
		ಹಿಂತಿರುಗಿ 0;
	}

	clock_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ*PWM_MODULE_ಸ್ಥಾನಾಂತರ + CLOCK_ರಿಜಿಸ್ಟರ್;
	*clock_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

	ಹಿಂತಿರುಗಿ 1;
}

/** @fn void pwm_clear_registers(int module_number)
 * @brief Function to clear all registers in a specific pwm module
 * @details This function will be called to clear all registers in a specific pwm module
 * @param int module_number- specifies the pwm module to be selected
 */
ಶೂನ್ಯ pwm_clear_registers(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ)
{
	ಗಣ_pwm_period_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, 0);
	ಗಣ_pwm_duty_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, 0);
	ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, 0);
	ಗಣ_pwm_clock_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, 0);

	log_info("\n All registers of module number %d cleared", module_ಸಂಖ್ಯೆ);
}

/** @fn void pwm_init
 * @brief Function to initialize all pwm modules
 * @details This function will be called to initialize all pwm modules
 */
ಶೂನ್ಯ pwm_init(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;

	ಗಾಗಿ (i = 0; i < 5; i++) {
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
ಪೂರ್ಣಾಂಕ configure_control_ರಿಜಿಸ್ಟರ್_ಬಹುಲಕ(ಪೂರ್ಣಾಂಕ ಬಹುಲಕ)
{
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 0x0;

	ಆದರೆ (ಬಹುಲಕ == 0) {
		log_info("\n Current Module is set to PWM mode");

		ಮೌಲ್ಯ += PWM_ENABLE;
		ಮೌಲ್ಯ += PWM_ಆರಂಭ;
		ಮೌಲ್ಯ += PWM_OUTPUT_ENABLE;
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಬಹುಲಕ == 1) {
		log_info("\n Current Module is set to timer once only mode");

		ಮೌಲ್ಯ += PWM_ಆರಂಭ;
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(ಬಹುಲಕ == 2) {
		log_info("\n Current Module is set to timer continuous mode");

		ಮೌಲ್ಯ += PWM_ಆರಂಭ;
		ಮೌಲ್ಯ += CONTINUOUS_ONCE;
	}

	ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
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
ಶೂನ್ಯ pwm_ಆರಂಭ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಬಹುಲಕ)
{
	ಪೂರ್ಣಾಂಕ control = configure_control_ರಿಜಿಸ್ಟರ್_ಬಹುಲಕ(ಬಹುಲಕ);

	ಆದರೆ(ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, control))
	{
		log_info("\n PWM module number %d has been entered", module_ಸಂಖ್ಯೆ);
	}

	ಆದರೆ(!ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, control))
	{
		log_error("\n PWM module number %d not entered",module_ಸಂಖ್ಯೆ);
	}
}

/** @fn void pwm_use_external_clock(int module_number, bool value)
 * @brief Function to set use of external clock
 * @details This function will set clock to external clock if set to true
 * @param int (module_number-  the pwm module to be selected )
 * @param int (value -true or 1  - External Clock 
 *                    false or 0 - Internal Clock )
 */
ಶೂನ್ಯ pwm_use_external_clock(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, bool ಮೌಲ್ಯ)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ* control_ಮೌಲ್ಯ;
	control_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ * PWM_MODULE_ಸ್ಥಾನಾಂತರ + CONTROL_ರಿಜಿಸ್ಟರ್;
	ಆದರೆ(ಮೌಲ್ಯ == 1)
	control_ಮೌಲ್ಯ += CLOCK_SELECTOR;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(control_ಮೌಲ್ಯ && CLOCK_SELECTOR)
	control_ಮೌಲ್ಯ -= CLOCK_SELECTOR;	
}

/** @fn void pwm_set_clock(int module_number, int clock_divisor) 
 * @brief Function to set the clock divisor value of a specific pwm module
 * @details This function will set the clock divisor value of a specific pwm module
 * @param int module_number-  the pwm module to be selected
              int clock_divisor- value of clock divisor to be used to divide base clock speed of 50MHz.
 */
ಶೂನ್ಯ pwm_ಗಣ_clock(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ clock_ಭಾಜಕ)
{
	ಆದರೆ (ಗಣ_pwm_clock_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, clock_ಭಾಜಕ) == 0)
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
ಶೂನ್ಯ pwm_ಗಣ_duty_ಚಕ್ರ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ duty)
{
	ಆದರೆ (ಗಣ_pwm_duty_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, duty) == 0) {
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
ಶೂನ್ಯ pwm_ಗಣ_periodic_ಚಕ್ರ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ period)
{
	ಆದರೆ(ಗಣ_pwm_period_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, period) == 0) {
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
ಶೂನ್ಯ pwm_configure(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ,ಪೂರ್ಣಾಂಕ clock_ಭಾಜಕ, ಪೂರ್ಣಾಂಕ period, ಪೂರ್ಣಾಂಕ duty, bool external_clock)
{
	pwm_ಗಣ_periodic_ಚಕ್ರ(module_ಸಂಖ್ಯೆ, period);
	pwm_ಗಣ_duty_ಚಕ್ರ(module_ಸಂಖ್ಯೆ, duty);
	pwm_ಗಣ_clock(module_ಸಂಖ್ಯೆ, clock_ಭಾಜಕ);
	pwm_use_external_clock(module_ಸಂಖ್ಯೆ, external_clock);
	log_info("\nPWM %d succesfully configured",module_ಸಂಖ್ಯೆ);
}

/** @fn void pwm_stop(int module_number)
 * @brief Function to stop a specific pwm module
 * @details This function will stop a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
ಶೂನ್ಯ pwm_stop(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ)
{
	ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(module_ಸಂಖ್ಯೆ, 0x0);
	log_info("\n PWM module number %d has been stopped", module_ಸಂಖ್ಯೆ);
}

/** @fn void show_register_values(int module_number)
 * @brief Function to print the values of all the registers of a specific pwm module
 * @details This function will print the values of all the registers of a specific pwm module
 * @param int module_number-  the pwm module to be selected
 */
ಶೂನ್ಯ show_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯಗಳು(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ)
{
	ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ* period_ಮೌಲ್ಯ;
	ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ* duty_ಮೌಲ್ಯ;
	ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*  control_ಮೌಲ್ಯ;
	ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ* clock_ಮೌಲ್ಯ;

	period_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ * PWM_MODULE_ಸ್ಥಾನಾಂತರ + PERIOD_ರಿಜಿಸ್ಟರ್;
	duty_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ * PWM_MODULE_ಸ್ಥಾನಾಂತರ + DUTY_ರಿಜಿಸ್ಟರ್;
	control_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ * PWM_MODULE_ಸ್ಥಾನಾಂತರ + CONTROL_ರಿಜಿಸ್ಟರ್;
	clock_ಮೌಲ್ಯ = PWM_ತಳ_ವಿಳಾಸ + module_ಸಂಖ್ಯೆ * PWM_MODULE_ಸ್ಥಾನಾಂತರ + CLOCK_ರಿಜಿಸ್ಟರ್;

	log_info("\nThe value of period register is %x",  *period_ಮೌಲ್ಯ);
	log_info("\nThe value of duty register is %x",    *duty_ಮೌಲ್ಯ);
	log_info("\nThe value of control register is %x", *control_ಮೌಲ್ಯ);
	log_info("\nThe value of clock register is %x",   *clock_ಮೌಲ್ಯ);
}

