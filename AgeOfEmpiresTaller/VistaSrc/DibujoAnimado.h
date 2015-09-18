/*
 * DibujoAnimado.h
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#ifndef DIBUJOANIMADO_H_
#define DIBUJOANIMADO_H_

#include "Dibujo.h"

class DibujoAnimado: public Dibujo {
	SDL_Rect* spriteClips;
public:
	DibujoAnimado();
	virtual ~DibujoAnimado();
	void set_cantidad_de_imagenes(size_t cant_de_imagenes);
	void set_imagen(size_t n_imagen, int x, int y, int ancho, int alto);
	void render( SDL_Renderer* gRenderer);
	void set_fps(int fps);
	int get_ancho(int n_imagen);
	int get_alto(int n_imagen);
	int get_ancho();
	int get_alto();
protected:
	void cambiar_frame();

};

#endif /* DIBUJOANIMADO_H_ */
