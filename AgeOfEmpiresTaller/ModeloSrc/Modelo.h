/*
 * Modelo.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Mapa.h"

#ifndef MODELO_H_
#define MODELO_H_

class Modelo {
	Mapa* mapa;

public:
	Modelo();
	virtual ~Modelo();
};

#endif /* MODELO_H_ */
