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

}
Escenario::Escenario(string nombre, int size_x, int size_y){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
}
Escenario::Escenario(string nombre, int size_x, int size_y, vector<Entidad> entidades){
	this -> nombre = nombre;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> entidades = entidades;
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
	//ObjetoMapa* tipo = new ObjetoMapa("protagonistaDefault",imagenes);
	//Entidad* entidad = new Entidad(tipo);
	return NULL;
}
Escenario::~Escenario() {
	delete this-> protagonista;
}

