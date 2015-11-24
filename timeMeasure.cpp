/*
 * timeMeasure.cpp
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timeMeasure.h"
#include "mainProgramFunctions.h"

<<<<<<< HEAD:timeMeasure.c
#include "UTILITY/USART/usart.h"
#include <stdlib.h>
=======
static uint16_t timeInterval = 0 ;
volatile uint16_t count = 0 ;
bool state ;
>>>>>>> parent of 6c2d23d... h:timeMeasure.cpp

volatile uint8_t mainTicks = 0 ;
volatile uint8_t baseTicks = 0 ;

CycleProcessStruct 	processArray[SZ_CYCLE_PROCESS] ;
volatile uint8_t 	lastStarts[SZ_CYCLE_PROCESS] ;

void initTimer() {
	// ustawienie Timera1 w cykl 2milisekundowy
	// porty timera1 rozłączone
	// prescaler taki jak timera0, czyli ps = 1
	// Tryb FAST PWM 15
	// Overflow on TOP (OCR1A)

	TCCR1A = (1 << WGM11) | (1 << WGM10) ;
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10) ;
	OCR1A = TICK_MAIN_VALUE ;

	CycleProcessStruct cp = {0, 0} ;
	for(uint8_t i = 0 ; i < SZ_CYCLE_PROCESS ; i++) {
		lastStarts[i] = 0 ;
		processArray[i] = cp ;
	}

	TIMSK1 &= ~(1 << TOV1) ; // na razie nie włączamy przerwań
}

void timeManager() {
	for(uint8_t i = 0 ; i < SZ_CYCLE_PROCESS ; i++) {
		if(processArray[i].ptrFun != 0) { // jeśli do tej pozycji jest podpięty proces
			if((uint8_t)(baseTicks - lastStarts[i]) >= processArray[i].period) { // cykl główny doliczył się, trzeba uruchomić proces
				lastStarts[i] = baseTicks ; // ustawiamy czas ostatniego uruchomienia(teraz)
				processArray[i].ptrFun() ; // odpalamy proces
			}
		}
	}
}

ISR(TIMER1_OVF_vect)
{
	// przerwanie przepełnienia timera1
	mainTicks++ ;
	if(mainTicks == TICK_BASE_VALUE) { // doliczyliśmy się cyklu głównego (np. 20MS)
		mainTicks = 0 ;
		// teraz trzeba wywołać zarządcę czasu, który uruchomi odpowiednie wydarzenia
		baseTicks++ ; // kolejny cykl główny
		timeManager() ;
	}
}

<<<<<<< HEAD:timeMeasure.c
void startTimer() {
	mainTicks = 0 ;
	baseTicks = 0 ;

	uint8_t i = 0 ;
	for(i = 0 ; i < SZ_CYCLE_PROCESS ; i++)
		lastStarts[i] = 0 ; // zerujemy czasy pierwszego uruchomienia
=======
	timeInterval = timeToCount ;
	count = 0 ;

	state = true ;
}
>>>>>>> parent of 6c2d23d... h:timeMeasure.cpp

	TCNT1 = 0 ;
	TIMSK1 |= (1 << TOV1) ; // włączenie przerwań cyklu 1milisekundowego
}

<<<<<<< HEAD:timeMeasure.c
void stopTimer() {
	TIMSK1 &= ~(1 << TOV0) ;
}

void handleMyProcess(uint8_t period, void (*ptr)(), uint8_t index) {
	// zapisujemy uchwyt do procesu wraz z czasem, co jaki jest on uruchamiany cyklicznie
	processArray[index].period = period ;
	processArray[index].ptrFun = ptr ;
=======
bool getMeasuringState() {
	return state ;
}

void stopTimeMeasuring() {
	TIMSK1 &= ~(1 << TOV0) ;
	state = false ;
>>>>>>> parent of 6c2d23d... h:timeMeasure.cpp
}

