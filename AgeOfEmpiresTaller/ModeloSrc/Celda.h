/*
 * Celda.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include <iostream>
#include "../VistaSrc/Dibujo.h"

#ifndef CELDA_H_
#define CELDA_H_

class Celda {
private:
	bool ocupada;
	Dibujo* dibujo;
public:
	Celda();
	bool estaOcupada();
	void setDibujo(Dibujo* dibujo);
	dibujo_t dibujar();
	virtual ~Celda();
};

#endif /* CELDA_H_ */
