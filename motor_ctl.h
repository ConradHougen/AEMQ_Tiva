/*
 * motor_ctl.h
 *
 * AEMQ Project - CU Robotics
 *
 * Who | Description of Changes ------------------------- | Date
 * cdh | Initial Revision                                 | 04/17/15
 */

#ifndef MOTOR_CTL_H_
#define MOTOR_CTL_H_

typedef enum
{
	FRONT_LEFT,   // PB4
	FRONT_RIGHT,  // PB5
	REAR_LEFT,    // PH0
	REAR_RIGHT    // PH1
} motor_e;

/*
 * Function: set_motor_speed
 * Arguments: motor_e motor, float frac
 * Return: None
 *
 * Description: Updates the PWM signal going to motor such that the speed is frac of the maximum.
 */
void set_motor_speed(motor_e motor, float frac);



#endif /* MOTOR_CTL_H_ */
