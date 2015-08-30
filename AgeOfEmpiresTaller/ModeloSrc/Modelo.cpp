/*
 * Modelo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Modelo.h"

#include "../ModeloSrc/Mapa.h"

Modelo::Modelo() {
	// TODO Auto-generated constructor stub
	this->mapa = new Mapa(1,1);


}

Modelo::~Modelo() {
	// TODO Auto-generated destructor stub
	this->mapa->~Mapa();

}

