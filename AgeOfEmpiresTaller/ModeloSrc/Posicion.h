/*
 * Posicion.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */
#include "math.h"
#ifndef POSICION_H_
#define POSICION_H_

class Posicion {
	double x;
	double y;
public:
	Posicion();
	Posicion(int x, int y);
	Posicion(double x, double y);
	virtual ~Posicion();

	int getX() const {
		return floor(x);
	}

	int getY() const {
		return floor(y);
	}
	double get_x_exacta() const {
		return x;
	}
	double get_y_exacta() const {
		return y;
	}
	double distancia(Posicion posicion);
};

#endif /* POSICION_H_ */
