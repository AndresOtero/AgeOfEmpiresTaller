/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/Textura.h"
#include <memory>
using namespace std;

#ifndef DIBUJO_H_
#define DIBUJO_H_

class Dibujo {

public:
	Dibujo();
	virtual bool cargar_archivo(std::string path, SDL_Renderer* renderer);
	virtual void render( SDL_Renderer* gRenderer){};
	virtual int get_x();
	virtual int get_y();
	virtual void set_posicion_default(int x,int y);
	virtual int get_alto();
	virtual int get_ancho();
	int getHeight() ;
	int getWidth() ;
	virtual void iluminar();
	virtual void resetear();
	virtual ~Dibujo();
protected:
	SDL_Rect spriteClips;
	shared_ptr <Textura> textura;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
};

#endif /* DIBUJO_H_ */
