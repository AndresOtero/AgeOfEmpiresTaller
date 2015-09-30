/*
 * Madera.h

 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */
#include "Recurso.h"
#include "RecursosJugador.h"
#ifndef MADERA_H_
#define MADERA_H_

class Madera: public Recurso{
public:
	Madera(ObjetoMapa* objetomapa):Recurso(objetomapa) {};
	Madera(ObjetoMapa* objetomapa,int x, int y):Recurso(objetomapa, x, y){};
	void recolectar(RecursosJugador* recusos);
	virtual ~Madera();
};

#endif /* MADERA_H_ */
