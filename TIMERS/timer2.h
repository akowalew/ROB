/*
 * timer2.h
 *
 *  Created on: 21 paź 2015
 *      Author: dicker
 */

#ifndef TIMERS_TIMER2_H_
#define TIMERS_TIMER2_H_

#include <avr/io.h>

namespace Timer2
{

	enum WAVEFORM_GENERATE_MODE
	{
		NORMAL = 0,					// TOP = 0xFF, OCR0 Update = Immediate,	OVF = MAX
		PWM_PHASE_CORRECT = 0x01,	// TOP = 0xFF, OCR0 Update = TOP, 		OVF = BOTTOM
		CTC = 0x08,					// TOP = OCR0, OCR0 Update = Immediate,	OVF = MAX
		FAST_PWM = 0x09 ,			// TOP = 0xFF, OCR0 Update = BOTTOM, 	OVF = MAX
	};

	// BOTTOM 	= The counter reaches the BOTTOM when it becomes zero (0x00).
	// MAX		= The counter reaches its MAXimum when it becomes 0xFF (decimal 255)
	// TOP		= The counter reaches the TOP when it becomes equal to the highest value in the count sequence (OCRn)

	enum NORMAL_CTC_MODE
	{
		OC0_DISCONNECTED = 0 ,	// NORMAL port operation, OCn disconnected.
		TOGGLE_OC0 = 1,			// TOGGLE OCn on compare match
		CLEAR_OC0 = 2,			// CLEAR OCn on compare match
		SET_OC0 = 3 ,			// SET OCn on compare match
	};

	enum FAST_PWM_MODE
	{
		FAST_PWM_DISCONNECTED = 0,	// NORMAL port operation, OCn disconnected.
		CLEAR_OCR_SET_BOTTOM = 2,	// CLEAR OCn on compare match, SET OCn at BOTTOM, (non-invert)
		SET_OCR_CLEAR_BOTTOM = 3,	// SET OCn on compare match, CLEAR OCn at BOTTOM, (invert)
	} ;

	enum PWM_PHASE_CORRECT_MODE
	{
		PWM_PHASE_CORRECT_DISCONNECTED = 0,	// NORMAL port operation, OCn disconnected.
		CLEAR_UPCOUNT_SET_DOWNCOUNT = 2,	// CLEAR OCn on compare match when up-counting. SET OCn on compare match when downcounting.
		SET_UPCOUNT_CLEAR_DOWNCOUNT = 3 	// SET OCn on compare match when up-counting. CLEAR OCn on compare match when downcounting
	};

	enum CLOCK_SELECT
	{
		NO_CLK = 0 , 				// Zegar wyłączony
		CLK_1 = 0x01, 				// CLK / 1 (bez skalowania)
		CLK_8 = 0x02, 				// CLK / 8
		CLK_32 = 0x03, 				// CLK / 32
		CLK_64 = 0x04, 				// CLK / 64
		CLK_128 = 0x05, 			// CLK / 128
		CLK_256 = 0x06, 			// CLK / 256
		CLK_1024 = 0x07,			// CLK / 1024
	};

	inline void 	timerInit(	WAVEFORM_GENERATE_MODE wgmMode = FAST_PWM,
								uint8_t modeFunctionality = CLEAR_OCR_SET_BOTTOM,
								CLOCK_SELECT cs = CLK_1)
	{
		TCCR2 = (modeFunctionality << COM00) | (cs << CS00) | (wgmMode << WGM00) ;
	}

	inline uint8_t 	getClock() { return TCNT2 ; }
	inline void		setClock(uint8_t data) { TCNT2 = data ; }
	inline void		setOCR(uint8_t data) { OCR2 = data ; }
	inline void		interruptsSettings(bool isOVF, bool isOC)
	{
		TIMSK &= ~((1 << TOIE2) | (1 << OCIE2)) ;
		TIMSK |= (isOVF << TOIE2) | (isOC << OCIE2) ;
	}
}




#endif /* TIMERS_TIMER2_H_ */
