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
	this->delay=1;
	pixel_x=0;
	pixel_y=0;
	gettimeofday(&estado,NULL);
}



void DibujoAnimado::set_cantidad_de_imagenes(int cant_de_imagenes) {
	if (cant_de_imagenes == 0) {
		return;
	}
	this->imagen_actual = 0;
	this->spriteClips = new SDL_Rect[cant_de_imagenes];
	this->cantidad_de_imagenes = cant_de_imagenes;
	this->termino_animacion = cant_de_imagenes;
}

void DibujoAnimado::set_imagen(unsigned int n_imagen, int x, int y,int h, int w) {
	if (this->cantidad_de_imagenes <= n_imagen) {
		return;
	}
	this->spriteClips[n_imagen].x = x;
	this->spriteClips[n_imagen].y = y;
	this->spriteClips[n_imagen].w = w / 5 ;
	this->spriteClips[n_imagen].h = h ;
}

void DibujoAnimado::setPixeles(int x, int y){
	this->pixel_x = x;
	this->pixel_y =y;
}
void DibujoAnimado::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen+pixel_x, this->y_imagen-pixel_y, &(this->spriteClips[this->imagen_actual%this->cantidad_de_imagenes]),renderer);
	if(this->animado)
		this->cambiar_frame();
}


void DibujoAnimado::set_fps(int fps) {
	this->fps = fps;
}
void DibujoAnimado::set_delay(double delay){
	this->delay = delay/100.0;
}

void DibujoAnimado::cambiar_frame(){
	struct timeval actual;
	gettimeofday(&actual,NULL);
	double ti = estado.tv_sec+(estado.tv_usec/1000000.0);
	double tf = actual.tv_sec+(actual.tv_usec/1000000.0);
	double tiempo = tf - ti;
	if ( tiempo > delay){
		acumulador++;
		if((50/fps)<=acumulador){
			imagen_actual++;
			acumulador=0;
			termino_animacion -= 1;
		}
		if (termino_animacion == 0){
			gettimeofday(&estado,NULL);
			termino_animacion = this->cantidad_de_imagenes;
		}
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

