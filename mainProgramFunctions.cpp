#include <avr/io.h>

volatile uint8_t programFlags ;
#define F_PWM 62500UL

#ifdef __AVR_ATmega328P__
#define MOTOR0A		PD6
#define MOTOR0B		PD5
#define MOTOR2A		PB3
#define MOTOR2B		PD3
#else

#endif

inline void setMod0A(uint8_t percent) {
	OCR0A |= (percent * 255) / 100 ;
}

inline void setMod0B(uint8_t percent) {
	OCR0B |= (percent * 255) / 100 ;
}

inline void setMod2A(uint8_t percent) {
	OCR2A |= (percent * 255) / 100 ;
}

inline void setMod2B(uint8_t percent) {
	OCR2B |= (percent * 255) / 100 ;
}

void turnOn0(bool onOff)
{
#ifdef __AVR_ATmega328P__
	if(onOff)
		DDRD |= (1 << MOTOR0A) | (1 << MOTOR0B) ;
	else
		DDRD &= ~((1 << MOTOR0A) | (1 << MOTOR0B)) ;
#else

#endif
}

void turnOn2(bool onOff)
{
#ifdef __AVR_ATmega328P__
	if(onOff) {
		DDRB |= (1 << MOTOR2A) ;
		DDRD |= (1 << MOTOR2B) ;
	} else {
		DDRB &= ~(1 << MOTOR2A) ;
		DDRD &= ~(1 << MOTOR2B) ;
	}
#else

#endif
}

inline void turnMotor0(int8_t percent)
{
	if(percent >= 0) {
		setMod0A((uint8_t) percent) ;
		setMod0B(0) ;
	} else {
		setMod0A(0) ;
		set
	}
	}
}
void initMotors() {
	// Inicjacja silników w trybie FAST_PWM

	// Clear at OCR, set at Bottom
	TCCR0A |= (1 << COM0A1) ;
	TCCR0A |= (1 << COM0B1) ;

	// Top = 0xFF, TOV = 0xFF
	TCCR0A |= (1 << WGM01) | (1 << WGM00) ;

	// CLock prescaler = 1,
	// F_pwm = 16MHz / 256 / 1 = 62,5kHz
	TCCR0B |= (1 << CS00) ;

	TCCR2A |= (1 << COM2A1) ;
	TCCR2A |= (1 << COM2B1) ;
	TCCR2A |= (1 << WGM21) | (1 << WGM20) ;
	TCCR2B |= (1 << CS20) ;
}

void initProgram() {

	// inicjacja rejestrów silników
}

