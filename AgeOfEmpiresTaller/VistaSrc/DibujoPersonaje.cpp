/*
 * DibujoPersonaje.cpp
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#include "DibujoPersonaje.h"
#include  "Textura.h"
DibujoPersonaje::DibujoPersonaje() {
	// TODO Auto-generated constructor stub
	this->imagen_actual = 0;
	this->movimiento_actual=0;
	this->acumulador=0;
	this->fps=1;
	pixel_x=0;
	pixel_y=0;
}
void DibujoPersonaje::congelar(){
	this->textura->congelar();
}
void DibujoPersonaje::setFps(int fps){
	this->fps = fps;
}
void DibujoPersonaje::setPixeles(int x, int y){
	this->pixel_x = x;
	this->pixel_y = y;
}
void DibujoPersonaje::descongelar(){
	this->textura->descongelar();
}
void DibujoPersonaje::set_cantidad_de_movimientos(int cant_de_mov){
	if(cant_de_mov>CANTIDAD_DE_MOVIMIENTOS){
		//Error
	}
	this->spriteClips=vector<SDL_Rect*>(cant_de_mov,NULL);
	this->cantidad_de_imagenes=vector<int>(cant_de_mov,0);
	this->cant_mov=cant_de_mov;
}
void DibujoPersonaje::set_cantidad_de_imagenes(int n_mov,int cant_de_imagenes) {
	if(n_mov>=cant_mov){
		return;
	}
	if (cant_de_imagenes == 0) {
		return;
	}
	this->spriteClips[n_mov] = new SDL_Rect[cant_de_imagenes];
	this->cantidad_de_imagenes[n_mov] = cant_de_imagenes;
}

void DibujoPersonaje::set_imagen(int n_mov,int n_imagen, int x, int y, int ancho, int alto) {
	if (this->cantidad_de_imagenes[n_mov] <= n_imagen) {
		return;
	}
	this->spriteClips[n_mov][n_imagen].x = x;
	this->spriteClips[n_mov][n_imagen].y = y;
	this->spriteClips[n_mov][n_imagen].w = ancho;
	this->spriteClips[n_mov][n_imagen].h = alto;
}

void DibujoPersonaje::elegir_frame(double des_x,double des_y) {
	double angulo = (std::atan2(des_y,des_x)/M_PI)*180.0;
	//cambie a uso en coordenadas cartesianas
	if ((angulo < 35) && (angulo > -35) && ((des_x != 0) || (des_y != 0))) {
		movimiento_actual = DIAGONAL_DERECHA_ABAJO;
		//movimiento_actual=DERECHA;
		//printf("DERECHA\n");
		//DERECHA
	} else if ((des_x < -145) || (angulo > 145)) {
		movimiento_actual = DIAGONAL_IZQUIERDA_ARRIBA;
		//movimiento_actual=IZQUIERDA;
		//printf("IZQUIERDA\n");
		//IZQUIERDA
	} else if ((angulo < -55) && (angulo > -125)) {

		movimiento_actual = DIAGONAL_DERECHA_ARRIBA;
		//movimiento_actual=ARRIBA;
		//printf("ARRIBA\n");
		//ARRIBA
	} else if ((angulo > 55) && (angulo < 125)) {
		movimiento_actual = DIAGONAL_IZQUIERDA_ABAJO;
		//movimiento_actual=ABAJO;
		//printf("ABAJO\n");
		//ABAJO
	} else if ((angulo >= -55) && (angulo <= -35)) {
		movimiento_actual = DERECHA;
		//movimiento_actual=DIAGONAL_DERECHA_ARRIBA;
		//printf("ARRIBA_DERECHA\n");
		//ARRIBA_DERECHA
	} else if ((angulo <= 55) && (angulo >= 35)) {
		movimiento_actual = ABAJO;
		//movimiento_actual=DIAGONAL_DERECHA_ABAJO;
		//printf("ABAJO_DERECHA\n");
		//ABAJO_DERECHA
	} else if ((angulo >= -145) && (angulo <= -125)) {
		movimiento_actual = ARRIBA;
		//movimiento_actual=DIAGONAL_IZQUIERDA_ARRIBA;
		//printf("ARRIBA_IZQUIERDA\n");
		//ARRIBA_IZQUIERDA
	} else if ((angulo <= 145) && (angulo >= 125)) {
		movimiento_actual = IZQUIERDA;
		//movimiento_actual=DIAGONAL_IZQUIERDA_ABAJO;
		//printf("ABAJO_IZQUIERDA\n");
		//ABAJO_IZQUIERDA
	}

	this->cambiar_frame();

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
	int n_mov=movimiento_actual%cant_mov;
	int n_imagen=this->imagen_actual%this->cantidad_de_imagenes[n_mov];
	this->textura->render(this->x_imagen - this->get_ancho(n_mov,n_imagen)/2, this->y_imagen-2*(this->get_alto(n_mov,n_imagen))/3, &(this->spriteClips[n_mov][n_imagen]),renderer);
}

void DibujoPersonaje::cambiar_frame(){
	acumulador++;
	if((fps)<=acumulador){
		imagen_actual++;
		acumulador=0;
	}
}

DibujoPersonaje::~DibujoPersonaje() {
	// TODO Auto-generated destructor stub
	for (int var = 0; var < CANTIDAD_DE_MOVIMIENTOS; ++var) {
		if(this->spriteClips[var]){
			delete this->spriteClips[var];
		}
	}
}

