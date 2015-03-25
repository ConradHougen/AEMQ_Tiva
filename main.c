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

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_hibernate.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/hibernate.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"

typedef struct __duty_t
{
	uint32_t period1;
	uint32_t cycle1;
	uint32_t period2;
	uint32_t cycle2;
	uint32_t period3;
	uint32_t cycle3;
	uint32_t period4;
	uint32_t cycle4;
} duty_t;

duty_t duty;

int main(void) {
	
	// Enable hardware floating point and allow in ISRs
	FPUEnable();
	FPUStackingEnable();

	// Enable system clock at 80 MHz using main oscillator
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	duty.period1 = SysCtlClockGet()/1000; // 1 kHz switching frequency
	duty.cycle1 = duty.period1 >> 1; // 50% duty cycle
	duty.period2 = duty.period1;
	duty.cycle2 = duty.cycle1;
	duty.period3 = duty.period1;
	duty.cycle3 = duty.cycle1;
	duty.period4 = duty.period1;
	duty.cycle4 = duty.cycle1;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enable control of PWM module 0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // Enable control of GPIO port B
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); // Enable control of GPIO port H

	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PH2_M0PWM2);
	GPIOPinConfigure(GPIO_PH3_M0PWM3);

	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTH_BASE, GPIO_PIN_2);
	GPIOPinTypePWM(GPIO_PORTH_BASE, GPIO_PIN_3);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
			PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN |
			PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN |
				PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN |
				PWM_GEN_MODE_NO_SYNC);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, duty.period1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty.cycle1);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, duty.period2);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty.cycle2);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_1);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, duty.period3);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty.cycle3);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_2);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, duty.period4);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty.cycle4);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_3);

	while(1)
	{
		// Loop forever, for now
	}

	return 0;
}
