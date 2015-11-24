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



	while(1) {
		//startTimeMeasuring(100UL) ;
		//while(getMeasuringState()) ;

	}

return 0;
	char str[32] ;
	while(1)
	{
		if(getState() == READ_MSG)
		{
			clearState() ;

			getReadMessage((uint8_t *) str) ;	// kopiujemy odczytany string do tablicy
			checkMessage(str) ;	// sprawdzamy, czy możemy z tym stringiem coś uczynić.
		}
	}
}

