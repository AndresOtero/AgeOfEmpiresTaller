/*
 * DibujoPersonaje.cpp
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#include "DibujoPersonaje.h"

DibujoPersonaje::DibujoPersonaje() {
	// TODO Auto-generated constructor stub
	this -> velocidad = 0;
}

void DibujoPersonaje::set_velocidad(int velocidad){
	this->velocidad=velocidad;
}


void DibujoPersonaje::mover(int x, int y) {

	double delta_x = (double) (x - x_imagen);
	double delta_y = (double) (y - y_imagen);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;
		if ((sqrt(des_x * des_x) > distancia)
				&& (sqrt(des_y * des_y) < distancia)) {
			x_imagen = x;
		}
		if ((sqrt(des_y * des_y) > distancia)
				&& ((sqrt(des_x * des_x) < distancia))) {
			y_imagen = y;
		}
		x_imagen += des_x;
		y_imagen += des_y;
		this->cambiar_frame();

	}
}
DibujoPersonaje::~DibujoPersonaje() {
	// TODO Auto-generated destructor stub
}

