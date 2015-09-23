/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"

Personaje::Personaje(float referencia_mapa_x,float referencia_mapa_y,	dibujo_t dibujo,float velocidad) {
	// TODO Auto-generated constructor stub
	this->referencia_mapa_x=referencia_mapa_x;
	this->referencia_mapa_y=referencia_mapa_y;
	this->velocidad=velocidad;
	this->dibujo=dibujo;
}
dibujo_t Personaje::dibujar(){
	return dibujo;
}
void Personaje::mover(int x,int y){
	double delta_x = (double) (x - referencia_mapa_x);
	double delta_y = (double) (y - referencia_mapa_y);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;
		if ((sqrt(des_x * des_x) > distancia)
				&& (sqrt(des_y * des_y) < distancia)) {
			this->referencia_mapa_x = x;
		}
		if ((sqrt(des_y * des_y) > distancia)
				&& ((sqrt(des_x * des_x) < distancia))) {
			this->referencia_mapa_y = y;
		}
		this->referencia_mapa_x += des_x;
		this->referencia_mapa_y += des_y;
	}
}
Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

