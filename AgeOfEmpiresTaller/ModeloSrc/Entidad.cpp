/*
 * Entidad.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Entidad.h"
#include "Recurso.h"
using namespace std;
int GeneradorNumeros::id =0;

Entidad::Entidad(ObjetoMapa* objetoMapa) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion();
	GeneradorNumeros generar;
	this->id = generar.otroID();
}
Entidad::Entidad(ObjetoMapa* objetoMapa, int x, int y) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion(x, y);
	GeneradorNumeros generar;
	this->id = generar.otroID();
}
bool Entidad::esUnRecurso(){
	if (Recurso* rec = dynamic_cast<Recurso*>(this)){
		return true;
	}
	return false;
}
string Entidad::mostrar_contenido() {
	return objetoMapa->nombre;

}
Entidad::~Entidad() {
	delete posicion;
	if(this->objetoMapa==NULL){
		delete objetoMapa;
	}
}

