/*
 * bluetoothIO2.h
 *
 *  Created on: 27 paź 2015
 *      Author: akowalew
 */

#ifndef BLUETOOTHIO2_H_
#define BLUETOOTHIO2_H_

#include <avr/io.h>
#include "progmemArrays.h"

#define CONST_STRLEN(s)	((sizeof((s)) / sizeof(char)) - 1)

volatile uint8_t * const ptrVariables[] =
{
		&OCR0A,
		&OCR0B,
		&OCR2A,
		&OCR2B
};
const uint8_t SZ_PTRVAR = sizeof(ptrVariables) / sizeof(volatile uint8_t * const) ;

const char ID[] = "ROB" ;
const char ID_OK[]  = "ROB:OK" ;
const char ID_OK_READ[]  = "ROB:OK:" ;

#define RX_BUFF_SZ	64
#define TX_BUFF_SZ	128

void checkOptionMessage(const char *str) ;
void checkReadMessage(const char *str) ;
void checkWriteMessage(const char *str) ;

void sendStringBt(const char *src) ;
void sendStringPBt(const char *srcP) ;

#endif /* BLUETOOTHIO2_H_ */
