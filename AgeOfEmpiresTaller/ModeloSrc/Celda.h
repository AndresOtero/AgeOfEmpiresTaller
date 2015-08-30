/*
 * Celda.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#ifndef CELDA_H_
#define CELDA_H_

class Celda {
	bool ocupada=false;
public:
	Celda();
	bool estaOcupada();
	virtual ~Celda();
};

#endif /* CELDA_H_ */
