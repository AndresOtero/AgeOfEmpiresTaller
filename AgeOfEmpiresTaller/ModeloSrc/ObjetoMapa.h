/*
 * ObjetoMapa.h
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include <string>
#include <vector>
#include "BaseLogica.h"
#include "PixelsReferencia.h"

using namespace std;

class ObjetoMapa{

public:
	string nombre;
	string imagen;
	BaseLogica* baseLogica;
	PixelsReferencia* pixelsReferencia;
	int fps;
	int delay;
	int velocidad;
	int vida;
	int fuerza;
	int armadura;
	int recoleccion;
	int construccion;
	ObjetoMapa(string nombre, string imagen);

	virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
