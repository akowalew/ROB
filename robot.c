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
	btInit() ;
	char s[10] ;
	char str[32] ;	// bufor do odczytu z RX

	EncoderResult enc ;

	while(1) {
		turnOnLed() ;
		enc = encodersReadEnc2() ;
		sprintf(s, "%u", enc.ticks) ;
		btSendString(s) ;
		turnOffLed() ;
		_delay_ms(1000) ;
	}

return 0;

	while(1)
	{
		if(btGetState() == READ_MSG)
		{
			btClearState() ;

			btGetReadMessage((uint8_t *) str) ;	// kopiujemy odczytany string do tablicy
			btCheckMessage(str) ;	// sprawdzamy, czy możemy z tym stringiem coś uczynić.
		}
		if(isBtn1Pressed()) {
			timeMeasureStop() ;
			char s[10] ;
			uint16_t tick = timeMeasureGetTime() ;

			sprintf(s, "%u", tick) ;

			btSendString(s) ;
			timeMeasureStart(1000UL) ;
		}
	}
}

