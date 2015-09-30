/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"



Personaje::Personaje(){
	this->objetoMapa = new ObjetoMapa("protagonistaDefault", "img/protagonista/spartan_small.png");
	this->referencia_mapa_x=5;
	this->referencia_mapa_y=2;
	this->objetoMapa->fps = 20; //FPS DEFAULT
	this->velocidad=1;
	this->objetoMapa->delay = 0; //delay default
	this->dibujo = 0;
}
Personaje::Personaje(ObjetoMapa* objetoMapa){
	this->referencia_mapa_x=1;
	this->referencia_mapa_y=1;
	this->velocidad=1;
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
}
Personaje::Personaje(ObjetoMapa* objetoMapa, int x, int y){
	this->referencia_mapa_x=x;
	this->referencia_mapa_y=y;
	this->velocidad=1;
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
}
dibujo_t Personaje::dibujar(){
	return dibujo;
}
Posicion Personaje::calcular_camino(double x,double y){
	Posicion adonde_voy=Posicion(x,y);
	return adonde_voy;
}

void Personaje::mover(double x, double y) {
	Posicion adonde_voy=calcular_camino(x,y);
	double delta_x = (double) (adonde_voy.get_x_exacta() - referencia_mapa_x);
	double delta_y = (double) (adonde_voy.get_y_exacta() - referencia_mapa_y);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		if ((sqrt(delta_x * delta_x) > distancia)
				&& (sqrt(delta_x * delta_x) < distancia)) {
			this->referencia_mapa_x = adonde_voy.get_x_exacta();
		}
		if ((sqrt(delta_y * delta_y) > distancia)
				&& ((sqrt(delta_y * delta_y) < distancia))) {
			this->referencia_mapa_y = adonde_voy.get_y_exacta();
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;

		this->referencia_mapa_x += des_x;
		this->referencia_mapa_y += des_y;
	}

}

Personaje::~Personaje() {

}

