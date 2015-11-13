/*
 * cycleBuffer.c
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#include "cycleBuffer.h"

uint8_t cycleBufferPush(CycleBuffer *cb, uint8_t data) {
	if(!(cb->full)) {
		cb->buff[cb->i] = data ;
		cb->i = (cb->i+1) & cb->MASK ;
		cb->empty = 0 ;
		if( cb->i == cb->j )
			cb->full = 1 ;

		cb->lastAdd = data ;
		return 1 ;
	}
	return 0 ;
}

uint8_t cycleBufferPop(CycleBuffer *cb, volatile uint8_t *dest) {
	if(!(cb->empty)) {
		*dest = cb->buff[cb->j] ;
		cb->j = (cb->j+1) & cb->MASK ;

		cb->full = 0 ;
		if(cb->i == cb->j)
			cb->empty = 1 ;
		return 1 ;
	}

	return 0 ;
}

void cycleBufferInit(CycleBuffer *cb, uint8_t *buffer, uint8_t SZz) {
	cb->i = 0;
	cb->j = 0;
	cb->full = 0 ;
	cb->empty = 1;
	cb->buff = buffer ;
	cb->SZ = SZz ;
	cb->MASK = SZz-1 ;
}



