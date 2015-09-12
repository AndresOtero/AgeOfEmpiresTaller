/*
 * Vista.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */
#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Dibujo.h"
#include "LTexture.h"

#ifndef VISTA_H_
#define VISTA_H_

class Vista {
	//The window we'll be rendering to
	SDL_Window* gWindow;
	//The window renderer
	SDL_Renderer* gRenderer;
	Dibujo* personaje;
	Dibujo* pasto;

public:
	Vista();
	bool init();
	int ancho_por_celda();
	int altura_por_celda();
	void transformar_cartesiana_isometrica(int cart_x,int cart_y,int& iso_x,int& iso_y);
	void transformar_isometrica_cartesiana(int iso_x,int iso_y,int& cart_x,int& cart_y);
	bool loadMedia();
	int run();
	virtual ~Vista();
};

#endif /* VISTA_H_ */
