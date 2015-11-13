/*
 * buforCykliczny.h
 *
 *  Created on: 28 paź 2015
 *      Author: akowalew
 */

#ifndef USART_CYCLEBUFFER_H_
#define USART_CYCLEBUFFER_H_

typedef unsigned char uint8_t ;

typedef struct {
	uint8_t SZ ;
	uint8_t *buff ;
	uint8_t i, j ;
	uint8_t MASK ;

	uint8_t lastAdd ;
	uint8_t full, empty ;

} CycleBuffer ;

uint8_t cycleBufferPush(CycleBuffer *cb, uint8_t data) ;
uint8_t cycleBufferPop(CycleBuffer *cb, volatile uint8_t *dest) ;
void cycleBufferInit(CycleBuffer *cb, uint8_t *buffer, uint8_t SZz) ;

#endif /* USART_BUFORCYKLICZNY_H_ */
