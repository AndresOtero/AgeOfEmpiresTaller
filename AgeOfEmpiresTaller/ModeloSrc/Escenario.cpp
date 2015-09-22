/*
 * Escenario.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Escenario.h"

Escenario::Escenario() {
	this -> nombre = "default";
	this -> size_x = 100;
	this -> size_y = 100;

	ObjetoMapa* objeto = new ObjetoMapa("protagonistaDefault","img/protagonista/spartan.png");
	objeto->fps = 10;
	EntidadAnimada* protagonista = new EntidadAnimada(objeto);
	this -> protagonista =  protagonista;
}
Escenario::Escenario(string nombre, int size_x, int size_y){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> protagonista = NULL;
}
Entidad* Escenario::getTexturaDefault(){
	ObjetoMapa* tipo = new ObjetoMapa("pasto","img/pasto.png");
	Entidad* entidad = new Entidad(tipo);
	return entidad;
}
Escenario::~Escenario() {
	delete this-> protagonista;
}

