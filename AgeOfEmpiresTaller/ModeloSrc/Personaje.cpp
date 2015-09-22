/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"

Personaje::Personaje(float referencia_mapa_x,float referencia_mapa_y,	dibujo_t dibujo) {
	// TODO Auto-generated constructor stub
	this->referencia_mapa_x=referencia_mapa_x;
	this->referencia_mapa_y=referencia_mapa_y;
	this->dibujo=dibujo;
}
dibujo_t Personaje::dibujar(){
	return dibujo;
}
void Personaje::mover(int x,int y){
	this->referencia_mapa_x=x;
	this->referencia_mapa_y=y;
}
Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

