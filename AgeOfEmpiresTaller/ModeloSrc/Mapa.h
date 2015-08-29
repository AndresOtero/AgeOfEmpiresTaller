/*
 * Mapa.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Celda.h"

#ifndef MAPA_H_
#define MAPA_H_

class Mapa {
	int largo,ancho;
	Celda*** celdas;

public:
	Mapa(int largo, int ancho);
	virtual ~Mapa();
};

#endif /* MAPA_H_ */
