/*
 * DibujoAnimado.h
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#ifndef DIBUJOANIMADO_H_
#define DIBUJOANIMADO_H_

#include "Dibujo.h"
#include "vector"
#include "memory.h"
#include <sys/time.h>
using namespace std;
class DibujoAnimado: public Dibujo {
	SDL_Rect* spriteClips;
public:
	DibujoAnimado();
	virtual ~DibujoAnimado();
	void set_cantidad_de_imagenes(int cant_de_imagenes);
	void set_imagen(unsigned int n_imagen, int x, int y, int h, int w);
	void render( SDL_Renderer* gRenderer);
	void set_fps(int fps);
	void set_delay(double delay);
	int get_ancho(int n_imagen);
	int get_alto(int n_imagen);

	int get_ancho();
	int get_alto();
	void setPixeles(int x, int y);
protected:

	void cambiar_frame();
	int fps;
	int acumulador;
	struct timeval estado;
	double delay;
	int termino_animacion;
	int pixel_x;
	int pixel_y;
};

#endif /* DIBUJOANIMADO_H_ */
