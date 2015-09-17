/*
 * ObjetoMapaAnimado.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "ObjetoMapaAnimado.h"

ObjetoMapaAnimado::ObjetoMapaAnimado(string nombre, vector <string>  imagenes) : ObjetoMapa(nombre, imagenes){
	this -> fps = 1;
	this -> delay = 0;
}
ObjetoMapaAnimado::ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int fps) : ObjetoMapa(nombre, imagenes){
	this -> fps = fps;
	this -> delay = 0;
}
ObjetoMapaAnimado::ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int fps, int delay): ObjetoMapa(nombre, imagenes){
	this -> fps = fps;
	this -> delay = delay;
}

ObjetoMapaAnimado::ObjetoMapaAnimado(string nombre,vector <string>  imagenes, int ancho_base, int alto_base, int fps, int delay ) : ObjetoMapa(nombre, imagenes, ancho_base, alto_base){
	this -> fps = fps;
	this -> delay = delay;
}

ObjetoMapaAnimado::ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int ancho_base, int alto_base, int pixel_ref_x, int pixel_ref_y, int fps, int delay ): ObjetoMapa(nombre,imagenes,ancho_base, alto_base,pixel_ref_x, pixel_ref_y){
	this -> fps = fps;
	this -> delay = delay;
}
ObjetoMapaAnimado::ObjetoMapaAnimado::~ObjetoMapaAnimado() {
}

