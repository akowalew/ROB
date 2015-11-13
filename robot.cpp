#define F_CPU 16000000UL

#include <avr/io.h>
#include "Bluetooth/bluetoothIO.h"
#include "mainProgramFunctions.h"

#include <util/delay.h>

#include <avr/interrupt.h>
#include "timeMeasure.h"

int main()
{
	initProgram() ;

	//startTimeMeasuring(1000UL) ;

	turnOffLed() ;
	while(1) {
		/* if(getMeasuringState() == false) {

			turnSwitchLed() ;
			startTimeMeasuring(1000UL) ;
		} */

		if(isBtn1Pressed())
			turnOnLed() ;

	}



	return 0 ;
	BluetoothIO::initBt() ;


	char str[32] ;	// bufor do odczytu z RX
	while(1)
	{
		if(BluetoothIO::getState() == BluetoothIO::READ_MSG)
		{
			BluetoothIO::clearState() ;

			BluetoothIO::getReadMessage((uint8_t *) str) ;	// kopiujemy odczytany string do tablicy
			BluetoothIO::checkMessage(str) ;	// sprawdzamy, czy możemy z tym stringiem coś uczynić.
		}
	}
}

