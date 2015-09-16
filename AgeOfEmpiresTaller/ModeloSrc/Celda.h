/*
 * Celda.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include <iostream>
typedef int dibujo_t;
#define DEFAULT 0
#define AFUERA -1
#ifndef CELDA_H_
#define CELDA_H_

class Celda {
private:
	bool ocupada;
	dibujo_t dibujo;
public:
	Celda();
	bool estaOcupada();
	void setDibujo(dibujo_t dibujo);
	dibujo_t dibujar();
	virtual ~Celda();
};

#endif /* CELDA_H_ */
