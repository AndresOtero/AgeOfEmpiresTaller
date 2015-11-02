/*
 * CentroCivico.cpp
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#include "CentroCivico.h"

Personaje * CentroCivico::crearPersonaje(string nombre){
	StatusPersonaje status = this->tipos_status[nombre];
	ObjetoMapa * objeto = this->modelo->juego->tipos[nombre];
	//obtener posicion vacia
	//Personaje * personaje = new Aldeano(objeto, pos.x,pos.y,status);
	//return personaje
}

CentroCivico::~CentroCivico() {
	// TODO Auto-generated destructor stub
}

