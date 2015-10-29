#include "bluetoothIO.h"
#include "bluetoothIO2.h"
#include <string.h>
#include "USART/usart.h"
#include "USART/buforCykliczny.h"

#include <avr/interrupt.h>

BuforCykliczny<uint8_t, 128> buffTx ;
BuforCykliczny<uint8_t, 64> buffRx ;

extern volatile uint8_t flagiProgramu ;
#define READ_MSG_FLAG 0
#define READ_MSG_OVF_FLAG 1

ISR(USART_UDRE_vect)
{
	if(buffTx.isEmpty())
		Usart::udrIntDisable() ;
	else
		buffTx.pop(&UDR0) ;
}

void obslugaFlagRx()
{
	if(buffRx.isFull())
		flagiProgramu |= (1 << READ_MSG_OVF_FLAG) ;
	if(buffRx.seeLastAdded() == '\n')
		flagiProgramu |= (1 << READ_MSG_FLAG) ;
}

ISR(USART_RX_vect)
{
	uint8_t c = UDR0 ;
	buffRx.push(c) ;
	obslugaFlagRx() ;
}

void sendStringBt(const char *src)
{
	while(*src)
	{
		if(buffTx.isFull()){
			Usart::udrIntEnable() ;
			while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
		}
		buffTx.push(*(src++)) ;
	}

	Usart::udrIntEnable() ;
}

void sendStringPBt(const char *srcP)
{
	uint8_t c ;

	while(1) {
		if(buffTx.isFull()){
			Usart::udrIntEnable() ;
			while(!buffTx.isEmpty()) ; // czekaj na zwolnienie zasobów
		}
	 	 if(c = pgm_read_byte(srcP++))
	 		 buffTx.push(c) ;
	}

	Usart::udrIntEnable() ;
}

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
		Usart::initUsart() ;
		Usart::txEnable() ;
		Usart::rxEnable() ;

		Usart::rxIntEnable() ;

		// Usart::udrIntEnable() ;
		sei() ;

		printStringPFunction(HELLO) ;
	}

	void shiftRxOut(uint8_t *dest)
	{
		while(!buffRx.isEmpty())
			buffRx.pop(dest++) ;
		*dest = '\0' ; // dodajemy zero, dla pewności
	}
}


