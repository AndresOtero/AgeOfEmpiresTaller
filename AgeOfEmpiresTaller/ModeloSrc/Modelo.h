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
#include "../VistaSrc/DatosSeleccionado.h"
#include <sys/time.h>
#define PISADA 1
#define VISIBLE 0
#define OSCURO 2
#define EDIFICIO_SUPERPUESTO -1
#define SELECCION_MAXIMA 5
using namespace std;

#ifndef MODELO_H_
#define MODELO_H_

typedef struct{
	string nombre;
	int cantidad;
}recurso_t;

typedef int Id;

class Modelo {
	vector<Personaje*> personajes_seleccionados;
	Entidad* entidad_seleccionada;
	Jugador* jugador;
	FactoryPersonaje factory_personaje;
	vector<Jugador*> jugadores; //asi puedo ver todos los jugadores
	vector<Personaje*> personajes;
	vector<vector<int>> pisadas;
	int idServer;
public:
	shared_ptr<Mapa> mapa;
	Modelo(Juego* juego);
	Juego* juego;
	void setMapa(int largo,int ancho);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<vector<dibujo_t>>> tiles);
	dibujo_t dibujar(int dim,int x,int y);
	int crearBandera(Entidad* bandera, Id id_edificio);
	int crearPersonajeServerEdificio(Personaje* personaje,Id id_edificio);
	string nombreJugador();
	void cambiar_personaje(Id id_personaje, string nombre,string raza);
	bool afueraDelMapa(int x,int y);
	int oscuridad(int dim,int x,int y);
	DatosSeleccionado seleccionar(double x,double y);
	vector<Personaje*> devolverTodosLosPersonajes();
	vector<Personaje*> devolverPersonajeSeleccionado();
	void  cambiar_destino_personaje(Id id ,double mov_x,double mov_y);
	Personaje* devolverPersonaje(int x,int y);
	int get_ancho_mapa();
	int get_alto_mapa();
	Jugador * getJugador(){return this->jugador;};
	void insertarEntidad(Entidad * entidad);
	Entidad * buscarEntidad(int id_entidad);
	//server
	void actualizarRecursosServer(int id ,int oro,int madera,int piedra,int comida);
	void congelarPersonaje(string id);
	void descongelarPersonaje(string id);
	void actualizarMapa();
	recurso_t generarRecursoRandom(Posicion pos);
	bool estaSeleccionada(int x,int y);
	vector<Entidad*> obtenerEntidadesDeInicializacion();
	//cliente
	void actualizarRecursos(string jugador, int id_pers, int cant,int id_rec);
	int agregarEntidad(string nombre,int x, int y,int cantidad);
	bool tocaSombra(Entidad * entidad);
	Entidad* get_entidad_seleccionada();
	~Modelo();
	void agregarPersonajeCliente(Personaje* personaje);
	int crearPersonajeServer(Personaje* personaje);
	vector<msg_t> eliminarEntidadPorID(int id);
	int cantidad_de_jugadores();
	void recolectar(Personaje*personaje, Recurso* recurso);
	void atacarServer(Id idAtacante ,Id idAtacado);
	Personaje*  get_Personaje_Por_Id(Id id);
	vector<msg_t> eliminar_personaje_por_Id(Id id);
	vector<msg_t> eliminarEntidad(Entidad *entidad);
	vector<msg_t> eliminar(int id);
	vector<msg_t> terminarConstruccion(int id);
	void finalizarAccion(int id);
	int crearEdificio(string nombre, int x,int y);
	void limpiarSeleccion();
	Entidad* set_CentroCivicoNuevoServer(string raza);
	bool puedoCrearSiEsPuerto(Entidad* entidad);
private:
	size_t acumuladorPiso;
	vector<Entidad *> obtenerCentrosCivicosEnMapa();
	vector<msg_t> eliminar_personaje(Personaje* eliminado);

	void set_posicionRandomPersonaje(Personaje* personaje);

	Posicion mover_personaje(Personaje* personaje);
	Posicion calcular_camino(Posicion adonde_estoy ,Posicion adonde_voy,bool es_bote);
	void insertarEntidades();
	bool celdaOcupada(Posicion);
	double heuristica(Posicion adonde_voy,Posicion adonde_estoy);
	double distancia(Posicion a,Posicion b);
	void agregarPosicionPisada(int x, int y);
	bool pisado(int x,int y);
	int totalRecursos;
	struct timeval estado;
};

#endif /* MODELO_H_ */
