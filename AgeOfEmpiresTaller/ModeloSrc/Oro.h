/*
 * Oro.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */
#include "Recurso.h"
#include "RecursosJugador.h"

#ifndef ORO_H_
#define ORO_H_

class Oro : public Recurso{
public:
	Oro(ObjetoMapa* objetomapa):Recurso(objetomapa) {};
	Oro(ObjetoMapa* objetomapa,int x, int y):Recurso(objetomapa, x, y){};
	void recolectar(RecursosJugador* recusos,int cantidad);
	virtual ~Oro();
};

#endif /* ORO_H_ */
