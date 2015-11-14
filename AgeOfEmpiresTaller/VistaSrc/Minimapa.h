/*
 * Minimapa.h
 *
 *  Created on: Oct 7, 2015
 *      Author: tobias
 */

#ifndef MINIMAPA_H_
#define MINIMAPA_H_
#define AZUL 1
#define ROJO 2
#define VERDE 3
#define NEGRO 4
#define BLANCO 5
#define VERDE_OSCURO 6
#define AMARILLO 7
#define AMARILLO_OSCURO 8
#define ROJO_OSCURO 9
#define AZUL_OSCURO 10
#include "Dibujo.h"
#include "../ModeloSrc/Modelo.h"
#include <math.h>
#include "Textura.h"
#include "CambioDeCoordendas.h"

class Minimapa: public Dibujo {
public:
	Minimapa(Modelo* modelo);
	virtual ~Minimapa();
	void render( SDL_Renderer* gRenderer);
	bool inicializar(SDL_Renderer * render);
	int altoMapa();
	int anchoPantalla();
	SDL_Color paleta(int color);
	int altoPorCelda();
	int anchoPorCelda();
private:
	bool invertir;
	int x;
	int y;
	int diagonal;
	int lado;
	int ancho_por_celda;
	int alto_por_celda;
	Modelo * modelo;
	SDL_Color fondo;
	void dibujarElemento(int x,int y,SDL_Renderer * renderer,int * count);
	int sombra(int color);
	void cambiar_coordenadas(int x, int y, int&pant_x, int &pant_y);
	void dibujarPuntoMapa(int pant_x,int pant_y, SDL_Color color,SDL_Renderer*renderer);
};

#endif /* MINIMAPA_H_ */
