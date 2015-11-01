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
	this->recursos = new RecursosJugador();
}

void Jugador::actualizarRecursos(int oro, int madera, int piedra){
	this->recursos->colectarOro(oro);
	this->recursos->colectarMadera(madera);
	this->recursos->colectarPiedra(piedra);
}

Jugador::~Jugador() {
	delete this->recursos;
}

