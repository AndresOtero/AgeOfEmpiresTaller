/*
 * Mapa.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Mapa.h"
#include "../ModeloSrc/Celda.h"

Mapa::Mapa(int largo, int ancho) {
	this->largo = largo;
	this->ancho = ancho;
	Celda*** celdas = new Celda**[ancho];
	for (int i = 0; i < ancho; ++i) {
		celdas[i] = new Celda*[largo];
	}
	for (int i = 0; i < ancho; ++i) {
		for (int j = 0; j < largo; ++j) {
			celdas[i][j] = new Celda();
		}
	}
	this->celdas=celdas;
}


bool Mapa::celdaOcupada(int largo, int ancho) {
	if ((largo >= this->largo) || (ancho >= this->ancho)) {
		return false;
	}
	return (this->celdas[largo][ancho]->estaOcupada());
}

Mapa::~Mapa() {
	int largo = this->largo;
	int ancho = this->ancho;
	Celda*** celdas = this->celdas;
	for (int i = 0; i < ancho; ++i) {
		for (int j = 0; j < largo; ++j) {
			delete celdas[i][j];
		}
	}
	for (int i = 0; i < ancho; ++i) {
			delete[] celdas[i] ;
	}
	delete[] celdas;

}
