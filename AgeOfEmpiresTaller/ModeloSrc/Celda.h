/*
 * Celda.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Dibujo.h"
#include <iostream>

#ifndef CELDA_H_
#define CELDA_H_

class Celda {
private:
	bool ocupada=false;
	Dibujo* dibujo=NULL;
public:
	Celda();
	bool estaOcupada();
	void setDibujo(Dibujo* dibujo);
	dibujo_t dibujar();
	virtual ~Celda();
};

#endif /* CELDA_H_ */
