/*
 * EdificioDeCreacion.h
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#ifndef EDIFICIODECREACION_H_
#define EDIFICIODECREACION_H_
#include <memory>
#include "Entidad.h"
#include "Personaje.h"
#include "ObjetoMapa.h"
#include "StatusPersonaje.h"
#include <map>
#include "Modelo.h"


class EdificioDeCreacion: public Entidad {
protected:
	Modelo * modelo;//para poder obtener los objetos mapa existentes
	std::map<std::string,StatusPersonaje> tipos_status; //los distintos tipo de personajes
public:
	EdificioDeCreacion(ObjetoMapa * objeto,Modelo * modelo): Entidad(objeto){
		this->modelo = modelo;
	};

	EdificioDeCreacion(ObjetoMapa* objeto, int x, int y,Modelo * modelo): Entidad(objeto,x,y){
		this->modelo = modelo;
	};

	virtual ~EdificioDeCreacion();
	vector<string> obtenerListaCreables();
	virtual Personaje * crearPersonaje(string nombre){};
};

#endif /* EDIFICIODECREACION_H_ */
