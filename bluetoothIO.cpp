#include "bluetoothIO.h"
#include "bluetoothIO2.h"
#include <string.h>

namespace BluetoothIO
{

	void obslugaKomunikatu(const char *komunikat)
	{
		if(strncmp(komunikat, ID, CONST_STRLEN(ID)) == 0)
		{

			if(komunikat[CONST_STRLEN(ID)] == '\0') // wprowadził tylko ID
				printStringFunction(ID) ;
			else
			{
				if(komunikat[CONST_STRLEN(ID)] == OPT)	// komendy pozostałe
					funkcjaOpcji(komunikat + CONST_STRLEN(ID) + 1) ;
				else if(komunikat[CONST_STRLEN(ID)] == READ)	// komputer chce pobrać zmienne
					funkcjaOdczytu(komunikat + CONST_STRLEN(ID) + 1) ;
				else if(komunikat[CONST_STRLEN(ID)] == WRITE)
					funkcjaZapisu(komunikat + CONST_STRLEN(ID) + 1) ;
			}
		}
	}
	
	void inicjacjaObslugi()
	{
		printStringPFunction(HELLO) ;
	}

}


