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
bool Entidad::estaADistancia(int rango, Posicion pos){
	int alto,ancho,x,y;
	alto = this->objetoMapa->baseLogica->alto;
	ancho = this->objetoMapa->baseLogica->ancho;
	Posicion temp1,temp2;
	//reviso si alguna fila de ancho esta en rango de la posicion
	for (x = 0; x <= (ancho); x++){
		temp1 = {this->posicion->getX()+x,this->posicion->getY()};
		temp2 = {this->posicion->getX()+x,posicion->getY()+alto};
		if (pos.distancia(temp1)<=rango || pos.distancia(temp2)<=rango) {
			return true;
		}
	}
	//reviso si alguna que no cheque esta en rango
	for (y = 1 ; y < (alto-1); y++){
		temp1 = {posicion->getX(),posicion->getY()+y};
		temp2 = {posicion->getX()+ancho,posicion->getY()+y};
		if (pos.distancia(temp1)<=rango || pos.distancia(temp2)<=rango){
			return true;
		}
	}
	return false;
}
Entidad::~Entidad() {
	delete posicion;
	if(this->objetoMapa==NULL){
		delete objetoMapa;
	}
}
