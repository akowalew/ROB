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

void checkOptionMessage(const char *str) ;
void checkReadMessage(const char *str) ;
void checkWriteMessage(const char *str) ;

void sendStringBt(const char *src) ;
void sendStringPBt(const char *srcP) ;

#endif /* BLUETOOTHIO2_H_ */
