/*
 * Madera.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Madera.h"

void Madera::recolectar(RecursosJugador * recursos, int cantidad){
	recursos->colectarMadera(this->sacarRecurso(cantidad));
	printf("recursos madera %d\n",recursos->cantMadera());
}

Madera::~Madera() {
	// TODO Auto-generated destructor stub
}

