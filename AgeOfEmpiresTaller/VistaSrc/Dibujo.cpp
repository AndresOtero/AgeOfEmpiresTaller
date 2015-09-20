/*
 * Dibujo.cpp
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */

#include "../VistaSrc/Dibujo.h"


Dibujo::Dibujo() {
	// TODO Auto-generated constructor stub
	shared_ptr <LTexture> text(new LTexture());
	this->textura = text;
	this -> acumulador = 0;
	this->fps=1;
}


void Dibujo::set_imagen( int x, int y, int ancho, int alto) {
	this->spriteClips.x = x;
	this->spriteClips.y = y;
	this->spriteClips.w = ancho;
	this->spriteClips.h = alto;
}
void Dibujo::set_posicion_default(int x, int y){
	this->x_imagen=x;
	this->y_imagen=y;
}

void Dibujo::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen, this->y_imagen, &(this->spriteClips),renderer);
}

bool Dibujo::cargar_archivo(std::string path, SDL_Renderer* renderer) {
	return this->textura->loadFromFile(path, renderer);
}

Dibujo::~Dibujo() {
	// TODO Auto-generated destructor stub


}

int Dibujo::get_x() {
	return this->x_imagen;
}
int Dibujo::get_y() {
	return this->y_imagen;
}

int Dibujo::get_alto(){
	return spriteClips.h;
}

int Dibujo::get_ancho(){
	return spriteClips.w;
}




