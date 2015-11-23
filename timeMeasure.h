/*
 * timeMeasure.h
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#ifndef TIMEMEASURE_H_
#define TIMEMEASURE_H_

#define TICK_HALF_MILISECOND 	7999UL
#define TICK_ONE_MILISECOND		15999UL
#define TICK_TWO_MILISECONDS	31999UL

#define MAX_U16	0xFFFF

void timeMeasureInit(uint16_t elementaryTick) ;
void timeMeasureStart(uint16_t timeToCount) ;

void timeMeasureStop() ;
uint16_t timeMeasureGetTime() ;

uint8_t timeMeasureGetState() ;
// TRUE - nadal mierzy
// FALSE - przestał mierzyć(sam, albo ktoś go wyłączył)

#endif /* TIMEMEASURE_H_ */
