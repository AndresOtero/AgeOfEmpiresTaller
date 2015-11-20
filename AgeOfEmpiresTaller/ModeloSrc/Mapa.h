/*
 * Mapa.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Celda.h"
#include <memory>
#include <vector>
#include "Posicion.h"
#include "GeneradorNumeros.h"
#include "../VistaSrc/DatosSeleccionado.h"

using namespace std;
#ifndef MAPA_H_
#define MAPA_H_

class Mapa {
	int largo,ancho;
	Celda*** celdas;

public:
	Mapa(int ancho, int largo);
	int getAncho();
	int getLargo();
	void seleccionar(int x,int y);
	bool estaSeleccionada(int x,int y);
	void deseleccionar();
	dibujo_t dibujarTiles(int x, int y);
	dibujo_t dibujarEscenario(int x, int y);
	void setTiles(dibujo_t dibujo,dibujo_t dibujoElfo,dibujo_t dibujoHobbit,dibujo_t dibujoHumanos,dibujo_t dibujoMordor,dibujo_t dibujoWater, int x, int y);
	void setEscenario(dibujo_t dibujo,int x,int y);
	DatosSeleccionado mostrar_contenido(int x,int y);
	DatosSeleccionado mostrar_entidad(int x, int y);
	virtual ~Mapa();
	Personaje* personaje_celda(int x, int y);
	bool hay_personaje(int x, int y);
	Posicion posicionVacia();
	Entidad * entidad_celda(int x, int y);
	bool hayRecursosEn(Posicion posicion);
	bool afueraDelMapa(int x,int y);
	bool celdaOcupada(int x,int y);
	vector<Posicion> adyacenciasNoOcupadas(Posicion posicion);
	Posicion encontrarAdyacenteMasCercano(Posicion posicion);
	void posicionarEntidad(Entidad* entidad);
	void sacarEntidad(Entidad * entidad);
	void actualizar(vector<Personaje*> personajes);
	Posicion validar_destino(Posicion adonde_voy,Posicion adonde_estoy);
	vector<Posicion> adyacencias(Posicion posicion);
	bool puedeUbicar(Entidad * entidad);
	bool estaDentroDeSector(Posicion sector,Posicion entidad);
	Posicion posicionValidaEnSector(Posicion sector,Entidad * entidad, int ancho_sector, int alto_sector, int separacion_ancho, int separacion_alto);
	Posicion posicionValidaParaCentroCivico(vector<Entidad*> centros, Entidad * base);
	void posicionarPersonaje(Personaje * pers);
	Celda* getCelda(int x,int y);
	bool celdaAgua(int x, int y);
	void hacerPileta(int x, int y);
private:
	Posicion acercar(Posicion adonde_estoy,Posicion adonde_voy);
	bool estoyAlLadoDeEntidadDestino(Posicion adonde_voy,Posicion adonde_estoy);


};

#endif /* MAPA_H_ */
