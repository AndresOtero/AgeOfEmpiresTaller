/*
 * Dibujo.h
 *
 *  Created on: 6 de set. de 2015
 *      Author: andres
 */

#ifndef DIBUJO_H_
#define DIBUJO_H_
enum dibujo_t {DEFAULT,AFUERA};

class Dibujo {
	dibujo_t tipo_de_dibujo=DEFAULT;
public:
	Dibujo(dibujo_t tipo_de_dibujo);
	dibujo_t dibujar();
	virtual ~Dibujo();
};

#endif /* DIBUJO_H_ */
