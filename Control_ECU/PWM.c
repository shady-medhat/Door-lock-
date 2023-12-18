/*
 * PWM.c
 *
 *  Created on: Oct 14, 2023
 *      Author: shady
 */
#include "DC.h"
#include "avr/io.h"
#include "PWM.h"
#include "gpio.h"
/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Function for initializing the PWM mode on Timer 0
 */
void PWM_Timer0_init(void)
{
	TCNT0 = 0; //Set Timer Initial value
	GPIO_writePin( OUTPUT_PORT,OUTPUT_PIN, LOGIC_HIGH); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	/* Configure timer control register
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01);
}
void PWM_Timer0_Start(uint8 duty_cycle)
{
#if((duty_cycle < 0) && (duty_cycle > 100))

#error "duty is not correct"

#endif


	OCR0  =duty_cycle; /* Set Compare Value */


	/* clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 |= (1<<CS01);
}
