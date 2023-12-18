/*
 * PWM.h
 *
 *  Created on: Oct 14, 2023
 *      Author: shady
 */

#ifndef PWM_H_
#define PWM_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definition                                *
 *******************************************************************************/
#define OUTPUT_PORT    PORTB_ID /* PWM port */
#define OUTPUT_PIN    PIN3_ID  /* output pin */
/* Declaration for PWM initialization function */
void PWM_Timer0_init(void);
/* Declaration for PWM operation function */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
