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

EncoderResult readEncoder0() {
	// zliczanie obrotów enkodera działa następująco :

}

EncoderResult readEncoder2() {

	startTimeMeasuring(1000UL) ;
	uint16_t ticks = 0 ;
	uint8_t isticked = 0 ;
	while(1) {
		if(getMeasuringState() == 0)
			break ;

		if((PINB & (1 << PB1)) && !isticked) {
			ticks++ ;
			isticked = 1 ;
		}
		else if( (!(PINB & (1 << PB1))) && isticked)
			isticked = 0 ;
	}
	EncoderResult ret ;
	ret.ticks = ticks ;

	return ret ;
}

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

