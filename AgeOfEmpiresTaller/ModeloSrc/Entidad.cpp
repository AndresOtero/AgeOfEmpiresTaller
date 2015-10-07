/*
 * Entidad.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Entidad.h"
using namespace std;
Entidad::Entidad(ObjetoMapa* objetoMapa) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion();
}
Entidad::Entidad(ObjetoMapa* objetoMapa, int x, int y) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion(x, y);
}
void Entidad::mostrar_contenido() {
	printf("%s\n",objetoMapa->nombre.c_str());

}
Entidad::~Entidad() {
	delete posicion;
	if(this->objetoMapa==NULL){
		delete objetoMapa;
	}
}

