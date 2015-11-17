/*
 * dibujoPiso.cpp
 *
 *  Created on: 16/11/2015
 *      Author: ger
 */

#include "dibujoPiso.h"

namespace std {

#define RESET 255

dibujoPiso::dibujoPiso() {
	shared_ptr <Textura> text(new Textura());
	this->textura = text;
	this -> acumulador = 0;
}
void dibujoPiso::iluminar(){
	Uint8 alpha=127;
	this->textura->setAlpha(alpha);
}

void dibujoPiso::oscurecer(){
	this->textura->oscurecer();
}

void dibujoPiso::reiniciar(){
	this->textura->reiniciar();
}

void dibujoPiso::ponerRojo(){
	this->textura->setColor(255,0,0);
}
void dibujoPiso::ponerVerde(){
	this->textura->setColor(0,255,0);
}
void dibujoPiso::ponerAmarillo(){
	this->textura->setColor(255,255,0);
}

void dibujoPiso::resetear(){
	this->textura->setAlpha(RESET);
}
void dibujoPiso::set_imagen( int x, int y) {
	this->spriteClips.x = x;
	this->spriteClips.y = y;
}

void dibujoPiso::set_posicion_default(int x, int y){
	this->x_imagen=x;
	this->y_imagen=y;
}
void dibujoPiso::render( SDL_Renderer* renderer) {
	this->textura->render((this->x_imagen+this->spriteClips.x / 10 * this->acumulador)  , (this->y_imagen-this->spriteClips.y / 10  * this->acumulador)
			,NULL,renderer);

	if (this->acumulador == 9){
		this->acumulador = 0;
	}else{
		this->acumulador++;
	}
}

dibujoPiso::~dibujoPiso() {
}

int dibujoPiso::get_x() {
	return this->x_imagen;
}
int dibujoPiso::get_y() {
	return this->y_imagen;
}

int dibujoPiso::get_alto(){
	return spriteClips.h / 10;
}

int dibujoPiso::get_ancho(){
	return spriteClips.w / 10;
}


} /* namespace std */
