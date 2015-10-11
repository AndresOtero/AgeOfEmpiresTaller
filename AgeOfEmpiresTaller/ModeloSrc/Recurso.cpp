/*
 * Recurso.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Recurso.h"

Recurso::Recurso(ObjetoMapa* objetoMapa): Entidad(objetoMapa) {

	cantidad = rand() % 150 + 100;//random entre 100 y 250

}
Recurso::Recurso(ObjetoMapa* objetoMapa,int x , int y): Entidad( objetoMapa,x,y) {

	cantidad = rand() % 150 + 100;//random entre 100 y 250
}

int Recurso::obtenerRecurso(){
	return this->cantidad;
}

Recurso::~Recurso() {
	// TODO Auto-generated destructor stub
}

