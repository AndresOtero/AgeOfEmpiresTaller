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
	int idServer;
	int idCliente;
public:
	shared_ptr<Mapa> mapa;
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void set_id(int i);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	dibujo_t dibujar(int dim,int x,int y);
	int oscuridad(int dim,int x,int y);
	string seleccionar(double x,double y);
	vector<Personaje*> devolverTodosLosPersonajes();
	Personaje* devolverPersonajeSeleccionado();
	void cambiar_destino_personaje(double mov_x,double mov_y);
	void  cambiar_destino_personaje(int id ,double mov_x,double mov_y);
	Personaje* devolverPersonaje(int x,int y);
	int get_ancho_mapa();
	int get_alto_mapa();

	//server
	void actualizarRecursosServer(int id ,int oro,int madera,int piedra);
	void congelarPersonaje(int id);
	void descongelarPersonaje(int id);
	void actualizarMapa();
	int generarRecursoRandom(Posicion pos);
	bool estaSeleccionada(int x,int y);
	//cliente
	void ubicarPersonaje(int idPersonaje,Posicion pos);
	void actualizarRecursos(int oro,int madera,int piedra);
	void agregarEntidad(string nombre,int x, int y);

	~Modelo();
	void agregarPersonajeCliente(Personaje* personaje);
	void crearPersonajeCliente(Personaje* personaje);
	void setearPersonajeCliente(int id,Posicion pos);
	int crearPersonajeServer(Personaje* personaje);
	void eliminarEntidadPorID(int id);
	int getIdCliente();
	int cantidad_de_jugadores();

private:
	void setIdCliente(int idCliente) ;

	void eliminarEntidad(Entidad *entidad);

	void set_posicionRandomPersonaje(Personaje* personaje);
	void recolectar(Personaje*personaje);
	Posicion mover_personaje(Personaje* personaje);
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
