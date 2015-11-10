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
	 ~Posicion();

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
	double distancia_euclidia(Posicion posicion);
	double distancia_octal(Posicion posicion);
	double distancia_manhattan(Posicion posicion);
	bool es_adyacente(Posicion posicion);

    friend bool operator== ( Posicion &P1,  Posicion &P2);
    friend bool operator== ( Posicion const &P1, const  Posicion &P2);
    friend Posicion operator+(const Posicion &c1, const Posicion &c2);
    friend Posicion operator-(const Posicion &c1, const Posicion &c2);


};

#endif /* POSICION_H_ */
