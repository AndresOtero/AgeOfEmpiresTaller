/*
 * Celda.h
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */
#include <iostream>
#include "Entidad.h"
#include "Personaje.h"
#include "../VistaSrc/DatosSeleccionado.h"
typedef int dibujo_t;
#define DEFAULT 0
#define AFUERA -1
#ifndef CELDA_H_
#define CELDA_H_

class Celda {
private:
	bool ocupada;
	bool agua;
	dibujo_t tiles;
	dibujo_t tiles_elfo;
	dibujo_t tiles_hobbit;
	dibujo_t tiles_humanos;
	dibujo_t tiles_mordor;
	dibujo_t tiles_water;

	dibujo_t tileActual;

	dibujo_t escenario;
	Entidad* entidad;
	Personaje* personaje;
public:
	Personaje* devolver_personaje();
	Entidad * devolver_entidad();
	Celda();
	bool estaOcupada();
	void setEscenario(dibujo_t dibujo);
	void setTiles(dibujo_t dibujo);
	void setTilesElfo(dibujo_t dibujo);
	void setTilesHobbit(dibujo_t dibujo);
	void setTilesHumanos(dibujo_t dibujo);
	void setTilesMordor(dibujo_t dibujo);
	void setTilesWater(dibujo_t dibujo);

	void mostrarTileNormal();
	void mostrarTileElfo();
	void mostrarTileHobbit();
	void mostrarTileHumanos();
	void mostrarTileMordor();
	void mostrarTileWater();

	void setAgua(){this->agua = true;};
	void actualizar();
	void ocuparCeldaPersonaje(Personaje* personaje);
	bool tieneRecurso();
	bool esAgua(){return agua;};
	dibujo_t dibujarEscenario();
	dibujo_t dibujarTiles();
	DatosSeleccionado mostrar_contenido();
	DatosSeleccionado mostrar_entidad();
	void ocuparCelda(Entidad*entidad);
	void liberarCelda();
	void seleccionarEntidad();
	void deseleccionarEntidad();
	bool estaSeleccionada();
	virtual ~Celda();
};

#endif /* CELDA_H_ */
