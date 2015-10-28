/*
 * Jugador.cpp
 *
 *  Created on: 25 de oct. de 2015
 *      Author: andres
 */

#include "Jugador.h"

Jugador::Jugador(string nombre,string ip,Personaje* personaje) {
	// TODO Auto-generated constructor stub
	this->personaje=personaje;
	this->personaje->setNombreJugador(nombre);
	this->nombre=nombre;
	this->ip=ip;
}

Jugador::~Jugador() {
	// TODO Auto-generated destructor stub
}

