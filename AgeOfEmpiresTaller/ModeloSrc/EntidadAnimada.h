/*
 * EntidadAnimada.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef ENTIDADANIMADA_H_
#define ENTIDADANIMADA_H_
#include "ObjetoMapaAnimado.h"
#include "Posicion.h"

class EntidadAnimada {

public:
	EntidadAnimada(ObjetoMapaAnimado* objetoMapaAnimado);
	EntidadAnimada(ObjetoMapaAnimado* objetoMapaAnimado, int x, int y);
	ObjetoMapaAnimado* objetoMapaAnimado;
	Posicion* posicion;
	virtual ~EntidadAnimada();
};

#endif /* ENTIDADANIMADA_H_ */
