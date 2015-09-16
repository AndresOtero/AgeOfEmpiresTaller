/*
 * FactoryDibujo.cpp
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */

#include "FactoryDibujo.h"
#define DIBUJOS_POR_DEFAULT 3

FactoryDibujo::FactoryDibujo() {
	// TODO Auto-generated constructor stub
	this->dibujos=vector<Dibujo*>(DIBUJOS_POR_DEFAULT);
	this->cantidad_de_dibujos=this->dibujos.size();
	this->dibujo_actual=0;
}
size_t FactoryDibujo::set_dibujo(Dibujo* dibujo){
	if(this->dibujos.capacity()==dibujo_actual){
		this->dibujos.resize(this->dibujos.capacity()*2,NULL);
	}
	this->dibujos.insert(this->dibujos.begin()+dibujo_actual,dibujo);
	dibujo_actual++;
	return (dibujo_actual-1);
}

Dibujo* FactoryDibujo::get_dibujo(size_t n_dibujo){
	if(n_dibujo>=this->dibujo_actual){
		return NULL;
	}
	return this->dibujos[n_dibujo];
}


FactoryDibujo::~FactoryDibujo() {

}

