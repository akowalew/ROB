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

extern const char ID[] ;
extern const char ID_OK[] ;
extern const char ID_OK_READ[] ;

#define RX_BUFF_SZ	64
#define TX_BUFF_SZ	128

void btCheckOptionMessage(const char *str) ;
void btCheckReadMessage(const char *str) ;
void btCheckWriteMessage(const char *str) ;

void btSendString(const char *src) ;
void btSendStringP(const char *srcP) ;

#endif /* BLUETOOTHIO2_H_ */
