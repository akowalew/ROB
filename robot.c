#define F_CPU 16000000UL

#include <avr/io.h>
#include "Bluetooth/bluetoothIO.h"
#include "Bluetooth/bluetoothIO2.h"
#include "mainProgramFunctions.h"

#include <avr/interrupt.h>
#include "timeMeasure.h"

#include <stdio.h>
#include <util/delay.h>
#include "encoders.h"

int main()
{
	initProgram() ;
	initBt() ;
	char s[10] ;
	char str[32] ;	// bufor do odczytu z RX

	EncoderResult enc ;

	while(1) {
		turnOnLed() ;
		enc = readEncoder2() ;
		sprintf(s, "%u", enc.ticks) ;
		sendStringBt(s) ;
		turnOffLed() ;
		_delay_ms(1000) ;
	}

return 0;

	while(1)
	{
		if(getState() == READ_MSG)
		{
			clearState() ;

			getReadMessage((uint8_t *) str) ;	// kopiujemy odczytany string do tablicy
			checkMessage(str) ;	// sprawdzamy, czy możemy z tym stringiem coś uczynić.
		}
		if(isBtn1Pressed()) {
			stopTimeMeasuring() ;
			char s[10] ;
			uint16_t tick = getTimeMeasure() ;

			sprintf(s, "%u", tick) ;

			sendStringBt(s) ;
			startTimeMeasuring(1000UL) ;
		}
	}
}

