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
	dibujo_t dibujarTiles(int x, int y);
	dibujo_t dibujarEscenario(int x, int y);
	void setTiles(dibujo_t dibujo,int x,int y);
	void setEscenario(dibujo_t dibujo,int x,int y);
	string mostrar_contenido(int x,int y);
	virtual ~Mapa();
	Personaje* personaje_celda(int x, int y);
	Entidad * entidad_celda(int x, int y);
	bool hayRecursosEn(Posicion posicion);
	bool afueraDelMapa(int x,int y);
	bool celdaOcupada(int x,int y);
	vector<Posicion> adyacenciasNoOcupadas(Posicion posicion);
	void posicionarEntidad(Entidad* entidad);
	void sacarEntidad(Entidad * entidad);
	void actualizar(vector<Personaje*> personajes);
	Posicion validar_destino(Posicion adonde_voy,Posicion adonde_estoy);
private:
	Celda* getCelda(int x,int y);

};

#endif /* MAPA_H_ */
