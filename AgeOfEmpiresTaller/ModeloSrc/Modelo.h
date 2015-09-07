/*
 * Modelo.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Mapa.h"
#include <iostream>

#ifndef MODELO_H_
#define MODELO_H_

class Modelo {
	Mapa* mapa=NULL;

public:
	Modelo();
	void setMapa(int largo,int ancho);
	void setDibujoMapa(dibujo_t** dibujos);
	dibujo_t** dibujar(int x,int y,int ancho,int alto);
	void eliminarDibujar(int ancho, int alto,dibujo_t** matriz);
	~Modelo();
};

#endif /* MODELO_H_ */
