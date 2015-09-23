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
#include "Personaje.h"
using namespace std;

#ifndef MODELO_H_
#define MODELO_H_

class Modelo {
	shared_ptr<Mapa> mapa;
public:
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	//vector<vector<vector<dibujo_t>>> dibujar(int x,int 	y,int ancho,int largo);
	dibujo_t dibujar(int dim,int x,int y);
	shared_ptr<Personaje> devolverPersonaje();

	int get_ancho_mapa();
	int get_alto_mapa();
	~Modelo();
};

#endif /* MODELO_H_ */
