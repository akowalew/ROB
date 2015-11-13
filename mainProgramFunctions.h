
#ifndef _MAINPROGRAMFUNCTIONS_H_
#define _MAINPROGRAMFUNCTIONS_H_

#include "motors.h"

extern const uint8_t NUMBER_OF_VARIABLES ;
extern volatile uint8_t * const ptrVariables[] ;

#define F_PWM 62500UL

#define LED_ONBRD	PB5
#define BTN1		PD7
#define BTN2		PB0

inline void turnOnLed() {
	PORTB |= (1 << LED_ONBRD) ;
}

inline void turnOffLed() {
	PORTB &= ~(1 << LED_ONBRD) ;
}

inline void turnSwitchLed() {
	PORTB ^= (1 << LED_ONBRD) ;
}

void initButtons() ;
uint8_t isBtn1Pressed() ;
uint8_t isBtn2Pressed()  ;

void initProgram() ;

#endif
