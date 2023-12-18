/*
 * Buzzer.c
 *
 *  Created on: Oct 29, 2023
 *      Author: shady
 */

#include "gpio.h"
#include "Buzzer.h"
// function for initiating the buzzer
void Buzzer_init(){
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID, PIN_OUTPUT); /*setting PC5 as an output*/
	 GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID, LOGIC_LOW );/*putting 0 initially on Buzzer pin*/
}
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID, LOGIC_HIGH );/*setting buzzer*/
}
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID, LOGIC_LOW ); /*clearing buzzer*/
}

