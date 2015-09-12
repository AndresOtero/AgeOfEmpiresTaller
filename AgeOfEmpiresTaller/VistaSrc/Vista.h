/*
 * Vista.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include <SDL2/SDL_video.h>

class Dibujo;
class Modelo;
struct SDL_Renderer;

#ifndef VISTA_H_
#define VISTA_H_

class Vista {
	//The window we'll be rendering to
	SDL_Window* gWindow;
	//The window renderer
	SDL_Renderer* gRenderer;
	Dibujo* personaje;
	Dibujo* pasto;
	Modelo* modelo;

	void dibujar_mapa();

public:
	Vista(Modelo* modelo);
	bool init();
	int ancho_por_celda();
	int altura_por_celda();
	void transformar_cartesiana_isometrica(int cart_x,int cart_y,int& iso_x,int& iso_y);
	void transformar_isometrica_cartesiana(int iso_x,int iso_y,int& cart_x,int& cart_y);
	bool loadMedia();
	void detectar_mouse_borde();
	int run();
	virtual ~Vista();
};

#endif /* VISTA_H_ */
