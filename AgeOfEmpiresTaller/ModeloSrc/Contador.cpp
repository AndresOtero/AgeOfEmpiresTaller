/*
 * Contador.cpp
 *
 *  Created on: 9 de nov. de 2015
 *      Author: andres
 */

#include "Contador.h"
#define DEFAULT 10
Contador::Contador() {
	// TODO Auto-generated constructor stub
	this->contador=DEFAULT;
	this->actual=0;
}
Contador::Contador(int n) {
	// TODO Auto-generated constructor stub
	this->contador=n;
	this->actual=0;
}
bool Contador::contar() {
	// TODO Auto-generated constructor stub
	actual++;
	if(actual==contador){
		actual=0;
		return true;
	}
	return false;
}

Contador::~Contador() {
	// TODO Auto-generated destructor stub
}

