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

	float referencia_mapa_x,referencia_mapa_y;
	dibujo_t dibujo;
	float velocidad;

public:
	Personaje();
	Personaje(ObjetoMapa* objetoMapa);
	Personaje(ObjetoMapa* objetoMapa, int x, int y);

	ObjetoMapa* objetoMapa;
	dibujo_t dibujar();
	virtual ~Personaje();
	void mover(int x,int y);

	void setVelocidad(float velocidad) {
		this->velocidad = velocidad;
	}

	void setDibujo(dibujo_t dibujo) {
		this->dibujo = dibujo;
	}

	float getReferenciaMapaX() const {
		return referencia_mapa_x;
	}

	float getReferenciaMapaY() const {
		return referencia_mapa_y;
	}
};

#endif /* PERSONAJE_H_ */
