/*
 * setup.c
 *
 * AEMQ Project - CU Robotics
 *
 * Who | Description of Changes ------------------------- | Date
 * cdh | Initial Revision                                 | 03/26/15
 *
 */

#include "setup.h"
#include <stdint.h>

extern pwm_t pwm_state; // declared in main.c

/*
 * Function: arm_motors
 * Arguments: None
 * Return: None
 *
 * Description: This function arms the motors by initializing pwm 0 generator
 * blocks 0 and 1.  The motor ESCs should be connected to the following pins:
 * Front Left Motor: PB4
 * Front Right Motor: PB5
 * Rear Right Motor: PH0
 * Rear Left Motor: PH1
 */
void arm_motors(void)
{
	uint32_t pwm_freq = 300; // 300 Hz
	uint32_t pwm_div = 16; // If this value is modified, then must change the following line
	SysCtlPWMClockSet(SYSCTL_PWMDIV_16); // This line and the previous line are correlated

	pwm_state.period = SysCtlClockGet() / (pwm_freq * pwm_div);
	// Set speed (duty cycle) based on fraction of period
	pwm_state.cycleFL = pwm_state.period * 0; // 1% duty cycle default
	pwm_state.cycleFR = pwm_state.cycleFL;
	pwm_state.cycleRR = pwm_state.cycleFL;
	pwm_state.cycleRL = pwm_state.cycleFL;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enable control of PWM module 0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enable control of GPIO port B
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); // Enable control of GPIO port H

	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PH0_M0PWM0);
	GPIOPinConfigure(GPIO_PH1_M0PWM1);

	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTH_BASE, GPIO_PIN_0);
	GPIOPinTypePWM(GPIO_PORTH_BASE, GPIO_PIN_1);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN |
			PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN |
			PWM_GEN_MODE_NO_SYNC);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, pwm_state.period);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pwm_state.cycleFL);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, pwm_state.cycleFR);
	PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_1);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, pwm_state.period);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pwm_state.cycleRR);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pwm_state.cycleRL);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);

	return;
}


