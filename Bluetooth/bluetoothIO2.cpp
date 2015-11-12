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
#include "../motors.h"

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

CycleBuffer<volatile uint8_t, TX_BUFF_SZ> buffTx ;
CycleBuffer<volatile uint8_t, RX_BUFF_SZ> buffRx ;

void checkRxBuffer() ;

void sendStringBt(const char *src)
{
	while(*src)
	{
		if(buffTx.isFull()){
			Usart::udrIntEnable() ;
			while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
		}
		buffTx.push(*(src++)) ;
	}

	if(buffTx.isFull()){
		Usart::udrIntEnable() ;
		while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
	}
	buffTx.push(0) ;

	Usart::udrIntEnable() ;
}

void sendStringPBt(const char *srcP)
{
	uint8_t c ;

	while(1) {
		if(buffTx.isFull()){
			Usart::udrIntEnable() ;
			while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
		}
	 	 if((c = pgm_read_byte(srcP++)))
	 		 buffTx.push(c) ;
	 	 else
	 		 break ;
	}

	if(buffTx.isFull()){
		Usart::udrIntEnable() ;
		while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
	}
	buffTx.push(0) ;

	Usart::udrIntEnable() ;
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
		turnMotors() ;
	}
	else if(strcmp(str, "BRKMOT") == 0) {
		sendStringBt(ID_OK) ;
		turnMotor0(0) ;
		turnMotor2(0) ;
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
	if(buffTx.isEmpty())
		Usart::udrIntDisable() ;
	else
		buffTx.pop(&UDR0) ;
}

ISR(USART_RX_vect)
{
	uint8_t c = UDR0 ;
	buffRx.push(c) ;
	checkRxBuffer() ;
}

void checkRxBuffer()
{
	if(buffRx.isFull())
		setFlag(READ_MSG_OVF_FLAG) ;
	if(buffRx.seeLastAdded() == '\n') {
		setFlag(READ_MSG_FLAG) ;
	}
}

