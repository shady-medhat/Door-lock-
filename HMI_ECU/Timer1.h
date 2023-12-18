/*
 * Timer1.h
 *
 *  Created on: Nov 1, 2023
 *      Author: shady
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
/*enumaration for the prescaler*/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;

/*enumaration for the Timer mode*/
typedef enum
{
	Normal_mode,Compare_mode=4
}Timer1_Mode;
/*structure holding configuration variables*/
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr); /* function to initialize the Timer */
void Timer1_deInit(void); /* function to de-initialize the Timer */
void Timer1_setCallBack(void(*a_ptr)(void)); /*function to set call back function in a global pointer */


#endif /* TIMER1_H_ */
