/*
 * Modelo.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Mapa.h"
#include "../ModeloSrc/Celda.h"
#include <iostream>
#include <memory>
#include <vector>
#include "../ModeloSrc/Juego.h"
using namespace std;

#ifndef MODELO_H_
#define MODELO_H_

class Modelo {
	shared_ptr<Mapa> mapa;

public:
	Modelo();
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> dibujos);
	vector<vector<dibujo_t>> dibujar(int x,int y,int ancho,int alto);
	void eliminarDibujar(int ancho, int alto,dibujo_t** matriz);
	int get_alto_mapa();
	int get_ancho_mapa();
	~Modelo();
};

#endif /* MODELO_H_ */
