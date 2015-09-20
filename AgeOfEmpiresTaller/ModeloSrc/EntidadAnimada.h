/*
 * EntidadAnimada.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef ENTIDADANIMADA_H_
#define ENTIDADANIMADA_H_
#include "ObjetoMapa.h"
#include "Posicion.h"

class EntidadAnimada {

public:
	EntidadAnimada();
	EntidadAnimada(ObjetoMapa* objetoMapaAnimado);
	EntidadAnimada(ObjetoMapa* objetoMapaAnimado, int x, int y);
	ObjetoMapa* objetoMapaAnimado;
	Posicion* posicion;
	virtual ~EntidadAnimada();
};

#endif /* ENTIDADANIMADA_H_ */
