/*
 * Piedra.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Piedra.h"

void Piedra::recolectar(RecursosJugador* recursos){
	recursos->colectarPiedra(this->sacarRecurso());
}

Piedra::~Piedra() {
	// TODO Auto-generated destructor stub
}

