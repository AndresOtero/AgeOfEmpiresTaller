/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/Vista.h"
#include "../VistaSrc/LTexture.h"


#ifndef DIBUJO_H_
#define DIBUJO_H_
enum dibujo_t {DEFAULT,AFUERA};


class Dibujo {
	dibujo_t tipo_de_dibujo;
	LTexture* textura ;
	SDL_Rect* spriteClips;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
	int velocidad=0;
public:
	Dibujo(dibujo_t tipo_de_dibujo);
	void set_cantidad_de_imagenes(size_t cant_de_imagenes);
	void set_imagen(size_t n_imagen,int x,int y, int ancho,int alto);
	bool cargar_archivo( std::string path ,SDL_Renderer* renderer );
	void render( int x, int y ,SDL_Renderer* gRenderer );
	void mover(int x,int y);
	void set_velocidad(int velocidad);
	dibujo_t dibujar();
	virtual ~Dibujo();
};

#endif /* DIBUJO_H_ */
