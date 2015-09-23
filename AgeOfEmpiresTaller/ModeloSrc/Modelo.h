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
	vector<shared_ptr<Personaje>> lista_personajes;
public:
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	//vector<vector<vector<dibujo_t>>> dibujar(int x,int 	y,int ancho,int largo);
	dibujo_t dibujar(int dim,int x,int y);
	void agregarPersonaje(float x,float y,dibujo_t dibujo);
	shared_ptr<Personaje> devolverPersonaje();
	void mover_personaje(float mov_x,float mov_y);
	int get_ancho_mapa();
	int get_alto_mapa();
	~Modelo();
};

#endif /* MODELO_H_ */
