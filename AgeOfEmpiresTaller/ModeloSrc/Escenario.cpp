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
	this -> size_y = size_y;
	this -> protagonista = NULL;
	//hacer protagonista default

}
Escenario::Escenario(string nombre, int size_x, int size_y){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> protagonista = NULL;
}
Entidad* Escenario::getTexturaDefault(){
	vector<string> imagenes;
	imagenes.push_back("../img/Sprites/grass_and_water/grass_and_water_0.png");
	//ObjetoMapa* tipo = new ObjetoMapa("protagonistaDefault",imagenes);
	//Entidad* entidad = new Entidad(tipo);
	return NULL;
}
Escenario::~Escenario() {
	delete this-> protagonista;
}

