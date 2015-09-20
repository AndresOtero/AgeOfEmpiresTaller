/*
 * EntidadAnimada.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "EntidadAnimada.h"

EntidadAnimada::EntidadAnimada(ObjetoMapa* objetoMapaAnimado){
	this -> objetoMapaAnimado = objetoMapaAnimado;
	this -> posicion = new Posicion();
}
EntidadAnimada::EntidadAnimada(ObjetoMapa* objetoMapaAnimado, int x , int y){
	this -> objetoMapaAnimado = objetoMapaAnimado;
	this -> posicion = new Posicion(x,y);
}
EntidadAnimada::~EntidadAnimada() {
	delete this -> objetoMapaAnimado;
	delete this -> posicion;
}

