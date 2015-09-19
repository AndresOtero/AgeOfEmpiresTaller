/*
 * DibujoPersonaje.cpp
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#include "DibujoPersonaje.h"
#include  "LTexture.h"
DibujoPersonaje::DibujoPersonaje() {
	// TODO Auto-generated constructor stub
	this -> velocidad = 0;
}

void DibujoPersonaje::set_cantidad_de_movimientos(size_t cant_de_mov){
	if(cant_de_mov>CANTIDAD_DE_MOVIMIENTOS){
		//Error
	}
	this->spriteClips=vector<SDL_Rect*>(cant_de_mov,NULL);
	this->cantidad_de_imagenes=vector<size_t>(cant_de_mov,0);
	this->cant_mov=cant_mov;
}
void DibujoPersonaje::set_cantidad_de_imagenes(size_t n_mov,size_t cant_de_imagenes) {
	if(n_mov>=cant_mov){
		return;
	}
	if (cant_de_imagenes == 0) {
		return;
	}
	this->imagen_actual = 0;
	this->movimiento_actual=0;
	this->spriteClips[n_mov] = new SDL_Rect[cant_de_imagenes];
	this->cantidad_de_imagenes[n_mov] = cant_de_imagenes;
}

void DibujoPersonaje::set_imagen(size_t n_mov,size_t n_imagen, int x, int y, int ancho, int alto) {
	if (this->cantidad_de_imagenes[n_mov] <= n_imagen) {
		return;
	}
	this->spriteClips[n_mov][n_imagen].x = x;
	this->spriteClips[n_mov][n_imagen].y = y;
	this->spriteClips[n_mov][n_imagen].w = ancho;
	this->spriteClips[n_mov][n_imagen].h = alto;
}
void DibujoPersonaje::set_velocidad(int velocidad){
	this->velocidad=velocidad;
}
void DibujoPersonaje::elegir_frame(double des_x,double des_y) {
	if((des_x>0)&&(des_y==0)){
		movimiento_actual=DERECHA;
		//printf("DERECHA\n");
		//DERECHA
	}
	if((des_x<0)&&(des_y==0)){
		movimiento_actual=IZQUIERDA;
		//printf("IZQUIERDA\n");
		//IZQUIERDA
	}
	if((des_x==0)&&(des_y<0)){
		movimiento_actual=ARRIBA;
		//printf("ARRIBA\n");
		//ARRIBA
	}
	if((des_x==0)&&(des_y>0)){
		movimiento_actual=ABAJO;
		//printf("ABAJO\n");
		//ABAJO
	}
	if((des_x>0)&&(des_y<0)){
		movimiento_actual=DIAGONAL_DERECHA_ARRIBA;
		//printf("ARRIBA_DERECHA\n");
		//ARRIBA_DERECHA
	}
	if((des_x>0)&&(des_y>0)){
		movimiento_actual=DIAGONAL_DERECHA_ABAJO;
		//printf("ABAJO_DERECHA\n");
		//ABAJO_DERECHA
	}
	if((des_x<0)&&(des_y<0)){
		movimiento_actual=DIAGONAL_IZQUIERDA_ARRIBA;
		//printf("ARRIBA_IZQUIERDA\n");
		//ARRIBA_IZQUIERDA
	}
	if((des_x<0)&&(des_y>0)){
		movimiento_actual=DIAGONAL_IZQUIERDA_ABAJO;
		//printf("ABAJO_IZQUIERDA\n");
		//ABAJO_IZQUIERDA
	}
}
int DibujoPersonaje::get_alto(int n_mov,int n_imagen){
	return spriteClips[n_mov][n_imagen].h;
}

int DibujoPersonaje::get_alto(){
	return get_alto(movimiento_actual,imagen_actual);
}

int DibujoPersonaje::get_ancho(int n_mov,int n_imagen){
	return spriteClips[n_mov][n_imagen].w;
}

int DibujoPersonaje::get_ancho(){
	return get_ancho(movimiento_actual,imagen_actual);
}
void DibujoPersonaje::render( SDL_Renderer* renderer) {
	this->textura->render(this->x_imagen, this->y_imagen , &(this->spriteClips[movimiento_actual%cant_mov][this->imagen_actual%this->cantidad_de_imagenes[movimiento_actual]]),renderer);
}

void DibujoPersonaje::mover(int x, int y) {
	double delta_x = (double) (x - x_imagen);
	double delta_y = (double) (y - y_imagen);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;
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
		this->elegir_frame(des_x,des_y);
		this->cambiar_frame();
	}
}

DibujoPersonaje::~DibujoPersonaje() {
	// TODO Auto-generated destructor stub
}

