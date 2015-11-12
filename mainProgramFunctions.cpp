#include <avr/io.h>
#include "mainProgramFunctions.h"

volatile uint8_t programFlags ;

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

void initProgram() {
	initMotors() ;
	turnOn0(true) ;
	turnOn2(true) ;
}

