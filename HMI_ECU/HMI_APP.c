/************************************************************************************************************
 *                                                                                                          *
 * Module: HUMAN MACHINE INTERFACE                                                                          *
 *                                                                                                          *
 * File Name: HMI_ECU.c                                                                                     *
 *                                                                                                          *
 *
 *                                                                                                          *
 * Author: Shady Medhat                                                                                      *
 *                                                                                                          *
 ************************************************************************************************************/


#include "keypad.h"
#include "uart.h"
#include "lcd.h"
#include <util/delay.h>
#include "timer1.h"
#include <avr/io.h>

#define MC2_READY 0x10
#define PASSWORD_LENGTH 5
#define identical 1
#define Not_identical 0
#define open_motor  1
#define change_Password  0
#define Buzzer 1
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* global variable contain the ticks count of the timer */

uint8 g_tick;
uint8 pass[PASSWORD_LENGTH],pass_2[PASSWORD_LENGTH];
/* global variable contain the received byte by UART from CONTROL_ECU */
uint8 receive = 0;

/*******************************************************************************
 *                     Functions Definitions                                   *
 *******************************************************************************/

/* Description:
 * take the password from the user
 * send it to CONTROL_ECU to check on it
 */
/*Function used to take 2 passwords from user and send to other ECU to initialize the password and save in EEPROM*/
void Initializing_pass(){
	uint8 key;
	LCD_clearScreen();/* clear LCD */
	LCD_displayStringRowColumn(0, 0, "Plz enter pass:"); /*display please enter pass*/

	for (uint8 i = 0; i < 5; i++){
		pass[i] = KEYPAD_getPressedKey();
		LCD_moveCursor(1, i);
		LCD_displayCharacter('*');
		_delay_ms(200); /* Press time */
	} /*take password from user and put in array*/
	key = KEYPAD_getPressedKey();
	if(key == '='){; /* make '=' as an Enter button */
    for (uint8 i = 0; i < 5; i++){
			   while(UART_recieveByte()!= MC2_READY){}
			   UART_sendByte(pass[i]);
			   _delay_ms(200);
}}/*send first password to another ECU*/

	LCD_clearScreen();/* clear LCD */
	LCD_displayStringRowColumn(0, 0, "Plz re-enter the");/*display please re enter function*/
	LCD_displayStringRowColumn(1, 0, "Same Pass:");
	LCD_moveCursor(1, 11);

	for (uint8 i = 0; i < 5; i++){
		pass_2[i] = KEYPAD_getPressedKey();

		LCD_displayCharacter('*'); /* display the pressed keypad switch as '*' */

		_delay_ms(500); /* Press time */
		}/*take the check password from user and put in array*/
	key = KEYPAD_getPressedKey();
	while(key != '='){}; /* make '=' as an Enter button */

			   for (uint8 i = 0; i < 5; i++){
				   while(UART_recieveByte()!= MC2_READY){}
				   UART_sendByte(pass_2[i]);
				   _delay_ms(200);
			   }/*send first password to another ECU*/

	receive = UART_recieveByte(); /*receive byte identifying whether they are identical or not */
	_delay_ms(500);
	if(receive == Not_identical)
	{
		Initializing_pass();
	}/*if not identical repeat function again*/

}
/*call back function that increments the g_tick every time the timer matches the compare value*/
void TIMER1_ticks()
{
	g_tick++;
}
/*Function used to operate the motor */
void LCD_Operation(){

	    g_tick = 0;/*Initiallizing g tick value to start counting*/
	    /* operating motor for 15 seconds CW*/
		if(g_tick == 5)
		{

			LCD_clearScreen();/*Clearing LCD*/
			LCD_displayStringRowColumn(0, 0, "Hold");/*Displaying Hold for 3 seconds*/

		}
		else if(g_tick == 6)
		{

			LCD_clearScreen();/*Clearing LCD*/
			LCD_displayStringRowColumn(0, 0, "Door is Locking");/*Displaying Door is Locking for 15 seconds*/

		}
		else if(g_tick == 11)
		{
			LCD_clearScreen();/*Clearing LCD*/
		    g_tick = 0;/*Initializing g_tick value to start counting*/
		}
}
/*function used to take password using keypad and send it to the other ECU*/
void PASS(void)
{
	uint8 key;
	LCD_clearScreen();/*Clearing LCD*/
	LCD_displayStringRowColumn(0, 0, "Plz enter pass:");/*Displaying please enter password*/

	for (uint8 i = 0; i < 5; i++){

		pass[i] = KEYPAD_getPressedKey();
		LCD_moveCursor(1, i);
		LCD_displayCharacter('*'); /* display the pressed keypad switch as '*' */

		_delay_ms(500); /* Press time */
	}
	key = KEYPAD_getPressedKey();
	while(key != '='){}; /* make '=' as an Enter button */

		   for (uint8 i = 0; i < 5; i++){
			   while(UART_recieveByte()!= MC2_READY){}
			   UART_sendByte(pass[i]);
			   _delay_ms(200);

		   }// send password to the other ECU

	receive = UART_recieveByte();/*receiving if password correct or not*/
	_delay_ms(500);

}
/*Function responsible for operating and managing the whole module */
void Motor_Change_operations(){
	uint8 k;/*variable to hold the key pressed */
	/*Displaying the main menu */
	LCD_displayStringRowColumn(0, 0, "+ : Open Door");
	LCD_displayStringRowColumn(0, 13, "   ");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	LCD_displayStringRowColumn(1, 15, "  ");
	k = KEYPAD_getPressedKey();
	if (k == '+'){
	   PASS();/*call the pass function to send password and check if correct*/
	   if(receive == identical)
		{
		   while(UART_recieveByte()!= MC2_READY){}/*wait until other ECU is ready to receive */
		   UART_sendByte(open_motor); /*send operation needed to be done */
		   _delay_ms(500);
		   LCD_clearScreen();
		   LCD_displayStringRowColumn(0, 0, "Door is");/*Display Door is unlocking for 15 seconds*/
		   LCD_displayStringRowColumn(1, 0, "Unlocking");
		   LCD_Operation(); /*call function responsible for doing the display operation*/
		}
	   /*taking password again to check if identical*/
	   else if(receive == Not_identical)
			{

		   PASS();/*call the pass function to send password and check if correct*/
		   if(receive == identical)
		   		{
		   		   while(UART_recieveByte()!= MC2_READY){}
		   		   UART_sendByte(open_motor);
		   		   _delay_ms(500);
		   		   LCD_clearScreen();
		   		   LCD_displayStringRowColumn(0, 0, "Door is");/*Display Door is unlocking for 15 seconds*/
		   		   LCD_displayStringRowColumn(1, 0, "Unlocking");
		   		   LCD_Operation();/*call function responsible for doing the display operation*/


			}
		   /*taking password again to check if identical*/
		   else if(receive == Not_identical){
			   PASS();/*call the pass function to send password and check if correct*/
			   if(receive == identical)
			    {
				   while(UART_recieveByte()!= MC2_READY){}
				   UART_sendByte(open_motor);
				   _delay_ms(500);
				   LCD_clearScreen();
				   LCD_displayStringRowColumn(0, 0, "Door is");/*Display Door is unlocking for 15 seconds*/
				   LCD_displayStringRowColumn(1, 0, "Unlocking");
				   LCD_Operation();/*call function responsible for doing the display operation*/

		   }
			   /*After giving 2 chances to get the correct password hold the system for 1 minute*/
			   else if(receive == Not_identical){
				   UART_sendByte(Buzzer); /* send Buzzer to the other ECU */
				   	LCD_clearScreen();
				   	LCD_displayString("ERROR!!!!");/*Display Error*/
				   	_delay_ms(60000); // wait a minute
				   	LCD_clearScreen();/*clear LCD*/
				   	Motor_Change_operations(); /*Start function from start*/
				   }
			   }

			}

	}
	if (k == '-'){
		PASS();/*call the pass function to send password and check if correct*/
		if(receive == identical)
	    {
			while(UART_recieveByte()!= MC2_READY){}
			UART_sendByte(change_Password);
			_delay_ms(200);
			Initializing_pass();
	     } /*if identical passwords Change password*/
		/*taking password again to check if identical*/
		else if(receive == Not_identical)
	    {

			   PASS();/*call the pass function to send password and check if correct*/
			   if(receive == identical)
			   		{
				   while(UART_recieveByte()!= MC2_READY){}
				   UART_sendByte(change_Password);
				   _delay_ms(200);
				   Initializing_pass();


				}
			   /*taking password again to check if identical*/
			   else if(receive == Not_identical){
				   PASS();/*call the pass function to send password and check if correct*/
				   if(receive == identical)
				    {
					   while(UART_recieveByte()!= MC2_READY){}
					   UART_sendByte(change_Password);
					   _delay_ms(200);
					   Initializing_pass();

			   }
				   /*After giving 2 chances to get the correct password hold the system for 1 minute*/
				   else if(receive == Not_identical){
					   UART_sendByte(Buzzer); /* send Buzzer to the other ECU */
					   	LCD_clearScreen();
					   	LCD_displayString("ERROR!!!!");/*Display Error*/
					   	_delay_ms(60000);
					   	LCD_clearScreen();/*clear LCD*/
					   	Motor_Change_operations();/*Start function from start*/
					   }
				   }

				}
		}

	}


int main(void){

	UART_ConfigType UART_Configuration={Eight_bit,Disabled,One_bit,9600}; /* configuring the UART as eight bit mode, disabled parity, One stop bit, and baud rate = 9600*/
	UART_init(&UART_Configuration); /*Initializing UART*/
	LCD_init();/*Initializing LCD*/
	Initializing_pass(); /*calling the initializing function to create password*/
	Timer1_ConfigType Configuration2={0,23438,F_CPU_1024,Compare_mode}; /* configuring Timer 1 as initial value = 0, compare value = 23438(3 seconds ), prescaler = 1024, and operate compare mode  */
	Timer1_init(&Configuration2);/*Initializing Timer 1*/
	Timer1_setCallBack(TIMER1_ticks); /*setting the call back function to increment the g_tick*/
	SREG |= (1<<7); /*Setting I_bit*/

	while (1)
	{
		Motor_Change_operations();
	}
}
