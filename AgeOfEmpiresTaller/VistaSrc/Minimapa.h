/*
 * Minimapa.h
 *
 *  Created on: Oct 7, 2015
 *      Author: tobias
 */

#ifndef MINIMAPA_H_
#define MINIMAPA_H_

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
	bool inicializar(string path,SDL_Renderer * render);

private:
	int x;
	int y;
	int diagonal;
	int lado;
	int ancho_por_celda;
	int alto_por_celda;
	Textura * girar;
	CambioDeCoordendas* transformador;
	Modelo * modelo;
	void cambiar_coordenadas(int x, int y, int&pant_x, int &pant_y);
	void dibujarPuntoMapa(int pant_x,int pant_y, SDL_Color color,SDL_Renderer*renderer);
};

#endif /* MINIMAPA_H_ */
