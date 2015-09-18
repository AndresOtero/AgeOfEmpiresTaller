/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/LTexture.h"
#include <memory>
using namespace std;

#ifndef DIBUJO_H_
#define DIBUJO_H_



class Dibujo {

public:
	Dibujo();
	void set_imagen( int x, int y, int ancho, int alto);
	bool cargar_archivo(std::string path, SDL_Renderer* renderer);
	void render( SDL_Renderer* gRenderer);
	int get_x();
	int get_y();
	void set_posicion_default(int x,int y);
	int get_alto();
	int get_ancho();

	virtual ~Dibujo();
private:
	SDL_Rect spriteClips;
protected:
	void cambiar_frame();
	shared_ptr <LTexture> textura;
	size_t cantidad_de_imagenes;
	size_t imagen_actual;
	int x_imagen;
	int y_imagen;
	int fps;
	int acumulador;
};

#endif /* DIBUJO_H_ */
