/*
 * Madera.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Madera.h"

void Madera::recolectar(RecursosJugador * recursos, int cantidad){
	recursos->colectarMadera(this->sacarRecurso(cantidad));
}

Madera::~Madera() {
	// TODO Auto-generated destructor stub
}

