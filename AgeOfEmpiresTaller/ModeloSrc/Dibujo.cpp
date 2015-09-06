/*
 * Dibujo.cpp
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */

#include "Dibujo.h"

Dibujo::Dibujo(dibujo_t tipo_de_dibujo) {
	// TODO Auto-generated constructor stub
	this->tipo_de_dibujo=tipo_de_dibujo;
}
dibujo_t Dibujo::dibujar() {
	// TODO Auto-generated destructor stub
	return this->tipo_de_dibujo;
}

Dibujo::~Dibujo() {
	// TODO Auto-generated destructor stub
}

