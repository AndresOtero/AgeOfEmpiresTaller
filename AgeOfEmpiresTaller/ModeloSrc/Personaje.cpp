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
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->objetoMapa->fps = 20; //FPS DEFAULT
	this->velocidad=1;
	this->objetoMapa->delay = 0; //delay default
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
}
Personaje::Personaje(ObjetoMapa* objetoMapa){
	this->referencia_mapa_x=1;
	this->referencia_mapa_y=1;
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->velocidad=1;
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
}
Personaje::Personaje(ObjetoMapa* objetoMapa, int x, int y){
	this->referencia_mapa_x=x;
	this->referencia_mapa_y=y;
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->velocidad=1;
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
}
dibujo_t Personaje::dibujar(){
	return dibujo;
}
string Personaje::mostrar_contenido(){
	return objetoMapa->nombre;
}

Posicion Personaje::get_posicion(){
	return Posicion(referencia_mapa_x,referencia_mapa_y);
}
void Personaje::set_destino(Posicion destino){
	this->destino=destino;
}
void Personaje::set_camino(Posicion camino){
	this->camino=camino;
}
Posicion Personaje::get_destino(){
	return destino;
}
void Personaje::mover() {
	double x = camino.get_x_exacta();
	double y = camino.get_y_exacta();
	double delta_x = (double) (x - referencia_mapa_x);
	double delta_y = (double) (y - referencia_mapa_y);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		if ((sqrt(delta_x * delta_x) > distancia)
				&& (sqrt(delta_x * delta_x) < distancia)) {

			this->referencia_mapa_x = x;
		}
		if ((sqrt(delta_y * delta_y) > distancia)
				&& ((sqrt(delta_y * delta_y) < distancia))) {
			this->referencia_mapa_y = y;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;

		this->referencia_mapa_x += des_x;
		this->referencia_mapa_y += des_y;
	}

}

Personaje::~Personaje() {
	delete recursos;
}

