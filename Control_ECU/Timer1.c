/*
 * Timer1.c
 *
 *  Created on: Nov 1, 2023
 *      Author: shady
 */

#include "Timer1.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include"gpio.h"
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/* Interrupt Service Routine for timer1 compare mode */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
	/* Call the Call Back function in the application */
			(*g_callBackPtr)();
		}
}

/* Interrupt Service Routine for timer1 compare mode */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
	/* Call the Call Back function in the application  */
			(*g_callBackPtr)();
		}
}
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCNT1 = (Config_Ptr->initial_value); /*Initializing The TCNT Register with the initial value*/

	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler); /*setting the prescaler */
	if ((Config_Ptr->mode)== Normal_mode )
	{
		TIMSK |= (1<<TOIE1);/*Enabling overflow interrupt*/
		TCCR1A = (1<<FOC1A) | (1<<FOC1B)  ; /*setting two registers in case of no PWM*/
	}
	else if ( (Config_Ptr->mode)== Compare_mode)
	{
		OCR1A = (Config_Ptr->compare_value); /* Set the compare value */
		TIMSK |= (1<<OCIE1A); /*Enabling compare mode interrupt*/
		TCCR1A = (1<<FOC1A)| (1<<FOC1B) ;/*setting two registers in case of no PWM*/
		TCCR1B |= (1<<WGM12);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
	}
}
void Timer1_deInit(void){
	/*clearing all registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
	TIMSK &= ~(1<<OCIE1A);
	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}
void Timer1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
		g_callBackPtr = a_ptr;
}



