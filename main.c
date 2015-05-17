/*
 * main.c
 *
 * AEMQ Project - CU Robotics
 *
 * Who | Description of Changes ------------------------- | Date
 * cdh | Initial Revision: PWM Setup                      | 03/25/15
 *
 *
 */

#include "setup.h"
#include "driverlib/sysctl.h"
#include "motor_ctl.h"

// Global state to keep track of motor PWM state
pwm_t pwm_state;

int main(void)
{
	volatile int i = 0, j = 0;
	float spd = 0.30; // something between like 30% and 50%

	// Enable system clock at 80 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	// Initialize PWM module 0 and generators 0 and 1 to drive motors
	arm_motors();

	for(j = 0; j < 4; j++)
	{
		spd += 0.01;
		// delay approx. 1 sec
		for(i = 0; i < 1000000; i++);
		set_motor_speed(FRONT_LEFT, spd);
		set_motor_speed(FRONT_RIGHT, spd);
	}

	while(1)
	{
		// delay approx. 1 sec
		for(i = 0; i < 10000000; i++);

		spd = 0.30;
		set_motor_speed(FRONT_LEFT, spd);
		set_motor_speed(FRONT_RIGHT, spd);

		// delay approx. 1 sec
		for(i = 0; i < 10000000; i++);

		spd = 0.36;
		set_motor_speed(FRONT_LEFT, spd);
		set_motor_speed(FRONT_RIGHT, spd);

	}

}
