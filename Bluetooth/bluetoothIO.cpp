#include "bluetoothIO.h"
#include "bluetoothIO2.h"

#include <string.h>

#include "../UTILITY/USART/usart.h"
#include "../UTILITY/cycleBuffer.h"

#include <avr/interrupt.h>

namespace BluetoothIO
{
	void checkMessage(const char *msg)
	{
		if(strncmp(msg, ID, CONST_STRLEN(ID)) == 0)
		{
			if(msg[CONST_STRLEN(ID)] == '\0') // wprowadził tylko ID
				sendStringBt(ID_OK) ;
			else
			{
				if(msg[CONST_STRLEN(ID)] == ':')	// komendy pozostałe
					checkOptionMessage(msg + CONST_STRLEN(ID) + 1) ;
				else if(msg[CONST_STRLEN(ID)] == '>')	// komputer chce pobrać zmienne
					checkReadMessage(msg + CONST_STRLEN(ID) + 1) ;
				else if(msg[CONST_STRLEN(ID)] == '<')
					checkWriteMessage(msg + CONST_STRLEN(ID) + 1) ;
			}
		}
	}
	
	void initBt()
	{
		Usart::initUsart() ;
		Usart::txEnable() ;
		Usart::rxEnable() ;

		Usart::rxIntEnable() ;

		sei() ;

		sendStringPBt(HELLO_P) ;
	}

	void getReadMessage(uint8_t *dest)
	{	// wyrzuca komunikat z buforu RX do 'dest'
		extern CycleBuffer<uint8_t, 64> buffRx ;
		while(!buffRx.isEmpty())
			buffRx.pop(dest++) ;
		*dest = '\0' ; // dodajemy zero, dla pewności
	}
}


