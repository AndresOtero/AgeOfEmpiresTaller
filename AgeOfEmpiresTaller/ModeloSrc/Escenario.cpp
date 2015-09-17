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
	vector<string> imagenes;
	imagenes.push_back("../img/foo.png");
	ObjetoMapaAnimado* tipo = new ObjetoMapaAnimado("protagonistaDefault",imagenes);
	this -> protagonista = new EntidadAnimada(tipo);
}
Escenario::Escenario(string nombre, int size_x, int size_y){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	vector<string> imagenes;
	imagenes.push_back("../img/foo.png");
	ObjetoMapaAnimado* tipo = new ObjetoMapaAnimado("protagonistaDefault",imagenes);
	this -> protagonista = new EntidadAnimada(tipo);
}
Escenario::Escenario(string nombre, int size_x, int size_y, vector<Entidad> entidades){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> entidades = entidades;
	vector<string> imagenes;
	imagenes.push_back("../img/foo.png");
	ObjetoMapaAnimado* tipo = new ObjetoMapaAnimado("protagonistaDefault",imagenes);
	this -> protagonista = new EntidadAnimada(tipo);
}
Escenario::Escenario(string nombre, int size_x, int size_y, vector<Entidad> entidades, EntidadAnimada* protagonista ){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> entidades = entidades;
	this -> protagonista = protagonista;
}
Entidad* Escenario::getTexturaDefault(){
	vector<string> imagenes;
	imagenes.push_back("../img/Sprites/grass_and_water/grass_and_water_0.png");
	ObjetoMapa* tipo = new ObjetoMapa("protagonistaDefault",imagenes);
	Entidad* entidad = new Entidad(tipo);
	return entidad;
}
Escenario::~Escenario() {
	delete this-> protagonista;
}

