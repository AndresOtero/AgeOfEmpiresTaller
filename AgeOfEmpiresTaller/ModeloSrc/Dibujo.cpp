/*
 * Dibujo.cpp
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */

#include "Dibujo.h"

Dibujo::Dibujo(dibujo_t tipo_de_dibujo) {
	// TODO Auto-generated constructor stub
	this->tipo_de_dibujo = tipo_de_dibujo;
	this->textura = new LTexture();
}

void Dibujo::set_cantidad_de_imagenes(size_t cant_de_imagenes) {
	if (cant_de_imagenes == 0) {
		return;
	}
	this->imagen_actual = 0;
	this->spriteClips = new SDL_Rect[cant_de_imagenes];
	this->cantidad_de_imagenes = cant_de_imagenes;
}

void Dibujo::set_imagen(size_t n_imagen, int x, int y, int ancho, int alto) {
	if (this->cantidad_de_imagenes <= n_imagen) {
		return;
	}
	this->spriteClips[n_imagen].x = x;
	this->spriteClips[n_imagen].y = y;
	this->spriteClips[n_imagen].w = ancho;
	this->spriteClips[n_imagen].h = alto;
}
void Dibujo::set_posicion_default(int x, int y){
	this->x_imagen=x;
	this->y_imagen=y;
}

void Dibujo::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen-(this->spriteClips->w)/2, this->y_imagen-(this->spriteClips->h)/2, &(this->spriteClips[this->imagen_actual%this->cantidad_de_imagenes]),renderer);

}

bool Dibujo::cargar_archivo(std::string path, SDL_Renderer* renderer) {
	return this->textura->loadFromFile(path, renderer);
}
dibujo_t Dibujo::dibujar() {
	// TODO Auto-generated destructor stub
	return this->tipo_de_dibujo;
}

Dibujo::~Dibujo() {
	// TODO Auto-generated destructor stub
	delete textura;

}
void Dibujo::set_velocidad(int velocidad) {
	this->velocidad = velocidad;
}
int Dibujo::get_x() {
	return this->x_imagen;
}
int Dibujo::get_y() {
	return this->y_imagen;
}
void Dibujo::cambiar_frame(){
	acumulador++;
	if((20/velocidad)<=acumulador){
		imagen_actual++;
		acumulador=0;
	}
}

void Dibujo::mover(int x, int y) {/**
	printf("X: %d\n", x);
	printf("x_imagen: %d\n", x_imagen);
**/	float delta_x = (double) (x - x_imagen);
	/**printf("Delta x: %f\n", delta_x);
	printf("Y: %d\n", y);
	printf("y_imagen: %d\n", y_imagen);**/
	float delta_y = (double) (y - y_imagen);
	//printf("Delta y: %f\n", delta_y);
	float distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
//		printf("Distancia: %f\n", distancia);
		float des_x = (velocidad * delta_x) / distancia;
	//	printf("desplazamiento x: %f\n", des_x);
		float des_y = (velocidad * delta_y) / distancia;
		//printf("desplazamiento y: %f\n", des_y);
		if ((sqrt(des_x * des_x) > distancia)
				&& (sqrt(des_y * des_y) < distancia)) {
			x_imagen = x;
		}
		if ((sqrt(des_y * des_y) > distancia)
				&& ((sqrt(des_x * des_x) < distancia))) {
			y_imagen = y;
		}
		x_imagen += des_x;
		y_imagen += des_y;
		this->cambiar_frame();

	}
}
//Move
/**
 if ((x != x_imagen) || (y != y_imagen)) {
 if (x == x_imagen) { //Si esta en el mismo eje x
 if (y > y_imagen) {
 y_imagen++;
 } else {
 y_imagen--;
 }
 } else if (y == y_imagen) { //Si esta en el mismo eje y
 if (x > x_imagen) {
 x_imagen++;
 } else {
 x_imagen--;
 }
 } else {
 if (x > x_imagen) { //Si esta en el mismo eje x
 x_imagen++;
 } else {
 x_imagen--;
 }
 y_imagen = (a * x_imagen + b);
 }
 }
 **/

