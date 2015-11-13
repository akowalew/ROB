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
bool state ;

void initTimeMeasure(uint16_t elementaryTick) {
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
		stopTimeMeasuring() ;
}

void startTimeMeasuring(uint16_t timeToCount) {
	TCNT1 = 0 ;
	TIMSK1 |= (1 << TOV1) ; // włączenie przerwań cyklu 1milisekundowego

	timeInterval = timeToCount ;
	count = 0 ;

	state = true ;
}

uint16_t getTimeMeasure() {
	return count ;
}

bool getMeasuringState() {
	return state ;
}

void stopTimeMeasuring() {
	TIMSK1 &= ~(1 << TOV0) ;
	state = false ;
}

