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
	string imagen_quieto;
	string imagen_atacando;
	string icono;
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
	int oro;
	int piedra;
	int madera;
	int comida;
	string raza;
	int velocidad_construcccion;
	string edificio_constructor;
	ObjetoMapa(string nombre, string imagen);

	virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
