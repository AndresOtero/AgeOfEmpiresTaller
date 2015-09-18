/*
 * Pantalla.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

class Pantalla {
public:
	Pantalla();
	Pantalla(int ancho, int alto);
	int ancho;
	int alto;
	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
