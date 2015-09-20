/*
 * Juego.cpp
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#include "Juego.h"

Juego::Juego() {
	this -> pantalla = new Pantalla();
	this -> conf = new Configuracion();
	this -> escenario = new Escenario();
}
Juego::Juego(Pantalla* pantalla, Configuracion* conf, Escenario* escenario, std::map<std::string, ObjetoMapa*> &tipos ){
	this -> pantalla = pantalla;
	this -> conf = conf;
	this -> escenario = escenario;
	this->tipos = tipos;
}
Juego::~Juego() {
	// TODO Auto-generated destructor stub
}

