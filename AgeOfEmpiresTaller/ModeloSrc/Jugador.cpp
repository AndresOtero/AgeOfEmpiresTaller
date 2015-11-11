/*
 * Jugador.cpp
 *
 *  Created on: 25 de oct. de 2015
 *      Author: andres
 */

#include "Jugador.h"

Jugador::Jugador(string nombre,string ip,string raza) {
	// TODO Auto-generated constructor stub
	this->raza=raza;
	this->nombre=nombre;
	this->ip=ip;
	this->recursos = new RecursosJugador();
	this->factory= FactoryEdificio();
}

void Jugador::actualizarRecursos(int oro, int madera, int piedra){
	this->recursos->colectarOro(oro);
	this->recursos->colectarMadera(madera);
	this->recursos->colectarPiedra(piedra);
}

Jugador::~Jugador() {
	delete this->recursos;
}

