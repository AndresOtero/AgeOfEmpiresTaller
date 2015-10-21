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
#include <sys/time.h>
using namespace std;

#ifndef MODELO_H_
#define MODELO_H_

class Modelo {
	Personaje* personaje_seleccionado;
	vector<Personaje*> personajes;
	vector<vector<int>> pisadas;
public:
	shared_ptr<Mapa> mapa;
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	dibujo_t dibujar(int dim,int x,int y);
	int oscuridad(int dim,int x,int y);
	void agregarPersonaje(Personaje*);
	string seleccionar(double x,double y);
	vector<Personaje*> devolverTodosLosPersonajes();
	Personaje* devolverPersonajeSeleccionado();
	void actualizarMapa();
	void cambiar_destino_personaje(double mov_x,double mov_y);
	void generarRecursoRandom();
	Posicion mover_personaje(Personaje* personaje);
	Personaje* devolverPersonaje(int x,int y);
	void eliminarEntidad(Entidad *entidad);
	int get_ancho_mapa();
	int get_alto_mapa();
	~Modelo();
private:
	Posicion calcular_camino(Posicion adonde_estoy ,Posicion adonde_voy);
	void insertarEntidades();
	bool celdaOcupada(Posicion);
	double heuristica(Posicion adonde_voy,Posicion adonde_estoy);
	double distancia(Posicion a,Posicion b);
	void agregarPosicion(Posicion pos);
	bool pisado(int x,int y);
	int totalRecursos;
	struct timeval estado;
};

#endif /* MODELO_H_ */
