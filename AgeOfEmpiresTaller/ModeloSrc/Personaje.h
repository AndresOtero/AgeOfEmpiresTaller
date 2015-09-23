/*
 * Personaje.h
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */
#include "../VistaSrc/Dibujo.h"
#include "ObjetoMapa.h"
#include "Posicion.h"
#ifndef PERSONAJE_H_
#define PERSONAJE_H_
typedef int dibujo_t;

class Personaje {

public:
	Posicion* posicion;
	Personaje();
	Personaje(ObjetoMapa* objetoMapa);
	Personaje(ObjetoMapa* objetoMapa, int x, int y);

	dibujo_t dibujo;
	ObjetoMapa* objetoMapa;
	dibujo_t dibujar();
	virtual ~Personaje();
	void mover(int x,int y);
};

#endif /* PERSONAJE_H_ */
