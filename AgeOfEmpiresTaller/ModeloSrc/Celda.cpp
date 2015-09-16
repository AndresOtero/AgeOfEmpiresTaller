/*
 * Celda.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Celda.h"
#include <iostream>
#include "../VistaSrc/Dibujo.h"

Celda::Celda() {
	this -> dibujo = DEFAULT;
	this -> ocupada = false;
}
void Celda::setDibujo(dibujo_t dibujo){
	this->ocupada=true;
	this->dibujo=dibujo;
}
dibujo_t Celda::dibujar(){
	return this->dibujo;
}
bool Celda::estaOcupada(){
	return this->ocupada;
}
Celda::~Celda() {
	// TODO Auto-generated destructor stub
	if(this->dibujo!=NULL){
		delete this->dibujo;
	}
}

