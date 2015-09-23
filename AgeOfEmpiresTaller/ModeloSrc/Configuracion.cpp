
/*
 * Configuracion.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Configuracion.h"

Configuracion::Configuracion() {
	this -> vel_personaje = 1;
	this -> margen_scroll = 30;
}
Configuracion::Configuracion(int vel_personaje, int margen_scroll){
	this -> vel_personaje = vel_personaje;
	this -> margen_scroll = margen_scroll;
}
Configuracion::~Configuracion() {
}

