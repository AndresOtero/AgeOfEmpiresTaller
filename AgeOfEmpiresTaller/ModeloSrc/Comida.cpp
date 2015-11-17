/*
 * Comida.cpp
 *
 *  Created on: 17/11/2015
 *      Author: ger
 */

#include "Comida.h"

namespace std {

void Comida::recolectar(RecursosJugador * recursos, int cantidad){
	recursos->colectarComida(this->sacarRecurso(cantidad));
}

Comida::~Comida() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
