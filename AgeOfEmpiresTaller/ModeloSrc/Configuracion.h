/*
 * Configuracion.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

class Configuracion {
public:
	Configuracion();
	Configuracion(int vel_personaje, int margen_scroll);
	int vel_personaje;
	int margen_scroll;
	virtual ~Configuracion();
};

#endif /* CONFIGURACION_H_ */
