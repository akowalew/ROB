/*
 * encoders.h
 *
 *  Created on: 13 lis 2015
 *      Author: akowalew
 */

#ifndef ENCODERS_H_
#define ENCODERS_H_

#define ENC0_A	PD4	// D4
#define ENC0_B 	PD2 // D2

#define ENC2_A	PB0	// D8, PCINT0
#define ENC2_B	PB1	// D9, PCINT1

struct EncoderResult {
	uint16_t ticks ;
	enum {
		FORWARD,
		BACKWARD
	} direction ;
};

inline uint8_t getEnc0A() {
	return PIND & (1 << ENC0_A) ;
}

inline uint8_t getEnc0B() {
	return PIND & (1 << ENC0_B) ;
}

inline uint8_t getEnc2A() {
	return PINB & (1 << ENC2_A) ;
}

inline uint8_t getEnc2B() {
	return PINB & (1 << ENC2_B) ;
}

EncoderResult readEncoder0() ;
EncoderResult readEncoder2() ;

void initEncoders() ;

#endif /* ENCODERS_H_ */
