#include <avr/io.h>
#include <avr/interrupt.h>
#include "mainProgramFunctions.h"
#include "encoders.h"
#include "timeMeasure.h"

extern int8_t motor0Value  ;
extern int8_t motor2Value  ;

volatile uint8_t * const ptrVariables[] =
{
	&OCR0A,
	&OCR0B,
	&OCR2A,
	&OCR2B,
	(uint8_t *)&motor0Value,
	(uint8_t *)&motor2Value
};
const uint8_t NUMBER_OF_VARIABLES = sizeof(ptrVariables) / sizeof(volatile uint8_t * const) ;

inline void setupLed() {
	DDRB |= (1 << LED_ONBRD) ;
}

void initButtons() {
	DDRD &= ~(1 << BTN1) ;
	PORTD |= (1 << BTN1) ; // włączenie rezystorów podciągających

	DDRB &= ~(1 << BTN2) ;
	PORTB |= (1 << BTN2) ;	// włączenie rezystorów podciągajacych
}

bool isBtn1Pressed() {
	if(PIND & (1 << BTN1))
		return false ;
	else
		return true ;
}

bool isBtn2Pressed() {
	if(PINB & (1 << BTN2))
		return false ;
	else
		return true ;
}


void initProgram() {
	//inicjacja pracy diody wbudowanej w płytkę
	setupLed() ;

	// inicjacja pracy silników
	initMotors() ;
	turnOn0(true) ;
	turnOn2(true) ;

	// inicjacja enkoderów
	initEncoders() ;

	// inicjacja odmierzacza czasu
	initTimeMeasure(TICK_ONE_MILISECOND) ;

	// inicjacja przycisków
	initButtons() ;

	sei() ;
}

