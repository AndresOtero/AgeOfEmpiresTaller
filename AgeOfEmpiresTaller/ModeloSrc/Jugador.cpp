/*
 * Jugador.cpp
 *
 *  Created on: 25 de oct. de 2015
 *      Author: andres
 */

#include "Jugador.h"

Jugador::Jugador(string nombre,string ip,string raza) {
	// TODO Auto-generated constructor stub
	printf("crea jugador\n");
	this->raza=raza;
	this->nombre=nombre;
	this->ip=ip;
	this->recursos = new RecursosJugador(200,200,200,200);
	this->factory.setRaza(raza);

}
void Jugador::cargarEdificios(map<string,ObjetoMapa*> tipos){
	this->factory.cargarEdificios(tipos);
}

map<string,ObjetoMapa*> Jugador::devolverEdificiosCreables(){
	return this->factory.devolverTipos();
}
void Jugador::actualizarRecursos(int oro, int madera, int piedra){
	this->recursos->colectarOro(oro);
	this->recursos->colectarMadera(madera);
	this->recursos->colectarPiedra(piedra);
}
void Jugador::pagar(Entidad * entidad){
	this->recursos->pagar(entidad->getCosto());
}
bool Jugador::puedePagar(Entidad * entidad){
	return this->recursos->puedePagar(entidad->getCosto());
}

Jugador::~Jugador() {
	delete this->recursos;
}

