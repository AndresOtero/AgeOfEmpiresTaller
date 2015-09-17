/*
 * Posicion.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef POSICION_H_
#define POSICION_H_

class Posicion {
public:
	Posicion();
	Posicion(int x, int y);
	int x;
	int y;
	virtual ~Posicion();
};

#endif /* POSICION_H_ */
