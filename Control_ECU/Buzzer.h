/*
 * Buzzer.h
 *
 *  Created on: Oct 29, 2023
 *      Author: shady
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#define BUZZER_PORT_ID                 PORTC_ID
#define BUZZER_PIN_ID                  PIN5_ID
// Defining Buzzer functions
void Buzzer_init(); /*function to initialize Buzzer*/
void Buzzer_on(void); /*function setting buzzer*/
void Buzzer_off(void); /*function clearing buzzer*/



#endif /* BUZZER_H_ */
