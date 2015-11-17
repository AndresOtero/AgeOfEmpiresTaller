/*
 * dibujoPiso.h
 *
 *  Created on: 16/11/2015
 *      Author: ger
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/Textura.h"
#include "Dibujo.h"
#include <memory>
#ifndef DIBUJOPISO_H_
#define DIBUJOPISO_H_

namespace std {

class dibujoPiso: public Dibujo {
public:
	dibujoPiso();
	void set_imagen( int x, int y);
	void render(SDL_Renderer* gRenderer);
	int get_x();
	int get_y();
	void set_posicion_default(int x, int y);
	int get_alto();
	int get_ancho();
	void iluminar();
	void oscurecer();
	void resetear();
	void reiniciar();
	void ponerRojo();
	void ponerVerde();
	void ponerAmarillo();
	virtual ~dibujoPiso();
protected:
	SDL_Rect spriteClips;
	shared_ptr <Textura> textura;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
	int acumulador;
};

} /* namespace std */

#endif /* DIBUJOPISO_H_ */
