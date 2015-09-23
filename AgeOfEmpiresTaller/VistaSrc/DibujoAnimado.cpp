/*
 * DibujoAnimado.cpp
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#include "DibujoAnimado.h"

DibujoAnimado::DibujoAnimado() {
	// TODO Auto-generated constructor stub
	this -> acumulador = 0;
	this->fps=1;
	this->spriteClips=NULL;
}

void DibujoAnimado::set_cantidad_de_imagenes(int cant_de_imagenes) {
	if (cant_de_imagenes == 0) {
		return;
	}
	this->imagen_actual = 0;
	this->spriteClips = new SDL_Rect[cant_de_imagenes];
	this->cantidad_de_imagenes = cant_de_imagenes;
}

void DibujoAnimado::set_imagen(int n_imagen, int x, int y,int h, int w) {
	if (this->cantidad_de_imagenes <= n_imagen) {
		return;
	}
	this->spriteClips[n_imagen].x = x;
	this->spriteClips[n_imagen].y = y;
	this->spriteClips[n_imagen].w = w / 5 ;
	this->spriteClips[n_imagen].h = h ;
}

void DibujoAnimado::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen, this->y_imagen, &(this->spriteClips[this->imagen_actual%this->cantidad_de_imagenes]),renderer);
	this->cambiar_frame();
}


void DibujoAnimado::set_fps(int fps) {
	this->fps = fps;
}

void DibujoAnimado::cambiar_frame(){
	acumulador++;
	if((fps)<=acumulador){
		imagen_actual++;
		acumulador=0;
	}

}

int DibujoAnimado::get_alto(int n_imagen){
	return spriteClips[n_imagen].h;
}

int DibujoAnimado::get_alto(){
	return get_alto(imagen_actual);
}

int DibujoAnimado::get_ancho(int n_imagen){
	return spriteClips[n_imagen].w;
}

int DibujoAnimado::get_ancho(){
	return get_ancho(imagen_actual);
}

DibujoAnimado::~DibujoAnimado() {
	// TODO Auto-generated destructor stub
	if(spriteClips!=NULL){
			delete[] spriteClips;
		}
}

