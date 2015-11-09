/*
 * Piedra.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Recurso.h"
#include "RecursosJugador.h"
#ifndef PIEDRA_H_
#define PIEDRA_H_

class Piedra: public Recurso {
public:
	Piedra(ObjetoMapa* objetomapa):Recurso(objetomapa) {};
	Piedra(ObjetoMapa* objetomapa, int x, int y) :
			Recurso(objetomapa, x, y) {
	};
	void recolectar(RecursosJugador* recusos, int cantidad);
	virtual ~Piedra();
};

#endif /* PIEDRA_H_ */
