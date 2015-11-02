#ifndef _UTILITYFUNCTIONS_H_
#define _UTILITYFUNCTIONS_H_

// Ideą tego pliku jest umieszczenie kilku funkcji,
// które dosyć często wykorzystuję w projektach,
// a konkretnej implementacji nie ma w AVRLibc

uint8_t myAtoi(volatile uint8_t *u8Dest, const char *src) ;
void myItoa(uint8_t var, char *dest) ;


#endif
