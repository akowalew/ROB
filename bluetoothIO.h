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
	
	ROB<A:0		Powoduje zapisanie do robota, do jego wszystkich zmiennych funkcyjnych, wartości 0
		ROB:OK
		ROB:OK
		ROB:OK
		...
		ROB:OK
			Tyle razy, ile mamy wszystkich zmiennych funkcyjnych w robocie
	
	Przykładowo operacje odczytu z robota :
	
	ROB>1		Rozkazujemy robotowi, by nam przesłał drugą zmienną funkcyjną
		ROB:OK:xxx
			Robot oddaje nam zawartość zmiennej drugiej
			
	ROB>A		Rozkazujemy robotowi, by nam przesłał wszystkie zmienne
		ROB:OK:xxx
		ROB:OK:yyy
		...
		ROB:OK:zzz
			Tyle razy, ile mamy zmiennych funkcyjnych

	Przykładowo operacje użytkowe na robocie
	
	ROB:STATE	Rozkazujemy robotowi, by powiedział o swoim aktualnym stanie
	ROB:SEE		Rozkazujemy robotowi, by dał opis każdej ze zmiennej
	ROB:RESET	Rozkazujemy robotowi, by się zresetował
	ROB		Sprawdzamy komunikację z robotem
*/

namespace BluetoothIO
{
	void obslugaKomunikatu(const char *komunikat) ;
	void inicjacjaObslugi() ;
	void shiftRxOut(uint8_t *dest) ; // wyrzuć wszystko z bufora RX
}

#endif // _BLUETOOTHIO_H_
