/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"


Personaje::Personaje(){
	this->posicion= new Posicion(); //crea posicion default (0,0)
	this->objetoMapa = new ObjetoMapa("protagonistaDefault", "img/protagonista/spartan.png");
	this->objetoMapa->fps = 4; //FPS DEFAULT
	this->objetoMapa->delay = 0; //delay default
	this->dibujo = 0;
}
Personaje::Personaje(ObjetoMapa* objetoMapa, int x, int y){
	this->posicion= new Posicion(x,y);
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
}
dibujo_t Personaje::dibujar(){
	return dibujo;
}
void Personaje::mover(int x,int y){
	this->posicion->x=x;
	this->posicion->y=y;
}
Personaje::~Personaje() {
	delete this->objetoMapa;
	delete this->posicion;
}

