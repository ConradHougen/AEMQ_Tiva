/*
 * motor_ctl.c
 *
 * AEMQ Project - CU Robotics
 *
 * Who | Description of Changes ------------------------- | Date
 * cdh | Initial Revision                                 | 04/17/15
 */

#include "motor_ctl.h"
#include "setup.h"
#include "driverlib/pwm.h"

extern pwm_t pwm_state;

/*
 * Function: set_motor_speed
 * Arguments: motor_e motor, float frac
 * Return: None
 *
 * Description: Updates the PWM signal going to motor such that the speed is frac of the maximum.
 */
void set_motor_speed(motor_e motor, float frac)
{
	// check that frac is between 0 and 1
	if(frac < 0.0 || frac > 1.0)
	{
		return;
	}

	// switch based on motor and update proper PWM signal
	switch(motor)
	{
		case FRONT_LEFT: // PB4
			pwm_state.cycleFL = pwm_state.period * frac;
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pwm_state.cycleFL);
			break;
		case FRONT_RIGHT: // PB5
			pwm_state.cycleFR = pwm_state.period * frac;
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, pwm_state.cycleFR);
			break;
		case REAR_RIGHT: // PH0
			pwm_state.cycleRR = pwm_state.period * frac;
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pwm_state.cycleRR);
			break;
		case REAR_LEFT: // PH1
			pwm_state.cycleRL = pwm_state.period * frac;
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pwm_state.cycleRL);
			break;
		default:
			break;
	}

	return;
}


