/*
 * encoders.cpp
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#include <avr/io.h>
#include "encoders.h"
#include <avr/interrupt.h>
#include "timeMeasure.h"


void initEncoders() {
	DDRD &= ~((1 << ENC0_A) | (1 << ENC0_B)) ;
	DDRB &= ~((1 << ENC2_A) | (1 << ENC2_B)) ;
}

uint8_t getEnc0A() {
	return PIND & (1 << ENC0_A) ;
}

uint8_t getEnc2A() {
	return PINB & (1 << ENC2_A) ;
}

