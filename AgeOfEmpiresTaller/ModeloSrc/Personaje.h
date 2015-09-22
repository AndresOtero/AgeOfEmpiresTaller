/*
 * Personaje.h
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */
#include "../VistaSrc/Dibujo.h"
#ifndef PERSONAJE_H_
#define PERSONAJE_H_
typedef int dibujo_t;

class Personaje {
	float referencia_mapa_x,referencia_mapa_y;
	dibujo_t dibujo;
public:
	Personaje(float referencia_mapa_x,float referencia_mapa_y,	dibujo_t dibujo);
	dibujo_t dibujar();
	virtual ~Personaje();
	void mover(int x,int y);
	float getReferenciaMapaX() const {
		return referencia_mapa_x;
	}

	float getReferenciaMapaY() const {
		return referencia_mapa_y;
	}
};

#endif /* PERSONAJE_H_ */
