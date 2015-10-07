/*
 * Celda.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Celda.h"
#include <iostream>
#include "../VistaSrc/Dibujo.h"
#define VACIO 0
Celda::Celda() {
	this -> escenario = DEFAULT;
	this -> tiles = DEFAULT;
	this -> ocupada = false;
	this->entidad = NULL;
}
void Celda::setEscenario(dibujo_t dibujo_n){

	this->escenario=dibujo_n;
}
void Celda::setTiles(dibujo_t dibujo_n){
	this->tiles=dibujo_n;
}
dibujo_t Celda::dibujarTiles(){
	return this->tiles;
}
dibujo_t Celda::dibujarEscenario(){
	return this->escenario;
}

bool Celda::estaOcupada(){
	if (this->entidad!=NULL)
		return true;
	return false;
}
void Celda::ocuparCelda(Entidad * entidad){
	this->entidad=entidad;
}
void Celda::mostrar_contenido(){
	if (this->entidad!=NULL){
		this->entidad->mostrar_contenido();
	}

}
Celda::~Celda() {
	// TODO Auto-generated destructor stub

}

