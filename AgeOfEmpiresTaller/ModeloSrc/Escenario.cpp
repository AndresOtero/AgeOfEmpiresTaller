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
	this->jugador = NULL;
	//this -> protagonista = new Personaje();
}
Escenario::Escenario(string nombre, int size_x, int size_y){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> protagonista = NULL;
	this->jugador = NULL;
}
Entidad* Escenario::getTexturaDefault(int num){
	string first = "img/extras/piso/";
	string last = ".png";
	string path = first + to_string(num) + last;
	ObjetoMapa* tipo = new ObjetoMapa("pasto",path);
	Entidad* entidad = new Entidad(tipo);
	return entidad;
}
Escenario::~Escenario() {
	for (unsigned int i= 0; i < entidades.size(); i++){
		Entidad* entidad = entidades[i];
		if(entidad!=NULL){
			delete entidad;
		}
	}
	if(this->protagonista){
	delete this-> protagonista;
	}
}

