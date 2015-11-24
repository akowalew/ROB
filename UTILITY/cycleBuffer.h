/*
 * buforCykliczny.h
 *
 *  Created on: 28 paź 2015
 *      Author: akowalew
 */

#ifndef USART_CYCLEBUFFER_H_
#define USART_CYCLEBUFFER_H_

typedef unsigned char uint8_t ;

template<typename Type, uint8_t SZ> class CycleBuffer
{ // SZ - koniecznie potęga dwójki!
	Type buff[SZ] ;
	uint8_t i, j ;
	static const uint8_t MASK = SZ-1 ;
	Type lastAdd ;

	bool full, empty ;

	// i - wskaźnik do wstawiania
	// j - wskaźnik do wyjmowania

public :

	bool push(Type data) {
		if(!isFull()) {
			buff[i] = data ;
			i = (i+1) & MASK ;
			empty = false ;
			if( i == j )
				full = true ;

			lastAdd = data ;
			return true ;
		}
		return false ;
	}

	bool pop(Type *dest) {
		if(!isEmpty()) {
			*dest = buff[j] ;
			j = (j+1) & MASK ;

			full = false ;
			if(i == j)
				empty = true ;
			return true ;
		}

		return false ;
	}

	bool isFull() const {
		return full ;
	}
	bool isEmpty() const {
		return empty ;
	}

	Type seeLastAdded() const {
		return lastAdd ;
	}

	CycleBuffer() : i(0), j(0) , full(false), empty(true) { }

};


#endif /* USART_BUFORCYKLICZNY_H_ */
