/*
 * Recurso.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Recurso.h"
#include <random>
#include <iostream>


Recurso::Recurso(ObjetoMapa* objetoMapa): Entidad(objetoMapa) {
	GeneradorNumeros generador;
	cantidad = generador.numeroRandom(100,250);//random entre 100 y 250

}
Recurso::Recurso(ObjetoMapa* objetoMapa,int x , int y): Entidad( objetoMapa,x,y) {
	GeneradorNumeros generador;
	cantidad = generador.numeroRandom(100,250);//random entre 100 y 250
}

int Recurso::sacarRecurso(int cantidad){
	int saco;
	if (this->cantidad-cantidad < 0){
		saco = this->cantidad;
		this->cantidad = 0;
	}else{
		saco = cantidad;
		this->cantidad-=cantidad;
	}
	//printf("Saco %d de recurso\n",saco);
	return saco;
}
bool Recurso::seAcabo(){
	if (this->cantidad>0){
		return false;
	}
	return true;
}
int Recurso::obtenerRecurso(){
	return this->cantidad;
}
void Recurso::setRecurso(int cantidad){
	this->cantidad=cantidad;
}

Recurso::~Recurso() {
	// TODO Auto-generated destructor stub
}

