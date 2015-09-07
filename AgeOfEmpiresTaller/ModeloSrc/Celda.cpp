/*
 * Celda.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Celda.h"
#include "../ModeloSrc/Dibujo.h"
#include <iostream>

Celda::Celda() {
	// TODO Auto-generated constructor stub
}
void Celda::setDibujo(Dibujo* dibujo){
	if(this->ocupada==true){
		this->dibujo->~Dibujo();
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
		this->dibujo->~Dibujo();
	}
}

