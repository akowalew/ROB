/*
 * progmemArrays.h
 *
 *  Created on: 30 paź 2015
 *      Author: dicker
 */

#ifndef PROGMEMARRAYS_H_
#define PROGMEMARRAYS_H_

#include <avr/pgmspace.h>

const char SEE_TEXT_P[]  PROGMEM =	"Oto opis wystepujacych zmiennych:\n"
					"0 : OCR0A\n"
					"1 : OCR0B\n"
					"2 : OCR2A\n"
					"3 : OCR2B\n"
					"4 : MOT0 SPEED\n"
					"5 : MOT2 SPEED";

const char RESET_TEXT_P[] PROGMEM = "Nastapi zresetowanie robota do poczatku..." ;
const char HELLO_P[] PROGMEM = "Witaj! To obsluga robota ROB!" ;

#endif /* PROGMEMARRAYS_H_ */
