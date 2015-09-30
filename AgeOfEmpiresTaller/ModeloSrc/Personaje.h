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
	double referencia_mapa_x,referencia_mapa_y;
	dibujo_t dibujo;
	double velocidad;

public:
	Personaje();
	Personaje(ObjetoMapa* objetoMapa);
	Personaje(ObjetoMapa* objetoMapa, int x, int y);

	ObjetoMapa* objetoMapa;
	dibujo_t dibujar();
	virtual ~Personaje();
	void mover(double x,double y);

	void setVelocidad(double velocidad) {
		this->velocidad = velocidad;
	}

	void setDibujo(dibujo_t dibujo) {
		this->dibujo = dibujo;
	}

	double getReferenciaMapaX() const {
		return referencia_mapa_x;
	}

	double getReferenciaMapaY() const {
		return referencia_mapa_y;
	}
private:
	Posicion calcular_camino(double x,double y);
};

#endif /* PERSONAJE_H_ */
