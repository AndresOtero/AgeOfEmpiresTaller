/*
 * Configuracion.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

class Configuracion {
	int vel_personaje;
	int margen_scroll;
public:
	Configuracion();
	Configuracion(int vel_personaje, int margen_scroll);

	virtual ~Configuracion();

	int get_margen_scroll() const {
		return margen_scroll;
	}

	int get_vel_personaje() const {
		return vel_personaje;
	}
};

#endif /* CONFIGURACION_H_ */
