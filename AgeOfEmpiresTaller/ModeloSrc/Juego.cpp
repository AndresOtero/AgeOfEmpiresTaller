/*
 * Juego.cpp
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#include "Juego.h"

Juego::Juego() {
	//configuracion default
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
	delete this->pantalla;
	delete this->conf;

	std::map<std::string, ObjetoMapa*> ::iterator it;
	for ( it = this->tipos.begin(); it !=this->tipos.end(); it++ ){
		delete it->second;
	}
	delete this-> escenario;
}

