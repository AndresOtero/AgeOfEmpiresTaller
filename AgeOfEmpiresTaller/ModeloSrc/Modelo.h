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
	int id;
	Personaje* personaje_seleccionado;
	vector<Personaje*> personajes;
	vector<vector<int>> pisadas;
public:
	shared_ptr<Mapa> mapa;
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void set_id(int i);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	dibujo_t dibujar(int dim,int x,int y);
	int oscuridad(int dim,int x,int y);
	int agregarPersonaje(Personaje*);
	string seleccionar(double x,double y);
	vector<Personaje*> devolverTodosLosPersonajes();
	Personaje* devolverPersonajeSeleccionado();
	void cambiar_destino_personaje(double mov_x,double mov_y);
	Personaje* devolverPersonaje(int x,int y);
	int get_ancho_mapa();
	int get_alto_mapa();
	//server
	void congelarPersonaje(Personaje* personaje);
	void descongelarPersonaje(Personaje* personaje);
	void actualizarMapa();
	void generarRecursoRandom();
	Posicion mover_personaje(Personaje* personaje);
	void recolectar(Personaje*personaje);
	void set_posicionRandomPersonaje(Personaje* personaje);
	void eliminarEntidad(Entidad *entidad);
	bool estaSeleccionada(int x,int y);
	//cliente
	void crearPersonaje(ObjetoMapa* objeto,Posicion pos);
	void ubicarPersonaje(Personaje* personaje,Posicion pos);
	void actualizarRecursos(int oro,int madera,int piedra);
	void agregarEntidad(string nombre,int x, int y);
	void eliminarEntidadPorID(int id);

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
