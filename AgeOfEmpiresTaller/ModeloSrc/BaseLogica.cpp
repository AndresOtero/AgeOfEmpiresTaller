/*
 * BaseLogica.cpp
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#include "BaseLogica.h"

BaseLogica::BaseLogica() {
	this -> alto = 1;
	this -> ancho = 1;

}
BaseLogica::BaseLogica(int ancho, int alto){
	this -> alto = alto;
	this -> ancho = ancho;
}
BaseLogica::~BaseLogica() {

}

