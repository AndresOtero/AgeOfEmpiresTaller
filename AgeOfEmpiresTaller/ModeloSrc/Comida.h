/*
 * Comida.h
 *
 *  Created on: 17/11/2015
 *      Author: ger
 */

#ifndef COMIDA_H_
#define COMIDA_H_

#include "Recurso.h"
#include "RecursosJugador.h"
#include "Entidad.h"

namespace std {

class Comida : public Recurso{
public:
	Comida(ObjetoMapa* objetomapa):Recurso(objetomapa) {};
	Comida(ObjetoMapa* objetomapa,int x, int y):Recurso(objetomapa, x, y){};
	void recolectar(RecursosJugador* recusos,int cantidad);
	virtual ~Comida();
};

} /* namespace std */

#endif /* COMIDA_H_ */
