/*
 * timeMeasure.cpp
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timeMeasure.h"

static uint16_t timeInterval = 0 ;
volatile uint16_t count = 0 ;
uint8_t state ;

void timeMeasureInit(uint16_t elementaryTick) {
	// ustawienie Timera1 w cykl 1milisekundowy

	// porty timera1 rozłączone
	// prescaler taki jak timera0, czyli ps = 1
	// Tryb FAST PWM 15
	// Overflow on TOP (OCR1A)
	// Cykl 1 ms (OCR1A = 15999)
	TCCR1A = (1 << WGM11) | (1 << WGM10) ;
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10) ;
	OCR1A = elementaryTick ;

	TIMSK1 &= ~(1 << TOV1) ; // na razie nie włączamy przerwań
}

ISR(TIMER1_OVF_vect) {
	// przerwanie przepełnienia timera1
	count++ ;
	if(count == timeInterval)
		timeMeasureStop() ;
}

void timeMeasureStart(uint16_t timeToCount) {
	TCNT1 = 0 ;
	TIMSK1 |= (1 << TOV1) ; // włączenie przerwań cyklu 1milisekundowego

	count = 0 ;
	timeInterval = timeToCount ;

	state = 1 ;
}

uint16_t timeMeasureGetTime() {
	return count ;
}

uint8_t timeMeasureGetState() {
	return state ;
}

void timeMeasureStop() {
	TIMSK1 &= ~(1 << TOV0) ;
	state = 0 ;
}

