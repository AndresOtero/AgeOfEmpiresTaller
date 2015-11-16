/*
 * Dibujo.cpp
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */

#include "DibujoEstatico.h"
#define RESET 255

Dibujo_Estatico::Dibujo_Estatico() {
	shared_ptr <Textura> text(new Textura());
	this->textura = text;
	this -> acumulador = 0;
	this->fps=1;
	pixel_x=0;
	pixel_y=0;
}
void Dibujo_Estatico::iluminar(){
	Uint8 alpha=127;
	this->textura->setAlpha(alpha);
}


void Dibujo_Estatico::oscurecer(){
	this->textura->oscurecer();
}

void Dibujo_Estatico::reiniciar(){
	this->textura->reiniciar();
}

void Dibujo_Estatico::ponerRojo(){
	this->textura->setColor(255,0,0);
}
void Dibujo_Estatico::ponerVerde(){
	this->textura->setColor(0,255,0);
}
void Dibujo_Estatico::ponerAmarillo(){
	this->textura->setColor(255,255,0);
}

void Dibujo_Estatico::resetear(){
	this->textura->setAlpha(RESET);
}
void Dibujo_Estatico::set_imagen( int x, int y) {
	this->spriteClips.x = x;
	this->spriteClips.y = y;
}
void Dibujo_Estatico::set_posicion_default(int x, int y){
	this->x_imagen=x;
	this->y_imagen=y;
}
void Dibujo_Estatico::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen+pixel_x, this->y_imagen-pixel_y
			,NULL,renderer);
}
bool Dibujo_Estatico::cargar_archivo(std::string path, SDL_Renderer* renderer) {
	bool textBool = this->textura->loadFromFile(path, renderer);
	this ->spriteClips.h = this->textura->getHeight();
	this -> spriteClips.w = this -> textura->getWidth();
	return textBool;
}
void Dibujo_Estatico::setPixeles(int x, int y){
	this->pixel_x= x;
	this->pixel_y = y;
}
Dibujo_Estatico::~Dibujo_Estatico() {
}

int Dibujo_Estatico::get_x() {
	return this->x_imagen;
}
int Dibujo_Estatico::get_y() {
	return this->y_imagen;
}

int Dibujo_Estatico::get_alto(){
	return spriteClips.h;
}

int Dibujo_Estatico::get_ancho(){
	return spriteClips.w;
}




