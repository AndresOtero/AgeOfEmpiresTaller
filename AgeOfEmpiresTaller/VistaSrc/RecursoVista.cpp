/*
 * RecursoVista.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: tobias
 */

#include "RecursoVista.h"

RecursoVista::RecursoVista() {
	shared_ptr<Textura> text(new Textura());
	this->text=text;
	shared_ptr<Textura> img(new Textura());
	this->img=img;
	this->cant=0;

}
void RecursoVista::cambiarCant(int cant){
	this->cant=cant;
}
int RecursoVista::cantidad(){
	return cant;
}
shared_ptr<Textura> RecursoVista::texto(){
	return this->text;
}

shared_ptr<Textura> RecursoVista::imagen(){
	return this->img;
}

RecursoVista::~RecursoVista() {
	// TODO Auto-generated destructor stub
}

