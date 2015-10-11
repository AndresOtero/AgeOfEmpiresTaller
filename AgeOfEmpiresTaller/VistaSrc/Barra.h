/*
 * BarraStatus.h
 *
 *  Created on: Oct 8, 2015
 *      Author: tobias
 */

#ifndef BARRA_H_
#define BARRA_H_
#include <plog/Log.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "Dibujo.h"
#include "Minimapa.h"
#include "CambioDeCoordendas.h"

class Barra: public Dibujo {
public:
	Barra(Modelo * modelo, double *x,double *y);
	void render(SDL_Renderer * renderer);
	void load(SDL_Renderer * renderer,string path, int ancho_por_celda, int alto_por_celda);
	void setDisplay(string display);
	void actualizar(Personaje * protagonista);
	virtual ~Barra();
private:
	void dimensionRectanguloDeMiniMapa(int ancho, int alto);
	void renderFondo(SDL_Renderer*renderer);
	void renderTexto(SDL_Renderer*renderer);
	bool cargarTexto(int x,int y,SDL_Renderer* renderer,SDL_Color color,shared_ptr<Textura> textura, string display);
	shared_ptr<Minimapa> mapa;
	shared_ptr<Textura> texto;
	shared_ptr<Textura> textOro;
	shared_ptr<Textura> textMadera;
	shared_ptr<Textura> textPiedra;
	shared_ptr<CambioDeCoordendas> transformador;
	TTF_Font* font;
	string display;
	int referencia_y;
	int oro;
	int madera;
	int piedra;
	int tamFont;
};

#endif /* BARRA_H_ */
