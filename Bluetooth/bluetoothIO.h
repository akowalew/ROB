#ifndef _BLUETOOTHIO_H_
#define _BLUETOOTHIO_H_

typedef unsigned char uint8_t ;

/*
	Komunikacja przez port szeregowy ma wyglądać następująco :
	Pierw podajemy identyfikator robota, potem kierunek transmisji, następnie miejsce zapisu
	i na koniec dane do zapisu. 
	
	Przykładowo operacje zapisu do robota :
	
	ROB<1:123	Powoduje zapisanie do robota, do jego drugiej zmiennej funkcyjnej, wartości 123
		Po odebraniu tego polecenia robot powinien odpowiedzieć :
		
		ROB:OK
	
	Przykładowo operacje odczytu z robota :
	
	ROB>1		Rozkazujemy robotowi, by nam przesłał drugą zmienną funkcyjną
		ROB:OK:xxx
			Robot oddaje nam zawartość zmiennej drugiej

	Przykładowo operacje użytkowe na robocie
	
	ROB:STATE	Rozkazujemy robotowi, by powiedział o swoim aktualnym stanie
	ROB:SEE		Rozkazujemy robotowi, by dał opis każdej ze zmiennej
	ROB:RESET	Rozkazujemy robotowi, by się zresetował
	ROB		Sprawdzamy komunikację z robotem
*/

	typedef enum  {
		NOTHING_TO_READ ,
		READ_MSG ,
		READ_MSG_OVF
	} BluetoothState ;

	uint8_t btGetState() ;
	void btClearState() ;

	void btCheckMessage(const char *komunikat) ;	// rozpoznaj komunikat
	void btInit() ;
	void btGetReadMessage(uint8_t *dest) ; // wyrzuć wszystko z bufora RX



#endif // _BLUETOOTHIO_H_
