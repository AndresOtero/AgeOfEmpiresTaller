/*
 * ObjetoMapa.cpp
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#include "ObjetoMapa.h"
ObjetoMapa::ObjetoMapa(string nombre, string imagen) {
	this->nombre = nombre;
	this->imagen = imagen;
	this->delay = 0;
	this->fps = 0;
	this->velocidad = 0;
	this->fuerza = 0;
	this->armadura = 0;
	this->recoleccion = 0;
	this->construccion = 0;
	this->vida=0;
	this->baseLogica = new BaseLogica();
	this->pixelsReferencia = new PixelsReferencia();
}
ObjetoMapa::~ObjetoMapa() {
	delete this -> baseLogica;
	delete this -> pixelsReferencia;
}

