#include "bluetoothIO.h"
#include "bluetoothIO2.h"

#include <string.h>

#include "../UTILITY/USART/usart.h"
#include "../UTILITY/cycleBuffer.h"

#include <avr/interrupt.h>

uint8_t TX_BUFF[TX_BUFF_SZ] ;
uint8_t RX_BUFF[RX_BUFF_SZ] ;

CycleBuffer buffRx ;
CycleBuffer buffTx ;

volatile uint8_t bluetoothState ;

const char SEE_TEXT_P[]  PROGMEM =	"Oto opis wystepujacych zmiennych:\n"
					"0 : OCR0A\n"
					"1 : OCR0B\n"
					"2 : OCR2A\n"
					"3 : OCR2B\n"
					"4 : MOT0 SPEED\n"
					"5 : MOT2 SPEED";

const char RESET_TEXT_P[] PROGMEM = "Nastapi zresetowanie robota do poczatku..." ;
const char HELLO_P[] PROGMEM = "Witaj! To obsluga robota ROB!" ;

const char ID[] = "ROB" ;
const char ID_OK[]  = "ROB:OK" ;
const char ID_OK_READ[]  = "ROB:OK:" ;


	void btCheckMessage(const char *msg)
	{
		if(strncmp(msg, ID, CONST_STRLEN(ID)) == 0)
		{
			if(msg[CONST_STRLEN(ID)] == '\0') // wprowadził tylko ID
				btSendString(ID_OK) ;
			else
			{
				if(msg[CONST_STRLEN(ID)] == ':')	// komendy pozostałe
					btCheckOptionMessage(msg + CONST_STRLEN(ID) + 1) ;
				else if(msg[CONST_STRLEN(ID)] == '>')	// komputer chce pobrać zmienne
					btCheckReadMessage(msg + CONST_STRLEN(ID) + 1) ;
				else if(msg[CONST_STRLEN(ID)] == '<')
					btCheckWriteMessage(msg + CONST_STRLEN(ID) + 1) ;
			}
		}

	}
	
	void btInit()
	{
		cycleBufferInit(&buffRx, RX_BUFF, RX_BUFF_SZ) ;
		cycleBufferInit(&buffTx, TX_BUFF, TX_BUFF_SZ) ;

		usartInit(USART_CHAR_SIZE_8, USART_PARITY_NONE, USART_STOP_BITS_ONE, USART_MODE_ASYNCHRONOUS) ;
		usartTxEnable() ;
		usartRxEnable() ;

		usartRxIntEnable() ;

		sei() ;

		btSendStringP(HELLO_P) ;
	}

	void btGetReadMessage(uint8_t *dest)
	{	// wyrzuca komunikat z buforu RX do 'dest'

		while(!buffRx.empty)
			cycleBufferPop(&buffRx, dest++) ;
		*(dest-1) = '\0' ; // dodajemy zero, dla pewności
	}

	uint8_t btGetState() {
		return bluetoothState ;
	}

	void btClearState() {
		bluetoothState = NOTHING_TO_READ ;
	}



