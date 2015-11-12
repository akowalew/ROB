/*
 * motors.h
 *
 *  Created on: 12 lis 2015
 *      Author: akowalew
 */

#ifndef MOTORS_H_
#define MOTORS_H_

// motors functions

#ifdef __AVR_ATmega328P__
#define MOTOR0A		PD6
#define MOTOR0B		PD5
#define MOTOR2A		PB3
#define MOTOR2B		PD3
#else

#endif

void initMotors() ;
void turnMotor2(int8_t percent) ;
void turnMotor0(int8_t percent) ;
void turnOn2(bool onOff) ;
void turnOn0(bool onOff) ;
void turnMotors() ;

inline void setMod0A(uint8_t percent) {
	OCR0A = (percent * 255) / 100 ;
}

inline void setMod0B(uint8_t percent) {
	OCR0B = (percent * 255) / 100 ;
}

inline void setMod2A(uint8_t percent) {
	OCR2A = (percent * 255) / 100 ;
}

inline void setMod2B(uint8_t percent) {
	OCR2B = (percent * 255) / 100 ;
}

#endif /* MOTORS_H_ */
