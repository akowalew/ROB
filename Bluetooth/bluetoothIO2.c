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
#include "../UTILITY/utilityFunctions.h"
#include "../UTILITY/cycleBuffer.h"
#include "../mainProgramFunctions.h"


#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

extern CycleBuffer buffRx ;
extern CycleBuffer buffTx ;
//TODO inicjacja

extern volatile uint8_t bluetoothState ;

void checkRxBuffer() ;

void sendStringBt(const char *src)
{
	while(*src)
	{
		if(buffTx.full){
			udrIntEnable() ;
			while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
		}
		cycleBufferPush(&buffTx, *(src++)) ;
	}

	if(buffTx.full){
		udrIntEnable() ;
		while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
	}
	cycleBufferPush(&buffTx, 0) ;

	udrIntEnable() ;
}

void sendStringPBt(const char *srcP)
{
	uint8_t c ;

	while(1) {
		if(buffTx.full){
			udrIntEnable() ;
			while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
		}
	 	 if((c = pgm_read_byte(srcP++)))
	 		 cycleBufferPush(&buffTx, c) ;
	 	 else
	 		 break ;
	}

	if(buffTx.full){
		udrIntEnable() ;
		while(!buffTx.empty) ; // czekaj na zwolnienie zasobów
	}
	cycleBufferPush(&buffTx, 0) ;
	udrIntEnable() ;
}

void checkOptionMessage(const char *str)
{
	if(strcmp(str, "SEE") == 0)
	{
		sendStringBt(ID_OK) ;
		sendStringPBt(SEE_TEXT_P) ;
	}
	else if(strcmp(str, "RESET") == 0)
	{
		sendStringBt(ID_OK) ;
		sendStringPBt(RESET_TEXT_P) ;
	}
	else if(strcmp(str, "SETMOT") == 0) {
		sendStringBt(ID_OK) ;
		motorsTurnMotors() ;
	}
	else if(strcmp(str, "BRKMOT") == 0) {
		sendStringBt(ID_OK) ;
		motorsTurnMot0(0) ;
		motorsTurnMot2(0) ;
	}
}

void checkReadMessage(const char *str)
{
	uint8_t n;
	uint8_t varNum ;

	n = myAtoi(&varNum, str) ;

	if(n > 0 && varNum < NUMBER_OF_VARIABLES)
	{
		char num[4] ;

		sendStringBt(ID_OK) ;
		myItoa(*ptrVariables[varNum], num) ; // odczytujemy wartość z tablicy zmiennych
		sendStringBt(num) ;
	}
}

void checkWriteMessage(const char *str)
{
	uint8_t varNum ;
	uint8_t n = myAtoi(&varNum, str) ;

	if(n > 0 && varNum < NUMBER_OF_VARIABLES && str[n] == ':')
	{
		myAtoi(ptrVariables[varNum], str + n + 1) ; // zapisujemy wartość do tablicy zmiennych
		sendStringBt(ID_OK) ;
	}
}

ISR(USART_UDRE_vect)
{
	if(buffTx.empty)
		udrIntDisable() ;
	else
		cycleBufferPop(&buffTx, &UDR0) ;
}

ISR(USART_RX_vect)
{
	uint8_t c = UDR0 ;
	cycleBufferPush(&buffRx, c) ;
	checkRxBuffer() ;
}

void checkRxBuffer()
{
	if(buffRx.full)
		bluetoothState = READ_MSG_OVF ;
	if(buffRx.lastAdd == '\n') {
		bluetoothState = READ_MSG;
	}
}

