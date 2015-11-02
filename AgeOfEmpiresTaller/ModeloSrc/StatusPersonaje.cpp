/*
 * StatusPersonaje.cpp
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#include "StatusPersonaje.h"

void StatusPersonaje::atacarStatusPersonaje(int ataque){

	// con una defensa de PARAMTERO/2 se le saca un 60% del ataque original
	this->vida-= ataque*exp(-(double)defensa/PARAMETRO_DEFENSA);
}



StatusPersonaje::~StatusPersonaje() {
	// TODO Auto-generated destructor stub
}

