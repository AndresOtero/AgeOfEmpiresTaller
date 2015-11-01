/*
 * RecursosJugador.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "RecursosJugador.h"

RecursosJugador::RecursosJugador() {
	this->oro = 0;
	this->madera = 0;
	this->piedra = 0;
}

int validarRecurso(int cant){
	if (cant>=0)
		return cant;
	//avisar por log que no estan bien los parametros
	return 0;
}

RecursosJugador::RecursosJugador(int oro, int madera, int piedra) {
	//carga de todas formas los parametros
	this->oro = validarRecurso(oro);
	this->madera = validarRecurso(madera);
	this->piedra = validarRecurso(piedra);
}

void RecursosJugador::reset(){
	this->oro= 0;
	this->madera= 0;
	this->piedra = 0;
}
void RecursosJugador::colectarOro(int cant){
	this->oro+=cant;
}
void RecursosJugador::colectarMadera(int cant){
	this->madera+=cant;
}
void RecursosJugador::colectarPiedra(int cant){
	this->piedra+=cant;
}

int RecursosJugador::cantOro(){
	return this->oro;
}
int RecursosJugador::cantPiedra(){
	return this->piedra;
}

int RecursosJugador::cantMadera(){
	return this->madera;
}


RecursosJugador::~RecursosJugador() {
	// TODO Auto-generated destructor stub
}

