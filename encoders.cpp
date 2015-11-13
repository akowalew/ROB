/*
 * encoders.cpp
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#include <avr/io.h>
#include "encoders.h"
#include <avr/interrupt.h>

EncoderResult readEncoder0() {
	// zliczanie obrotów enkodera działa następująco :

}

EncoderResult readEncoder2() {

}

void initEncoders() {
	DDRD &= ~((1 << ENC0_A) | (1 << ENC0_B)) ;
	DDRB &= ~((1 << ENC2_A) | (1 << ENC2_B)) ;
}



