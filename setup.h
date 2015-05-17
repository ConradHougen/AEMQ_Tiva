/*
 * setup.h
 *
 * AEMQ Project - CU Robotics
 *
 * Who | Description of Changes ------------------------- | Date
 * cdh | Initial Revision                                 | 03/26/15
 */

#ifndef SETUP_H_
#define SETUP_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"

// Struct for maintaining motor pwm state
typedef struct __pwm_t
{
	uint32_t period;
	uint32_t deadband;
	uint32_t cycleFL; // front left
	uint32_t cycleFR; // front right
	uint32_t cycleRR; // rear right
	uint32_t cycleRL; // rear left
} pwm_t;

/*
 * Function: arm_motors
 * Arguments: None
 * Return: None
 *
 * Description: This function arms the motors by initializing pwm 0 generator
 * blocks 0 and 1.  The motor ESCs should be connected to the following pins:
 * Front Left Motor: PB5
 * Rear Left Motor: PB4
 * Front Right Motor: PH0
 * Rear Right Motor: PH1
 */
void arm_motors(void);

#endif /* SETUP_H_ */
