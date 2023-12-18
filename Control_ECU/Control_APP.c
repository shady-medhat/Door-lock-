/*
 * Control_APP.c
 *
 *  Created on: Nov 4, 2023
 *      Author: shady Medhat
 */
#include <util/delay.h> /* For the delay functions */
#include "UART.h"
#include "Timer1.h"
#include <avr/io.h>
#include "twi.h"
#include "DC.h"
#include "PWM.h"
#include "Buzzer.h"
#include "external_eeprom.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MC2_READY 0x10    /*  MC2_READY byte to tell other MCU that i am ready */
#define PASSWORD_LENGTH 5 /* Password length */
#define identical 1
#define Not_identical 0
#define open_motor  1
#define change_Password  0
#define Buzzer   1

uint16 *ADDRESS; /*pointer to location in the EEPROM */
uint8 g_tick; /*incrementing variable used to use Timer 1 as a delay*/
uint8 pass[PASSWORD_LENGTH],pass_2[PASSWORD_LENGTH];/*2 arrays to hold passwords all over the Module*/
uint8_t receive; /*variable used to recieve Needed operation from the other MCU*/

/*Function used to check if 2 password given equal or not*/
uint8 check_Identical(uint8_t* array1, uint8_t* array2, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (array1[i] != array2[i]) {
            return 0; // Arrays are not identical
        }
    }
    return 1; // Arrays are identical
}
/*Function used to initialize the password and save in EEPROM*/
void Initiating_Passwords()
{
	uint8 Identical;/* variable to hold value after checking identicality*/


	for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
        UART_sendByte(MC2_READY);
        _delay_ms(200); /*delay for communication to be done effiecently*/
		pass[i]=UART_recieveByte();
		_delay_ms(200); /*delay to give time for recieving data*/
	} /*receiving the first password in an array*/

	for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
         UART_sendByte(MC2_READY);
         _delay_ms(200); /*delay for communication to be done effiecently*/
		 pass_2[i]=UART_recieveByte();
		 _delay_ms(200); /*delay to give time for receiving data*/
	}/*receiving the first password in an array*/
	Identical= check_Identical(pass,pass_2, PASSWORD_LENGTH);/* Checking if identical or not*/
	if (Identical){

		UART_sendByte(identical); /*send to other ECU that 2 passwords identical  */
		for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
			EEPROM_writeByte((0x01) + i, pass[i]);
			_delay_ms(200);
	} /*writing in the EEPRM The password*/
	}
	else{
		UART_sendByte(Not_identical);}/*send to other ECU that 2 passwords not identical  */
	}
/*call back function that increments the g_tick every time the timer matches the compare value*/
void TIMER1_ticks()
{
	g_tick++;
}
/*Function used to operate the motor */
void motor_operation(void)
{
    g_tick= 0; /*Initiallizing g tick value to start counting*/




	if(g_tick == 5)  /* operating motor for 15 seconds CW*/
	{

		DcMotor_Rotate(Stop,0); /* stop motor*/
		PWM_Timer0_Start(duty_cycle); /* operating PWM*/

	}
	else if(g_tick == 6)
	{

		DcMotor_Rotate(Anti_Clockwise,100); /* operating motor ACW*/
		PWM_Timer0_Start(duty_cycle); /* operating PWM*/

	}
	else if(g_tick == 11) /* operating motor for 15 seconds ACW*/
	{

		DcMotor_Rotate(Stop,0);  /* stop motor*/
		g_tick = 0; /*Initializing g_tick value to start counting*/

	}
}
/*Function used to choose between the two options */
void Open_Or_Change_operation(uint8 receive){

		if (receive == open_motor)
			     {
				  DcMotor_Rotate(Clockwise,100);/*rotating motor full speed CW*/
				  PWM_Timer0_Start(duty_cycle); /* operating PWM*/
				  motor_operation(); /*calling operating motor function*/
			     }
		else if (receive == change_Password) {

				 Initiating_Passwords();/* calling the function responsible for creating new password */
				 }
	}

/*Function responsible for operating and managing the whole module */
void Option_Processing(){
uint8 Identical; /* variable to hold value after checking identicality*/
uint8 val; /* variable to hold values of password from EEPROM*/


for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
    UART_sendByte(MC2_READY);
    _delay_ms(200); /*delay for communication to be done effiecently*/
	pass[i]=UART_recieveByte();
	_delay_ms(200); /*delay to give time for recieving data*/
} /*receiving the sent password in an array*/

for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
	        EEPROM_readByte((0x01) + i,&val);
	        _delay_ms(200);
		    pass_2[i] = val;} /* getting the password from EEPROM to compare it with given pass*/

Identical= check_Identical(pass,pass_2, PASSWORD_LENGTH); /* Checking if identical or not*/
if (Identical){
		UART_sendByte(identical);/* send identical to other ECU*/
		_delay_ms(200); /*delay between 2 sending for the receiver to take time to receive efficiently*/
		UART_sendByte(MC2_READY); /* send ready Byte*/
        receive = UART_recieveByte(); /* Receive the operation option for the ECU to work on */
         _delay_ms(200);
	     Open_Or_Change_operation(receive); /* Calling the operation function with input the operation needed*/
	}
else{

	UART_sendByte(Not_identical); /*send not identical because passwords do not match*/
	/*taking password again to check if identical*/
	for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
        UART_sendByte(MC2_READY);
        _delay_ms(200); /*delay for communication to be done effiecently*/
		pass[i]=UART_recieveByte();
		_delay_ms(200); /*delay to give time for recieving data*/
	} /*receiving the first password in an array*/

	Identical= check_Identical(pass,pass_2, PASSWORD_LENGTH); /* Checking if identical or not*/
	if (Identical){
			UART_sendByte(identical);/* send identical to other ECU*/
			_delay_ms(200); /*delay between 2 sending for the receiver to take time to receive efficiently*/
			UART_sendByte(MC2_READY); /* send ready Byte*/
	        receive = UART_recieveByte(); /* Receive the operation option for the ECU to work on */
	         _delay_ms(200);
		     Open_Or_Change_operation(receive); /* Calling the operation function with input the operation needed*/
		}
	else {

		  UART_sendByte(Not_identical); /*send not identical because passwords do not match*/
		  /*taking password again to check if identical*/
          for (uint8_t i = 0; i < PASSWORD_LENGTH; i++) {
                    UART_sendByte(MC2_READY);
                    _delay_ms(200); /*delay for communication to be done effiecently*/
            		pass[i]=UART_recieveByte();
            		_delay_ms(200); /*delay to give time for receiving data*/
            	} /*receiving the first password in an array*/
         Identical= check_Identical(pass,pass_2, PASSWORD_LENGTH);/* Checking if identical or not*/
         if (Identical){
         		UART_sendByte(identical);/* send identical to other ECU*/
         		_delay_ms(200); /*delay between 2 sending for the receiver to take time to receive efficiently*/
         		UART_sendByte(MC2_READY); /* send ready Byte*/
                 receive = UART_recieveByte(); /* Receive the operation option for the ECU to work on */
                  _delay_ms(200);
         	     Open_Or_Change_operation(receive); /* Calling the operation function with input the operation needed*/
         	} /*After giving 2 chances to get the correct password hold the system for 1 minute*/
         else {
        	        UART_sendByte(Not_identical);/*send not identical because passwords do not match*/
        	        _delay_ms(200);/*delay between 2 sending for the receiver to take time to receive efficiently*/
                    UART_sendByte(MC2_READY);
                    _delay_ms(200);/*delay to give the receiver time to receive and send*/
                    receive = UART_recieveByte(); /*receive byte*/
                    if (receive == Buzzer){
                    Buzzer_on();
		           _delay_ms(60000);
		           Buzzer_off();
		           Option_Processing();} /*initiate Buzzer for one minute then close it and start function again from start*/
               }


		 }
	}

	}

int main(void){
	TWI_ConfigType TWI_Configuration={0x01,400000}; /* Bit Rate: 400.000 and address 0x01*/
	TWI_init(&TWI_Configuration); /*Initializing I2C*/
	UART_ConfigType UART_Configuration={Eight_bit,Disabled,One_bit,9600}; /* configuring the UART as eight bit mode, disabled parity, One stop bit, and baud rate = 9600*/
	UART_init(&UART_Configuration); /*Initializing UART*/
	PWM_Timer0_init();/* Initializing PWM Timer0 */
	DcMotor_Init(); /*Initializing DC Motor*/
	Buzzer_init(); /*Initializing Buzzer*/
	Initiating_Passwords(); /*calling the initializing function to create password*/
	Timer1_ConfigType Configuration2={0,23438,F_CPU_1024,Compare_mode};/* configuring Timer 1 as initial value = 0, compare value = 23438(3 seconds ), prescaler = 1024, and operate compare mode  */
	Timer1_init(&Configuration2); /*Initializing Timer 1*/
	Timer1_setCallBack(TIMER1_ticks); /*setting the call back function to increment the g_tick*/
	SREG |= (1<<7); /*Setting I_bit*/

	while (1)
	{
		Option_Processing();
	}
}



