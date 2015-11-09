/*
 * Oro.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Oro.h"

void Oro::recolectar(RecursosJugador * recursos, int cantidad){
	recursos->colectarOro(this->sacarRecurso(cantidad));
	printf("recursos oro %d\n",recursos->cantOro());
}

Oro::~Oro() {
	// TODO Auto-generated destructor stub
}

