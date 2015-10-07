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
	vector<Personaje*> personajes;
public:
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	//vector<vector<vector<dibujo_t>>> dibujar(int x,int 	y,int ancho,int largo);
	dibujo_t dibujar(int dim,int x,int y);
	void agregarPersonaje(Personaje*);
	void seleccionar(double mov_x,double mov_y);
	Personaje* devolverPersonaje();
	Posicion mover_personaje(double mov_x,double mov_y);
	int get_ancho_mapa();
	int get_alto_mapa();
	~Modelo();
private:
	Posicion calcular_camino(double x,double y);
	void insertarEntidades();
	bool celdaOcupada(Posicion);
	double heuristica(Posicion adonde_voy,Posicion adonde_estoy);
	double distancia(Posicion a,Posicion b);


};

#endif /* MODELO_H_ */
