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
	Mapa(int ancho, int largo);
	int getAncho();
	int getLargo();
	dibujo_t dibujar(int x, int y);
	void setDibujo(dibujo_t dibujo,int x,int y);

	virtual ~Mapa();
	bool celdaOcupada(int largo,int ancho);
private:
	Celda* getCelda(int largo,int ancho);

};

#endif /* MAPA_H_ */
