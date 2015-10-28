/*
 * bluetoothIO2.h
 *
 *  Created on: 27 paź 2015
 *      Author: akowalew
 */

#ifndef BLUETOOTHIO2_H_
#define BLUETOOTHIO2_H_

#include <avr/io.h>
#include "USART/usart.h"
#include <avr/pgmspace.h>

#define CONST_STRLEN(s)	((sizeof((s)) / sizeof(char)) - 1)

const uint8_t SZ_PTRVAR = 4 ;
void (* const printStringFunction)(const char*) = Usart::sendLine ;
void (* const printStringPFunction)(const char*) = Usart::sendLineP ;
volatile uint8_t * const ptrVariables[SZ_PTRVAR] =
{
		&OCR0A,
		&OCR0B,
		&OCR2A,
		&OCR2B
};

const char SEE_TEXT[]  PROGMEM =	"Oto opis wystepujacych zmiennych:\n"
									"0 : OCR0A\n"
									"1 : OCR0B\n"
									"2 : OCR2A\n"
									"3 : OCR2B" ;

const char RESET_TEXT[] PROGMEM = 	"Nastapi zresetowanie robota do poczatku..." ;

const char HELLO[] PROGMEM = "Witaj! To obsluga robota ROB!" ;
const char ID[]  = "ROB" ;
const char ID_OK[]  = "ROB:OK" ;
const char ID_OK_READ[]  = "ROB:OK:" ;
const char READ = '>' ;
const char WRITE = '<' ;
const char OPT = ':' ;

uint8_t myAtoi(volatile uint8_t *u8Dest, const char *src) ;
void myItoa(uint8_t var, char *dest) ;
void sendVar(uint8_t whichVar) ;

void funkcjaOpcji(const char *str) ;
void funkcjaOdczytu(const char *str) ;
void funkcjaZapisu(const char *str) ;

#endif /* BLUETOOTHIO2_H_ */
