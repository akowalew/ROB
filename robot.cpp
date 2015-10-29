#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "bluetoothIO.h"

#include <avr/pgmspace.h>

#include "USART/usart.h"

volatile uint8_t flagiProgramu = 0 ;

#define READ_MSG_FLAG 0
#define READ_MSG_OVF_FLAG 1

int main()
{
	BluetoothIO::inicjacjaObslugi() ;

	char str[64] ;



	while(1)
	{
		if(flagiProgramu & (1 << READ_MSG_FLAG))
		{
			flagiProgramu &= ~(1 << READ_MSG_FLAG) ;
			BluetoothIO::shiftRxOut((uint8_t *) str) ;
			BluetoothIO::obslugaKomunikatu(str) ;

		}
	}
}

