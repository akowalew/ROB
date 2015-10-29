/*
 * bluetoothIO2.cpp
 *
 *  Created on: 27 paź 2015
 *      Author: akowalew
 */

#include "bluetoothIO2.h"
#include "bluetoothIO.h"

#include <string.h>
#include "USART/usart.h"
#include <avr/interrupt.h>

uint8_t myAtoi(volatile uint8_t *u8Dest, const char *src)
{
	// zwraca ilość wczytanych znaków
	// wczytuje tylko liczbę 8bit, więc wczyta co najwyżej 3 cyfry

	uint8_t ret = 0 ;

	*u8Dest = 0 ;

	while(src[ret] >= '0' && src[ret] <= '9' && ret < 3)
		*u8Dest = ((*u8Dest) * 10) + (src[ret++] - '0') ;

	return ret ;
}

void myItoa(uint8_t var, char *dest)
{
	uint8_t i = 0 ;
	char tmp[3] ;

	if(var == 0)
	{
		dest[0] = '0' ;
		dest[1] = '\0' ;
		return ;
	}

	while(var)
	{
		tmp[i++] = (var % 10) + '0' ;
		var /= 10 ;
	}

	--i ;
	uint8_t j = i ;

	do
	{
		dest[j-i] = tmp[i] ;
	}while(i-- > 0) ;

	dest[j+1] = '\0' ;
}

void funkcjaOpcji(const char *str)
{
	if(strncmp(str, "SEE", 3) == 0)
	{
		printStringFunction(ID_OK) ;
		printStringPFunction(SEE_TEXT) ;
	}
	else if(strncmp(str, "RESET", 5) == 0)
	{
		printStringFunction(ID_OK) ;
		printStringPFunction(RESET_TEXT) ;
	}
}

void funkcjaOdczytu(const char *str)
{
	uint8_t ileWczytanych;
	uint8_t varNum ;

	ileWczytanych = myAtoi(&varNum, str) ;

	if(ileWczytanych > 0 && varNum < SZ_PTRVAR)
	{
		char num[4] ;

		printStringFunction(ID_OK) ;
		myItoa(*ptrVariables[varNum], num) ;
		printStringFunction(num) ;
	}
}

void funkcjaZapisu(const char *str)
{
	uint8_t varNum ;
	uint8_t ileWczytanych = myAtoi(&varNum, str) ;

	if(ileWczytanych > 0 && varNum < SZ_PTRVAR && str[ileWczytanych] == ':')
	{
		myAtoi(ptrVariables[varNum], str + ileWczytanych + 1) ;
		printStringFunction(ID_OK) ;
	}
}

