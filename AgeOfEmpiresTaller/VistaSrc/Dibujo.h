/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/LTexture.h"


#ifndef DIBUJO_H_
#define DIBUJO_H_



class Dibujo {

	LTexture* textura;
	SDL_Rect* spriteClips;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
	int velocidad;
	int acumulador;



public:
	Dibujo();
	void set_cantidad_de_imagenes(size_t cant_de_imagenes);
	void set_imagen(size_t n_imagen, int x, int y, int ancho, int alto);
	bool cargar_archivo(std::string path, SDL_Renderer* renderer);
	void render( SDL_Renderer* gRenderer);
	int get_x();
	int get_y();
	void set_posicion_default(int x,int y);
	void mover(int x, int y);
	void set_velocidad(int velocidad);
	int get_alto();
	int get_alto(int n_imagen);
	int get_ancho();
	int get_ancho(int n_imagen);
	virtual ~Dibujo();
private:
	void cambiar_frame();
};

#endif /* DIBUJO_H_ */
