
#ifndef _MAINPROGRAMFUNCTIONS_H_
#define _MAINPROGRAMFUNCTIONS_H_

#include "motors.h"

extern volatile uint8_t programFlags ;
extern const uint8_t NUMBER_OF_VARIABLES ;
extern volatile uint8_t * const ptrVariables[] ;

#define F_PWM 62500UL

enum	FLAG_MASK
{
	READ_MSG_FLAG = 0,
	READ_MSG_OVF_FLAG = 1
} ;

inline void setFlag(uint8_t flag)
{
	programFlags |= 1 << flag ;
}

inline void clearFlag(uint8_t flag)
{
	programFlags &= ~(1 << flag) ;
}

inline uint8_t isSetFlag(uint8_t flag)
{
	return programFlags & (1 << flag) ;
}

void initProgram() ;

#endif
