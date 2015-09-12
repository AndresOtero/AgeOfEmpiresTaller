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
	this -> dibujo = NULL;
	this -> ocupada = false;
}
void Celda::setDibujo(Dibujo* dibujo){
	if(this->ocupada==true){
		delete this->dibujo;
	}else{
		this->ocupada=true;
	}
	this->dibujo=dibujo;
}
dibujo_t Celda::dibujar(){
	return this->dibujo->dibujar();
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
