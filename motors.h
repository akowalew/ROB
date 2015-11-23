/*
 * motors.h
 *
 *  Created on: 12 lis 2015
 *      Author: akowalew
 */

#ifndef MOTORS_H_
#define MOTORS_H_

// motors functions
#include <avr/io.h>

#define MOTOR0A		PD6
#define MOTOR0B		PD5
#define MOTOR2A		PB3
#define MOTOR2B		PD3

#ifdef __AVR_ATmega328P__

#else

#endif

void motorsInit() ;
void motorsTurnMot2(int8_t percent) ;
void motorsTurnMot0(int8_t percent) ;
void motorsTurnOn2(uint8_t onOff) ;
void motorsTurnOn0(uint8_t onOff) ;
void motorsTurnMotors() ;

 void motorsSetMod0A(uint8_t percent) ;

void motorsSetMod0B(uint8_t percent) ;

void motorsSetMod2A(uint8_t percent) ;

void motorsSetMod2B(uint8_t percent) ;

#endif /* MOTORS_H_ */
