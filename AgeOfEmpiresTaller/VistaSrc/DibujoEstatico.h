/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/Textura.h"
#include "Dibujo.h"
#include <memory>
using namespace std;

#ifndef DIBUJOESTATICO_H_
#define DIBUJOESTATICO_H_



class Dibujo_Estatico : public Dibujo{

public:
	Dibujo_Estatico();
	void set_imagen( int x, int y);
	bool cargar_archivo(std::string path, SDL_Renderer* renderer);
	void render( SDL_Renderer* gRenderer);
	int get_x();
	int get_y();
	void set_posicion_default(int x,int y);
	int get_alto();
	int get_ancho();
	void iluminar();
	void resetear();
	virtual ~Dibujo_Estatico();
protected:
	SDL_Rect spriteClips;
	shared_ptr <Textura> textura;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
	int fps;
	int acumulador;
};

#endif /* DIBUJOESTATICO_H_ */
