/*
 * DibujoPersonaje.h
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#ifndef DIBUJOPERSONAJE_H_
#define DIBUJOPERSONAJE_H_

#include "DibujoAnimado.h"

class DibujoPersonaje: public DibujoAnimado {
	int velocidad;
public:

	void set_velocidad(int velocidad);
	DibujoPersonaje();
	void mover(int x, int y) ;
	virtual ~DibujoPersonaje();
};

#endif /* DIBUJOPERSONAJE_H_ */
