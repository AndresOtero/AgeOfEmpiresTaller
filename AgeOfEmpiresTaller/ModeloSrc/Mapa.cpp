/*
 * Mapa.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "Mapa.h"
#include "Celda.h"
#include <iostream>

Mapa::Mapa(int ancho, int largo) {
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

Celda* Mapa::getCelda(int x,int y){
	return this->celdas[x][y];
}
void Mapa::setTiles(dibujo_t dibujo,int x,int y){
	this->getCelda(x,y)->setTiles(dibujo);
}
void Mapa::setEscenario(dibujo_t dibujo,int x,int y){
	this->getCelda(x,y)->setEscenario(dibujo);
}
bool Mapa::celdaOcupada(int x, int y) {
	Celda* celda=this->getCelda(x,y);
	if (celda==NULL) {
		return false;
	}
	return (celda->estaOcupada());
}
dibujo_t Mapa::dibujarEscenario(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho)||(y <0)||(x <0)) {
		return AFUERA;
	}
	return this->getCelda(x,y)->dibujarEscenario();

}
dibujo_t Mapa::dibujarTiles(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho)||(y <0)||(x <0)) {
		return AFUERA;
	}
	return this->getCelda(x,y)->dibujarTiles();

}

int Mapa::getAncho(){
	return this->ancho;
}
int Mapa::getLargo(){
	return this->largo;
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
