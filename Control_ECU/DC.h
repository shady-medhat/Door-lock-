/*
 * DC.h
 *
 *  Created on: Oct 14, 2023
 *      Author: shady
 */

#ifndef DC_H_
#define DC_H_
#include "std_types.h"

/*******************************************************************************
 *                                Declaration                                *
 *******************************************************************************/
// enumaration for motor state
typedef enum
{
	Stop,Anti_Clockwise,Clockwise
}DcMotor_State;
/*******************************************************************************
 *                                Definition                                *
 *******************************************************************************/
#define INPUT_PORT    PORTB_ID
#define INPUT_PIN1    PIN0_ID
#define INPUT_PIN2    PIN1_ID
#define NO_OF_STEPS   256
#define MAXIMUM_SPEED  100
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by PWM module */

extern volatile uint8 duty_cycle;
/* Declaration for DC initialization function */
void DcMotor_Init(void);
/* Declaration for DC operation function */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_H_ */
