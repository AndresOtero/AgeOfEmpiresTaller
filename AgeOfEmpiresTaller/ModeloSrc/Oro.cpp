/*
 * Oro.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Oro.h"

void Oro::recolectar(RecursosJugador * recursos){
	recursos->colectarOro(this->obtenerRecurso());
}

Oro::~Oro() {
	// TODO Auto-generated destructor stub
}

