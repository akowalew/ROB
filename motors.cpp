/*
 * motors.cpp
 *
 *  Created on: 12 lis 2015
 *      Author: akowalew
 */
#include <avr/io.h>
#include "motors.h"

 int8_t motor0Value = 0 ;
 int8_t motor2Value = 0 ;

void turnMotors() {

	turnMotor0(motor0Value) ;
	turnMotor2(motor2Value) ;
}

void turnOn0(bool onOff)
{
#ifdef __AVR_ATmega328P__
	if(onOff)
		DDRD |= (1 << MOTOR0A) | (1 << MOTOR0B) ;
	else
		DDRD &= ~((1 << MOTOR0A) | (1 << MOTOR0B)) ;
#else

#endif
}

void turnOn2(bool onOff)
{
#ifdef __AVR_ATmega328P__
	if(onOff) {
		DDRB |= (1 << MOTOR2A) ;
		DDRD |= (1 << MOTOR2B) ;
	} else {
		DDRB &= ~(1 << MOTOR2A) ;
		DDRD &= ~(1 << MOTOR2B) ;
	}
#else

#endif
}

void turnMotor0(int8_t percent)
{
	if(percent >= 0) {
		setMod0A((uint8_t) percent) ;
		setMod0B(0) ;
	} else {
		setMod0A(0) ;
		setMod0B((uint8_t) -percent) ;
	}

	motor0Value = percent ;
}

void turnMotor2(int8_t percent)
{
	if(percent >= 0) {
		setMod2B((uint8_t) percent) ;
		setMod2A(0) ;
	} else {
		setMod2B(0) ;
		setMod2A ((uint8_t) -percent) ;
	}

	motor2Value = percent ;
}

void initMotors() {
	// Inicjacja silników w trybie FAST_PWM

	// Clear at OCR, set at Bottom
	TCCR0A |= (1 << COM0A1) ;
	TCCR0A |= (1 << COM0B1) ;

	// Top = 0xFF, TOV = 0xFF
	TCCR0A |= (1 << WGM01) | (1 << WGM00) ;

	// CLock prescaler = 1,
	// F_pwm = 16MHz / 256 / 1 = 62,5kHz
	TCCR0B |= (1 << CS00) ;

	TCCR2A |= (1 << COM2A1) ;
	TCCR2A |= (1 << COM2B1) ;
	TCCR2A |= (1 << WGM21) | (1 << WGM20) ;
	TCCR2B |= (1 << CS20) ;
}


