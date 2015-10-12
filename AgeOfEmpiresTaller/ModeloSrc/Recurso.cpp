/*
 * Recurso.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Recurso.h"
#include <random>

Recurso::Recurso(ObjetoMapa* objetoMapa): Entidad(objetoMapa) {
	std::random_device rd;
	std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(100, 250);

	cantidad = dist(mt);//random entre 100 y 250

}
Recurso::Recurso(ObjetoMapa* objetoMapa,int x , int y): Entidad( objetoMapa,x,y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(100, 250);

	cantidad = dist(mt);//random entre 100 y 250
}

int Recurso::obtenerRecurso(){
	return this->cantidad;
}

Recurso::~Recurso() {
	// TODO Auto-generated destructor stub
}

