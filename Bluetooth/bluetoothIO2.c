/*
 * bluetoothIO2.cpp
 *
 *  Created on: 27 paź 2015
 *      Author: akowalew
 */

#include "bluetoothIO2.h"
#include "bluetoothIO.h"

#include <string.h>

#include "../UTILITY/USART/usart.h"
#include "../UTILITY/cycleBuffer.h"
#include "../mainProgramFunctions.h"


#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>


#include <stdlib.h>

extern CycleBuffer buffRx ;
extern CycleBuffer buffTx ;
//TODO inicjacja

extern volatile uint8_t bluetoothState ;

void btCheckRxBuffer() ;

void btSendString(const char *src)
{
	while(*src)
	{
		if(buffTx.full){
			usartUdrIntEnable() ;
			while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
		}
		cycleBufferPush(&buffTx, *(src++)) ;
	}

	if(buffTx.full){
		usartUdrIntEnable() ;
		while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
	}
	cycleBufferPush(&buffTx, 0) ;

	usartUdrIntEnable() ;
}

void btSendStringP(const char *srcP)
{
	uint8_t c ;

	while(1) {
		if(buffTx.full){
			usartUdrIntEnable() ;
			while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
		}
	 	 if((c = pgm_read_byte(srcP++)))
	 		 cycleBufferPush(&buffTx, c) ;
	 	 else
	 		 break ;
	}

	if(buffTx.full){
		usartUdrIntEnable() ;
		while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
	}
	cycleBufferPush(&buffTx, 0) ;
	usartUdrIntEnable() ;
}

void btCheckOptionMessage(const char *str)
{
	if(strcmp(str, "SEE") == 0)
	{
		btSendString(ID_OK) ;
		btSendStringP(SEE_TEXT_P) ;
	}
	else if(strcmp(str, "RESET") == 0)
	{
		btSendString(ID_OK) ;
		btSendStringP(RESET_TEXT_P) ;
	}
	else if(strcmp(str, "SETMOT") == 0) {
		btSendString(ID_OK) ;
		motorsTurnMotors() ;
	}
	else if(strcmp(str, "BRKMOT") == 0) {
		btSendString(ID_OK) ;
		motorsTurnMot0(0) ;
		motorsTurnMot2(0) ;
	}
}

void btCheckReadMessage(const char *str)
{
	uint8_t varNum ;
	char *pEnd ;

	varNum = strtol(str, &pEnd, 10) ;
	// varNum = atoi(str) ;

	if( ((pEnd - str) / sizeof(char)) > 0 && varNum < NUMBER_OF_VARIABLES)
	{
		char num[4] ;

		btSendString(ID_OK) ;
		itoa(*ptrVariables[varNum], num, 10) ; // odczytujemy wartość z tablicy zmiennych
		btSendString(num) ;
	}
}

void btCheckWriteMessage(const char *str)
{
// TODO: poprawić !!!
	char *pEnd ;
	uint8_t varNum = strtol(str, &pEnd, 10) ;
	uint8_t n = (pEnd - str) / sizeof(char) ;
	if( n > 0 && varNum < NUMBER_OF_VARIABLES && str[n] == ':')
	{
		//myAtoi(ptrVariables[varNum], str + n + 1) ; // zapisujemy wartość do tablicy zmiennych
		*ptrVariables[varNum] = strtol(str + n + 1, pEnd, 10) ;
		btSendString(ID_OK) ;
	}
}

ISR(USART_UDRE_vect)
{
	if(buffTx.empty)
		usartUdrIntDisable() ;
	else
		cycleBufferPop(&buffTx, &UDR0) ;
}

ISR(USART_RX_vect)
{
	uint8_t c = UDR0 ;
	cycleBufferPush(&buffRx, c) ;
	btCheckRxBuffer() ;
}

void btCheckRxBuffer()
{
	if(buffRx.full)
		bluetoothState = READ_MSG_OVF ;
	if(buffRx.lastAdd == '\n') {
		bluetoothState = READ_MSG;
	}
}

