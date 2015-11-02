
#ifndef _MAINPROGRAMFUNCTIONS_H_
#define _MAINPROGRAMFUNCTIONS_H_

extern volatile uint8_t programFlags ;
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
