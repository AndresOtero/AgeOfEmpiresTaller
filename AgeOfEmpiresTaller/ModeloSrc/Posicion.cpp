/*
 * Posicion.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Posicion.h"
#include "math.h"

Posicion::Posicion() {
	this -> x = 0;
	this -> y = 0;
}
Posicion::Posicion(int x, int y) {
	this -> x = x;
	this -> y = y;
}
Posicion::Posicion(double x, double y) {
	this -> x = x;
	this -> y = y;
}
double Posicion::distancia(Posicion posicion) {
	double delta_x = (double) (x - posicion.get_x_exacta());
	double delta_y = (double) (y - posicion.get_y_exacta());
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}


Posicion::~Posicion() {
}
