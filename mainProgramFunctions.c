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

static inline void setupLed() {
	DDRB |= (1 << LED_ONBRD) ;
}

void initButtons() {
	DDRD &= ~(1 << BTN1) ;
	PORTD |= (1 << BTN1) ; // włączenie rezystorów podciągających

	DDRB &= ~(1 << BTN2) ;
	PORTB |= (1 << BTN2) ;	// włączenie rezystorów podciągajacych
}

uint8_t isBtn1Pressed() {
	return !(PIND & (1 << BTN1)) ;
}

uint8_t isBtn2Pressed() {
	return !(PINB & (1 << BTN2)) ;
}

inline void turnOnLed() {
	PORTB |= (1 << LED_ONBRD) ;
}

inline void turnOffLed() {
	PORTB &= ~(1 << LED_ONBRD) ;
}

inline void turnSwitchLed() {
	PORTB ^= (1 << LED_ONBRD) ;
}


void initProgram() {
	//inicjacja pracy diody wbudowanej w płytkę
	setupLed() ;

	// inicjacja pracy silników
	motorsInit() ;
	motorsTurnOn0(1) ;
	motorsTurnOn2(1) ;

	// inicjacja enkoderów
	encodersInit() ;

	// inicjacja odmierzacza czasu
	timeMeasureInit(TICK_ONE_MILISECOND) ;

	// inicjacja przycisków
	initButtons() ;

	sei() ;
}

