/*
 * Pantalla.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

class Pantalla {
	int ancho;
	int alto;
public:
	Pantalla();
	Pantalla(int ancho, int alto);

	virtual ~Pantalla();

	int getAlto() const {
		return alto;
	}

	int getAncho() const {
		return ancho;
	}
};

#endif /* PANTALLA_H_ */
