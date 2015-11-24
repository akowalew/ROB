/*
 * timeMeasure.h
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#ifndef TIMEMEASURE_H_
#define TIMEMEASURE_H_

#define TICK_MAIN_HALF_MILISECOND 	7999UL
#define TICK_MAIN_ONE_MILISECOND	15999UL
#define TICK_MAIN_TWO_MILISECONDS	31999UL

#define TICK_MAIN_VALUE	TICK_MAIN_TWO_MILISECONDS // tyle trwa cykl główny (2ms)

#define TICK_BASE_MILISECONDS		20 // tyle wynosi rozdzielczość bazowego (20ms)
#define TICK_BASE_VALUE	(TICK_BASE_MILISECONDS / 2) // dzielimy przez 2, bo główny wynosi 2ms

#define MAX_U16	0xFFFF

#define CALCULATE_TIME(x) ((uint8_t)((x)/TICK_BASE_MILISECONDS))
/* Zaprogramowany zarządca cyklicznymi procesami
	Wysyłamy do niego wskaźniki na funkcje wraz z czasami, co jakie musi się dany proces załączać
	Licznik 1 liczy w swoim głównym przebiegu cykle "mainTicks".

	Pierw trzeba zainicjować wszystko procedurą initTimer()
		mainTickConstant mówi, jaki jest czas trwania głównego cyklu (pół, jedna, dwie milisekundy)

	Potem trzeba procesy metodą void handleProcess(CycleProcessStruct process, uint8_t index)

	Na koniec trzeba uruchomić maszynerię void startTimer() ;

		Od tej pory uruchamiane są cykle główne co czas (pół, jedna, dwie milisekundy) a
		następnie w przerwaniach inkrementowany jest bazowy licznik, który zlicza do wartości bazowej
		TICK_BASE_MILISECONDS. Jest to podstawowa rozdzielczość, względem której odmierzane są procesy.


*/
void initTimer() ;
void startTimer() ;
void stopTimer() ;

typedef struct  {
	uint8_t period ;
	void (*ptrFun)() ;
	// gdy ptrFun == 0 to procedura nie jest sprawdzana nawet

} CycleProcessStruct ;

void handleMyProcess(uint8_t period, void (*ptr)(void), uint8_t index) ;

#define SZ_CYCLE_PROCESS 3

#endif /* TIMEMEASURE_H_ */
