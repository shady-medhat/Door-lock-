/*
 * UART.h
 *
 *  Created on: Nov 2, 2023
 *      Author: shady
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

#define UART_BaudRate uint32 /*macro used to define Baud rate as uint32*/
/*enumaration for bit data mode*/
typedef enum
{
	Five_bit,Six_bit,Seven_bit,Eight_bit,Nine_bit
}UART_BitData;
/*enumaration for Parity mode*/
typedef enum
{
	Disabled,Even=2,Odd=3
} UART_Parity;
/*enumaration for how many stop bits*/
typedef enum
{
	One_bit,Two_bit
}UART_StopBit;
/*structure caring configrable variables*/
typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #


#endif /* UART_H_ */
