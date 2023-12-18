/*
 * DC.c
 *
 *  Created on: Oct 14, 2023
 *      Author: shady
 */
#include "gpio.h"
#include "DC.h"
/*global variable holding the duty cycle value and volatile because it can be changed in run time by hard ware */
volatile uint8 duty_cycle;
/* funtion responsible to initialize DC driver*/
void DcMotor_Init(void){
/*setting directions of input pins to the DC and initializing them with 0 */
	 GPIO_setupPinDirection( INPUT_PORT,  INPUT_PIN1, PIN_OUTPUT);
	 GPIO_setupPinDirection( INPUT_PORT,  INPUT_PIN2, PIN_OUTPUT);
	 GPIO_writePin(INPUT_PORT,INPUT_PIN1, Stop);
	 GPIO_writePin(INPUT_PORT,INPUT_PIN2, Stop);

}
/*setting the purpose of the DC and getting its operation*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* nested if to write on port the suitable binary according to the state */
if(state == Clockwise)
	GPIO_writePort(INPUT_PORT,Clockwise);
else if(state == Anti_Clockwise)
	GPIO_writePort(INPUT_PORT,Anti_Clockwise);
else if(state == Stop)
	 GPIO_writePort(INPUT_PORT, Stop);


#if((speed < 0) && (speed > 100))

#error "Speed not valid"

#endif

duty_cycle= (speed/MAXIMUM_SPEED)*NO_OF_STEPS ; /* calculating the duty cycle value to be used by PWM and application file*/


}
